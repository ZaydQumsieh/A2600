#include <fstream>
#include <iostream>
#include <iomanip>

#include "disassembler.h"

/* testing opcode parsing with a disassembler */

int get_filesize(std::ifstream& file) {
    //returns the size of the file
    file.seekg(0, file.end);
    int filesize = file.tellg();
    file.seekg(0, file.beg);
    return filesize;
}

void hexdump(char* buffer, int buffersize) {
    //reads from a buffer and outputs data in hexadecimal
    const int numcols = 16;
    int numrows = buffersize / numcols;

    for (int i = 0; i < numrows; i++) {
        //print each row with the number of bytes and a newline after the data
        std::cout << std::hex << std::setfill('0') << std::setw(6);
        std::cout << i << "0 ";
        for (int j = 0; j < numcols; j++) {
            //read 16 bytes from the buffer at a time
            int index = numcols * i + j;
            std::cout << std::hex << std::setfill('0') << std::setw(2);
            std::cout << static_cast<unsigned int>(static_cast<unsigned char>(buffer[index])) << ' ';
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    char* code_buf;

    std::ifstream rom_file(argv[1], std::ifstream::binary);
    if (rom_file.is_open()) {
        // load rom file
        int size = get_filesize(rom_file);
        code_buf = new char[size];
        rom_file.read(code_buf, size);

        // hex dump rom
        std::cout << "== hexdump ==" << std::endl;
        hexdump(code_buf, size);

        std::cout << "== disassembly ==" << std::endl;
        // dump disassembly
        disassemble_rom(code_buf, size);

        rom_file.close();
    } else {
        std::cout << "could not open file" << std::endl;
    }

    return 0;
}
