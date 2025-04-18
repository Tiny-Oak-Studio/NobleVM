#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <vector>

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
        ValueType Peek(Address::Single offset = 0) const;
        ValueType Pop();

        static void PrintValue(ValueType value) ;

        std::vector<ValueType> stack;
        std::vector<ValueType> globalVariables;
    };
} // Noble::VM

#endif //VIRTUALMACHINE_H
