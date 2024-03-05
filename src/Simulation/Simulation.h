#pragma once

#include "SN.h"
#include "Analysis/Analysis.h"
#include <ProgressBar>

#include <memory>
#include <chrono>
#include <vector>

class Simulation
{
public:
  /// @brief コンストラクタ
  Simulation();

  /// @brief デストラクタ
  ~Simulation();

  /// @brief 初期化
  virtual void init();

  /// @brief エラーを記録するクラスの呼び出し
  virtual void set_ERR() = 0;

  /// @brief ループ前の処理
  virtual void Config() = 0;

  /// @brief ループ内の処理（1入力）
  virtual void Run(SC::SN& input) {}

  /// @brief ループ内の処理（2入力）
  virtual void Run(SC::SN& rhs, SC::SN& lhs) {}

  /// @brief ループ回数などのパラメータ
  /// @return trials_, rep1Start_, rep1End_, rep2Start_, rep2End_
  virtual std::vector<std::uint32_t> get_Param() { return {trials_, rep1Start_, rep1End_, rep2Start_, rep2End_}; }

protected:
  /// @brief エラーを記録するクラスの呼び出し
  /// @param tag クラスのタグ
  void Call_Analyzer(const std::string& tag);

  /// @brief エラーを記録するクラスの呼び出し
  /// @param tag クラスのタグ
  void Update_Analyzer(const std::string& tag, const SC::SN& input, const SC::SN& output);

  /// @brief エラーを記録するクラスの呼び出し
  /// @param tag クラスのタグ
  void Update_Analyzer(const std::string& tag, const SC::SN& input1, const SC::SN& input2, const SC::SN& output);

  /// @brief for(i = 0; i <= tials_; i++)
  std::uint32_t trials_;

  /// @brief for(i = rep1Start_; i <= rep1End_; i++)
  std::uint32_t rep1Start_;
  
  /// @brief for(i = rep1Start_; i <= rep1End_; i++)
  std::uint32_t rep1End_;
  
  /// @brief for(i = rep2Start_; i <= rep2End_; i++)
  std::uint32_t rep2Start_;
  
  /// @brief for(i = rep2Start_; i <= rep2End_; i++)
  std::uint32_t rep2End_;

  /// @brief Precision Levels
  std::uint32_t N_;

  /// @brief Analyzer's tags
  std::vector<std::string> tags_;

private:
  /// @brief Start Time
  std::chrono::_V2::system_clock::time_point s_time_;

  /// @brief Analyzer
  std::shared_ptr<SC::Analysis> analyzer_;
};