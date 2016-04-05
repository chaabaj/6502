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

#include "spi/opcode/arithmetic.h"
#include "spi/debug.h"

void    spi_adc(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_byte_t byte = spi_cpu_read_value(cpu, mode, mem);
    int result = cpu->registers[A] + byte + SPI_GET_FLAG(cpu->flags, CARRY);

    SPI_ENABLE_FLAG_IF(cpu->flags, OVERFLOW,
                       SPI_GET_BIT(result, 7) != SPI_GET_BIT(cpu->registers[A], 7));
    SPI_ENABLE_FLAG_IF(cpu->flags, NEGATIVE, SPI_GET_BIT(result, 7));
    SPI_ENABLE_FLAG_IF(cpu->flags, ZERO, result == 0)
    if (SPI_GET_FLAG(cpu->flags, DECIMAL)) {
        result = SPI_BCD(cpu->registers[A]) + SPI_BCD(byte) + SPI_GET_FLAG(cpu->flags, CARRY);
        SPI_ENABLE_FLAG_IF(cpu->flags, CARRY, result > 99)
    } else {
        SPI_ENABLE_FLAG_IF(cpu->flags, CARRY, result > 255)
    }
    cpu->registers[A] = (spi_byte_t)result;
}

void spi_asl(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_mem_addr_t  addr = 0;
    spi_byte_t      value;

    if (mode == ACCUMULATOR) {
        value = cpu->registers[A];
    } else {
        addr = spi_cpu_get_addr(cpu, mode, mem);
        value = mem[addr];
    }
    SPI_SET_FLAGS(cpu->flags, CARRY, SPI_GET_BIT(value, 7));
    value = (uint8_t)((value << 1) & 0xFE);
    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(value, 7));
    SPI_SET_FLAGS(cpu->flags, ZERO, value == 0 ? 1 : 0);
    if (mode == ACCUMULATOR) {
        cpu->registers[A] = value;
    } else {
        mem[addr] = value;
    }
}

void spi_dec(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_mem_addr_t addr = spi_cpu_get_addr(cpu, mode, mem);

    mem[addr] = (spi_byte_t)(mem[addr] - 1);
    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(mem[addr], 7));
    SPI_SET_FLAGS(cpu->flags, ZERO, mem[addr] == 0);
}

void spi_dex(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    cpu->registers[X]--;
    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(cpu->registers[X], 7));
    SPI_SET_FLAGS(cpu->flags, ZERO, cpu->registers[X] == 0);
}

void spi_dey(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    cpu->registers[Y]--;
    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(cpu->registers[Y], 7));
    SPI_SET_FLAGS(cpu->flags, ZERO, cpu->registers[Y] == 0);
}

void spi_inc(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_mem_addr_t addr = spi_cpu_get_addr(cpu, mode, mem);

    mem[addr] = (spi_byte_t)(mem[addr] + 1);
    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(mem[addr], 7));
    SPI_SET_FLAGS(cpu->flags, ZERO, mem[addr] == 0);
}

void spi_inx(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    cpu->registers[X]++;
    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(cpu->registers[X], 7));
    SPI_SET_FLAGS(cpu->flags, ZERO, cpu->registers[X] == 0);
}

void spi_iny(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    cpu->registers[Y]++;
    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(cpu->registers[X], 7));
    SPI_SET_FLAGS(cpu->flags, ZERO, cpu->registers[X] == 0);
}

void spi_sbc(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    int32_t     result;
    spi_byte_t  value = spi_cpu_read_value(cpu, mode, mem);

    if (SPI_GET_FLAG(cpu->flags, DECIMAL)) {
        result = SPI_BCD(cpu->registers[A]) - SPI_BCD(value) - !SPI_GET_FLAG(cpu->flags, CARRY);
        SPI_SET_FLAGS(cpu->flags, OVERFLOW, result > 99 || result < 0);
    } else {
        result = cpu->registers[A] - value, !SPI_GET_FLAG(cpu->flags, CARRY);
        SPI_SET_FLAGS(cpu->flags, OVERFLOW, result > 127 || result < -128);
    }
    SPI_SET_FLAGS(cpu->flags, CARRY, result >= 0);
    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(result, 7));
    SPI_SET_FLAGS(cpu->flags, ZERO, result == 0);
    cpu->registers[A] = (spi_byte_t)result;
}

