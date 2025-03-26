#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include "RuntimeFrame.h"
#include "VirtualMachineGraphics.h"
#include "../NobleCore/List.h"

using namespace Noble::Core::Runtime;

namespace Noble::VM
{
    class VirtualMachine
    {
    public:
        VirtualMachine(VirtualMachineGraphics* graphicsObject);

        /// @brief Run the provided frame
        void RunFrame(Frame& frame);

        /// @brief Sets the current VM frame to the provided one
        void SetFrame(Frame& frame);
    protected:
        //Graphics
        VirtualMachineGraphics* vmGraphics = nullptr;

        Frame* currentFrame = nullptr;
        Op::Type* pc = nullptr;

        Address::Single ReadAddress();

        List<ValueType> stack;
    };
} // Noble::VM

#endif //VIRTUALMACHINE_H
