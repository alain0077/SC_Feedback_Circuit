#pragma once

#include "Simulation.h"

#include <memory>

class MgrSim final
{
public:
  MgrSim(std::shared_ptr<Simulation> sim);
  ~MgrSim() = default;
  void init();
  void run();

  enum eSimFlag
  {
    TRIAL_IN1,
    TRIAL_IN2,
  };

  void set_flag(eSimFlag flag) { eSimFlag_ = flag; }

  /// @brief 1入力用
  void trial_in1();

  /// @brief 2入力用
  void trial_in2();
  
private:
  /// @brief Sim flag
  eSimFlag eSimFlag_;

  /* Gaming */
  bool gaming_flag_;

  /* Progress Bar */
  bool prog_flag_;
  bool sim_flag_;
  std::vector<std::shared_ptr<pbr::pbar>> pbv_;

  std::uint32_t get_sim_cnt() { return sim_cnt_; }
  std::uint32_t get_rep1() { return rep1_; }
  std::uint32_t get_rep2() { return rep2_; }

  /* Params */
  uint32_t trials_;
  uint32_t sim_cnt_;
  uint32_t rep1Start_;
  uint32_t rep1End_;
  uint32_t rep1_;
  uint32_t rep2Start_;
  uint32_t rep2End_;
  uint32_t rep2_;

  /* Simulator */
  std::shared_ptr<Simulation> ptr_;
};