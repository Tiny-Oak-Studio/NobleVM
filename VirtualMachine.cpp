#include "VirtualMachine.h"
#include "NobleCore/Debug.h"
#include <iostream>

#define BINARY_OP(op) \
		do { \
			const FloatType a = ToFloat(Pop()); \
			const FloatType b = ToFloat(Pop()); \
			stack.push_back(ToValue(a op b)); \
		} while (false)

namespace Noble::VM
{
	void VirtualMachine::RunFrame(Frame& frame)
    {
		SetFrame(frame);

        while (true)
        {
			#ifdef DEBUG_ENABLED
        	std::cout << static_cast<unsigned>(pc - &frame.ops[0]) << " ";
			#endif

        	switch (*pc++)
            {
				case Op::Code::Add:
                {
                    BINARY_OP(+);
	            	break;
	            }
        		case Op::Code::Constant:
				{
                    const Address::Single addr = ReadAddress();
                    stack.push_back(frame.constants[addr]);
					break;
				}
        		case Op::Code::DefineGlobal:
        		{
					globalVariables.push_back(Pop());
					break;
				}
        		case Op::Code::Divide:
				{
					BINARY_OP(/);
					break;
				}
        		case Op::Code::Equal:
        		{
					BINARY_OP(==);
					break;
				}
        		case Op::Code::False:
				{
					stack.push_back(FalseValue);
					break;
				}
        		case Op::Code::GetGlobal:
        		{
					const Address::Single varAddress = ReadAddress();
					stack.push_back(globalVariables[varAddress]);
					break;
				}
        		case Op::Code::GetLocal:
        		{
					const Address::Single varAddress = ReadAddress();
					stack.push_back(stack[varAddress]);
					break;
				}
        		case Op::Code::Greater:
				{
					BINARY_OP(>);
					break;
				}
        		case Op::Code::GreaterEqual:
				{
					BINARY_OP(>=);
					break;
				}
        		case Op::Code::Jump:
				{
					const Address::Single offset = ReadAddress();
					pc += offset;
					break;
				}
        		case Op::Code::JumpIfFalse:
				{
					const Address::Single offset = ReadAddress();
					if (IsFalsey(Peek()))
					{
						pc += offset;
					}
					break;
				}
        		case Op::Code::JumpIfTrue:
				{
					const Address::Single offset = ReadAddress();
					if (IsTruthy(Peek()))
					{
						pc += offset;
					}
					break;
				}
        		case Op::Code::Less:
				{
					BINARY_OP(<);
					break;
				}
        		case Op::Code::LessEqual:
				{
					BINARY_OP(<=);
					break;
				}
        		case Op::Code::Loop:
				{
					const Address::Single offset = ReadAddress();
					pc -= offset;
					break;
				}
        		case Op::Code::Multiply:
				{
					BINARY_OP(*);
					break;
				}
        		case Op::Code::Negate:
				{
					ValueType val = Peek(0);
                    val = ToValue(ToFloat(val) * -1);
					stack.back() = val;
					break;
				}
        		case Op::Code::Not:
				{
					const ValueType a = stack.back();
					stack.pop_back();
                    stack.push_back(IsTruthy(a) ? FalseValue : TrueValue);
					break;
				}
        		case Op::Code::NotEqual:
        		{
					BINARY_OP(!=);
					break;
				}
        		case Op::Code::Null:
        		{
					stack.push_back(NullValue);
					break;
				}
        		case Op::Code::Pop:
        		{
					stack.pop_back();
					break;
				}
        		case Op::Code::PopN:
        		{
					const Address::Single popCount = ReadAddress();
					for (Address::Single i = 0; i < popCount; ++i)
					{
						stack.pop_back();
					}
					break;
				}
        		case Op::Code::Print:
        		{
					PrintValue(Pop());
					break;
				}
        		case Op::Code::Return:
				{
					return;
				}
        		case Op::Code::SetGlobal:
        		{
					const Address::Single globalAddr = ReadAddress();
					globalVariables[globalAddr] = stack.back();
					break;
				}
        		case Op::Code::SetLocal:
        		{
					const Address::Single localAddr = ReadAddress();
					stack[localAddr] = stack.back();
					break;
				}
        		case Op::Code::Subtract:
				{
					BINARY_OP(-);
					break;
				}
        		case Op::Code::True:
        		{
					stack.push_back(TrueValue);
					break;
				}
        		default: break;
            }
			#ifdef DEBUG_ENABLED
        	std::cout << Debug::OpToString(op) << " ";
        	for (const auto i : stack)
        	{
        		std::cout << "[ ";
        		PrintValue(i);
        		std::cout << " ]";
        	}
        	std::cout << "\n";
			#endif
        }
    }

	void VirtualMachine::SetFrame(Frame& frame)
	{
    	currentFrame = &frame;
        pc = &frame.ops[0];
    }

    Address::Single VirtualMachine::ReadAddress()
    {
        Address::Single addr;
        memcpy(&addr, pc, sizeof(addr));
        pc += sizeof(addr) / sizeof(Op::Type);
        return addr;
    }

	ValueType VirtualMachine::Peek(const Address::Single offset) const
	{
		return stack[stack.size() - offset - 1];
	}

	ValueType VirtualMachine::Pop()
	{
		const ValueType value = stack.back();
		stack.pop_back();
		return value;
	}

	void VirtualMachine::PrintValue(const ValueType value)
	{
		if (IsNull(value)) std::cout << "null";
		else if (IsBool(value)) std::cout << (ToBool(value) ? "true" : "false");
		else if (IsFloat(value)) std::cout << static_cast<float>(ToFloat(value));
	}

}

#undef BINARY_OP