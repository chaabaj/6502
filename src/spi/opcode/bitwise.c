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

#include "spi/opcode/bitwise.h"
#include "spi/debug.h"

void spi_bit(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_mem_addr_t  addr = spi_cpu_get_addr(cpu, mode, mem);
    spi_byte_t      value = mem[addr];
    spi_byte_t      result = cpu->registers[A] & value;

    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(result, 7));
    SPI_SET_FLAGS(cpu->flags, OVERFLOW, SPI_GET_BIT(result, 6));
    SPI_SET_FLAGS(cpu->flags, ZERO, result == 0);
    mem[addr] = result;
}

void spi_and(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_byte_t byte = spi_cpu_read_value(cpu, mode, mem);
    spi_byte_t result = cpu->registers[A] & byte;

    PRINT_DEBUG("VALUE : %d", byte);
    SPI_SET_FLAGS(cpu->flags, NEGATIVE, (int8_t)(result) < 0);
    SPI_SET_FLAGS(cpu->flags, ZERO, result == 0);
    cpu->registers[A] = (spi_byte_t)result;
    PRINT_DEBUG("PROCESSOR STATUS : %X", cpu->flags);
    PRINT_DEBUG("ACCUMULATOR VALUE : %d", (spi_byte_t)result);
}

void spi_eor(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_byte_t value = spi_cpu_read_value(cpu, mode, mem);

    cpu->registers[A] ^= value;
    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(cpu->registers[A], 7));
    SPI_SET_FLAGS(cpu->flags, ZERO, cpu->registers[A] == 0);
}

void spi_lsr(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_byte_t      value;
    spi_mem_addr_t  value_addr = 0;

    if (mode == ACCUMULATOR) {
        value = cpu->registers[A];
    } else {
        value_addr = spi_cpu_get_addr(cpu, mode, mem);
        value = mem[value_addr];
    }
    SPI_DISABLE_FLAG(cpu->flags, NEGATIVE);
    SPI_SET_FLAGS(cpu->flags, CARRY, SPI_GET_BIT(value, 0));
    value = (spi_byte_t)((value >> 1) & 0x7F);
    SPI_SET_FLAGS(cpu->flags, ZERO, value == 0);
    if (mode == ACCUMULATOR) {
        cpu->registers[A] = value;
    } else {
        mem[value_addr] = value;
    }
}

void spi_ora(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_byte_t value = spi_cpu_read_value(cpu, mode, mem);

    cpu->registers[A] |= value;
    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(cpu->registers[A], 7));
    SPI_SET_FLAGS(cpu->flags, ZERO, cpu->registers[A] == 0);
}

void spi_rol(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_byte_t      value;
    spi_mem_addr_t  value_addr = 0;
    spi_byte_t t;

    if (mode == ACCUMULATOR) {
        value = cpu->registers[A];
    } else {
        value_addr = spi_cpu_get_addr(cpu, mode, mem);
        value = mem[value_addr];
    }
    t = SPI_GET_BIT(value, 7);
    value = (spi_byte_t )((value << 1) & 0xFE);
    value |= SPI_GET_FLAG(cpu->flags, CARRY);
    SPI_SET_FLAGS(cpu->flags, CARRY, t);
    SPI_SET_FLAGS(cpu->flags, ZERO, value == 0);
    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(value, 7));
    if (mode == ACCUMULATOR) {
        cpu->registers[A] = value;
    } else {
        mem[value_addr] = value;
    }
}

void spi_ror(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_byte_t      value;
    spi_mem_addr_t  addr = 0;
    spi_byte_t      t;

    if (mode == ACCUMULATOR) {
        value = cpu->registers[A];
    } else {
        addr = spi_cpu_get_addr(cpu, mode, mem);
        value = mem[addr];
    }
    t = SPI_GET_BIT(value, 0);
    value = (spi_byte_t )((value >> 1) & 0x7F);
    value |= (SPI_GET_FLAG(cpu->flags, CARRY) ? 0x80 : 0x00);
    SPI_SET_FLAGS(cpu->flags, CARRY, t);
    SPI_SET_FLAGS(cpu->flags, ZERO, value == 0);
    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(value, 7));
    if (mode == ACCUMULATOR) {
        cpu->registers[A] = value;
    } else {
        mem[addr] = value;
    }
}

SPI_INSTRUCTION_ALIAS(spi_bit, ABSOLUTE, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_bit, ZERO_PAGE, 2, 3);

