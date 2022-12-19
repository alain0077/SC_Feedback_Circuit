#include "AbsError.h"

/// @brief Constructor
AbsError::AbsError() : _sum_err(0.0), _per_err(0.0), _time(0)
{
}

/// @brief Update the value
/// @param ans Correct value
/// @param val The value of output SN
void AbsError::Update_Error(double ans, double val)
{
    // Count up
    _time++;

    // Absolute Error
    double err = std::abs(ans - val);

    // Sum of Absolute Error
    _sum_err += err;

    // Sum of Absolute Percentage Error
    _per_err += err / ans;
}

/// @brief Reset the parameters
void AbsError::reset()
{
    _sum_err = 0.0;
    _per_err = 0.0;
    _time = 0;
}