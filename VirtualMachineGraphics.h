//
// Created by aaron on 25/03/25.
//

#ifndef VIRTUALMACHINEGRAPHICS_H
#define VIRTUALMACHINEGRAPHICS_H

namespace Noble::VM
{
    struct VirtualMachineGraphics
    {
        VirtualMachineGraphics() = default;
        virtual ~VirtualMachineGraphics() = default;

        virtual void Initialise();
        virtual void SetPixel(int x, int y, bool value) = 0;
        virtual bool GetPixel(int x, int y) = 0;
    };
} // Noble::VM

#endif //VIRTUALMACHINEGRAPHICS_H
