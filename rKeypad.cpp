#include "B4RDefines.h"
namespace B4R {
	void B4RKeypad::Initialize(B4RString* Keys, ArrayByte* RowPins, ArrayByte* ColPins, SubVoidB4RString KeyPressedSub) {
		kp = new (backend) Keypad((char*)Keys->data, (Byte*)RowPins->data, (Byte*)ColPins->data, RowPins->length, ColPins->length);
		this->KeyPressedSub = KeyPressedSub;
		FunctionUnion fu;
		fu.PollerFunction = looper;
		pnode.functionUnion = fu;
		pnode.tag = this;
		if (pnode.next == NULL) {
			pollers.add(&pnode);
		}
	}
	//static
	void B4RKeypad::looper(void* b) {
		B4RKeypad* me = (B4RKeypad*) b;
		char c = me->kp->getKey();
		if (c) {
			const UInt cp = B4R::StackMemory::cp;
			B4RString* str = CreateStackMemoryObject(B4RString);
			str->data = (const char*)StackMemory::buffer + StackMemory::cp;
			StackMemory::buffer[StackMemory::cp++] = c;
			StackMemory::buffer[StackMemory::cp++] = 0;
			me->KeyPressedSub(str);
			B4R::StackMemory::cp = cp;
		}
		
	}
}