SPI_INSTRUCTION_ALIAS(spi_and, IMMEDIATE, 2, 2);
SPI_INSTRUCTION_ALIAS(spi_and, ZERO_PAGE, 2, 2);
SPI_INSTRUCTION_ALIAS(spi_and, ZERO_PAGE_INDEXED_X, 2, 3);
SPI_INSTRUCTION_ALIAS(spi_and, ABSOLUTE, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_and, ABSOLUTE_INDEXED_X, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_and, ABSOLUTE_INDEXED_Y, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_and, INDEXED_INDIRECT, 2, 6);
SPI_INSTRUCTION_ALIAS(spi_and, INDIRECT_INDEXED, 2, 5);

SPI_INSTRUCTION_ALIAS(spi_eor, IMMEDIATE, 2, 2);
SPI_INSTRUCTION_ALIAS(spi_eor, ZERO_PAGE, 2, 3);
SPI_INSTRUCTION_ALIAS(spi_eor, ZERO_PAGE_INDEXED_X, 2, 4);
SPI_INSTRUCTION_ALIAS(spi_eor, ABSOLUTE, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_eor, ABSOLUTE_INDEXED_X, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_eor, ABSOLUTE_INDEXED_Y, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_eor, INDEXED_INDIRECT, 2, 6);
SPI_INSTRUCTION_ALIAS(spi_eor, INDIRECT_INDEXED, 2, 5);

SPI_INSTRUCTION_ALIAS(spi_lsr, ACCUMULATOR, 1, 2);
SPI_INSTRUCTION_ALIAS(spi_lsr, ZERO_PAGE, 2, 5);
SPI_INSTRUCTION_ALIAS(spi_lsr, ZERO_PAGE_INDEXED_X, 2, 6);
SPI_INSTRUCTION_ALIAS(spi_lsr, ABSOLUTE, 3, 6);
SPI_INSTRUCTION_ALIAS(spi_lsr, ABSOLUTE_INDEXED_X, 3, 7);

SPI_INSTRUCTION_ALIAS(spi_ora, IMMEDIATE, 2, 2);
SPI_INSTRUCTION_ALIAS(spi_ora, ZERO_PAGE, 2, 2);
SPI_INSTRUCTION_ALIAS(spi_ora, ZERO_PAGE_INDEXED_X, 2, 3);
SPI_INSTRUCTION_ALIAS(spi_ora, ABSOLUTE, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_ora, ABSOLUTE_INDEXED_X, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_ora, ABSOLUTE_INDEXED_Y, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_ora, INDEXED_INDIRECT, 2, 6);
SPI_INSTRUCTION_ALIAS(spi_ora, INDIRECT_INDEXED, 2, 5);

SPI_INSTRUCTION_ALIAS(spi_rol, ACCUMULATOR, 1, 2);
SPI_INSTRUCTION_ALIAS(spi_rol, ZERO_PAGE, 2, 5);
SPI_INSTRUCTION_ALIAS(spi_rol, ZERO_PAGE_INDEXED_X, 2, 6);
SPI_INSTRUCTION_ALIAS(spi_rol, ABSOLUTE, 3, 6);
SPI_INSTRUCTION_ALIAS(spi_rol, ABSOLUTE_INDEXED_X, 3, 7);

SPI_INSTRUCTION_ALIAS(spi_ror, ACCUMULATOR, 1, 2);
SPI_INSTRUCTION_ALIAS(spi_ror, ZERO_PAGE, 2, 5);
SPI_INSTRUCTION_ALIAS(spi_ror, ZERO_PAGE_INDEXED_X, 2, 6);
SPI_INSTRUCTION_ALIAS(spi_ror, ABSOLUTE, 3, 6);
SPI_INSTRUCTION_ALIAS(spi_ror, ABSOLUTE_INDEXED_X, 3, 7);

