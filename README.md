# プログラム概要 <!-- omit in toc -->
Stochastic Computing（SC）での演算回路についての理論値を求めるためのプログラムです．Stochastic Numberの生成・相関操作などをSCというnamespaceにまとめました．
また，FeedbackによるSC演算の実現手法によって実現した回路のシミュレーションが簡単にできるようにしました．

# FeedbackによるSC演算の実現手法とは？ <!-- omit in toc -->
プログラム製作者の研究テーマです．簡単に説明すると，「Feedback回路により，従来のSC演算回路よりも低コストで実現できるのでは」という考えをもとに，その実装手順をフレームワークにまとめ，有用性を示すために実現例を模索しています．下図のような回路をFeedback回路と呼んでいます．

![Feedback回路](https://github.com/alain0077/SC_Feedback_Circuit/blob/img/Feedback.png)

この図のOutput関数とFeedback関数を何かしらの回路に置き換えることにより，目的の演算回路を実現します．

例えば，目的の演算回路を平方根として，Output関数を[NSAdd](https://ieeexplore.ieee.org/document/9139000)という飽和加算器の回路に置き換えたとします[^nsadd]．先ほどの図の回路の出力は次の式のような式で表すことが出来ます．

$Out = In + Feedback$

これをFeedbackについて解くと，

$Feedback = In - Out$

が得られます．このとき，目的の演算回路を平方根回路であるから，$Out = In^2$となります．つまり，先ほどの式は，

$Feedback = \sqrt{Out^2} + Out$

となります．したがって，Feedback関数がこの式を満たすとき，平方根回路の実現ができます．また，この式を変形すると，

$Feedback = \sqrt{Out^2} * (1 - \sqrt{Out^2})$

が得られます．よって，目的の演算回路が平方根のとき，Feedback関数は次のような図の回路を満たせば良いことが分かります．

![平方根回路](https://github.com/alain0077/SC_Feedback_Circuit/blob/img/SQRT.png)

本手法は[こちら](https://ieeexplore.ieee.org/document/9319166)の論文がもとになっています．ここで説明した平方根の実現の仕方も，少し違うアプローチですが，提案されています．

[^nsadd]: Non-Scale-Additionのこと．詳しくは[こちら](https://ieeexplore.ieee.org/document/9139000)の論文を参照．

# 基本的な使い方 <!-- omit in toc -->


# 仕様・説明 <!-- omit in toc -->
本プログラムで実装した一部のクラスや関数の使い方などについて簡単に説明．
###### ※使用例などで書いているコードはコンパイルは通らないです．

- [SC::SN](#scsn)
  - [メンバ関数](#メンバ関数)
  - [非メンバ関数](#非メンバ関数)
  - [構築・破壊](#構築破壊)
  - [表示・取得](#表示取得)
  - [生成](#生成)
  - [相関](#相関)
- [Calculation.h](#calculationh)
  - [演算](#演算)
- [Feedback::FeedbackCircuit](#feedbackfeedbackcircuit)
  - [メンバ関数](#メンバ関数-1)
  - [構築・破壊](#構築破壊-1)
  - [実行](#実行)
  - [使用例](#使用例)
- [Feedback::Function](#feedbackfunction)
  - [メンバ変数](#メンバ変数)
  - [メンバ関数](#メンバ関数-2)
  - [構築・破壊](#構築破壊-2)
  - [実行](#実行-1)
  - [取得](#取得)
  - [使用例](#使用例-1)
- [AbsError](#abserror)
  - [メンバ関数](#メンバ関数-3)
  - [構築・破壊・初期化](#構築破壊初期化)
  - [更新](#更新)
  - [表示・取得](#表示取得-1)
  - [使用例](#使用例-2)
- [Analysis](#analysis)
  - [メンバ関数](#メンバ関数-4)
  - [構築・破壊・初期化](#構築破壊初期化-1)
  - [更新](#更新-1)
  - [表示・取得](#表示取得-2)
  - [使用例](#使用例-3)
- [Random](#random)
  - [メンバ関数](#メンバ関数-5)
  - [構築・破壊・初期化](#構築破壊初期化-2)
  - [生成](#生成-1)
  - [プロパティ](#プロパティ)
  - [使用例](#使用例-4)

# SC::SN
Stochastic Number（SN）を生成，管理するための機能をまとめた．
`namespace SC`にグルーピングされている．
SNのビット列や値を管理するクラスやSNを生成する関数，SNの相関操作を行う関数を含む．

## メンバ関数
+ [構築・破壊](#構築破壊)
  + SN(int, int)
  + SN(int, int, int)
  + SN(double, double, bitset<N>)
  + ~SN() = default;
+ [表示・取得](#表示取得)
  + print_bs() : void
  + get_sn() : bitset<N>
  + get_val() : double
  + get_ans() : double

## 非メンバ関数
+ [生成](#生成)
  + SNG(int, int) : SN
  + SNG(int, int, int) : SN
+ [相関](#相関)
  + SCC(SN) : double

## 構築・破壊
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
> Note：
> 
> コンストラクタは3つあります．それぞれ下記のように目的によって使い分けて下さい．
> LFSRなどの準乱数生成器についての仕組みは[wiki](https://ja.wikipedia.org/wiki/Linear-feedback_shift_register)などを参照して下さい．
> なお，引数なしのデフォルトコンストラクタ（```SN()```）は宣言していないため，下記のような宣言はできません．

```c++
SN sn4; // コンパイルエラー
```

## 表示・取得
|      name      | description                            |
| :------------: | :------------------------------------- |
| ```print_bs``` | ビット列とSNの値，本来の値を表示する． |
|  ```get_sn```  | ビット列を取得する．                   |
| ```get_val```  | SNの値を取得する．                     |
| ```get_ans```  | 演算誤差なしのSNの値を取得する．       |

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

## 生成
|   name    | description  |
| :-------: | :----------- |
| ```SNG``` | SNを生成する |

```c++
int N;      // SNのビット長
int x;      // 定数（SNに変換する値）
int seed;   // 準乱数生成器の初期値，基本的には乱数
int shift;  // シフトするビット長

// 与えられた引数xより，準乱数生成器（LFSR，non-LFSR）を用いてSNを生成する．
// 準乱数生成器の初期値はseedが設定される
SN sn1 = SNG(x, seed);

// 用いる準乱数生成器がビットシフトに対応している
// 基本的な生成の流れは同様．第3引数にはシフトするビット長を与える
SN sn2 = SNG(x, seed, shift);
```

## 相関
|   name    | description                          |
| :-------: | :----------------------------------- |
| ```SCC``` | 引数で与えられたSNとの相関を求める． |

```c++
int x, y;   // 定数（SNに変換する値）
int seed1;  // 乱数その１
int seed2;  // 乱数その２

// SNを生成
SN sn1 = SN(x, seed1);
SN sn2 = SN(y, seed1);
SN sn3 = SN(y, seed2);

// 2つのSNの相関を求める
double scc1 = sn1.SCC(sn2);
double scc2 = sn1.SCC(sn3);

// andをとる
AND(sn1, sn2); // Min
AND(sn1, sn3); // 掛け算
```
> Note：
> 
> この例の```scc1```と```scc2```は違う値になります．
> 厳密には，```scc1```は1に近い値を，```scc2```は0に近い値をそれぞれとる（はず…）．
> このとき，```sn1```と```sn2```，```sn1```と```sn3```の組み合わせでANDをとると，Min関数と掛け算という結果にそれぞれなります．

# Calculation.h
SCに関する演算をまとめたヘッダ．実装した関数は，`namespace SC`にグルーピングしている．SCにおける演算をまとめている．実装した演算は，下記の表の通り．

## 演算
|      name      | description                                  |
| :------------: | :------------------------------------------- |
|   ```MUX```    | 1/2スケール加算．                            |
|    ```OR```    | 入力の負の相関が最大のときに，飽和加算．     |
|  ```NSAdd```   | 飽和加算．                                   |
|   ```AND```    | 入力に相関ないときに，乗算．                 |
|  ```CORDIV```  | 入力の正の相関が最大のときに，除算．         |
| ```Min::AND``` | 入力の正の相関が最大のときに，最小値を出力． |
| ```Max::OR```  | 入力の正の相関が最大のときに，最小値を出力． |

# Feedback::FeedbackCircuit
本プログラムのメインの機能．Feedback回路のフレームワークをまとめたクラス．
`namespace Feedback`にグルーピングされている．
任意のOutput関数とFeedback関数を設定することで，その組み合わせに関する回路のシミュレーションを行うことができる．

## メンバ関数
+ [構築・破壊](#構築破壊-1)
  + FeedbackCircuit(Function*, Function*)
  + ~FeedbackCircuit() = default;
+ [実行](#実行)
  + Run(const bool&) : bool
  + Run(const initializer_list<bool>&) : bool
  + Run(const bool&, const bool&) : bool
  + Run(const initializer_list<bool>&, const bool&) : bool
  + Run(const bool&, const initializer_list<bool>&) : bool
  + Run(const initializer_list<bool>&, const initializer_list<bool>&) : bool

## 構築・破壊
|          name          | description |
| :--------------------: | :---------- |
| ```FeedbackCircuit```  | 生成．      |
| ```~FeedbackCircuit``` | default     |

## 実行
|   name    | description                                                                          |
| :-------: | :----------------------------------------------------------------------------------- |
| ```Run``` | 第1引数に与えるのがOutput関数への入力．第2引数に与えるのがFeedback関数への入力． |

> Note：
> 
> 設定したOutput関数やFeedback関数の入力によって，与える引数は変わります．
> Output関数からFeedback関数への入力，またはその逆は固定で与えられるようになっているので，それ以外の入力のみを引数に設定するように注意して下さい．
>  詳しくは，[cppファイル]()でのメンバ関数`Run`の実装を確認してください．
> [Function](#feedbackfunction)の定義してある通り，Output関数，Feedback関数ともに，対応している最大入力数は，3入力（固定の入力を除くと2入力）までです．
> それ以上は未実装なため，3入力として扱われます．

## 使用例
例えば，平方根をとるようなFeedback回路について検証したい場合．

まず，`SCSQRT`という関数を作ります．この時，事前に[Function](#feedbackfunction)クラスを継承したOutput関数とFeedback関数は実装しているものとします．実際にどのような関数を実装すればよいかの詳細は省きます．知りたい場合は，「[FeedbackによるSC演算の実現手法とは？](##feedbackによるsc演算の実現手法とは)」を読んでみて下さい．

```c++:SCSQRT.h
int N;      // SNのビット長

SN SCSQRT(SN& input) {
  OutputFunc output;      // 実装したOutput関数
  FeedbackFunc feedback;  // 実装したFeedback関数

  // FeedbackCircuitクラスを生成
  // 引数にはOutput関数とFeedback関数を与える
  FeedbackCircuit circuit(&output, &feedback);

  // FeedbackCircuitの出力を記録
  bitset<N> res;

  // 入力SNを回路に与える
  // Output関数にinputを与える
  // Feedback関数への入力はなし
  for(int i = 0; i < N; i++)
  {
    res[i] = circuit.Run(input.get_sn()[i]);
  }

  // 正しい値
  double ans = sqrt(input.get_ans());

  // 生成されたSNの値
  double val = (double)res.count() / (double)N;

  return SN(ans, val, res);
}
```
次に，main関数で与えるSNを生成し，[Analysis](#analysis)クラスや[AbsError](#abserror)クラスを用いて演算誤差を求めます．今回は，[AbsError](#abserror)クラスを使用してます．

```c++:main.cpp
int N;      // SNのビット長
int seed;   // 乱数

int main()
{ 
  // AbsErrorクラスを生成
  AbsError error;

  // seed値を固定し，全ての入力パターンを検証
  for(int i = 1; i < N; j++) {
    // 入力SNを生成
    SN sn = SN(i, seed);

    // 演算実行
    SN ans = SCSQRT(sn);

    // 誤差の更新
    error.Update(ans.get_ans(), ans.get_val())
  }
  
  // 演算誤差などの結果を表示
  error..print_Summary();

  return 0;
}
```
実際に実行できるSQRT関数は[SQRT.h](https://github.com/alain0077/SC_Feedback_Circuit/blob/master/SQRT.h)で定義してます．実装は[SQRT.cpp](https://github.com/alain0077/SC_Feedback_Circuit/blob/master/SQRT.cpp)です．興味があれば参考にして下さい．

# Feedback::Function
[FeedbackCircuit](#feedbackfeedbackcircuit)クラスに与える，Output関数とFeedback関数を実装するときに継承するクラス．任意の関数を実装したいときは，このクラスを継承しないと[FeedbackCircuit](#feedbackfeedbackcircuit)クラスのコンストラクタに引数として与えることができないので注意．
`namespace Feedback`にグルーピングされている．
すでに幾つかの関数は実装済．

## メンバ変数
+ 出力
  + _output : bool
## メンバ関数
+ [構築・破壊](#構築破壊-2)
  + Function()
  + ~Function() = default;
+ [実行](#実行-1)
  + Run(const bool&) : void
  + Run(const bool&, const bool&) : void
  + Run(const bool&, const bool&, const bool&) : void
+ [取得](#取得)
  + get_Output() : bool

## 構築・破壊
|      name      | description |
| :------------: | :---------- |
| ```Function``` | 生成．      |

## 実行
|   name    | description                          |
| :-------: | :----------------------------------- |
| ```Run``` | 与えられた引数からパラメータを更新． |

> Note：
> 
> 実装する関数の入力数に応じて，この関数をオーバライドして実装して下さい．
> 最大入力数は3まで対応しています．
> 幾つかの関数は実装済みなので，新しい関数を作るときに参考にして下さい．

## 取得
|       name       | description        |
| :--------------: | :----------------- |
| ```get_Output``` | 関数の出力を取得． |

## 使用例
2入力のANDをとるだけの関数を実装する場合．
実際に実装したものは[AND.h](https://github.com/alain0077/SC_Feedback_Circuit/blob/master/AND.h)と[AND.cpp](https://github.com/alain0077/SC_Feedback_Circuit/blob/master/AND.cpp)を参照して下さい．
Functionクラスを継承した，ANDクラスを宣言します．
2入力なので，引数が2つある`Run`関数をオーバーライドします．

```c++:AND.h
int N;      // SNのビット長

class AND : public Function
{
public:
  void Run(const bool&, const bool&) override;
};

void AND::Run(const bool& input1, const bool& input2)
{
  _output = input1 & input2;
}

```
以上で実装は終わりです．
後はこれを[FeedbackCircuit](#feedbackfeedbackcircuit)クラスに与えれば，Output関数やFeedback関数として使えます．
> 注意：
>
> [FeedbackCircuit](#feedbackfeedbackcircuit)クラスの実装の都合上，Output関数からFeedback関数へ入力，またはその逆の入力は2入力の回路に対して，両方の入力に設定することはできません．
> もし，そういったことがしたいのであれば1入力関数として実装をして下さい．

# AbsError
演算誤差を保持・管理するクラス．
Mean Absolute Error（MAE）やMean Absolute Percentage Error（MAPE）を計算し，それらの最大値や最小値も記録する．

## メンバ関数
+ [構築・破壊・初期化](#構築破壊初期化)
  + AbsError()
  + ~AbsError() = default;
  + reset()
+ [更新](#更新)
  + Update(const double&, const double&) : void
+ [表示・取得](#表示取得-1)
  + get_MAE() : double
  + get_MAPE() : double
  + get_MAX_AE() : double
  + get_MAX_APE() : double
  + get_MIN_AE() : double
  + get_MIN_APE() : double
  + print_Summary() : void

## 構築・破壊・初期化
|      name      | description                                   |
| :------------: | :-------------------------------------------- |
| ```AbsError``` | 生成．                                        |
|  ```reset```   | MAEやMAPEなどの演算誤差のパラメータの初期化． |

## 更新
|     name     | description                          |
| :----------: | :----------------------------------- |
| ```Update``` | 与えられた引数からパラメータを更新． |

## 表示・取得
|        name         | description                              |
| :-----------------: | :--------------------------------------- |
|    ```get_MAE```    | 絶対平均誤差を取得する．                 |
|   ```get_MAPE```    | 平均エラー率を取得する．                 |
|  ```get_MAX_AE```   | 最大の絶対誤差を取得する．               |
|  ```get_MAX_APE```  | 最大のエラー率を取得する．               |
|  ```get_MIN_AE```   | 最小の絶対誤差を取得する．               |
|  ```get_MIN_APE```  | 最小のエラー率を取得する．               |
| ```print_Summary``` | それぞれのパラメータをまとめて表示する． |

## 使用例
Stochastic Number Generator（SNG）に与えるseed値を固定したとき，Nビット長のSNの全ての組み合わせに対して，掛け算を実行しています．そして，結果を`print_Summary()`で表示すると，MAEやMAPEなどを確認することができます．

```c++
int N;      // SNのビット長
int seed1;  // 乱数その１
int seed2;  // 乱数その２

// 入力SNを生成
SN sn1 = SN(x, seed1);
SN sn2 = SN(y, seed2);

// AbsErrorクラスを生成
AbsError error;

// SNGに与えるseedを固定して
// 入力の全パターンを実行
for(int i = 1; i < N; i++) {
  for(int j = 1; j < N; j++) {
    // 入力SNを生成
    SN sn1 = SN(i, seed1);
    SN sn2 = SN(j, seed2);

    // 演算実行
    SN ans = AND(sn1, sn2);

    // 誤差の更新
    error.Update(ans.get_ans(), ans.get_val())
  }
}

// 演算誤差などの結果を表示
error..print_Summary();
```

# Analysis
[AbsError](#abserror)クラスを継承したクラス．相関による演算誤差を確かめるために，与えられた入力の組み合わせの中で，相関が1，0，-1にそれぞれ一番近いときの誤差を記録する機能を追加した．

## メンバ関数
+ [構築・破壊・初期化](#構築初期化-1)
  + Analysis()
  + ~Analysis() = default;
  + reset()
+ [更新](#更新)
  + Update(const double&, const double&, const double&) : void
+ [表示・取得](#表示取得-1)
  + get_MAE() : double
  + get_MAPE() : double
  + get_MAX_AE() : double
  + get_MAX_APE() : double
  + get_MIN_AE() : double
  + get_MIN_APE() : double
  + get_SCC() : vector<pair<double, double>>
  + print_Summary() : void

## 構築・破壊・初期化
|      name      | description                                   |
| :------------: | :-------------------------------------------- |
| ```Analysis``` | 生成．                                        |
|  ```reset```   | MAEやMAPEなどの演算誤差のパラメータの初期化． |

## 更新
|     name     | description                          |
| :----------: | :----------------------------------- |
| ```Update``` | 与えられた引数からパラメータを更新． |

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

## 使用例
基本的な使い方はAbsErrorの[使用例](#使用例-2)で示されている通りですが，`Update`の引数が違う点に注意して下さい．

```c++
int N;      // SNのビット長
int seed1;  // 乱数その１
int seed2;  // 乱数その２

// 入力SNを生成
SN sn1 = SN(x, seed1);
SN sn2 = SN(y, seed2);

// AbsErrorクラスを生成
Analysis error;

// SNGに与えるseedを固定して
// 入力の全パターンを実行
for(int i = 1; i < N; i++) {
  for(int j = 1; j < N; j++) {
    // 入力SNを生成
    SN sn1 = SN(i, seed1);
    SN sn2 = SN(j, seed2);

    // 演算実行
    SN ans = AND(sn1, sn2);

    // 誤差の更新
    error.Update(ans.get_ans(), ans.get_val(), SCC(sn1, sn2))
  }
}

// 演算誤差などの結果を表示
error..print_Summary();
```

# Random
SNの生成時にSNGに与える整数の乱数を生成するためのクラス．C++のライブラリである`random`を用いた乱数生成の流れをクラスにまとめた．分布生成器は一様整数分布（`uniform_int_distribution`）を，疑似乱数生成器はメルセンヌ・ツイスター法（`mt19937`）を用いている．詳しくは[こちら](https://cpprefjp.github.io/reference/random.html)を参照．乱数生成のためのseed値は，コンストラクタの呼び出し時に`rnd()`で得られる値で初期化される．また，SNのビット長をNとすると，乱数の生成範囲は`1`から`N - 1`までに初期化される．

## メンバ関数
+ [構築・破壊・初期化](#構築破壊初期化-2)
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

## 構築・破壊・初期化
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