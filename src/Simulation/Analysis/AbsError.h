#pragma once
#include "AbstractError.h"
#include <optional>

namespace SC {
namespace err {
  // holds the error
  class AbsError : public AbstractError
  {
  private:
    // Sum of Absolute Error
    double sum_err_;

    // Sum of Absolute Percentage Error
    double per_err_;

    // Miximum value of Absolute Error
    std::optional<double> max_abs_;

    // Miximum value of Absolute Percentage Error
    std::optional<double> max_per_;

    // Minimum value of Absolute Error
    std::optional<double> min_abs_;

    // Minimum value of Absolute Percentage Error
    std::optional<double> min_per_;
    
    // Trials
    std::uint32_t time_;

  public:
    /// @brief Constructor
    AbsError();
    virtual ~AbsError() = default;

    /// @brief Update the value
    /// @param ans Correct value
    /// @param val The value of output SN
    virtual void Update(const double& ans, const double& val);

    /// @brief Update the value
    /// @param input
    /// @param output 
    virtual void Update(const SN& input, const SN& output) override;

    /// @brief Update the value (2 inputs)
    /// @param input1
    /// @param input2
    /// @param output
    virtual void Update(const SN& input1, const SN& input2, const SN& output) override;

    /// @brief Reset the parameters
    virtual void reset() override;

    /// @brief Print All Parameters to ostream os
    virtual void print_Summary(std::ostream& os) const override;

    /// @brief Retrun All Parameters
    /// @return map<tag, data>
    virtual std::map<std::string, std::string> get_Summary() const override;
  };
} // namespace err
} // namespace SC