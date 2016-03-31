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

#include "spi/opcode/memory.h"

void spi_lda(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    cpu->registers[A] = spi_cpu_read_value(cpu, mode, mem);
    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(cpu->registers[A], 7));
    SPI_SET_FLAGS(cpu->flags, ZERO, cpu->registers[A] == 0);
}

void spi_ldx(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    cpu->registers[X] = spi_cpu_read_value(cpu, mode, mem);
    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(cpu->registers[A], 7));
    SPI_SET_FLAGS(cpu->flags, ZERO, cpu->registers[A] == 0);
}

void spi_ldy(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    cpu->registers[Y] = spi_cpu_read_value(cpu, mode, mem);
    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(cpu->registers[A], 7));
    SPI_SET_FLAGS(cpu->flags, ZERO, cpu->registers[A] == 0);
}

void spi_sta(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_cpu_write_value(cpu, mode, mem, cpu->registers[A]);
}

void spi_stx(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_cpu_write_value(cpu, mode, mem, cpu->registers[X]);
}

void spi_sty(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_cpu_write_value(cpu, mode, mem, cpu->registers[Y]);
}

SPI_INSTRUCTION_ALIAS(spi_lda, IMMEDIATE, 2, 2);
SPI_INSTRUCTION_ALIAS(spi_lda, ZERO_PAGE, 2, 3);
SPI_INSTRUCTION_ALIAS(spi_lda, ZERO_PAGE_INDEXED_X, 2, 4);
SPI_INSTRUCTION_ALIAS(spi_lda, ABSOLUTE, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_lda, ABSOLUTE_INDEXED_X, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_lda, ABSOLUTE_INDEXED_Y, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_lda, INDEXED_INDIRECT, 2, 6);
SPI_INSTRUCTION_ALIAS(spi_lda, INDIRECT_INDEXED, 2, 5);

SPI_INSTRUCTION_ALIAS(spi_ldx, IMMEDIATE, 2, 2);
SPI_INSTRUCTION_ALIAS(spi_ldx, ZERO_PAGE, 2, 3);
SPI_INSTRUCTION_ALIAS(spi_ldx, ZERO_PAGE_INDEXED_Y, 2, 4);
SPI_INSTRUCTION_ALIAS(spi_ldx, ABSOLUTE, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_ldx, ABSOLUTE_INDEXED_Y, 3, 4);

SPI_INSTRUCTION_ALIAS(spi_ldy, IMMEDIATE, 2, 2);
SPI_INSTRUCTION_ALIAS(spi_ldy, ZERO_PAGE, 2, 3);
SPI_INSTRUCTION_ALIAS(spi_ldy, ZERO_PAGE_INDEXED_X, 2, 4);
SPI_INSTRUCTION_ALIAS(spi_ldy, ABSOLUTE, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_ldy, ABSOLUTE_INDEXED_X, 3, 4);

SPI_INSTRUCTION_ALIAS(spi_sta, ZERO_PAGE,2, 3);
SPI_INSTRUCTION_ALIAS(spi_sta, ZERO_PAGE_INDEXED_X, 2, 4);
SPI_INSTRUCTION_ALIAS(spi_sta, ABSOLUTE, 3, 4);
SPI_INSTRUCTION_ALIAS(spi_sta, ABSOLUTE_INDEXED_X, 3, 5);
SPI_INSTRUCTION_ALIAS(spi_sta, ABSOLUTE_INDEXED_Y, 3, 5);
SPI_INSTRUCTION_ALIAS(spi_sta, INDEXED_INDIRECT, 2, 6);
SPI_INSTRUCTION_ALIAS(spi_sta, INDIRECT_INDEXED, 2, 6);

SPI_INSTRUCTION_ALIAS(spi_stx, ZERO_PAGE, 2, 3);
SPI_INSTRUCTION_ALIAS(spi_stx, ZERO_PAGE_INDEXED_Y, 2, 4);
SPI_INSTRUCTION_ALIAS(spi_stx, ABSOLUTE, 3, 4);

SPI_INSTRUCTION_ALIAS(spi_sty, ZERO_PAGE, 2, 3);
SPI_INSTRUCTION_ALIAS(spi_sty, ZERO_PAGE_INDEXED_X, 2, 4);
SPI_INSTRUCTION_ALIAS(spi_sty, ABSOLUTE, 3, 4);

