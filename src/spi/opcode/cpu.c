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

#include "spi/opcode/cpu.h"

void spi_clc(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    SPI_DISABLE_FLAG(cpu->flags, CARRY);
}

void spi_cld(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    SPI_DISABLE_FLAG(cpu->flags, DECIMAL);
}

void spi_cli(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    SPI_DISABLE_FLAG(cpu->flags, DISABLE_INTERRUPTS);
}

void spi_clv(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    SPI_DISABLE_FLAG(cpu->flags, OVERFLOW);
}

SPI_INSTRUCTION_ALIAS(spi_clc, IMPLIED, 1, 2);
SPI_INSTRUCTION_ALIAS(spi_cld, IMPLIED, 1, 2);
SPI_INSTRUCTION_ALIAS(spi_cli, IMPLIED, 1, 2);
SPI_INSTRUCTION_ALIAS(spi_clv, IMPLIED, 1, 2);

void spi_register_cpu_opcodes(spi_cpu_t *cpu) {
    cpu->opcode_table[0x18] = &SPI_GET_INSTRUCTION_ALIAS(spi_clc, IMPLIED);
    cpu->opcode_table[0xD8] = &SPI_GET_INSTRUCTION_ALIAS(spi_cld, IMPLIED);
    cpu->opcode_table[0x58] = &SPI_GET_INSTRUCTION_ALIAS(spi_cli, IMPLIED);
    cpu->opcode_table[0xB8] = &SPI_GET_INSTRUCTION_ALIAS(spi_clv, IMPLIED);
}

