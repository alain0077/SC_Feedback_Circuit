#include "DIV.h"

#include "Calculation/MyDiv.h"
#include "Calculation/Calculation.h"
#include <CSVLoad>
#include <Random>
#include <Gaming>
#include <ProgressBar>

#define STDOUT Define::STDOUT

using namespace std;
using namespace chrono;
using namespace SC;
using namespace tools;

namespace {
  auto s_time = system_clock::now();
}

Sim_DIV::Sim_DIV() : Simulation()
{
  trials_ = 10u;
  rep1Start_ = 1u;
  rep1End_ = N_ - 1u;
  rep2Start_ = 1u;
  rep2End_ = N_;
}

/// @brief エラーを記録するクラスの呼び出し
void Sim_DIV::set_ERR()
{
  /* 演算誤差などを記録するクラス */
  /* Correlated Division */
  Call_Analyzer("CORDIV");

  /* Feedback Divison */
  Call_Analyzer("FBDIV");
} 

/// @brief ループ前の処理
void Sim_DIV::Config()
{
}

/// @brief ループ内の処理（2入力）
/// @note x が y より小さくならないように与える．(1 <= x <= N-1, x <= y <= N)
void Sim_DIV::Run(SN& x, SN& y)
{
  // x が y より大きいとき，return
  if(x.get_const() > y.get_const()) return;

  // Analyzerクラスのtagを取得
  auto it = tags_.begin();

  // x と相関が最大のSNを生成
  SN z = SN(y.get_const().value(), x.get_seed().value(), x.size());

  /* Correlated Division */
  // Update_Analyzer("CORDIV", x, y, CORDIV(y, x));
  Update_Analyzer((*it), x, z, CORDIV(z, x)), it++;

  /* Feedback Divison */
  // Update_Analyzer("FBDIV", x, y, MyDiv(y, x));
  Update_Analyzer((*it), x, y, MyDiv(y, x)), it++;
}