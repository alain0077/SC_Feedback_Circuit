# <!-- omit in toc -->
Stochastic Computing（SC）での演算回路についての理論値を求めるためのプログラムです．

# Class <!-- omit in toc -->
本プログラムで実装した一部のクラスについて簡単に説明．

- [SN](#sn)
  - [メンバ関数](#メンバ関数)
  - [コンストラクタ](#コンストラクタ)
  - [相関](#相関)
  - [表示・取得](#表示取得)
- [SC::Division::Feedback](#scdivisionfeedback)
  - [メンバ関数](#メンバ関数-1)
  - [使用例](#使用例)

---
# SN
Stochastic Number（SN）を生成，管理するクラス．
SNのビット列や値，そのSNの相関操作を行うことができる．

## メンバ関数
+ [コンストラクタ](#コンストラクタ)
    + SN(int, int)
    + SN(int, int, int)
    + SN(double, double, bitset<N>)

+ [相関](#相関)
    + SCC(SN) : double
    + ReSNG(int) : SN

+ [表示・取得](#表示取得)
    + print_bs() : void
    + get_sn() : bitset<N>
    + get_val() : double
    + get_ans() : double

## コンストラクタ

コンストラクタは3つあり，それぞれ下記のように目的によって使い分けられる．
LFSRなどの準乱数生成器についての仕組みは[wiki](https://ja.wikipedia.org/wiki/Linear-feedback_shift_register)などを参照．
```c++
int N;      // SNのビット長
int x;      // 定数（SNに変換する値）
int seed;   // 準乱数生成器の初期値，基本的には乱数
int shift;  // シフトするビット長
double val;   // SNの値（ ビット列中の1の数 / ビット長N ）
double ans;   // SNの本来の値（演算誤差を含まない値，生成時は　x/N となる．）
bitset<N> sn; // SNのビット列．

// 与えられた引数xより，準乱数生成器（LFSR，non-LFSR）を用いてSNを生成する．
// 準乱数生成器の初期値はseedが設定される．
SN sn1 = SN(x, seed);

// 用いる準乱数生成器がビットシフトに対応している．
// 基本的な生成の流れは同様．第3引数にはシフトするビット長を与える．
SN sn2 = SN(x, seed, shift);

// 任意のSNを生成するためのコンストラクタ．
SN sn3 = SN(val, ans, sn);
```

なお，引数なしのデフォルトコンストラクタ（```SN()```）は宣言していないため，下記のような宣言はできない．
```c++
SN sn4; // コンパイルエラー
```

## 相関
|    name     | description                                |
| :---------: | :----------------------------------------- |
|  ```SCC```  | 引数で与えられたSNとの相関を求める．       |
| ```ReSNG``` | 引数で与えられたseedをもとにSNを再生する． |

各メンバ関数についての使用例を下記に示す．相関の操作などにかかわる関数で，演算誤差を抑えたり，意図した相関で演算するために用いる．

```c++
int x, y;   // 定数（SNに変換する値）
int seed1;  // 乱数その１
int seed2;  // 乱数その２

// SNを生成
SN sn1 = SN(x, seed1);
SN sn2 = SN(y, seed1);

// SNを再生成
SN sn3 = sn2.ReSNG(seed2);

// 2つのSNの相関を求める．
double scc1 = sn1.SCC(sn2);
double scc2 = sn1.SCC(sn3);

// andをとる
AND(sn1, sn2); // Min
AND(sn1, sn3); // 掛け算
```

この例の```scc1```と```scc2```は違う値になる．
厳密には，```scc1```は1に近い値を，```scc2```は0に近い値をそれぞれとる（はず，，，）．
このとき，```sn1```と```sn2```，```sn1```と```sn3```の組み合わせでANDをとると，Min関数と掛け算という結果にそれぞれなる．

## 表示・取得
|      name      | description                            |
| :------------: | :------------------------------------- |
| ```print_bs``` | ビット列とSNの値，本来の値を表示する． |
|  ```get_sn```  | ビット列を取得する．                   |
| ```get_val```  | SNの値を取得する．                     |
| ```get_ans```  | 演算誤差なしのSNの値を取得する．       |

SNの状態を表示したり，取得したりするための関数．使用例を下記に示す．

```c++
int N;      // SNのビット長
int x, y;   // 定数（SNに変換する値）
int seed1;  // 乱数その１
int seed2;  // 乱数その２

// SNを生成
SN sn1 = SN(x, seed1);
SN sn2 = SN(y, seed2);

// 演算前のSNの状態をprint
sn1.print_bs();

// ANDで積をとる
SN sn3 = AND(sn1, sn2);

// 演算後のSNの状態をprint
sn3.print_bs();

// 演算後のSNのパラメータを取得
double val = sn3.get_val();
double ans = sn3.get_ans();

// 演算誤差を計算
double err = ans - val;
```

演算前後のSNの状態の確認や，演算誤差の計算に用いることができる．

# SC::Division::Feedback
SCに関する演算はSCというnamespaceにまとめている．使い方は統一しているため，その内の一つであるDivisionのFeedbackについて説明する．SCでの除算をするクラス．Feedbackによる除算回路がベースになっている．

## メンバ関数
+ [コンストラクタ](#コンストラクタ-1)
  + Feedback()
+ [演算子](#演算子)
  + operator() (SN, SN) : SN
+ [表示・取得](#表示取得-1)
  + get_SCC() : vector<pair<double, double>>
  + print_Summary() : void
+ [初期化](#初期化)
  + reset() : void

## 使用例
```c++
int x, y;   // 定数（SNに変換する値）
int seed1;  // 乱数その１
int seed2;  // 乱数その２

// SNを生成
SN sn1 = SN(x, seed1);
SN sn2 = SN(y, seed2);

// 演算クラスを呼び出す
Feedback div = Feedback();

// 演算実行
SN sn3 = div(sn1, sn2);

// 演算誤差などの詳細をprint
div.print_Summary();
```