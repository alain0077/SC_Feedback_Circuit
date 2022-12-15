#include <cmath>

// 絶対誤差を保持するクラス
class AbsError
{
protected:
    // Sum of Absolute Error
    double _sum_err;

    // Sum of Absolute Percentage Error
    double _per_err;

    // 試行回数
    unsigned int _time;

public:
    AbsError();
    virtual ~AbsError() = default;

    // Mean Absolute Error (MAE)
    double get_MAE() {return _sum_err/double(_time); };

    // Mean Absolute Percentage Error (MAPE)
    double get_RAE() { return _per_err/double(_time); };
};