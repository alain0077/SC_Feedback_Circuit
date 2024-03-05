#include "AbsError.h"
#include <cmath>
#include <cfloat>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
using namespace SC::err;

/// @brief Constructor
SC::err::AbsError::AbsError() : AbstractError()
{
  time_ = 0u;
  sum_err_ = 0.0;
  per_err_ = 0.0;
  max_abs_ = nullopt;
  min_abs_ = nullopt;
  max_per_ = nullopt;
  min_per_ = nullopt;
}

/// @brief Update the value
/// @param ans Correct value
/// @param val The value of output SN
void SC::err::AbsError::Update(const double& ans, const double& val)
{
  // Count up
  time_++;

  // Absolute Error
  double err = std::abs(ans - val);

  // Absolute Percentage Error
  double per = err / ans;

  // Compair and Update
  max_abs_ = max_abs_ > err ? max_abs_ : err;
  min_abs_ = min_abs_ ? min(min_abs_.value(), err) : err;
  max_per_ = max_per_ > per ? max_per_ : per;
  min_per_ = min_per_ ? min(min_per_.value(), per) : per;

  // Sum of Absolute Error
  sum_err_ += err;

  // Sum of Absolute Percentage Error
  per_err_ += per;
}

/// @brief Update the value
/// @param input
/// @param output 
void SC::err::AbsError::Update(const SN& input, const SN& output)
{
  Update(output.get_ans(), output.get_val());
}

/// @brief Update the value (2 inputs)
/// @param input1
/// @param input2
/// @param output
void SC::err::AbsError::Update(const SN& input1, const SN& input2, const SN& output)
{
  Update(output.get_ans(), output.get_val());
}

/// @brief Reset the parameters
void SC::err::AbsError::reset()
{
  time_ = 0u;
  sum_err_ = 0.0;
  per_err_ = 0.0;
  max_abs_ = nullopt;
  min_abs_ = nullopt;
  max_per_ = nullopt;
  min_per_ = nullopt;
}

/// @brief Retrun All Parameters
/// @return map<tag, data>
map<string, string> SC::err::AbsError::get_Summary() const
{
  map<string, string> res;

  res["Trials"] = to_string(time_);
  res["MAE"] = to_string(sum_err_/double(time_));
  res["MAX AE"] = to_string(max_abs_.value_or(0.0));
  res["MIN AE"] = to_string(min_abs_.value_or(0.0));
  res["MAPE"] = to_string(per_err_/double(time_));
  res["MAX APE"] = to_string(max_per_.value_or(0.0));
  res["MIN APE"] = to_string(min_per_.value_or(0.0));

  return res;
}

void SC::err::AbsError::print_Summary(ostream& os) const
{ 
  os << "-----------------------------------\n";
  os << "╎            About ERR            ╎\n";
  os << "-----------------------------------\n";
  os << " Trials : " +  to_string(time_) + "\n";
  os << "------- Absolute Error (AE) -------\n";
  os << "    MAE : " + to_string(sum_err_/double(time_)) + "\n";
  os << " MAX AE : " + to_string(max_abs_.value_or(0.0)) + "\n";
  os << " MIN AE : " + to_string(min_abs_.value_or(0.0)) + "\n";
  os << "- Absolute Percentage Error (APE) -\n";
  os << "   MAPE : " + to_string(per_err_/double(time_)) + "\n";
  os << "MAX APE : " + to_string(max_per_.value_or(0.0)) + "\n";
  os << "MIN APE : " + to_string(min_per_.value_or(0.0)) + "\n";
}