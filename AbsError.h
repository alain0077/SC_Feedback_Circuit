#include <cmath>

// holds the error
class AbsError
{
private:
    // Sum of Absolute Error
    double _sum_err;

    // Sum of Absolute Percentage Error
    double _per_err;

    // Trials
    unsigned int _time;

protected:
    /// @brief Update the value
    /// @param ans Correct value
    /// @param val The value of output SN
    void Update_Error(double ans, double val);

public:
    /// @brief Constructor
    AbsError();
    virtual ~AbsError() = default;

    /// @brief Reset the parameters
    void reset();
     
    /// @brief Return Mean Absolute Error (MAE)
    /// @return MAE
    double get_MAE() {return _sum_err/double(_time); };

    /// @brief Return Mean Absolute Percentage Error (MAPE)
    /// @return MAPE
    double get_RAE() { return _per_err/double(_time); };
};