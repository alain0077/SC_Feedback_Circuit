#include "SCC.h"
#include <cmath>
#include <cfloat>
#include <iostream>
#include <iomanip>

using namespace std;

/// @brief Constructor
SC::err::SCCError::SCCError() : AbstractError()//, max_scc_({-1.1, 0.0}), min_scc_({1.1, 0.0}), scc_({1.1, 0.0}), sum_scc_(0.0), time_(0)
{
  reset();
}

/// @brief Initialize the parameters
void SC::err::SCCError::reset()
{
  max_scc_ = {-1.1, 0.0};
  min_scc_ = {1.1, 0.0};
  scc_ = {1.1, 0.0};
  sum_scc_ = 0.0;
  time_ = 0u;
}

/// @brief Update paramerter
/// @param ans Correct answer
/// @param val The value of output SN
/// @param scc SCC of inputs SN
/// @note Error is calculated by (output.ans - output.val)
void SC::err::SCCError::Update(const double& ans, const double& val, const double& scc)
{
  // Count up
  time_++;

  // Compair and Update
  auto p = make_pair(scc, ans - val);
  if(std::abs(max_scc_.first - scc) < DBL_EPSILON) max_scc_ = std::abs(max_scc_.second) > std::abs(p.second) ? max_scc_ : p;
  max_scc_ = max_scc_.first > scc ? max_scc_ : p;
  if(std::abs(min_scc_.first - scc) < DBL_EPSILON) min_scc_ = std::abs(min_scc_.second) > std::abs(p.second) ? min_scc_ : p;
  min_scc_ = min_scc_.first < scc ? min_scc_ : p;
  if(std::abs(scc_.first - scc) < DBL_EPSILON) scc_ = std::abs(scc_.second) > std::abs(p.second) ? scc_ : p;
  scc_ = std::abs(scc_.first) < std::abs(scc) ? scc_ : p;
  
  sum_scc_ += scc;
}

/// @brief Update the value (2 inputs)
/// @param input1
/// @param input2
/// @param output
/// @note Error is calculated by (output.ans - output.val)
void SC::err::SCCError::Update(const SN& input1, const SN& input2, const SN& output)
{
  Update(output.get_ans(), output.get_val(), SCC(input1, input2));
}

/// @brief Retrun All Parameters
/// @return string
map<string, string> SC::err::SCCError::get_Summary() const
{
  map<string, string> res;

  res["AVG"] = to_string(sum_scc_ / static_cast<double>(time_));
  res["MAX SCC"] = to_string(max_scc_.first);
  res["MAX ERR"] = to_string(max_scc_.second);
  res["MIN SCC"] = to_string(min_scc_.first);
  res["MIN ERR"] = to_string(min_scc_.second);
  res["CLOSE0 SCC"] = to_string(scc_.first);
  res["CLOSE0 ERR"] = to_string(scc_.second);

  return res;
}

/// @brief Print All Parameters to ostream os
void SC::err::SCCError::print_Summary(std::ostream& os) const
{
  os << "-----------------------------------\n";
  os << "╎            About SCC            ╎\n";
  os << "-----------------------------------\n";
  os << "avg : " + to_string(sum_scc_ / static_cast<double>(time_)) + "\n";
  os << "------------- Maximum -------------\n";
  os << "SCC : " + to_string(max_scc_.first) + "\n";
  os << "Err : " + to_string(max_scc_.second) + "\n";
  os << "------------- Minimum -------------\n";
  os << "SCC : " + to_string(min_scc_.first) + "\n";
  os << "Err : " + to_string(min_scc_.second) + "\n";
  os << "--------- Closest to zero ---------\n";
  os << "SCC : " + to_string(scc_.first) + "\n";
  os << "Err : " + to_string(scc_.second) + "\n";
}

