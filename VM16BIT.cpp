#include "VM16BIT.hpp"


#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
/*
int main() {
    // Specify the path to your binary file.
    const std::string filename = "your_binary_file.bin";

    // Open the binary file for reading in binary mode.
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return 1;
    }

    // Create a vector to store pairs of instructions and arguments.
    std::vector<std::pair<int, int>> instructions;

    // Read the binary file word (two bytes) by word (little-endian).
    

    // Close the file.
    file.close();

    // Print the instructions and arguments.
    for (const auto& instruction : instructions) {
        std::cout << "Opcode: " << instruction.first << ", Argument: " << instruction.second << std::endl;
    }

    return 0;
}



*/


VM::~VM() {
    delete[] mem;
}

void VM::loadFile(const char fileName[]) {
    this->file.open(fileName);
}

void VM::lex () {

    uint16_t word;
    while (file.read(reinterpret_cast<char*>(&word), sizeof(word))) {
        int opcode = word & 0xFF;
        int argument = (word >> 8) & 0xFF;

        // Store the opcode and argument as a pair.
        this->inst.emplace_back(opcode, argument);
    }
    /*
    * interpreter mode
    std::string line;
    while (std::getline(this->file, line)) {
        std::string command = line.substr(0, 3);
        std::string remvals = line.substr(3, line.length());

        std::pair<std::string, std::string> insertVal(command, remvals);

        this->inst.insert(this->inst.end(), insertVal);

    }
    */
}

void VM::MOV(short x, short y, bool isVal) {
    if (isVal == true /*When the 'y' is a value*/) {
        this->mem[x] = y;
    }
    else {
        this->mem[x] = this->mem[y];
    }
    
}
    

void VM::ADD(short x, short y) {
    this->mem[x] = this->mem[x] + y;
}

void VM::SUB(short x, short y) {
    this->mem[x] = this->mem[x] - y;
}

void VM::MUL(short x, short y) {
    this->mem[x] = this->mem[x] * y;
}

void VM::DIV(short x, short y) {
    this->mem[x] = this->mem[x] - y;
}

void VM::INT(short x) {
    
}

void VM::DIS(short x) {
    uint8_t valAtX = this->mem[x];
    std::cout << valAtX;
}

void VM::exec() {
    for (std::pair<std::uint16_t, std::uint16_t> com : this->inst) {
        switch (com.first) {

        case Instructions::MOV:

            x = (com.second << 8) & 0xFF;
            y = com.second & 0xFF;

            this->MOV(x, y, 1);
            std::cout << "X is equal to " << x << " and y is equal to " << y;

            break;

        case Instructions::ADD:

            x = (com.second >> 8) & 0xFF;
            y = com.second & 0xFF;

            this->ADD(x, y);
            break;

        default:
            this->DIS(x);
            break;
        }
    }

}

int main(int argc, char* argv[])
{

    VM vm;
    char* fileName = argv[1];
    const char fileNameX[] = "C:/USERS/ASUS/DESKTOP/SUP.bin";/* Change in production */

    vm.loadFile(fileNameX);
    vm.lex();

    vm.exec();
}