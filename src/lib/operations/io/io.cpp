/**
 * @file io.cpp
 * @brief 入出力の共通処理のクラスの実装.
 **/
#include "io.hpp"

void TFHEIO::find_file_pointer(const char *path, int id, long result[3]) {
  if (id == -1) {
    // -1は使えない
  }
  int inbf[3];
  FILE *fp;

  if ((fp = fopen(path, "ab+")) == NULL) {
    printf("ファイルオープンエラー\n");
    exit(EXIT_FAILURE);
  }
  fseek(fp, 0L, SEEK_END);
  long fsize = ftell(fp);
  if (fsize == 0) {
    result[0] = -1;
    fclose(fp);
    return;
  }

  long seeker = 0;
  fseek(fp, seeker, SEEK_SET);
  fread(inbf, sizeof(int), 3, fp);

  while (inbf[0] != id) {
    if (seeker >= fsize) {
      result[0] = -1;
      break;
    }
    if (inbf[2] == 0) {
      // endless
      exit(0);
    }
    seeker += inbf[2];
    fseek(fp, seeker, SEEK_SET);
    fread(inbf, sizeof(int), 3, fp);
  }

  fclose(fp);
  result[0] = seeker;
  result[1] = inbf[1];
  result[2] = inbf[2];
}

void TFHEIO::remove_from_file(const char *path, long pos[3]) {
  FILE *fp0;
  if ((fp0 = fopen(path, "rb")) == NULL) {
    printf("ファイルオープンエラー\n");
    exit(EXIT_FAILURE);
  }

  fseek(fp0, 0L, SEEK_END);
  long fsize = ftell(fp0);
  fseek(fp0, 0L, SEEK_SET);
  char *data1;
  if (pos[0] != 0) {
    data1 = new char[pos[0]];

    fread(data1, sizeof(char), pos[0], fp0);
  }

  char *data2;
  long asize = fsize - pos[0] - pos[2];
  if (pos[0] + pos[2] < fsize) {
    long cur = ftell(fp0);

    fseek(fp0, pos[2], SEEK_CUR);

    data2 = new char[asize];
    fread(data2, sizeof(char), asize, fp0);
  }

  fclose(fp0);

  FILE *fp1;
  if ((fp1 = fopen(path, "wb")) == NULL) {
    printf("ファイルオープンエラー\n");
    exit(EXIT_FAILURE);
  }

  fseek(fp1, 0L, SEEK_SET);
  if (pos[0] != 0) {
    fwrite(data1, sizeof(char), pos[0], fp1);
  }

  if (pos[0] + pos[2] < fsize) {
    fwrite(data2, sizeof(char), asize, fp1);
  }

  fclose(fp1);
  if (pos[0] != 0) {
    delete data1;
  }

  if (pos[0] + pos[2] < fsize) {
    delete data2;
  }
}