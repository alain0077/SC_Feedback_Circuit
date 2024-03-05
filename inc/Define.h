#pragma once

namespace Define
{
  // SNの精度
  constexpr unsigned short N = 256;

  // Simulatorのフラグ（1入力は0，2入力は1）
  constexpr unsigned short eSIMFLAG = 0u;

  // SRの深さ
  constexpr unsigned int SQRT_SR_DEPTH = 10;
  constexpr unsigned int CBRT_SR_DEPTH = 10;

  // 乱数生成器の最小値と最大値
  constexpr unsigned short MIN = 1;
  constexpr unsigned short MAX = 1023;

  // SNGの擬似乱数生成器のフラグ
  // 0：LFSR，1：nonliner-LFSR
  constexpr bool PRNG = false;

  // 標準出力のフラグ
  constexpr bool STDOUT = true;

  // Gaming フラグ
  constexpr bool GAMINGFLAG = false;
};
