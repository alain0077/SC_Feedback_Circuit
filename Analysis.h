#pragma once

#include "AbsError.h"
#include "SN.h"
#include <string>
#include <vector>

class Analysis : public AbsError
{
private:
    /* 
     * SCC of inputs SN and error at that time
    */
    // Maximum
    std::pair<double, double> _max_scc;
    // Minimum
    std::pair<double, double> _min_scc;
    // Close to 0
    std::pair<double, double> _scc;

protected:
    /// @brief Update paramerter
    /// @param ans Correct answer
    /// @param val The value of output SN
    /// @param scc SCC of inputs SN
    void Update_Analysis(double ans, double val, double scc);

    //void Update_Analysis(double ans, double val, SN input1, SN input2);

public:
    /// @brief Constractor
    Analysis();
    virtual ~Analysis() = default;

    /// @brief Initialize the parameters
    void reset();

    /// @brief Return list of SCC and error when SCC is largest, smallest, and closest to zero, respectively.
    /// @return 0 : <maximum, error>, 1 : <minimum, error>, 2 : <close to 0, error>
    std::vector<std::pair<double, double>> get_SCC() { return {_max_scc, _min_scc, _scc}; };

    /// @brief Print All Parameters
    void print_Summary() const;
};