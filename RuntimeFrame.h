#ifndef RUNTIMEFRAME_H_INCLUDED
#define RUNTIMEFRAME_H_INCLUDED

#include <vector>

#include "NobleCore/Op.h"
#include "NobleCore/Value.h"
#include "NobleCore/Address.h"

using namespace Noble::Core;

namespace Noble::VM
{
    struct Frame
    {
        std::vector<Op::Type> ops;
        std::vector<Runtime::ValueType> constants;
    };
}

#endif //RUNTIMEFRAME_H_INCLUDED
