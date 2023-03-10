#pragma once

class Define final
{
public:
    // SNのビット長:N，LFSRのビット数:Bを決定
	const static int N = 16;
    const static short B = 4;

    // SNGの擬似乱数生成器のフラグ
    // 0：LFSR，1：nonliner-LFSR
    const static bool PRNG = false;
};