#include "../RuntimeFrame.h"

namespace Noble::VM
{
    Frame::~Frame()
    {
        delete [] ops;
        delete [] constants;
    }
}