SPI_INSTRUCTION_ALIAS(spi_adc, IMMEDIATE, 2, 2);
SPI_INSTRUCTION_ALIAS(spi_adc, ZERO_PAGE, 2, 3);
SPI_INSTRUCTION_ALIAS(spi_adc, ZERO_PAGE_INDEXED_X, 2, 4);
SPI_INSTRUCTION_ALIAS(spi_adc, ABSOLUTE, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_adc, ABSOLUTE_INDEXED_X, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_adc, ABSOLUTE_INDEXED_Y, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_adc, INDEXED_INDIRECT, 2, 6);
SPI_INSTRUCTION_ALIAS(spi_adc, INDIRECT_INDEXED, 2, 5);

SPI_INSTRUCTION_ALIAS(spi_asl, ACCUMULATOR, 1, 2);
SPI_INSTRUCTION_ALIAS(spi_asl, ZERO_PAGE, 2, 5);
SPI_INSTRUCTION_ALIAS(spi_asl, ZERO_PAGE_INDEXED_X, 2, 6);
SPI_INSTRUCTION_ALIAS(spi_asl, ABSOLUTE, 3, 6);
SPI_INSTRUCTION_ALIAS(spi_asl, ABSOLUTE_INDEXED_X, 3, 7);

SPI_INSTRUCTION_ALIAS(spi_dec, ZERO_PAGE, 2, 5);
SPI_INSTRUCTION_ALIAS(spi_dec, ZERO_PAGE_INDEXED_X, 2, 6);
SPI_INSTRUCTION_ALIAS(spi_dec, ABSOLUTE, 3, 6);
SPI_INSTRUCTION_ALIAS(spi_dec, ABSOLUTE_INDEXED_X, 3, 7);

SPI_INSTRUCTION_ALIAS(spi_dex, IMPLIED, 1, 2);

SPI_INSTRUCTION_ALIAS(spi_dey, IMPLIED, 1, 2);

SPI_INSTRUCTION_ALIAS(spi_inc, ZERO_PAGE, 2, 5);
SPI_INSTRUCTION_ALIAS(spi_inc, ZERO_PAGE_INDEXED_X, 2, 6);
SPI_INSTRUCTION_ALIAS(spi_inc, ABSOLUTE, 3, 6);
SPI_INSTRUCTION_ALIAS(spi_inc, ABSOLUTE_INDEXED_X, 3, 7);

SPI_INSTRUCTION_ALIAS(spi_inx, IMPLIED, 1, 2);

SPI_INSTRUCTION_ALIAS(spi_iny, IMPLIED, 1, 2);

SPI_INSTRUCTION_ALIAS(spi_sbc, IMMEDIATE, 2, 2);
SPI_INSTRUCTION_ALIAS(spi_sbc, ZERO_PAGE, 2, 3);
SPI_INSTRUCTION_ALIAS(spi_sbc, ZERO_PAGE_INDEXED_X, 2, 4);
SPI_INSTRUCTION_ALIAS(spi_sbc, ABSOLUTE, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_sbc, ABSOLUTE_INDEXED_X, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_sbc, ABSOLUTE_INDEXED_Y, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_sbc, INDEXED_INDIRECT, 2, 6);
SPI_INSTRUCTION_ALIAS(spi_sbc, INDIRECT_INDEXED, 2, 5);

