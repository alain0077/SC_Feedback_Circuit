#pragma once
#include "AbstractError.h"
#include <string>
#include <map>
#include <memory>
#include <vector>

namespace SC {
  class Analysis final
  {
  private:
    /// @brief Analyzers
    std::map<std::string, std::vector<std::shared_ptr<err::AbstractError>>> ERRs_;

    /// @brief Sort Falg
    std::uint8_t SortFlag_;

    /// @brief Table of Sorted Results
    std::string table_;

  public:
    /// @brief Constructor
    Analysis();

    /// @brief Destructor
    virtual ~Analysis();

    /// @brief Call Analyzers
    /// @param tag tag
    void push_back(const std::string& tag);

    /// @brief Update the value
    /// @param input
    /// @param output
    void Update(const std::string& tag, const SN& input, const SN& output);

    /// @brief Update the value (2 inputs)
    /// @param input1
    /// @param input2
    /// @param output
    void Update(const std::string& tag, const SN& input1, const SN& input2, const SN& output);

    /// @brief Save Results to Files
    void Save();

    /// @brief Print Sorted Results
    void Draw() const;
  };
} // namespace SC