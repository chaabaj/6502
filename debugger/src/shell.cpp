/**
 * The MIT License (MIT)

 * Copyright (c) 2016 Chaabane Jalal

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <iostream>
#include <bitset>
#include "shell.hpp"
#include "string-utils.hpp"

Shell::Shell(spi_cpu_t &cpu, spi_byte_t *mem) : _cpu(cpu), _mem(mem) {
    using namespace std::placeholders;

    _commands["reg_read"] = std::bind(&Shell::read_registers, this, _1);
    _commands["reg_write"] = std::bind(&Shell::write_register, this, _1);
    _commands["mem_read"] = std::bind(&Shell::read_memory, this, _1);
    _commands["mem_write"] = std::bind(&Shell::write_memory, this, _1);
    _commands["cpu_state"] = std::bind(&Shell::read_cpu_state, this, _1);
    _commands["next"] = std::bind(&Shell::next_instruction, this, _1);
}

void Shell::execute(std::string const &str) {
    ArgsType args;

    args = tokenize(str);
    std::cout << std::endl;
    if (args.size() > 0 && _commands.find(args[0]) != _commands.cend()) {
        _commands[args[0]](args);
    } else {
        std::cout << "Command not found" << std::endl;
    }
}

void Shell::read_registers(ArgsType const &args) {
    std::cout << "Registers:" << std::endl
              << "X=" << static_cast<uint16_t>(_cpu.registers[X]) << std::endl
              << "Y=" << static_cast<uint16_t>(_cpu.registers[Y]) << std::endl
              << "A=" << static_cast<uint16_t>(_cpu.registers[A]) << std::endl;
}

void Shell::write_register(ArgsType const &args) {
    if (args.size() > 2) {
        spi_byte_t value = static_cast<spi_byte_t>(std::stoi(args[2], 0, 0));

        switch (args[1][0])
        {
        case 'X':
            _cpu.registers[X] = value;
            break;
        case 'A':
            _cpu.registers[A] = value;
            break;
        case 'Y':
            _cpu.registers[Y] = value;
            break;
        default:
            std::cout << "Register must be X, Y or A" << std::endl;
            break;
        }
    } else {
        std::cout << "reg_write X|Y|A <value>" << std::endl;
    }
}

void Shell::read_memory(ArgsType const &args) {
    if (args.size() > 1) {
        spi_mem_addr_t addr = static_cast<spi_mem_addr_t>(std::stoi(args[1], 0, 0));

        std::cout << "mem[" << addr << "]=" << static_cast<uint16_t>(_mem[addr]) << std::endl;
    } else {
        std::cout << "mem_read addr" << std::endl;
    }
}

void Shell::write_memory(ArgsType const &args) {
    if (args.size() > 2) {
        spi_mem_addr_t addr = static_cast<spi_mem_addr_t>(std::stoi(args[1], 0, 0));
        spi_byte_t value = static_cast<spi_byte_t>(std::stoi(args[2], 0, 0));

        _mem[addr] = value;
        std::cout << "mem[" << addr << "]=" << static_cast<uint16_t>(_mem[addr]) << std::endl;
    } else {
        std::cout << "mem_write addr value" << std::endl;
    }
}

void Shell::read_cpu_state(ArgsType const &args) {
    std::cout << "CPU State:" << std::endl
              << "PC=" << _cpu.pc << std::endl
              << "Flags=" << std::bitset<8>(_cpu.flags) << std::endl
              << "SP=" << static_cast<uint16_t>(_cpu.sp) << std::endl
              << "Available cycles=" << _cpu.available_cycles << std::endl
              << "Total cycles=" << _cpu.total_cycles << std::endl;
}

void Shell::next_instruction(ArgsType const &args) {
    spi_cpu_execute(&_cpu, _mem);
}

void Shell::run() {
    _running = true;
    // setting print value in hex mode
    std::cout << std::hex;
    while (_running) {
        std::string line;

        std::cout << "shell>" << std::flush;
        std::getline(std::cin, line);
        this->execute(line);
    }
}
