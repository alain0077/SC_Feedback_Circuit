# プログラム概要
Stochastic Computing（SC）での演算回路についての理論値を求めるためのプログラムです．
また，FeedbackによるSC演算の実現手法によって実現した回路のシミュレーションが簡単にできるようにしました．
言語はC++です．

# FeedbackによるSC演算の実現手法とは？
プログラム製作者の研究テーマです．簡単に説明すると，「Feedback回路により，従来のSC演算回路よりも低コストで実現できるのでは」という考えをもとに，その実装手順をフレームワークにまとめ，有用性を示すために実現例を模索しています．下図のような回路をFeedback回路と呼んでいます．

![Feedback回路](https://github.com/alain0077/SC_Feedback_Circuit_Private/blob/img/Feedback.png)

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

![平方根回路](https://github.com/alain0077/SC_Feedback_Circuit_Private/blob/img/SQRT.png)

本手法は[こちら](https://ieeexplore.ieee.org/document/9319166)の論文がもとになっています．ここで説明した平方根の実現の仕方も，少し違うアプローチですが，提案されています．

[^nsadd]: Non-Scale-Additionのこと．詳しくは[こちら](https://ieeexplore.ieee.org/document/9139000)の論文を参照．

# 使い方
本プログラムの使い方をAND回路のシミュレーションの実装例と合わせながら簡単に説明します．  
まず，シミュレーションしたい回路を実装します．基本的な回路の実装はディレクトリ`src/Simulation/Calculation`にまとめています．今回の例で用いるAND回路についてはあるため実装は割愛します．  
次に，以下のひな形を用いてシミュレーションを行うクラスを実装します．
```c++
/*** .h ヘッダー ***/
#pragma once
#include "Simulation.h"

class MySim : public Simulation
{
public:
  /// @brief Constructor
  MySim();

  /// @brief Destructor
  ~MySim() = default;

  /// @brief エラーを記録するクラスの呼び出し
  virtual void set_ERR() override;

  /// @brief ループ前の処理
  virtual void Config() override;

  /// @brief ループ内の処理（1入力）
  virtual void Run(SC::SN& input) override;

  /// @brief ループ内の処理（2入力）
  virtual void Run(SC::SN& rhs, SC::SN& lhs) override;

private:
  /* 必要に応じてメンバ変数を宣言 */

};

/*** .cpp ソース ***/
#include "MySim.h"

#include "Calculation/シミュレーションしたい回路.h"

#define STDOUT Define::STDOUT

using namespace std;
using namespace SC;

MySim::MySim() : Simulation()
{
  /*** ループ回数の設定 ***/
  // シミュレーションの試行回数
  trials_ = 10u;

  // 入力として1からNを与えたい時の設定
  // (1,1) (1,2) (1,3) ... (N,N-1) (N,N)
  // ループ1のスタート
  rep1Start_ = 1u;
  // ループ1のエンド
  rep1End_ = N_;
  // ループ2のスタート
  rep2Start_ = 1u;
  // ループ3のスタート
  rep2End_ = N_;
}

/// @brief エラーを記録するクラスの呼び出し
void Sim_DIV::set_ERR()
{
  /* 演算誤差などを記録するクラス */
  Call_Analyzer("てきとーなタグ");
} 

/// @brief ループ前の処理
void MySim::Config()
{
  /* 必要に応じて */
}

// @brief ループ内の処理（1入力）
void MySim::Run(SN& x)
{
  // Analyzerクラスのtagを取得
  auto it = tags_.begin();

  /* シミュレーションしたい関数の呼び出し */
  Update_Analyzer((*it), x, MyFunc(x)), it++;
}

/// @brief ループ内の処理（2入力）
void MySim::Run(SN& x, SN& y)
{
  // Analyzerクラスのtagを取得
  auto it = tags_.begin();

  /* シミュレーションしたい関数の呼び出し */
  Update_Analyzer((*it), x, y, MyFunc(x, y)), it++;
}
```
このひな形を用いてANDによる乗算をシミュレートするクラスを下記のように実装します．
ファイル名，クラス名ともに`Sim_AND`とします．
今回は2入力なので，1入力のオーバーライドはコメントアウトしてます．しなくても問題はないです．
```c++
/*** Sim_AND.h ***/
#pragma once
#include "Simulation.h"

class Sim_AND : public Simulation
{
public:
  /// @brief Constructor
  Sim_AND();

  /// @brief Destructor
  ~Sim_AND() = default;

  /// @brief エラーを記録するクラスの呼び出し
  virtual void set_ERR() override;

  /// @brief ループ前の処理
  virtual void Config() override;

  /// @brief ループ内の処理（1入力）
  // virtual void Run(SC::SN& input) override;

  /// @brief ループ内の処理（2入力）
  virtual void Run(SC::SN& rhs, SC::SN& lhs) override;

private:
  /* 必要に応じてメンバ変数を宣言 */

};

/*** Sim_AND.cpp ***/
#include "Sim_AND.h"

#include "Calculation/Calculation.h"

#define STDOUT Define::STDOUT

using namespace std;
using namespace SC;

Sim_AND::Sim_AND() : Simulation()
{
  /*** ループ回数の設定 ***/
  // シミュレーションの試行回数
  trials_ = 10u;
  
  // 入力として1からNを与えたい時の設定
  // (1,1) (1,2) (1,3) ... (N,N-1) (N,N)
  // ループ1のスタート
  rep1Start_ = 1u;
  // ループ1のエンド
  rep1End_ = N_;
  // ループ2のスタート
  rep2Start_ = 1u;
  // ループ3のスタート
  rep2End_ = N_;
}

/// @brief エラーを記録するクラスの呼び出し
void Sim_DIV::set_ERR()
{
  /* 演算誤差などを記録するクラス */
  // AND回路の乗算
  Call_Analyzer("AND");
} 

/// @brief ループ前の処理
void Sim_AND::Config()
{
  /* 必要に応じて */
}

/// @brief ループ内の処理（2入力）
void Sim_AND::Run(SN& x, SN& y)
{
  // Analyzerクラスのtagを取得
  auto it = tags_.begin();

  /* シミュレーションしたい関数の呼び出し */
  Update_Analyzer((*it), x, y, AND(x, y)), it++;
}
```
そして，これを下記のように'main.cpp'で呼ぶことでシミュレーションができます．
```c++
#include "Simulation/MgrSim.h"
#include "Simulation/Sim_AND.h"

using namespace std;

int main()
{
  auto sim = make_shared<Sim_AND>();

  make_shared<MgrSim>(sim)->run();
  
  return EXIT_SUCCESS;
}
```
> Note：
> 
> 1入力と2入力の切り替えは`inc/Define.h`でして下さい．
> その他の切り替えもできます．

# 最後に
その他便利な？機能があったりなかったりしますが，手が疲れたのでこの辺にしときます．
読解頑張ってください～