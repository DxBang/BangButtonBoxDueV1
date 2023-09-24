// Game Profile: NoFunctions
#ifndef BANG_h
	#include "Bang.h"
#endif

class NoFunctions : public Game {
	public:
		void button(unsigned char pin, bool pressed) override {}
		void begin() override {}
		void end() override {}
};