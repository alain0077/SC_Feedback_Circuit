#include "Analysis.h"
#include <cmath>
#include <cfloat>
#include <iostream>
#include <iomanip>

using namespace std;

/// @brief Constractor
Analysis::Analysis() : AbsError(), _max_scc({0.0, 0.0}), _min_scc({-1.0, 0.0}), _scc({1.1, 0.0})
{
}

/// @brief Initialize the parameters
void Analysis::reset()
{
    AbsError::reset();

    _max_scc = {0.0, 0.0};
    _min_scc = {-1.1, 0.0};
    _scc = {1.1, 0.0};
}

/// @brief Update paramerter
/// @param ans Correct answer
/// @param val The value of output SN
/// @param scc SCC of inputs SN
void Analysis::Update_Analysis(double ans, double val, double scc)
{
    Update_Error(ans, val);

    // Compair and Update
    auto p = make_pair(scc, ans - val);
    _max_scc = _max_scc.first > scc ? _max_scc : p;
    _min_scc = _min_scc.first < scc ? _min_scc : p;
    _scc = std::abs(_scc.first) < std::abs(scc) ? _scc : p;
}

/// @brief Print All Parameters
void Analysis::print_Summary() const
{
    AbsError::print_Summary();

    cout << "\n";

    cout << "-----------------------------------" << "\n";
    cout << "|            About SCC            |" << "\n";
    cout << "-----------------------------------" << "\n";
    cout << "------------- Maximum -------------" << "\n";
    cout << "SCC : " << _max_scc.first << "\n";
    cout << "Err : " << setprecision(8) << ((std::abs(_max_scc.second) > DBL_EPSILON) ? _max_scc.second : 0.0) << "\n";
    cout << "------------- Minimum -------------" << "\n";
    cout << "SCC : " << _min_scc.first << "\n";
    cout << "Err : " << setprecision(8) << ((std::abs(_min_scc.second) > DBL_EPSILON) ? _min_scc.second : 0.0) << "\n";
    cout << "--------- Closest to zero ---------" << "\n";
    cout << "SCC : " << _scc.first << "\n";
    cout << "Err : " << setprecision(8) << ((std::abs(_scc.second) > DBL_EPSILON) ? _scc.second : 0.0) << "\n";
}