void    spi_register_arithmetic_opcodes(spi_cpu_t *cpu) {
    cpu->opcode_table[0x69] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, IMMEDIATE);
    cpu->opcode_table[0x65] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, ZERO_PAGE);
    cpu->opcode_table[0x75] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, ZERO_PAGE_INDEXED_X);
    cpu->opcode_table[0x6D] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, ABSOLUTE);
    cpu->opcode_table[0x7D] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, ABSOLUTE_INDEXED_X);
    cpu->opcode_table[0x79] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, ABSOLUTE_INDEXED_Y);
    cpu->opcode_table[0x61] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, INDEXED_INDIRECT);
    cpu->opcode_table[0x71] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, INDIRECT_INDEXED);

    cpu->opcode_table[0x0A] = &SPI_GET_INSTRUCTION_ALIAS(spi_asl, ACCUMULATOR);
    cpu->opcode_table[0x06] = &SPI_GET_INSTRUCTION_ALIAS(spi_asl, ZERO_PAGE);
    cpu->opcode_table[0x16] = &SPI_GET_INSTRUCTION_ALIAS(spi_asl, ZERO_PAGE_INDEXED_X);
    cpu->opcode_table[0x0E] = &SPI_GET_INSTRUCTION_ALIAS(spi_asl, ABSOLUTE);
    cpu->opcode_table[0x1E] = &SPI_GET_INSTRUCTION_ALIAS(spi_asl, ABSOLUTE_INDEXED_X);

    cpu->opcode_table[0xC6] = &SPI_GET_INSTRUCTION_ALIAS(spi_dec, ZERO_PAGE);
    cpu->opcode_table[0xD6] = &SPI_GET_INSTRUCTION_ALIAS(spi_dec, ZERO_PAGE_INDEXED_X);
    cpu->opcode_table[0xCE] = &SPI_GET_INSTRUCTION_ALIAS(spi_dec, ABSOLUTE);
    cpu->opcode_table[0xDE] = &SPI_GET_INSTRUCTION_ALIAS(spi_dec, ABSOLUTE_INDEXED_X);

    cpu->opcode_table[0xCA] = &SPI_GET_INSTRUCTION_ALIAS(spi_dex, IMPLIED);

    cpu->opcode_table[0x88] = &SPI_GET_INSTRUCTION_ALIAS(spi_dey, IMPLIED);

    cpu->opcode_table[0xE6] = &SPI_GET_INSTRUCTION_ALIAS(spi_inc, ZERO_PAGE);
    cpu->opcode_table[0xF6] = &SPI_GET_INSTRUCTION_ALIAS(spi_inc, ZERO_PAGE_INDEXED_X);
    cpu->opcode_table[0xEE] = &SPI_GET_INSTRUCTION_ALIAS(spi_inc, ABSOLUTE);
    cpu->opcode_table[0xFE] = &SPI_GET_INSTRUCTION_ALIAS(spi_inc, ABSOLUTE_INDEXED_X);

    cpu->opcode_table[0xE8] = &SPI_GET_INSTRUCTION_ALIAS(spi_inx, IMPLIED);

    cpu->opcode_table[0xC8] = &SPI_GET_INSTRUCTION_ALIAS(spi_iny, IMPLIED);

    cpu->opcode_table[0xE9] = &SPI_GET_INSTRUCTION_ALIAS(spi_sbc, IMMEDIATE);
    cpu->opcode_table[0xE5] = &SPI_GET_INSTRUCTION_ALIAS(spi_sbc, ZERO_PAGE);
    cpu->opcode_table[0xF5] = &SPI_GET_INSTRUCTION_ALIAS(spi_sbc, ZERO_PAGE_INDEXED_X);
    cpu->opcode_table[0xED] = &SPI_GET_INSTRUCTION_ALIAS(spi_sbc, ABSOLUTE);
    cpu->opcode_table[0xFD] = &SPI_GET_INSTRUCTION_ALIAS(spi_sbc, ABSOLUTE_INDEXED_X);
    cpu->opcode_table[0xF9] = &SPI_GET_INSTRUCTION_ALIAS(spi_sbc, ABSOLUTE_INDEXED_Y);
    cpu->opcode_table[0xE1] = &SPI_GET_INSTRUCTION_ALIAS(spi_sbc, INDEXED_INDIRECT);
    cpu->opcode_table[0xF1] = &SPI_GET_INSTRUCTION_ALIAS(spi_sbc, INDIRECT_INDEXED);
}