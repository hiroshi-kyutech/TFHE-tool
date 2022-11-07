## TFHE_LIBEX
拡張TFHEライブラリ.
[TFHEライブラリ](https://github.com/tfhe/tfhe)を使いやすく,多機能にすることで  
より簡単に実験的アルゴリズムを作成できる機会を提供します.
このライブラリは,九州工業大学情報工学部の坂本研B4の坪田君が作成したものを元に部分的に改良して公開しています．

### 機能
秘密鍵, クラウド鍵の管理  
整数型(TFHEInteger,TFHEInt8,16,32)とその演算(四則/剰余演算,比較), 演算時のエラー検出(division by zero, overflow)  
真理値型(TFHEBool)とその論理演算(and,not,or,xor)  
三項演算子(multiplexor)  
多次元配列(TFHEArray)  
鍵, 各型及び配列の保存, 読み込み

### ビルド
ビルド用ディレクトリを作成するためコマンドライン上で以下を実行.  
cd tfhe_libex   
mkdir build  

buildディレクトリに移動しコンパイル.  
コンパイルには[TFHEライブラリ](https://github.com/tfhe/tfhe)が必要.  
cd build  
cmake ..  
make  

build/src/libディレクトリ下にlibtfhe_libex.soが作成されます.  

### API
[APIリファレンス](https://hiroshi-kyutech.github.io/TFHE-tool/public/)公開しました.  

### テスト
src/testディレクトリにテストコードがあります.  
各型の演算テストの他に配列にはソートのテストもあります.  

### Nightly
Nightly版はnightlyディレクトリ下の新規ファイルの追加及び既存ファイルの上書きで実行可能。
Nightly版に浮動小数点型(保存, エラーチェック機能なし)とその加算を追加.  

## Attention
[TFHEライブラリ](https://github.com/tfhe/tfhe)が必要.  
No Coding Comment.  
No Enough Error Check.  

## ライセンス
ライセンスは本ライブラリが依存する[TFHEライブラリ](https://github.com/tfhe/tfhe)が許可する範囲でオープンソース、コピーレフトとします。
