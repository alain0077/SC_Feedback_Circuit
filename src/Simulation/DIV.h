#pragma once
#include "Simulation.h"

class Sim_DIV : public Simulation
{
public:
  /// @brief Constructor
  Sim_DIV();

  /// @brief Destructor
  ~Sim_DIV() = default;

  /// @brief エラーを記録するクラスの呼び出し
  virtual void set_ERR() override;

  /// @brief ループ前の処理
  virtual void Config() override;

  /// @brief ループ内の処理（2入力）
  virtual void Run(SC::SN& rhs, SC::SN& lhs) override;

private:
};