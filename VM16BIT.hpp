#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>

short x;
short y;

struct Instructions {
	static const int MOV = 0b11000110;
	static const int INT = 0b11001100;
	static const int HLT = 0b11110000;
	static const int ADD = 0b00000000;  // Note: Corrected binary representation
	static const int SUB = 0b00101000;
	static const int MUL = 0b11110100;  // Note: Corrected binary representation
	static const int DIV = 0b11110101;  // Note: Corrected binary representation
};

class VM {

public:

	void exec();
	void lex();
	void loadFile(const char fileName[]);

	void ADD(short x, short y);
	void SUB(short x, short y);
	void MUL(short x, short y);
	void DIV(short x, short y);

	void MOV(short x, short y, bool isVal);
	void INT(short val);

	void DIS(short x);

	~VM();

private:
	std::ifstream file;
	std::vector<std::pair<uint16_t, uint16_t>> inst;

    uint8_t* mem = new uint8_t[65536];

	short ax;
	short bx;
	short cx;
	short dx;

};