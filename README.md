# 


# Class
本プログラムで実装した一部のクラスについて簡単に説明．

## 一覧
+ [SN](#SN)

## SN
Stochastic Number（SN）を生成，管理するクラス．

### メンバ関数
+ [コンストラクタ](#コンストラクタ)
    + SN(int, int)
    + SN(int, int, int)
    + SN(double, double, bitset<N>)

+ [相関](#相関)
    + SCC(SN) : double
    + ReSNG(int) : SN

+ [表示・取得](#表示・取得)
    + print_bs() : void
    + get_sn() : bitset<N>
    + get_val() : double
    + get_ans() : double

### コンストラクタ
コンストラクタは3つあり，それぞれ下記のように目的によって使い分けられる．
```
int N;      // SNのビット長
int x;      // 定数（SNに変換する値）
int seed;   // 準乱数生成器の初期値，基本的には乱数
int shift;  // シフトするビット長
double val;   // SNの値（ ビット列中の1の数 / ビット長N ）
double ans;   // SNの本来の値（演算誤差を含まない値，生成時は　x/N となる．）
bitset<N> sn; // SNのビット列．

// 与えられた引数xより，準乱数生成器（LFSR，non-LFSR）を用いてSNを生成する．準乱数生成器の初期値はseedが設定される．
SN sn1 = SN(x, seed);

// 上記のコンストラクタとの違いは，用いる準乱数生成器がビットシフトに対応しているかどうか．基本的な生成の流れは同様．第3引数にはシフトするビット長を与える．
SN sn2 = SN(x, seed, shift);

// 任意のSNを生成するためのコンストラクタ．
SN sn3 = SN(val, ans, sn);
```
LFSRなどの準乱数生成器についての仕組みは，[wiki](https://ja.wikipedia.org/wiki/Linear-feedback_shift_register)などを参照．

なお，引数なしのデフォルトコンストラクタ（```SN()```）は宣言していないため，下記のような宣言はできない．
```
SN sn4; // コンパイルエラー
```

### 相関

### 表示・取得

## Division
Stochastic Number（SN）を生成，管理するクラス．

### メンバ関数
+ [コンストラクタ](#コンストラクタ)
    + SN(int, int)
    + SN(int, int, int)
    + SN(double, double, bitset<N>)

+ [相関](#相関)
    + SCC(SN) : double
    + ReSNG(int) : SN

+ [表示・取得](#表示・取得)
    + print_bs() : void
    + get_sn() : bitset<N>
    + get_val() : double
    + get_ans() : double

### コンストラクタ
コンストラクタは3つあり，それぞれ下記のように目的によって使い分けられる．
```
int N;      // SNのビット長
int x;      // 定数（SNに変換する値）
int seed;   // 準乱数生成器の初期値，基本的には乱数
int shift;  // シフトするビット長
double val;   // SNの値（ ビット列中の1の数 / ビット長N ）
double ans;   // SNの本来の値（演算誤差を含まない値，生成時は　x/N となる．）
bitset<N> sn; // SNのビット列．

// 与えられた引数xより，準乱数生成器（LFSR，non-LFSR）を用いてSNを生成する．準乱数生成器の初期値はseedが設定される．
SN sn1 = SN(x, seed);

// 上記のコンストラクタとの違いは，用いる準乱数生成器がビットシフトに対応しているかどうか．基本的な生成の流れは同様．第3引数にはシフトするビット長を与える．
SN sn2 = SN(x, seed, shift);

// 任意のSNを生成するためのコンストラクタ．
SN sn3 = SN(val, ans, sn);
```
LFSRなどの準乱数生成器についての仕組みは，[wiki](https://ja.wikipedia.org/wiki/Linear-feedback_shift_register)などを参照．

なお，引数なしのデフォルトコンストラクタ（```SN()```）は宣言していないため，下記のような宣言はできない．
```
SN sn4; // コンパイルエラー
```

### 相関

### 表示・取得