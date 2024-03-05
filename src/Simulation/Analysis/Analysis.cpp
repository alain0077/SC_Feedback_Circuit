#include "Analysis.h"
#include "AbsError.h"
#include "Input.h"
#include "SCC.h"
#include "CreateTable.h"

#define STDOUT Define::STDOUT

using namespace std;
using namespace SC::err;

namespace {
  enum eErrFlag
  {
    ABSERR,
    PARERR,
    MAXABS,
    eErrFlagNum
  };

  constexpr bool PRINT_SUMMARY = false;
}

/// @brief Constrctor
SC::Analysis::Analysis()
{
  SortFlag_ = eErrFlag::eErrFlagNum;
}

SC::Analysis::~Analysis()
{
  for(auto err : ERRs_)
    for(auto e : err.second)
  {
    if(STDOUT && PRINT_SUMMARY) e->print_Summary();
    e->Save_Param();
  }

  Save();
  if(STDOUT) Draw();
}

void SC::Analysis::push_back(const std::string& tag)
{
  // Call Analyzer
  ERRs_[tag].push_back(make_shared<AbsError>());
  ERRs_[tag].push_back(make_shared<InputError>(tag));
  if(Define::eSIMFLAG == 1u) ERRs_[tag].push_back(make_shared<SCCError>());
  /*****************
   * Add from here *
   *****************/
  /*code*/
}

/// @brief Update the value
/// @param input
/// @param output
void SC::Analysis::Update(const string& tag, const SN& input, const SN& output)
{
  for(auto e : ERRs_[tag]) e->Update(input, output);
}

/// @brief Update the value (2 inputs)
/// @param input1
/// @param input2
/// @param output
void SC::Analysis::Update(const string& tag, const SN& input1, const SN& input2, const SN& output)
{
  for(auto e : ERRs_[tag]) e->Update(input1, input2, output);
}

void SC::Analysis::Save()
{
  // About Absolute Error
  ofstream ofs("rst/Abs_.csv");

  ofs << "TAG"  << ",";
  ofs << "MAE"  << "," << "MAX AE"  << "," << "MIN AE" << ",";
  ofs << "MAPE" << "," << "MAX APE" << "," << "MIN APE";
  ofs << endl;

  for(auto err : ERRs_)
  {
    auto param = err.second[0]->get_Summary();

    ofs << err.first << ",";
    ofs << param["MAE"]  << "," << param["MAX AE"]  << "," << param["MIN AE"] << ",";
    ofs << param["MAPE"] << "," << param["MAX APE"] << "," << param["MIN APE"];
    ofs << endl;
  }

  ofs.close();

  ofs.open("rst/Abs_Table_.txt");
  tools::CreateTable table("rst/Abs_.csv");

  optional<string> tag = nullopt;
  switch (SortFlag_)
  {
  case eErrFlag::ABSERR:
    tag = "MAE";
    break;
  case eErrFlag::PARERR:
    tag = "MAPE";
    break;
  case eErrFlag::MAXABS:
    tag = "MAX AE";
    break;
  default:
    break;
  }

  table_ = table.get_Table(tag);
  ofs << table_;
  ofs.close();

  // About Absolute Error
  if(Define::eSIMFLAG == 1u)
  {
    ofstream ofs("rst/SCC_.csv");

    ofs << "TAG" << "," << "AVG" << ",";
    ofs << "MAX SCC"  << "," << "MAX ERR"  << "," << "MIN SCC" << ",";
    ofs << "MIN ERR" << "," << "CLOSE0 SCC" << "," << "CLOSE0 ERR";
    ofs << endl;

    for(auto err : ERRs_)
    {
      auto param = err.second[2]->get_Summary();

      ofs << err.first << "," << param["AVG"] << ",";
      ofs << param["MAX SCC"] << "," << param["MAX ERR"] << ",";
      ofs << param["MIN SCC"] << "," << param["MIN ERR"] << ",";
      ofs << param["CLOSE0 SCC"] << "," << param["CLOSE0 ERR"];
      ofs << endl;
    }

    ofs.close();

    ofs.open("rst/SCC_Table_.txt");
    tools::CreateTable table("rst/SCC_.csv");
    ofs << table.get_Table();
  }
}

/// @brief Print Sorted Results
void SC::Analysis::Draw() const
{
  cout << table_ << flush;
}