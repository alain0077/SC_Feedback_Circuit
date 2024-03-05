#include "MgrSim.h"

#include "SN.h"
#include <cui>
#include <Define.h>
#include <Gaming>
#include <ProgressBar>
#include <Random>

#include <functional>
#include <thread>

using namespace std;
using namespace tools;
using namespace Define;

MgrSim::MgrSim(shared_ptr<Simulation> sim) : ptr_(sim)
{
  sim_cnt_ = 0u;
  gaming_flag_ = GAMINGFLAG;
  sim_flag_ = true;
  eSimFlag_ = static_cast<eSimFlag>(Define::eSIMFLAG);
}

void MgrSim::init()
{
  sim_cnt_ = 0u;
  sim_flag_ = true;
  eSimFlag_ = static_cast<eSimFlag>(Define::eSIMFLAG);
  pbv_.clear();
  ptr_->init();
}

void MgrSim::run()
{
  // エラークラスの設定
  ptr_->set_ERR();

  // ループ回数などのパラメータの設定
  auto v = ptr_->get_Param();
  trials_ = v[0];
  rep1Start_ = v[1];
  rep1End_ = v[2];
  rep2Start_ = v[3];
  rep2End_ = v[4];

  // Progress Bar
  pbv_.push_back(make_shared<pbr::pbar>(trials_,[this](){ return get_sim_cnt(); }, "Trial"));

  // 1重ループ
  function<void()> sim = [this](){this->trial_in1();};

  // 呼び出す関数の切り替え
  switch (eSimFlag_)
  {
  case eSimFlag::TRIAL_IN1:
    // Progress Bar
    pbv_.push_back(make_shared<pbr::pbar>(rep1End_,[this](){ return get_rep1(); }, "Rep"));
    break;
  case eSimFlag::TRIAL_IN2:
    // Progress Bar
    pbv_.push_back(make_shared<pbr::pbar>(rep1End_,[this](){ return get_rep1(); }, "Rep1"));
    pbv_.push_back(make_shared<pbr::pbar>(rep2End_,[this](){ return get_rep2(); }, "Rep2"));
    // 2重ループに切り替え
    sim = [this](){this->trial_in2();};
    break;
  default:
    throw std::runtime_error("MgrSim::eSimFlag_に無効な値が設定されました");
    return;
    break;
  }

  using namespace pbr;
  using namespace gmg;
  cui::init();
  Gaming::getIns()->init();

  thread th1(
    [this, sim]()
    { 
      for(; sim_cnt_ < trials_; sim_cnt_++)
      {
        sim();
      }

      sim_flag_ = false;
      
      Gaming::getIns()->set_false();
    }
  );
  
  thread th2(
    [this]()
    {
      if(STDOUT)
      {
        while(sim_flag_)
        {
          cout << Gaming::getIns()->get_Clr();
          for(auto pb : pbv_) pb->draw();
          cout << cui::Up(static_cast<uint16_t>(pbv_.size()));
          cout << flush;
        }

        for(auto pb : pbv_) pb->draw();
        cout << flush;
      }
    }
  );

  thread th3([this](){ if(gaming_flag_) Gaming::getIns()->Run(); });

  th1.join();
  th2.join();
  th3.join();

  cui::finit();
}

void MgrSim::trial_in1()
{
  using namespace SC;

  // 乱数生成器
  auto randN = Random(N);

  // 乱数生成
  int rn = randN();

  // ループ前の処理
  ptr_->Config();

  for(rep1_ = rep1Start_; rep1_ <= rep1End_; rep1_++)
  {
    // 入力SNの生成
    SN sn = SN(rep1_, rn, N);

    // ループ内の処理
    ptr_->Run(sn);
  }
}

void MgrSim::trial_in2()
{
  using namespace SC;
  
  // 乱数生成器
  auto randN = Random(N);

  // 乱数生成
  auto rn1 = randN();
  auto rn2 = randN();

  // ループ前の処理
  ptr_->Config();

  for(rep1_ = rep1Start_; rep1_ <= rep1End_; rep1_++)
  {
    // 入力SN1の生成
    SN sn1 = SN(rep1_, rn1, N);

    for(rep2_ = rep2Start_; rep2_ <= rep2End_; rep2_++)
    {
      // 入力SN1の生成
      SN sn2 = SN(rep2_, rn2, N);

      // ループ内の処理
      ptr_->Run(sn1, sn2);
    }
  }
}