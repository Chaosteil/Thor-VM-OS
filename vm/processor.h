#ifndef _THOR_VM_PROCESSOR_H_
#define _THOR_VM_PROCESSOR_H_

#include "register.h"
#include "value.h"
#include "memory.h"

namespace Thor{
namespace VM{

	class Processor{
		public:
			enum RegType{
				RT_CS = 0, RT_DS = 1, RT_SS = 2, RT_FLAGS = 3, RT_TIME = 4,
				RT_IP = 5, RT_SP = 6, RT_DI = 7, RT_SI = 8,
				RT_AX = 9, RT_BX = 10, RT_CX = 11, RT_DX = 12, RT_R0 = 13, RT_R1 = 14,
				RT_CIR = 15, RT_COR = 16, RT_CDR = 17, RT_PTR = 18, RT_None
			};

			enum OpType{
				OT_Direct = 0,
				OT_In, OT_Out,
				OT_Registers,
				OT_None
			};

			Processor(Memory &memory);
			virtual ~Processor();

			void cycle();

			void setRegister(RegType type, const Value &value);
			Value getRegister(RegType type) const;

			void add(OpType op, RegType left, RegType right, const Value &vleft = Value(0), const Value &vright = Value(0));
			void sub(OpType op, RegType left, RegType right, const Value &vleft = Value(0), const Value &vright = Value(0));
			void cmp(OpType op, RegType left, RegType right, const Value &vleft = Value(0), const Value &vright = Value(0));

			void andOp(OpType op, RegType left, RegType right, const Value &vleft = Value(0), const Value &vright = Value(0));
			void orOp(OpType op, RegType left, RegType right, const Value &vleft = Value(0), const Value &vright = Value(0));
			void xorOp(OpType op, RegType left, RegType right, const Value &vleft = Value(0), const Value &vright = Value(0));

			void mov(OpType op, RegType left, RegType right, const Value &vleft = Value(0), const Value &vright = Value(0));

			void inc(RegType reg);
			void dec(RegType reg);
			void nop();

		private:
			void _opBlockIn(Value &x, Value &y, OpType op, RegType left, RegType right, const Value &vleft, const Value &vright);
			void _opBlockOut(const Value &z, OpType op, RegType left, RegType right, const Value &vleft, const Value &vright);
			OpType _getOpType(char op) const;

			void _parseOp(const std::string &cmd, OpType &op, RegType &left, RegType &right, Value &vleft, Value &vright);
			RegType _parseRT(const std::string &cmd);

			Value _getCommand() const;
			Value _getNumber() const;
			Value _translatePage(const Value &value) const;
			
			bool _parseCommand(const Value &word);

			Register _regs[19];

			Memory &_memory;
	};

}
}

#endif
