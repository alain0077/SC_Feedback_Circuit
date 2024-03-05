#include "FeedbackCircuit.h"

using namespace std;
using namespace Circuit;

/// @brief Constructor
FeedbackCircuit::FeedbackCircuit()
{
    Output_ = make_shared<Circuit>();
    Feedback_ = make_shared<Circuit>();
}

/// @brief Destructor
FeedbackCircuit::~FeedbackCircuit()
{
    Output_.reset();
    Feedback_.reset();
}

bool FeedbackCircuit::Run(const bool& input1)
{
    bool F_out = Feedback_->get_Output();
    Output_->Run(F_out, input1);

    bool O_out = Output_->get_Output();
    Feedback_->Run(O_out);

    output_ = O_out;

    return output_;
}

bool FeedbackCircuit::Run(const std::initializer_list<bool>& inputs1)
{
    bool F_out = Feedback_->get_Output();
    auto it = inputs1.begin();
    Output_->Run(F_out, it, *(it+1));

    bool O_out = Output_->get_Output();
    Feedback_->Run(O_out);

    output_ = O_out;

    return O_out;
}

bool FeedbackCircuit::Run(const bool& input1, const bool& input2)
{
    bool F_out = Feedback_->get_Output();
    Output_->Run(F_out, input1);

    bool O_out = Output_->get_Output();
    Feedback_->Run(O_out, input2);

    output_ = O_out;

    return output_;
}

bool FeedbackCircuit::Run(const std::initializer_list<bool>& inputs1, const bool& input2)
{
    bool F_out = Feedback_->get_Output();
    auto it = inputs1.begin();
    Output_->Run(F_out, *it, *(it+1));

    bool O_out = Output_->get_Output();
    Feedback_->Run(O_out, input2);

    output_ = O_out;

    return O_out;
}

bool FeedbackCircuit::Run(const bool& input1, const std::initializer_list<bool>& inputs2)
{
    bool F_out = Feedback_->get_Output();
    Output_->Run(F_out, input1);

    bool O_out = Output_->get_Output();
    auto it = inputs2.begin();
    Feedback_->Run(O_out, *it, *(it+1));

    output_ = O_out;

    return O_out;
}

bool FeedbackCircuit::Run(const std::initializer_list<bool>& inputs1, const std::initializer_list<bool>& inputs2)
{
    bool F_out = Feedback_->get_Output();
    auto it1 = inputs1.begin();
    Output_->Run(F_out, *it1, *(it1+1));

    bool O_out = Output_->get_Output();
    auto it2 = inputs2.begin();
    Feedback_->Run(O_out, *it2, *(it2+1));

    output_ = O_out;

    return O_out;
}