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

#include "spi/opcode/adc.h"
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

void spi_register_adc_opcode(spi_cpu_t *cpu) {
    cpu->opcode_table[0x69] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, IMMEDIATE);
    cpu->opcode_table[0x65] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, ZERO_PAGE);
    cpu->opcode_table[0x75] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, ZERO_PAGE_INDEXED_X);
    cpu->opcode_table[0x6D] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, ABSOLUTE);
    cpu->opcode_table[0x7D] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, ABSOLUTE_INDEXED_X);
    cpu->opcode_table[0x79] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, ABSOLUTE_INDEXED_Y);
    cpu->opcode_table[0x61] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, INDEXED_INDIRECT);
    cpu->opcode_table[0x71] = &SPI_GET_INSTRUCTION_ALIAS(spi_adc, INDIRECT_INDEXED);
}
