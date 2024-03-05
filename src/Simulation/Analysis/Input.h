#pragma once
#include "AbstractError.h"
#include <map>
#include <optional>
#include <set>

namespace SC {
namespace err {
  struct InputErrorData
  {
    double err;
    std::optional<std::uint16_t> seed1;
    std::optional<std::uint16_t> seed2;
  };

  inline bool operator<(const InputErrorData& lhs, const InputErrorData& rhs) { return lhs.err < rhs.err; };
  inline bool operator>(const InputErrorData& lhs, const InputErrorData& rhs) { return rhs < lhs; }
  inline bool operator<=(const InputErrorData& lhs, const InputErrorData& rhs) { return !(lhs > rhs); }
  inline bool operator>=(const InputErrorData& lhs, const InputErrorData& rhs) { return !(lhs < rhs); }

  // holds the error
  class InputError : public AbstractError
  {
  private:
    /// @brief bit length
    std::optional<std::uint16_t> N_;

    /// @brief tag
    std::string tag_;

    /// @brief Output for Input
    std::map<double, std::pair<double, std::uint32_t>> out_;
    
    /// @brief Sum Error per input
    std::map<double, std::pair<double, std::uint32_t>> err_;

    /// @brief MIN or MAX Error per input
    /// @note pair<MIN, MAX>
    std::map<double, std::pair<InputErrorData, InputErrorData>> err_minmax_;

    /// @brief Output for 2 Inputs
    std::map<double, std::map<double, std::pair<double, std::uint32_t>>> out_2_;

    /// @brief Sum Error per 2 inputs
    std::map<double, std::map<double, std::pair<double, std::uint32_t>>> err_2_;

    /// @brief MIN or MAX Error per 2 inputs
    /// @note pair<MIN, MAX>
    std::map<double, std::map<double, std::pair<InputErrorData, InputErrorData>>> err_2_minmax_;

    /// @brief Input's Seed
    std::optional<std::uint16_t> seed1_;
    /// @brief Input's Seed
    std::optional<std::uint16_t> seed2_;

    /// @brief Print Summary for 1 input
    void print_Summary_1(std::ostream& os) const;

    /// @brief Print Summary for 2 input
    void print_Summary_2(std::ostream& os) const;

  public:
    /// @brief Constructor
    InputError();

    /// @brief Constructor
    /// @param tag tag
    InputError(std::string tag);

    /// @brief Destructor
    virtual ~InputError() { reset(); }

    /// @brief Update the value
    /// @param val input SN's value
    /// @param err error
    void Update(const double& val, const double& err);

    /// @brief Update the value (2 input)
    /// @param val1 input SN's value
    /// @param val2 input SN's value
    /// @param err error
    void Update(const double& val1, const double& val2, const double& err);

    /// @brief Update the value
    /// @param input
    /// @param output 
    void Update(const SN& input, const SN& output) override;

    /// @brief Update the value (2 inputs)
    /// @param input1
    /// @param input2
    /// @param output
    void Update(const SN& input1, const SN& input2, const SN& output) override;

    /// @brief Reset the parameters
    void reset() override;

    /// @brief set tag
    /// @param tag tag 
    void set_tag(std::string& tag) { tag_ = tag; }

    /// @brief Retrun All Parameters
    /// @return map<tag, data>
    virtual std::map<std::string, std::string> get_Summary() const override;

    /// @brief Print All Parameters
    virtual void print_Summary() const override {}

    /// @brief Print All Parameters to ostream os
    virtual void print_Summary(std::ostream& os) const override;

    /// @brief Save Parameter to the File
    virtual void Save_Param() const;
  };
} // namespace err
} // namespace SC