void spi_register_memory_opcodes(spi_cpu_t *cpu) {
    cpu->opcode_table[0xA9] = &SPI_GET_INSTRUCTION_ALIAS(spi_lda, IMMEDIATE);
    cpu->opcode_table[0xA5] = &SPI_GET_INSTRUCTION_ALIAS(spi_lda, ZERO_PAGE);
    cpu->opcode_table[0xB5] = &SPI_GET_INSTRUCTION_ALIAS(spi_lda, ZERO_PAGE_INDEXED_X);
    cpu->opcode_table[0xAD] = &SPI_GET_INSTRUCTION_ALIAS(spi_lda, ABSOLUTE);
    cpu->opcode_table[0xBD] = &SPI_GET_INSTRUCTION_ALIAS(spi_lda, ABSOLUTE_INDEXED_X);
    cpu->opcode_table[0xB9] = &SPI_GET_INSTRUCTION_ALIAS(spi_lda, ABSOLUTE_INDEXED_Y);
    cpu->opcode_table[0xA1] = &SPI_GET_INSTRUCTION_ALIAS(spi_lda, INDEXED_INDIRECT);
    cpu->opcode_table[0xB1] = &SPI_GET_INSTRUCTION_ALIAS(spi_lda, INDIRECT_INDEXED);

    cpu->opcode_table[0xA2] = &SPI_GET_INSTRUCTION_ALIAS(spi_ldx, IMMEDIATE);
    cpu->opcode_table[0xA6] = &SPI_GET_INSTRUCTION_ALIAS(spi_ldx, ZERO_PAGE);
    cpu->opcode_table[0xB6] = &SPI_GET_INSTRUCTION_ALIAS(spi_ldx, ZERO_PAGE_INDEXED_Y);
    cpu->opcode_table[0xAE] = &SPI_GET_INSTRUCTION_ALIAS(spi_ldx, ABSOLUTE);
    cpu->opcode_table[0xBE] = &SPI_GET_INSTRUCTION_ALIAS(spi_ldx, ABSOLUTE_INDEXED_Y);

    cpu->opcode_table[0xA0] = &SPI_GET_INSTRUCTION_ALIAS(spi_ldy, IMMEDIATE);
    cpu->opcode_table[0xA4] = &SPI_GET_INSTRUCTION_ALIAS(spi_ldy, ZERO_PAGE);
    cpu->opcode_table[0xB4] = &SPI_GET_INSTRUCTION_ALIAS(spi_ldy, ZERO_PAGE_INDEXED_X);
    cpu->opcode_table[0xAC] = &SPI_GET_INSTRUCTION_ALIAS(spi_ldy, ABSOLUTE);
    cpu->opcode_table[0xBC] = &SPI_GET_INSTRUCTION_ALIAS(spi_ldy, ABSOLUTE_INDEXED_X);

    cpu->opcode_table[0x85] = &SPI_GET_INSTRUCTION_ALIAS(spi_sta, ZERO_PAGE);
    cpu->opcode_table[0x96] = &SPI_GET_INSTRUCTION_ALIAS(spi_sta, ZERO_PAGE_INDEXED_X);
    cpu->opcode_table[0x8D] = &SPI_GET_INSTRUCTION_ALIAS(spi_sta, ABSOLUTE);
    cpu->opcode_table[0x9D] = &SPI_GET_INSTRUCTION_ALIAS(spi_sta, ABSOLUTE_INDEXED_X);
    cpu->opcode_table[0x99] = &SPI_GET_INSTRUCTION_ALIAS(spi_sta, ABSOLUTE_INDEXED_Y);
    cpu->opcode_table[0x81] = &SPI_GET_INSTRUCTION_ALIAS(spi_sta, INDEXED_INDIRECT);
    cpu->opcode_table[0x91] = &SPI_GET_INSTRUCTION_ALIAS(spi_sta, INDIRECT_INDEXED);

    cpu->opcode_table[0x86] = &SPI_GET_INSTRUCTION_ALIAS(spi_stx, ZERO_PAGE);
    cpu->opcode_table[0x96] = &SPI_GET_INSTRUCTION_ALIAS(spi_stx, ZERO_PAGE_INDEXED_Y);
    cpu->opcode_table[0x8E] = &SPI_GET_INSTRUCTION_ALIAS(spi_stx, ABSOLUTE);

    cpu->opcode_table[0x84] = &SPI_GET_INSTRUCTION_ALIAS(spi_sty, ZERO_PAGE);
    cpu->opcode_table[0x94] = &SPI_GET_INSTRUCTION_ALIAS(spi_sty, ZERO_PAGE_INDEXED_X);
    cpu->opcode_table[0x8C] = &SPI_GET_INSTRUCTION_ALIAS(spi_sty, ABSOLUTE);
}