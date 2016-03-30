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
    int result = cpu->registers[A] + byte + cpu->registers[A] + SPI_GET_FLAGS(cpu->flags, CARRY);

    PRINT_DEBUG("VALUE : %d", byte);
    SPI_ENABLE_FLAGS_IF(cpu->flags, OVERFLOW, result > 255)
    SPI_ENABLE_FLAGS_IF(cpu->flags, NEGATIVE, (int8_t)(result) < 0)
    SPI_ENABLE_FLAGS_IF(cpu->flags, ZERO, result == 0)
    if (SPI_GET_FLAGS(cpu->flags, ENABLE_BCD)) {
        result = SPI_BCD(cpu->registers[A]) + SPI_BCD(byte) + SPI_GET_FLAGS(cpu->flags, CARRY);
        SPI_ENABLE_FLAGS_IF(cpu->flags, CARRY, result > 99)
    } else {
        SPI_ENABLE_FLAGS_IF(cpu->flags, CARRY, result > 255)
    }
    cpu->registers[A] = (spi_byte_t)result;
    PRINT_DEBUG("PROCESSOR STATUS : %X", cpu->flags);
    PRINT_DEBUG("ACCUMULATOR VALUE : %d", (spi_byte_t)result);
}

SPI_INSTRUCTION_ALIAS(spi_adc, IMMEDIATE, 2, 2);
SPI_INSTRUCTION_ALIAS(spi_adc, ZERO_PAGE, 2, 3);
SPI_INSTRUCTION_ALIAS(spi_adc, ZERO_PAGE_INDEXED_X, 2, 4);
SPI_INSTRUCTION_ALIAS(spi_adc, ABSOLUTE, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_adc, ABSOLUTE_INDEXED_X, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_adc, ABSOLUTE_INDEXED_Y, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_adc, INDEXED_INDIRECT, 2, 6);
SPI_INSTRUCTION_ALIAS(spi_adc, INDIRECT_INDEXED, 2, 5);

void    spi_and(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_byte_t byte = spi_cpu_read_value(cpu, mode, mem);
    spi_byte_t result = cpu->registers[A] & byte;

    PRINT_DEBUG("VALUE : %d", byte);
    SPI_ENABLE_FLAGS_IF(cpu->flags, NEGATIVE, (int8_t)(result) < 0)
    SPI_ENABLE_FLAGS_IF(cpu->flags, ZERO, result == 0)
    cpu->registers[A] = (spi_byte_t)result;
    PRINT_DEBUG("PROCESSOR STATUS : %X", cpu->flags);
    PRINT_DEBUG("ACCUMULATOR VALUE : %d", (spi_byte_t)result);
}

SPI_INSTRUCTION_ALIAS(spi_and, IMMEDIATE, 2, 2);
SPI_INSTRUCTION_ALIAS(spi_and, ZERO_PAGE, 2, 2);
SPI_INSTRUCTION_ALIAS(spi_and, ZERO_PAGE_INDEXED_X, 2, 3);
SPI_INSTRUCTION_ALIAS(spi_and, ABSOLUTE, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_and, ABSOLUTE_INDEXED_X, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_and, ABSOLUTE_INDEXED_Y, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_and, INDEXED_INDIRECT, 2, 6);
SPI_INSTRUCTION_ALIAS(spi_and, INDIRECT_INDEXED, 2, 5);

void    spi_asl(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_byte_t value;

    if (mode == ACCUMULATOR) {
        value = cpu->registers[A];
    } else {
        value = spi_cpu_read_value(cpu, mode, mem);
    }
    SPI_SET_FLAGS(cpu->flags, CARRY, SPI_GET_BIT(value, 7));
    value = (uint8_t)((value << 1) & 0xFE);
    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(value, 7));
    SPI_SET_FLAGS(cpu->flags, ZERO, value == 0 ? 1 : 0);
}

SPI_INSTRUCTION_ALIAS(spi_asl, ACCUMULATOR, 1, 2);
SPI_INSTRUCTION_ALIAS(spi_asl, ZERO_PAGE, 2, 5);
SPI_INSTRUCTION_ALIAS(spi_asl, ZERO_PAGE_INDEXED_X, 2, 6);
SPI_INSTRUCTION_ALIAS(spi_asl, ABSOLUTE, 3, 6);
SPI_INSTRUCTION_ALIAS(spi_asl, ABSOLUTE_INDEXED_X, 3, 7);


void    spi_bit(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    int8_t      value = spi_cpu_read_value(cpu, mode, mem);
    spi_byte_t  result = cpu->registers[A] & value;

    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(result, 7));
    SPI_SET_FLAGS(cpu->flags, OVERFLOW, SPI_GET_BIT(result, 6));
    SPI_SET_FLAGS(cpu->flags, ZERO, result == 0);
}

SPI_INSTRUCTION_ALIAS(spi_bit, ABSOLUTE, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_bit, ZERO_PAGE, 2, 3);

void    spi_register_arithmetic_opcodes(spi_cpu_t *cpu) {
    cpu->opcode_table[0x69] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, IMMEDIATE);
    cpu->opcode_table[0x65] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, ZERO_PAGE);
    cpu->opcode_table[0x75] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, ZERO_PAGE_INDEXED_X);
    cpu->opcode_table[0x6D] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, ABSOLUTE);
    cpu->opcode_table[0x7D] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, ABSOLUTE_INDEXED_X);
    cpu->opcode_table[0x79] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, ABSOLUTE_INDEXED_Y);
    cpu->opcode_table[0x61] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, INDEXED_INDIRECT);
    cpu->opcode_table[0x71] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, INDIRECT_INDEXED);

    cpu->opcode_table[0x29] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, IMMEDIATE);
    cpu->opcode_table[0x25] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, ZERO_PAGE);
    cpu->opcode_table[0x35] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, ZERO_PAGE_INDEXED_X);
    cpu->opcode_table[0x2D] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, ABSOLUTE);
    cpu->opcode_table[0x3D] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, ABSOLUTE_INDEXED_X);
    cpu->opcode_table[0x39] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, ABSOLUTE_INDEXED_Y);
    cpu->opcode_table[0x21] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, INDEXED_INDIRECT);
    cpu->opcode_table[0x31] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, INDIRECT_INDEXED);

    cpu->opcode_table[0x0A] = &SPI_GET_INSTRUCTION_ALIAS(spi_asl, ACCUMULATOR);
    cpu->opcode_table[0x06] = &SPI_GET_INSTRUCTION_ALIAS(spi_asl, ZERO_PAGE);
    cpu->opcode_table[0x16] = &SPI_GET_INSTRUCTION_ALIAS(spi_asl, ZERO_PAGE_INDEXED_X);
    cpu->opcode_table[0x0E] = &SPI_GET_INSTRUCTION_ALIAS(spi_asl, ABSOLUTE);
    cpu->opcode_table[0x1E] = &SPI_GET_INSTRUCTION_ALIAS(spi_asl, ABSOLUTE_INDEXED_X);

    cpu->opcode_table[0x24] = &SPI_GET_INSTRUCTION_ALIAS(spi_bit, ZERO_PAGE);
    cpu->opcode_table[0x2C] = &SPI_GET_INSTRUCTION_ALIAS(spi_bit, ABSOLUTE);
}