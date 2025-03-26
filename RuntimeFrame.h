#ifndef RUNTIMEFRAME_H_INCLUDED
#define RUNTIMEFRAME_H_INCLUDED

#include "NobleCore/Op.h"
#include "NobleCore/Value.h"
#include "NobleCore/Address.h"

using namespace Noble::Core;

namespace Noble::VM
{
    struct Frame
    {
        ~Frame();

        Op::Type* ops = nullptr;
        Address::Single numOps = 0;

        Runtime::ValueType* constants = nullptr;
        Address::Single numConstants = 0;
    };
}

#endif //RUNTIMEFRAME_H_INCLUDED
