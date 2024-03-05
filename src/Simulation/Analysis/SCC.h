#pragma once
#include "AbstractError.h"
#include <string>
#include <vector>

namespace SC {
namespace err {
  class SCCError : public AbstractError
  {
  private:
    /* 
    * SCC of inputs SN and error at that time
    */
    // Maximum
    std::pair<double, double> max_scc_;
    // Minimum
    std::pair<double, double> min_scc_;
    // Close to 0
    std::pair<double, double> scc_;

    // sum of SCC
    double sum_scc_;

    // Trials
    std::uint32_t time_;

  public:
    /// @brief Constructor
    SCCError();

    /// @brief Destructor
    virtual ~SCCError() { reset(); }

    /// @brief Update paramerter
    /// @param ans Correct answer
    /// @param val The value of output SN
    /// @param scc SCC of inputs SN
    /// @note Error is calculated by (output.ans - output.val)
    void Update(const double& ans, const double& val, const double& scc);

    /// @brief Update the value
    /// @param input
    /// @param output
    /// @note Not use in 1 input
    virtual void Update(const SN& input, const SN& output) {};

    /// @brief Update the value (2 inputs)
    /// @param input1
    /// @param input2
    /// @param output
    /// @note Error is calculated by (output.ans - output.val)
    virtual void Update(const SN& input1, const SN& input2, const SN& output) override;

    /// @brief Initialize the parameters
    void reset();

    /// @brief Return list of SCC and error when SCC is largest, smallest, and closest to zero, respectively.
    /// @return 0 : <maximum, error>, 1 : <minimum, error>, 2 : <close to 0, error>
    std::vector<std::pair<double, double>> get_SCC() { return {max_scc_, min_scc_, scc_}; };

    /// @brief Retrun All Parameters
    /// @return string
    virtual std::map<std::string, std::string> get_Summary() const override;

    /// @brief Print All Parameters to ostream os
    virtual void print_Summary(std::ostream& os) const override;
  };
} // namespace err
} // namespace SC