#include "Simulation.h"
#include <Define.h>

#include <iostream>

#define STDOUT Define::STDOUT

using namespace std;
using namespace chrono;
using namespace SC;

/// @brief Constructor
/// @param n Precision Levels
Simulation::Simulation()
{
  N_ = Define::N;
  s_time_ = system_clock::now();  
  analyzer_ = make_shared<SC::Analysis>();
}

/// @brief Destructor
Simulation::~Simulation()
{
  if(STDOUT)
  {
    // 終了時間
    auto end = system_clock::now();
    auto dur = end - s_time_;
    auto msec = duration_cast<milliseconds>(dur).count();
    cout << "time : " << msec << "[ms]" << endl;
  }

  analyzer_.reset();
}

void Simulation::init()
{
  analyzer_.reset();
  analyzer_ = make_shared<SC::Analysis>();
  s_time_ = system_clock::now();
}

void Simulation::Call_Analyzer(const string& tag)
{
  tags_.push_back(tag);
  analyzer_->push_back(tags_.back());
}

void Simulation::Update_Analyzer(const string& tag, const SN& input, const SN& output)
{
  analyzer_->Update(tag, input, output);
}

void Simulation::Update_Analyzer(const std::string& tag, const SC::SN& input1, const SC::SN& input2, const SC::SN& output)
{
  analyzer_->Update(tag, input1, input2, output);
}