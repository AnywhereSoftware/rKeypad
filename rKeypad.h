#pragma once
#include "B4RDefines.h"
#include "Keypad.h"
namespace B4R {
	
	//~Version: 1.00
	//~Event: KeyPressed (Key As String)
	//~shortname: Keypad
	/**
	*This library is based on "Keypad Library for Arduino".
	*It monitors the state of a connected keypad.
	*/
	class B4RKeypad {
		private:
			Keypad* kp;
			uint8_t backend[sizeof(Keypad)];
			typedef void (*SubVoidB4RString)(B4RString* Key) ;
			SubVoidB4RString KeyPressedSub;
			static void looper(void* b);
			PollerNode pnode;
		public:
			//Initializes the keypad and starts monitoring the keys state.
			//Keys - A string with the keys characters, one row after another.
			//RowPins - The row pins.
			//ColPins - The column pins.
			//KeyPressedSub - Sub that will handle the KeyPressed event.
			void Initialize(B4RString* Keys, ArrayByte* RowPins, ArrayByte* ColPins, SubVoidB4RString KeyPressedSub);
   
	};
}