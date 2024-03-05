#include "CBRT.h"

#include "Calculation/CBRT.h"
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

Sim_CBRT::Sim_CBRT() : Simulation()
{
  count_flag_ = true;
  inter_flag_ = true;

  N_ = 1024u;

  trials_ = 10u;
  rep1Start_ = 1u;
  rep1End_ = N_ - 1u;
}

/// @brief エラーを記録するクラスの呼び出し
void Sim_CBRT::set_ERR()
{
  /* 演算誤差などを記録するクラス */
  /* 立方根回路 */
  Call_Analyzer("CBRT");

  /* 単調なエラーに有効な手法 */
  if(count_flag_)
  Call_Analyzer("FixCBRT_Counter_2bit"),
  Call_Analyzer("FixCBRT_Counter_3bit"),
  Call_Analyzer("FixCBRT_Counter_4bit"),
  Call_Analyzer("FixCBRT_Counter_5bit"),
  Call_Analyzer("FixCBRT_Counter_6bit");

  /* 区間分けによる手法 */
  // ORの最適化なし
  // _Analyzer.push_back(make_shared<Analysis>("FixCBRT_offset_2"));
  
  // 最後の区間の補正値が0
  if(inter_flag_)
  Call_Analyzer("FixCBRT_offset_2_OR"),

  // 全ての区間について補正
  Call_Analyzer("FixCBRT_offset_3_512"),
  Call_Analyzer("FixCBRT_offset_3_256"),
  Call_Analyzer("FixCBRT_offset_3_128"),
  Call_Analyzer("FixCBRT_offset_3_64"),
  Call_Analyzer("FixCBRT_offset_3_256bit"),
  Call_Analyzer("FixCBRT_offset_3_128bit");
} 

/// @brief ループ前の処理
void Sim_CBRT::Config()
{
  // 乱数生成器
  auto randN = Random(N_);
  auto now_time = system_clock::now() - s_time;
  auto seed = duration_cast<microseconds>(now_time).count();
  randN.seed(static_cast<uint32_t>(seed));

  // offsetのための値0のSN
  vector<bool> bs0(N_/2, false);

  // 乱数生成
  auto rn = randN();

  /* 区間分けによる手法 */
  // ORの最適化なし
  offset1.clear();
  offset1.push_back(make_pair(82, SN(144, rn, 512).get_sn()));
  offset1.push_back(make_pair(238, SN(52, rn, 512).get_sn()));
  offset1.push_back(make_pair(512, bs0));

  // 最後の区間の補正値が0
  offset2.clear();
  offset2.push_back(make_pair(82, SN(197, rn, 512).get_sn()));
  offset2.push_back(make_pair(238, SN(137, rn, 512).get_sn()));
  offset2.push_back(make_pair(512, bs0));

  // 全ての区間について補正
  offset3.clear();
  offset3.push_back(make_pair(82, SN(197, rn, 512).get_sn()));
  offset3.push_back(make_pair(238, SN(138, rn, 512).get_sn()));
  offset3.push_back(make_pair(512, SN(88, rn, 512).get_sn()));

  offset4.clear();
  offset4.push_back(make_pair(82, SN(99, rn, 256).get_sn()));
  offset4.push_back(make_pair(238, SN(69, rn, 256).get_sn()));
  offset4.push_back(make_pair(512, SN(44, rn, 256).get_sn()));

  offset5.clear();
  offset5.push_back(make_pair(82, SN(50, rn, 128).get_sn()));
  offset5.push_back(make_pair(238, SN(35, rn, 128).get_sn()));
  offset5.push_back(make_pair(512, SN(22, rn, 128).get_sn()));

  offset6.clear();
  offset6.push_back(make_pair(82, SN(25, rn, 64).get_sn()));
  offset6.push_back(make_pair(238, SN(18, rn, 64).get_sn()));
  offset6.push_back(make_pair(512, SN(11, rn, 64).get_sn()));

  offset7.clear();
  offset7.push_back(make_pair(41, SN(66, rn, 256).get_sn()));
  offset7.push_back(make_pair(119, SN(46, rn, 256).get_sn()));
  offset7.push_back(make_pair(256, SN(29, rn, 256).get_sn()));

  offset8.clear();
  offset8.push_back(make_pair(21, SN(28, rn, 128).get_sn()));
  offset8.push_back(make_pair(60, SN(19, rn, 128).get_sn()));
  offset8.push_back(make_pair(128, SN(13, rn, 128).get_sn()));
}

void Sim_CBRT::Run(SN& in)
{
  // 演算誤差などを記録するクラス
  auto it = tags_.begin();

  /* 立方根回路 */
  Update_Analyzer((*it), in, CBRT(in)), it++;

  /* 単調なエラーに有効な手法 */
  if(count_flag_)
  Update_Analyzer((*it), in, FixCBRT(in, 2)), it++,
  Update_Analyzer((*it), in, FixCBRT(in, 3)), it++,
  Update_Analyzer((*it), in, FixCBRT(in, 4)), it++,
  Update_Analyzer((*it), in, FixCBRT(in, 5)), it++,
  Update_Analyzer((*it), in, FixCBRT(in, 6)), it++;

  /* 区間分けによる手法 */
  // 最後の区間は0を足す
  //(*it)->Update(in, FixCBRT(in, offset1, randSR)), it++;
  if(inter_flag_)
  Update_Analyzer((*it), in, FixCBRT(in, offset2)), it++,

  // 全ての区間について補正
  Update_Analyzer((*it), in, FixCBRT(in, offset3)), it++,
  Update_Analyzer((*it), in, FixCBRT(in, offset4)), it++,
  Update_Analyzer((*it), in, FixCBRT(in, offset5)), it++,
  Update_Analyzer((*it), in, FixCBRT(in, offset6)), it++,
  Update_Analyzer((*it), in, FixCBRT(in, offset7, 256)), it++,
  Update_Analyzer((*it), in, FixCBRT(in, offset8, 128)), it++;
}