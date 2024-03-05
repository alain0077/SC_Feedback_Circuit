#include "Input.h"
#include <cmath>
#include <cfloat>
#include <iostream>
#include <iomanip>

using namespace std;


/// @brief Constructor
SC::err::InputError::InputError() : InputError("")
{
}

/// @brief Constructor
/// @param t tag
SC::err::InputError::InputError(string t) : AbstractError(), N_(nullopt), tag_(t+"_")
{
}

/// @brief Initialize the parameters
void SC::err::InputError::reset()
{
  N_ = nullopt;
  seed1_ = nullopt;
  seed2_ = nullopt;
  tag_ = "";
  err_.clear();
  err_minmax_.clear();
  err_2_.clear();
  err_2_minmax_.clear();
}

/// @brief Update the value
/// @param val input SN's value
/// @param err error
void SC::err::InputError::Update(const double& val, const double& err)
{
  InputErrorData data = {err, seed1_};
  auto it = err_.find(val);
  if(it == err_.end())
  {
    err_.emplace(val, make_pair(err, 1));
    err_minmax_.emplace(val, make_pair(data, data));
  }
  else 
  {
    err_[val].first += err;
    err_[val].second++;

    // Update min and max
    err_minmax_[val].first = std::min(err_minmax_[val].first, data);
    err_minmax_[val].second = std::max(err_minmax_[val].second, data);
  }
}

/// @brief Update the value (2 input)
/// @param val1 input SN's value
/// @param val2 input SN's value
/// @param err error
void SC::err::InputError::Update(const double& val1, const double& val2, const double& err)
{
  InputErrorData data = {err, seed1_, seed2_};
  auto it = err_2_.find(val1);
  if(it == err_2_.end())
  {
    err_2_[val1][val2] = make_pair(err, 1);
    err_2_minmax_[val1][val2] = make_pair(data, data);
  }
  else
  {
    auto it2 = it->second.find(val2);
    if(it2 == it->second.end())
    {
      err_2_[val1][val2] = make_pair(err, 1);
      err_2_minmax_[val1][val2] = make_pair(data, data);
    }
    else
    {
      it2->second.first += err;
      it2->second.second++;
      
      // Update min and max
      err_2_minmax_[val1][val2].first = std::min(err_2_minmax_[val1][val2].first, data);
      err_2_minmax_[val1][val2].second = std::max(err_2_minmax_[val1][val2].second, data);
    }
  }
}

/// @brief Update the value
/// @param input
/// @param output 
void SC::err::InputError::Update(const SN& input, const SN& output)
{
  // Calculate Error
  double err = std::abs(output.get_ans() - output.get_val());

  // Save Output
  out_[input.get_ans()].first += output.get_val();
  out_[input.get_ans()].second++;

  // Save Bit Length
  if(!N_) N_ = static_cast<decltype(N_)>(output.size());

  // Save Input's Seed
  seed1_ = input.get_seed();

  Update(input.get_ans(), err);
}

/// @brief Update the value (2 inputs)
/// @param input1
/// @param input2
/// @param output
void SC::err::InputError::Update(const SN& input1, const SN& input2, const SN& output)
{
  // Calculate Error
  double err = std::abs(output.get_ans() - output.get_val());

  // // Save Output
  out_2_[input1.get_ans()][input2.get_ans()].first += output.get_val();
  out_2_[input1.get_ans()][input2.get_ans()].second++;

  // Save Bit Length
  if(!N_) N_ = output.size();

  // Save Input's Seed
  seed1_ = input1.get_seed();
  seed2_ = input2.get_seed();

  Update(input1.get_ans(), input2.get_ans(), err);
}

/// @brief Retrun All Parameters
/// @return string
map<string, string> SC::err::InputError::get_Summary() const
{
  map<string, string> res;

  return res;
}

/// @brief Print All Parameters to ostream os
void SC::err::InputError::print_Summary(std::ostream& ofs) const
{
  if(err_.size() != err_minmax_.size() || err_2_.size() != err_2_minmax_.size())
  {
    throw std::runtime_error("InputError::Save_Param データサイズが一致しません");
    return;
  }

  if(err_.size() != 0) print_Summary_1(ofs);
  else print_Summary_2(ofs);
}

void SC::err::InputError::print_Summary_1(ostream& ofs) const
{
  auto it1 = begin(err_);
  auto end1 = end(err_);
  auto it2 = begin(err_minmax_);
  auto end2 = end(err_minmax_);
  auto it3 = begin(out_);
  auto end3 = end(out_);

  ofs << "INPUT" << ",";

  if(N_) ofs << "OUTPUT" << ",";

  ofs << "ERROR" << "," << "MIN" << "," << "MAX";

  if(N_) ofs << "," << "MIN_SEED" << "," << "MAX_SEED";

  ofs << endl;

  for(;it1 != end1 && it2 != end2; it1++, it2++)
  {
    auto p1 = it1->second;
    auto p2 = it2->second;

    // INPUT
    ofs << it1->first << ",";

    // OUTPUT
    if(N_ && it3 != end3)
    {
      auto p3 = it3->second;
      ofs << p3.first / (double)(p3.second) << ",";
      it3++;
    }

    // ERROR MIN MAX
    ofs << p1.first / (double)(p1.second) << "," << p2.first.err << "," << p2.second.err;

    // MIN_SEED MAX_SEED
    if(N_) ofs << "," << p2.first.seed1.value_or(-1) << "," << p2.second.seed1.value_or(-1);

    ofs  << endl;
  }
}

void SC::err::InputError::print_Summary_2(ostream& ofs) const
{
  ofs << "INPUT1" << "," << "INPUT2" << ",";

  if(N_) ofs << "OUTPUT" << ",";

  ofs << "ERROR" << "," << "MIN" << "," << "MAX";

  if(N_) ofs << "," << "MIN_SEED1" << "," << "MIN_SEED2" << "," << "MAX_SEED1" << "," << "MAX_SEED2";

  ofs << endl;

  for(auto m : err_2_)
  {
    for(auto p : m.second)
    {
      auto in1 = m.first;
      auto in2 = p.first;

      // INPUT1 INPUT2
      ofs << in1 << "," << in2 << ",";

      // OUTPUT
      if(N_)
      {
        auto p1 = out_2_.at(in1).at(in2);
        ofs << p1.first / (double)(p1.second) << ",";
      }

      // ERROR MIN MAX
      auto p2 = err_2_.at(in1).at(in2);
      auto p3 = err_2_minmax_.at(in1).at(in2);
      ofs << p2.first / (double)(p2.second) << "," << p3.first.err << "," << p3.second.err;

      // MIN_SEED1 MIN_SEED2 MAX_SEED1 MAX_SEED2
      if(N_)
        ofs << "," << p3.first.seed1.value_or(-1) << "," << p3.first.seed2.value_or(-1),
        ofs << "," << p3.second.seed1.value_or(-1) << "," << p3.second.seed2.value_or(-1);

      ofs  << endl;
    }
  }
}

/// @brief Save Parameter to the File
void SC::err::InputError::Save_Param() const
{
  string n = "";
  if(N_) n = "_" + to_string(N_.value());

  ofstream ofs("rst/Input_" + tag_ + n + "_bit.csv");

  print_Summary(ofs);
}

