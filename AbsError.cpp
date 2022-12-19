#include "AbsError.h"
#include <cmath>
#include <iostream>

using namespace std;

/// @brief Constructor
AbsError::AbsError() : _time(0), _sum_err(0.0), _per_err(0.0), _
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
    double err = abs(ans - val);

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

/// @brief Print All Parameters
void AbsError::print_Summary() const
{
    cout << "-----------------------" << "\n";
    cout << "|      About ERR      |" << "\n";
    cout << "-----------------------" << "\n";
    cout << " Trials : " << _time << "\n";
    cout << "-- AE --" << "\n";
    cout << "    MAE : " << _sum_err/double(_time) << "\n";
    cout << "MAX  AE : " << _max_abs_err << "\n";
    cout << "MIN  AE : " << _min_abs_err << "\n";
    cout << "-- APE --" << "\n";
    cout << "   MAPE : " << _per_err/double(_time) << "\n";
    cout << "MAX APE : " << _max_per_err << "\n";
    cout << "MIN APE : " << _min_per_err << "\n";
}