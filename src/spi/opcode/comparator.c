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

#include "spi/opcode/comparator.h"

static void spi_compare_with_register(spi_cpu_register_t reg, spi_cpu_t *cpu,
                                      spi_address_mode_t mode, spi_byte_t *mem) {
    spi_byte_t value = spi_cpu_read_value(cpu, mode, mem);
    spi_byte_t result = cpu->registers[reg] - value;

    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(result, 7));
    SPI_SET_FLAGS(cpu->flags, CARRY, cpu->registers[reg] >= value);
    SPI_SET_FLAGS(cpu->flags, ZERO, result == 0);
}

void spi_cmp(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_compare_with_register(A, cpu, mode, mem);
}

void spi_cpx(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_compare_with_register(X, cpu, mode, mem);
}

void spi_cpy(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_compare_with_register(Y, cpu, mode, mem);
}

SPI_INSTRUCTION_ALIAS(spi_cmp, IMMEDIATE, 2, 2);
SPI_INSTRUCTION_ALIAS(spi_cmp, ZERO_PAGE, 2, 3);
SPI_INSTRUCTION_ALIAS(spi_cmp, ZERO_PAGE_INDEXED_X, 2, 4);
SPI_INSTRUCTION_ALIAS(spi_cmp, ABSOLUTE, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_cmp, ABSOLUTE_INDEXED_X, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_cmp, ABSOLUTE_INDEXED_Y, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_cmp, INDEXED_INDIRECT, 2, 6);
SPI_INSTRUCTION_ALIAS(spi_cmp, INDIRECT_INDEXED,2, 5);

SPI_INSTRUCTION_ALIAS(spi_cpx, IMMEDIATE, 2, 2);
SPI_INSTRUCTION_ALIAS(spi_cpx, ZERO_PAGE, 2, 3);
SPI_INSTRUCTION_ALIAS(spi_cpx, ABSOLUTE, 3, 4);

SPI_INSTRUCTION_ALIAS(spi_cpy, IMMEDIATE, 2, 2);
SPI_INSTRUCTION_ALIAS(spi_cpy, ZERO_PAGE, 2, 3);
SPI_INSTRUCTION_ALIAS(spi_cpy, ABSOLUTE, 3, 4);

void spi_register_comparator_opcodes(spi_cpu_t *cpu) {
    cpu->opcode_table[0xC9] = &SPI_GET_INSTRUCTION_ALIAS(spi_cmp, IMMEDIATE);
    cpu->opcode_table[0xC5] = &SPI_GET_INSTRUCTION_ALIAS(spi_cmp, ZERO_PAGE);
    cpu->opcode_table[0xD5] = &SPI_GET_INSTRUCTION_ALIAS(spi_cmp, ZERO_PAGE_INDEXED_X);
    cpu->opcode_table[0xCD] = &SPI_GET_INSTRUCTION_ALIAS(spi_cmp, ABSOLUTE);
    cpu->opcode_table[0xDD] = &SPI_GET_INSTRUCTION_ALIAS(spi_cmp, ABSOLUTE_INDEXED_X);
    cpu->opcode_table[0xD9] = &SPI_GET_INSTRUCTION_ALIAS(spi_cmp, ABSOLUTE_INDEXED_Y);
    cpu->opcode_table[0xC1] = &SPI_GET_INSTRUCTION_ALIAS(spi_cmp, INDEXED_INDIRECT);
    cpu->opcode_table[0xD1] = &SPI_GET_INSTRUCTION_ALIAS(spi_cmp, INDIRECT_INDEXED);

    cpu->opcode_table[0xE0] = &SPI_GET_INSTRUCTION_ALIAS(spi_cpx, IMMEDIATE);
    cpu->opcode_table[0xE4] = &SPI_GET_INSTRUCTION_ALIAS(spi_cpx, ZERO_PAGE);
    cpu->opcode_table[0xEC] = &SPI_GET_INSTRUCTION_ALIAS(spi_cpx, ABSOLUTE);

    cpu->opcode_table[0xC0] = &SPI_GET_INSTRUCTION_ALIAS(spi_cpy, IMMEDIATE);
    cpu->opcode_table[0xC4] = &SPI_GET_INSTRUCTION_ALIAS(spi_cpy, ZERO_PAGE);
    cpu->opcode_table[0xCC] = &SPI_GET_INSTRUCTION_ALIAS(spi_cpy, ABSOLUTE);
}
