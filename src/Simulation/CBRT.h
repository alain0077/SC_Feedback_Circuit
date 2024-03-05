#pragma once
#include "Simulation.h"

class Sim_CBRT : public Simulation
{
public:
  /// @brief Constructor
  Sim_CBRT();

  /// @brief Destructor
  ~Sim_CBRT() = default;

  /// @brief エラーを記録するクラスの呼び出し
  virtual void set_ERR() override;

  /// @brief ループ前の処理
  virtual void Config() override;

  /// @brief ループ内の処理（1入力）
  virtual void Run(SC::SN& input) override;

private:
  /* シミュレーションのフラグ */
  bool count_flag_;
  bool inter_flag_;

  /* ループ前の処理の変数 */
  std::vector<std::pair<int, std::vector<bool>>> offset1;
  std::vector<std::pair<int, std::vector<bool>>> offset2;
  std::vector<std::pair<int, std::vector<bool>>> offset3;
  std::vector<std::pair<int, std::vector<bool>>> offset4;
  std::vector<std::pair<int, std::vector<bool>>> offset5;
  std::vector<std::pair<int, std::vector<bool>>> offset6;
  std::vector<std::pair<int, std::vector<bool>>> offset7;
  std::vector<std::pair<int, std::vector<bool>>> offset8;  
};