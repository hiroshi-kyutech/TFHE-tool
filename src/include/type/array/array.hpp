/**
 * @file array.hpp
 * @brief TFHEの多次元配列のクラス.
 **/
#ifndef ARRAY
#define ARRAY
#include "../../common/common.hpp"
#include "../../operations/io/io.hpp"
#include "../type.hpp"

/**
 * @brief TFHEの多次元配列のクラス.
 **/
template <typename Type>
class TFHEArray : virtual protected TFHEKeySet, virtual protected TFHEIO {
 public:
  std::vector<Type> array;
  std::vector<int> shape;

  /**
   * @brief 多次元のstd::vector vecとその形を示すstd::vector<int>
   * array_shapeからTFHEArrayを作成するコンストラクタ
   * @param[in] std::vector<T, Alloc> vec(多次元ベクタ)
   * @param[in] std::vector<int> array_shape(ベクタの形)
   * @return TFHEArray
   **/
  template <typename T, typename Alloc = std::allocator<T>>
  TFHEArray(std::vector<T, Alloc> vec) {
    shape = std::vector<int>();
    mold(vec);
    int index = 1;
    int depth = 1;
    for (int i = depth; i < shape.size(); i++) {
      index *= shape[i];
    }

    array = std::vector<Type>(index * shape[0]);

    for (int i = 0; i < vec.size(); i++) {
      write(vec[i], i * index, depth);
    }
  }

  template <typename T, typename Alloc = std::allocator<T>>
  void mold(std::vector<T, Alloc> vec) {
    int size = vec.size();
    shape.emplace_back(size);
    if (size > 0) {
      mold(vec[0]);
    }
  }
  void mold(int num) {}

  void mold(std::vector<bool>::reference value) {}

  /**
   * @brief TFHEの配列をファイルから読み込むコンストラクタ.
   * @param[in] const char* path(保存先のパス)
   * @param[in] int id(識別用のID)
   **/
  TFHEArray(const char* path, int id) {
    long pos[3];
    find_file_pointer(path, id, pos);
    if (pos[0] == -1) {
      // 見つからない
    }

    if (pos[1] != static_cast<int>(TFHEType::TFHEArray)) {
      // Error 該当するIDは要求する型ではない
    }

    FILE* fp;
    if ((fp = fopen(path, "rb")) == NULL) {
      printf("ファイルオープンエラー\n");
      exit(EXIT_FAILURE);
    }

    fseek(fp, pos[0] + 12L + Type::array_option_num() * 4L, SEEK_SET);
    int inbf[1];
    fread(inbf, sizeof(int), 1, fp);

    int* tmp = new int[inbf[0]];

    fread(tmp, sizeof(int), inbf[0], fp);
    shape = std::vector<int>(inbf[0]);
    for (int i = 0; i < shape.size(); i++) {
      shape[i] = tmp[i];
    }

    int size = array_size();

    array = std::vector<Type>(size);
    for (int i = 0; i < array.size(); i++) {
      array[i].load_raw(fp);
    }
    delete tmp;
    fclose(fp);
  }

  /**
   * @brief TFHEの配列の要素の参照を返すメソッド.
   * @param[in] int n,...(index)
   * @return 任意の型Type
   **/
  template <class... T>
  Type& at(T... n) {
    std::initializer_list<int> q{n...};
    std::vector<int> p(q.begin(), q.end());
    int pos = 0;
    int size = shape.size();
    int index = 1;

    for (int i = 0; i < size - 1; i++) {
      index *= shape[size - i - 1];
      pos += p[i] * index;
    }
    pos += p[size - 1];
    return array[pos];
  }

  /**
   * @brief TFHEの配列をファイルに保存するメソッド.
   * @param[in] const char* path(保存先のパス)
   * @param[in] int id(識別用のID)
   **/
  void save(const char* path, int id) {
    long pos[3];

    find_file_pointer(path, id, pos);

    if (pos[0] != -1) {
      remove_from_file(path, pos);
    }
    FILE* fp;
    if ((fp = fopen(path, "ab+")) == NULL) {
      printf("ファイルオープンエラー\n");
      exit(EXIT_FAILURE);
    }
    fseek(fp, 0L, SEEK_END);
    save_meta(fp, id);

    Type::save_option_forArray(fp);
    save_option(fp);
    for (int i = 0; i < array.size(); i++) {
      array[i].save_raw(fp);
    }

    fclose(fp);
  }

 protected:
  void save_option(FILE* fp) {
    int* outbf = new int[1 + shape.size()];
    outbf[0] = shape.size();
    for (int i = 0; i < shape.size(); i++) {
      outbf[1 + i] = shape[i];
    }
    fwrite(outbf, sizeof(int), 1 + shape.size(), fp);
    delete outbf;
  }

  void save_meta(FILE* fp, int id) {
    int size = Type::array_size(shape.size(), array.size());

    int outbf[3];
    outbf[0] = id;
    outbf[1] = static_cast<int>(TFHEType::TFHEArray);
    outbf[2] = size;
    fwrite(outbf, sizeof(int), 3, fp);
  }

  template <typename T>
  void write(T vec, int pos, int depth) {
    int index = 1;
    depth++;
    for (int i = depth; i < shape.size(); i++) {
      index *= shape[i];
    }
    for (int i = 0; i < vec.size(); i++) {
      write(vec[i], pos + i * index, depth);
    }
  }

  void write(int num, int pos, int depth) { array[pos] = Type(num); }

  void write(std::vector<bool>::reference value, int pos, int depth) {
    array[pos] = Type(value);
  }

  int array_size() {
    int size = 1;
    for (int i = 0; i < shape.size(); i++) {
      size *= shape[i];
    }
    return size;
  }
};
#endif