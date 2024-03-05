#pragma once
#include "../SN.h"
#include <fstream>
#include <iostream>
#include <map>

namespace SC {
namespace err {
  // holds the error
  class AbstractError
  {
  public:
    /// @brief Constructor
    AbstractError() {};
    virtual ~AbstractError() = default;

    /// @brief Update the value
    /// @param input
    /// @param output 
    virtual void Update(const SN& input, const SN& output) = 0;

    /// @brief Update the value (2 inputs)
    /// @param input1
    /// @param input2
    /// @param output
    virtual void Update(const SN& input1, const SN& input2, const SN& output) = 0;

    /// @brief Reset the parameters
    virtual void reset() = 0;

    /// @brief Print All Parameters
    /// @note print to std::cout
    virtual void print_Summary() const { print_Summary(std::cout); }

    /// @brief Print All Parameters to ostream os
    /// @note implement this
    virtual void print_Summary(std::ostream& os) const = 0;

    /// @brief Retrun All Parameters
    /// @return map<tag, data>
    virtual std::map<std::string, std::string> get_Summary() const = 0;

    /// @brief Save Parameter to the File
    virtual void Save_Param() const {};
  };
} // namespace err
} // namespace SC