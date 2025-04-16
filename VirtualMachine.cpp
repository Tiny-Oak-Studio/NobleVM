#include "VirtualMachine.h"

namespace Noble::VM
{
	void VirtualMachine::RunFrame(Frame& frame)
    {
		SetFrame(frame);

        while (true)
        {
        	switch (*pc++)
            {
				case Op::Code::Add:
                {
                    const ValueType b = stack.Pop();
					const ValueType a = stack.Pop();
                    stack.Add(a + b);
	            	break;
	            }
        		case Op::Code::Constant:
				{
                    const Address::Single addr = ReadAddress();
                    stack.Add(frame.constants[addr]);
					break;
				}
        		case Op::Code::DefineGlobal:
        		{

					break;
				}
        		case Op::Code::Divide:
				{
					const ValueType b = stack.Pop();
					const ValueType a = stack.Pop();
					stack.Add(a / b);
					break;
				}
        		case Op::Code::Equal:
        		{
					const ValueType b = stack.Pop();
					const ValueType a = stack.Pop();
					stack.Add(a == b);
					break;
				}
        		case Op::Code::False:
				{
					stack.Add(false);
					break;
				}
        		case Op::Code::Greater:
				{
					const ValueType b = stack.Pop();
					const ValueType a = stack.Pop();
                    stack.Add(a > b ? TrueValue : FalseValue);
					break;
				}
        		case Op::Code::Jump:
				{
					const Address::Single offset = ReadAddress();
					pc += offset;
					break;
				}
        		case Op::Code::Less:
				{
					const ValueType b = stack.Pop();
					const ValueType a = stack.Pop();
                    stack.Add(a < b ? TrueValue : FalseValue);
					break;
				}
        		case Op::Code::Multiply:
				{
					const ValueType b = stack.Pop();
					const ValueType a = stack.Pop();
					stack.Add(a * b);
					break;
				}
        		case Op::Code::Negate:
				{
                    stack.Peek(0) *= -1;
					break;
				}
        		case Op::Code::Not:
				{
					const ValueType a = stack.Pop();
                    stack.Add(a ? FalseValue : TrueValue);
					break;
				}
        		case Op::Code::Return:
				{
					return;
				}
        		case Op::Code::Subtract:
				{
					const ValueType b = stack.Pop();
					const ValueType a = stack.Pop();
					stack.Add(a - b);
					break;
				}
        		default: break;
            }
        }
    }

	void VirtualMachine::SetFrame(Frame& frame)
	{
    	currentFrame = &frame;
        pc = currentFrame->ops;
    }

    Address::Single VirtualMachine::ReadAddress()
    {
        Address::Single addr;
        memcpy(&addr, pc, sizeof(addr));
        pc += sizeof(addr) / sizeof(Op::Type);
        return addr;
    }

	bool VirtualMachine::IsFalsey(const ValueType value)
	{
		return IsNull(value) or (IsBool(value) and ToBool(value));
	}
}