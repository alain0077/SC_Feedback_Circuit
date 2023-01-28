# プログラム概要 <!-- omit in toc -->
Stochastic Computing（SC）での演算回路についての理論値を求めるためのプログラムです．Stochastic Numberの生成・相関操作などをまとめたSNクラスやSC演算クラスなどを作成しました．また，実装した各SC演算クラスは演算誤差を表示できるようになっています．

# Class <!-- omit in toc -->
本プログラムで実装した一部のクラスの使い方などについて簡単に説明．

- [SN](#sn)
  - [メンバ関数](#メンバ関数)
  - [コンストラクタ](#コンストラクタ)
  - [相関](#相関)
  - [表示・取得](#表示取得)
- [SC演算回路](#sc演算回路)
  - [メンバ関数](#メンバ関数-1)
  - [コンストラクタ](#コンストラクタ-1)
  - [演算子](#演算子)
  - [表示・取得](#表示取得-1)
  - [初期化](#初期化)
  - [使用例1](#使用例1)
  - [使用例2](#使用例2)
- [Random](#random)
  - [メンバ関数](#メンバ関数-2)
  - [構築・リセット](#構築リセット)
  - [生成](#生成)
  - [プロパティ](#プロパティ)
  - [使用例](#使用例)

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
厳密には，```scc1```は1に近い値を，```scc2```は0に近い値をそれぞれとる（はず…）．
このとき，```sn1```と```sn2```，```sn1```と```sn3```の組み合わせでANDをとると，Min関数と掛け算という結果にそれぞれなる．

## 表示・取得
|      name      | description                            |
| :------------: | :------------------------------------- |
| ```print_bs``` | ビット列とSNの値，本来の値を表示する． |
|  ```get_sn```  | ビット列を取得する．                   |
| ```get_val```  | SNの値を取得する．                     |
| ```get_ans```  | 演算誤差なしのSNの値を取得する．       |

SNの状態を表示したり，取得したりするための関数．
演算前後のSNの状態の確認や，演算誤差の計算に用いることができる．

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

# SC演算回路
SCに関する演算回路はSCというnamespaceにまとめている．
実行毎に演算誤差や最大・最小誤差などを記録する．また，相関による演算誤差を確かめるために，与えられた入力の組み合わせの中で，相関が1，0，-1にそれぞれ一番近いときの誤差を記録する．実装した演算は下記の通りである．

+ Addtion
  + MUX
  + OR
  + NSAdd
+ Multiplication
  + AND
+ Division
  + CORDIV
  + Feedback
+ Min
  + AND
+ Max
  + OR

## メンバ関数
+ [コンストラクタ](#コンストラクタ-1)
  + MUX()
  + OR()
  + NSAdd()
  + Multiplication::AND()
  + CORDIV()
  + Feedback()
  + Min::AND()
  + Max::OR()
+ [演算子](#演算子)
  + operator() (SN, SN) : SN
+ [表示・取得](#表示取得-1)
  + get_MAE() : double
  + get_MAPE() : double
  + get_MAX_AE() : double
  + get_MAX_APE() : double
  + get_MIN_AE() : double
  + get_MIN_APE() : double
  + get_SCC() : vector<pair<double, double>>
  + print_Summary() : void
+ [初期化](#初期化)
  + reset() : void

使い方は統一しているため，下記の[使用例1](#使用例1)や[使用例2](#使用例2)では，MultiplicationのANDでの例を示している．

## コンストラクタ
|           name            | description                                  |
| :-----------------------: | :------------------------------------------- |
|         ```MUX```         | 1/2スケール加算．                            |
|         ```OR```          | 入力の負の相関が最大のときに，飽和加算．     |
|        ```NSAdd```        | 飽和加算．                                   |
| ```Multiplication::AND``` | 入力に相関ないときに，乗算．                 |
|       ```CORDIV```        | 入力の正の相関が最大のときに，除算．         |
|      ```Feedback```       | 除算．                                       |
|      ```Min::AND```       | 入力の正の相関が最大のときに，最小値を出力． |
|       ```Max::OR```       | 入力の正の相関が最大のときに，最小値を出力． |

## 演算子
|       name       | description      |
| :--------------: | :--------------- |
| ```operator()``` | 演算を実行する． |

## 表示・取得
|        name         | description                                            |
| :-----------------: | :----------------------------------------------------- |
|    ```get_MAE```    | 絶対平均誤差を取得する．                               |
|   ```get_MAPE```    | 平均エラー率を取得する．                               |
|  ```get_MAX_AE```   | 最大の絶対誤差を取得する．                             |
|  ```get_MAX_APE```  | 最大のエラー率を取得する．                             |
|  ```get_MIN_AE```   | 最小の絶対誤差を取得する．                             |
|  ```get_MIN_APE```  | 最小のエラー率を取得する．                             |
|    ```get_SCC```    | 相関が1，0，-1にそれぞれ一番近いときの誤差を取得する． |
| ```print_Summary``` | それぞれのパラメータをまとめて表示する．               |


## 初期化
|    name     | description                                   |
| :---------: | :-------------------------------------------- |
| ```reset``` | MAEやMAPEなどの演算誤差のパラメータの初期化． |

## 使用例1
`x`と`y`を`mult`に与え，結果を表示し，その絶対誤差とエラー率を表示している．この例では，演算を一回しか実行していないため，`print_Summary()`などで表示されるパラメータは，あまり意味はなさない（かも…？）．

```c++
int x, y;   // 定数（SNに変換する値）
int seed1;  // 乱数その１
int seed2;  // 乱数その２

// 入力SNを生成
SN sn1 = SN(x, seed1);
SN sn2 = SN(y, seed2);

// 入力SNを表示
sn1.print_bs();
sn2.print_bs();

// 演算回路クラスを呼び出す
auto mult = SC::Multiplication::AND();

// 演算実行
SN sn3 = mult(sn1, sn2);

// 出力SNを表示
sn3.print_bs();

// 絶対誤差・エラー率を取得
std::cout << mult.get_MAE()  << std::endl;
std::cout << mult.get_MAPE() << std::endl;
```

## 使用例2
Stochastic Number Generator（SNG）に与えるseed値を固定したとき，Nビット長のSNの全ての組み合わせに対して，掛け算を実行している．そして，結果を`print_Summary()`で表示すると，MAEやMAPEなどを確認することができる．

```c++
int N;      // SNのビット長
int seed1;  // 乱数その１
int seed2;  // 乱数その２

// 演算回路クラスを呼び出す
auto mult = SC::Multiplication::AND();

// SNGに与えるseedを固定して
// 入力の全パターンを実行
for(int i = 1; i < N; i++) {
  for(int j = 1; j < N; j++) {
    // 入力SNを生成
    SN sn1 = SN(i, seed1);
    SN sn2 = SN(j, seed2);

    // 演算実行
    mult(sn1, sn2);
  }
}

// 演算誤差などの結果を表示
mult.print_Summary();
```

# Random
SNの生成時にSNGに与える整数の乱数を生成するためのクラス．C++のライブラリである`random`を用いた乱数生成の流れをクラスにまとめた．分布生成器は一様整数分布（`uniform_int_distribution`）を，疑似乱数生成器はメルセンヌ・ツイスター法（`mt19937`）を用いている．詳しくは[こちら](https://cpprefjp.github.io/reference/random.html)を参照．乱数生成のためのseed値は，コンストラクタの呼び出し時に`rnd()`で得られる値で初期化される．また，SNのビット長をNとすると，乱数の生成範囲は`1`から`N - 1`までに初期化される．

## メンバ関数
+ [構築・リセット](#構築リセット)
  + Random()
  + ~Random() = default;
  + reset() : void
+ [生成](#生成)
  + operator() () : int;
+ [プロパティ](#プロパティ)
  + range(int, int) : void
  + seed(unsigned int) : void
  + max() : int
  + min() : int

## 構築・リセット
|   name    | description    |
| :-------: | :------------- |
| `Random`  | コンストラクタ |
| `~Random` | デストラクタ   |
|  `reset`  | 状態を初期化   |

## 生成
|     name     | description      |
| :----------: | :--------------- |
| `operator()` | 乱数を生成する． |

## プロパティ
|  name   | description                    |
| :-----: | :----------------------------- |
| `range` | 生成範囲を設定する．           |
| `seed`  | seed値を設定する．             |
|  `max`  | 生成し得る値の上限を取得する． |
|  `min`  | 生成し得る値の下限を取得する． |

## 使用例
```c++
int N;    // SNのビット長
int x,y;  // 定数（SNに変換する値）

// 乱数生成器を生成
auto randN = Random();

// 1からN-1の範囲で乱数を生成
int rnd1 = randN();
int rnd2 = randN();

// 乱数rndからSNを生成
SN sn1 = SN(x, rnd1);
SN sn2 = SN(y, rnd2);

// 相関
sn1.SCC(sn2);
```
これは，2つの乱数を生成してから，その乱数をもとに，2つのSNを生成している．
`sn2`と`sn2`の相関は`0`もしくは，`0`に近い値になる（はず…）．