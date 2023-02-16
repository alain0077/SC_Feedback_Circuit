#include "FeedbackCircuit.h"

using namespace Feedback;

FeedbackCircuit::FeedbackCircuit(Function* output, Function* feedback) :
_Output(output), _Feedback(feedback)
{
}

bool FeedbackCircuit::Run(const bool& input1)
{
    bool F_out = _Feedback->get_Output();
    _Output->Run(F_out, input1);

    bool O_out = _Output->get_Output();
    _Feedback->Run(O_out);

    return O_out;
}

bool FeedbackCircuit::Run(const std::initializer_list<bool>& inputs1)
{
    bool F_out = _Feedback->get_Output();
    auto it = inputs1.begin();
    _Output->Run(F_out, it, ++it);

    bool O_out = _Output->get_Output();
    _Feedback->Run(O_out);

    return O_out;
}

bool FeedbackCircuit::Run(const bool& input1, const bool& input2)
{
    bool F_out = _Feedback->get_Output();
    _Output->Run(F_out, input1);

    bool O_out = _Output->get_Output();
    _Feedback->Run(O_out, input2);

    return O_out;
}

bool FeedbackCircuit::Run(const std::initializer_list<bool>& inputs1, const bool& input2)
{
    bool F_out = _Feedback->get_Output();
    auto it = inputs1.begin();
    _Output->Run(F_out, it, ++it);

    bool O_out = _Output->get_Output();
    _Feedback->Run(O_out, input2);

    return O_out;
}

bool FeedbackCircuit::Run(const bool& input1, const std::initializer_list<bool>& inputs2)
{
    bool F_out = _Feedback->get_Output();
    _Output->Run(F_out, input1);

    bool O_out = _Output->get_Output();
    auto it = inputs2.begin();
    _Feedback->Run(O_out, it, ++it);

    return O_out;
}

bool FeedbackCircuit::Run(const std::initializer_list<bool>& inputs1, const std::initializer_list<bool>& inputs2)
{
    bool F_out = _Feedback->get_Output();
    auto it = inputs1.begin();
    _Output->Run(F_out, it, ++it);

    bool O_out = _Output->get_Output();
    it = inputs2.begin();
    _Feedback->Run(O_out, it, ++it);

    return O_out;
}