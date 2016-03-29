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

#include "spi/opcode/and.h"
#include "spi/debug.h"

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

void    spi_register_and_opcode(spi_cpu_t *cpu) {
    cpu->opcode_table[0x29] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, IMMEDIATE);
    cpu->opcode_table[0x25] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, ZERO_PAGE);
    cpu->opcode_table[0x35] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, ZERO_PAGE_INDEXED_X);
    cpu->opcode_table[0x2D] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, ABSOLUTE);
    cpu->opcode_table[0x3D] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, ABSOLUTE_INDEXED_X);
    cpu->opcode_table[0x39] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, ABSOLUTE_INDEXED_Y);
    cpu->opcode_table[0x21] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, INDEXED_INDIRECT);
    cpu->opcode_table[0x31] = &SPI_GET_INSTRUCTION_ALIAS(spi_and, INDIRECT_INDEXED);
}
