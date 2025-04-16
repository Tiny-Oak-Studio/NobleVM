#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include "NobleCore/List.h"
#include "NobleCore/Value.h"
#include "RuntimeFrame.h"

using namespace Noble::Core::Runtime;

namespace Noble::VM
{
    class VirtualMachine
    {
    public:
        /// @brief Run the provided frame
        void RunFrame(Frame& frame);

        /// @brief Sets the current VM frame to the provided one
        void SetFrame(Frame& frame);
    protected:
        Frame* currentFrame = nullptr;
        Op::Type* pc = nullptr;

        Address::Single ReadAddress();

        static bool IsFalsey(ValueType value);

        List<ValueType> stack;
    };
} // Noble::VM

#endif //VIRTUALMACHINE_H