void spi_register_bitwise_opcodes(spi_cpu_t *cpu) {
    cpu->opcode_table[0x29] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, IMMEDIATE);
    cpu->opcode_table[0x25] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, ZERO_PAGE);
    cpu->opcode_table[0x35] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, ZERO_PAGE_INDEXED_X);
    cpu->opcode_table[0x2D] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, ABSOLUTE);
    cpu->opcode_table[0x3D] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, ABSOLUTE_INDEXED_X);
    cpu->opcode_table[0x39] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, ABSOLUTE_INDEXED_Y);
    cpu->opcode_table[0x21] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, INDEXED_INDIRECT);
    cpu->opcode_table[0x31] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, INDIRECT_INDEXED);

    cpu->opcode_table[0x24] = &SPI_GET_INSTRUCTION_ALIAS(spi_bit, ZERO_PAGE);
    cpu->opcode_table[0x2C] = &SPI_GET_INSTRUCTION_ALIAS(spi_bit, ABSOLUTE);

    cpu->opcode_table[0x49] = &SPI_GET_INSTRUCTION_ALIAS(spi_eor, IMMEDIATE);
    cpu->opcode_table[0x45] = &SPI_GET_INSTRUCTION_ALIAS(spi_eor, ZERO_PAGE);
    cpu->opcode_table[0x55] = &SPI_GET_INSTRUCTION_ALIAS(spi_eor, ZERO_PAGE_INDEXED_X);
    cpu->opcode_table[0x4D] = &SPI_GET_INSTRUCTION_ALIAS(spi_eor, ABSOLUTE);
    cpu->opcode_table[0x5D] = &SPI_GET_INSTRUCTION_ALIAS(spi_eor, ABSOLUTE_INDEXED_X);
    cpu->opcode_table[0x59] = &SPI_GET_INSTRUCTION_ALIAS(spi_eor, ABSOLUTE_INDEXED_Y);
    cpu->opcode_table[0x41] = &SPI_GET_INSTRUCTION_ALIAS(spi_eor, INDEXED_INDIRECT);
    cpu->opcode_table[0x51] = &SPI_GET_INSTRUCTION_ALIAS(spi_eor, INDIRECT_INDEXED);

    cpu->opcode_table[0x4A] = &SPI_GET_INSTRUCTION_ALIAS(spi_lsr, ACCUMULATOR);
    cpu->opcode_table[0x46] = &SPI_GET_INSTRUCTION_ALIAS(spi_lsr, ZERO_PAGE);
    cpu->opcode_table[0x56] = &SPI_GET_INSTRUCTION_ALIAS(spi_lsr, ZERO_PAGE_INDEXED_X);
    cpu->opcode_table[0x4E] = &SPI_GET_INSTRUCTION_ALIAS(spi_lsr, ABSOLUTE);
    cpu->opcode_table[0x5E] = &SPI_GET_INSTRUCTION_ALIAS(spi_lsr, ABSOLUTE_INDEXED_X);

    cpu->opcode_table[0x09] = &SPI_GET_INSTRUCTION_ALIAS(spi_ora, IMMEDIATE);
    cpu->opcode_table[0x05] = &SPI_GET_INSTRUCTION_ALIAS(spi_ora, ZERO_PAGE);
    cpu->opcode_table[0x15] = &SPI_GET_INSTRUCTION_ALIAS(spi_ora, ZERO_PAGE_INDEXED_X);
    cpu->opcode_table[0x0D] = &SPI_GET_INSTRUCTION_ALIAS(spi_ora, ABSOLUTE);
    cpu->opcode_table[0x1D] = &SPI_GET_INSTRUCTION_ALIAS(spi_ora, ABSOLUTE_INDEXED_X);
    cpu->opcode_table[0x19] = &SPI_GET_INSTRUCTION_ALIAS(spi_ora, ABSOLUTE_INDEXED_Y);
    cpu->opcode_table[0x01] = &SPI_GET_INSTRUCTION_ALIAS(spi_ora, INDEXED_INDIRECT);
    cpu->opcode_table[0x11] = &SPI_GET_INSTRUCTION_ALIAS(spi_ora, INDIRECT_INDEXED);

    cpu->opcode_table[0x2A] = &SPI_GET_INSTRUCTION_ALIAS(spi_rol, ACCUMULATOR);
    cpu->opcode_table[0x26] = &SPI_GET_INSTRUCTION_ALIAS(spi_rol, ZERO_PAGE);
    cpu->opcode_table[0x36] = &SPI_GET_INSTRUCTION_ALIAS(spi_rol, ZERO_PAGE_INDEXED_X);
    cpu->opcode_table[0x2E] = &SPI_GET_INSTRUCTION_ALIAS(spi_rol, ABSOLUTE);
    cpu->opcode_table[0x3E] = &SPI_GET_INSTRUCTION_ALIAS(spi_rol, ABSOLUTE_INDEXED_X);

    cpu->opcode_table[0x6A] = &SPI_GET_INSTRUCTION_ALIAS(spi_ror, ACCUMULATOR);
    cpu->opcode_table[0x66] = &SPI_GET_INSTRUCTION_ALIAS(spi_ror, ZERO_PAGE);
    cpu->opcode_table[0x76] = &SPI_GET_INSTRUCTION_ALIAS(spi_ror, ZERO_PAGE_INDEXED_X);
    cpu->opcode_table[0x6E] = &SPI_GET_INSTRUCTION_ALIAS(spi_ror, ABSOLUTE);
    cpu->opcode_table[0x7E] = &SPI_GET_INSTRUCTION_ALIAS(spi_ror, ABSOLUTE_INDEXED_X);
}