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

void spi_nop(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {}

void spi_sec(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    SPI_ENABLE_FLAG(cpu->flags, CARRY);
}

void spi_sed(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    SPI_ENABLE_FLAG(cpu->flags, DECIMAL);
}

void spi_sei(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    SPI_ENABLE_FLAG(cpu->flags, DISABLE_INTERRUPTS);
}

void spi_tax(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    cpu->registers[X] = cpu->registers[A];
    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(cpu->registers[X], 7));
    SPI_SET_FLAGS(cpu->flags, ZERO, cpu->registers[X] == 0);
}

void spi_tay(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    cpu->registers[Y] = cpu->registers[A];
    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(cpu->registers[Y], 7));
    SPI_SET_FLAGS(cpu->flags, ZERO, cpu->registers[Y] == 0);
}

void spi_tsx(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    cpu->registers[X] = cpu->sp;
}

void spi_txa(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    cpu->registers[A] = cpu->registers[X];
    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(cpu->registers[A], 7));
    SPI_SET_FLAGS(cpu->flags, ZERO, cpu->registers[A] == 0);
}

void spi_txs(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    cpu->sp = cpu->registers[X];
}

void spi_tya(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    cpu->registers[A] = cpu->registers[Y];
    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(cpu->registers[A], 7));
    SPI_SET_FLAGS(cpu->flags, ZERO, cpu->registers[A] == 0);
}


SPI_INSTRUCTION_ALIAS(spi_clc, IMPLIED, 1, 2);

SPI_INSTRUCTION_ALIAS(spi_cld, IMPLIED, 1, 2);

SPI_INSTRUCTION_ALIAS(spi_cli, IMPLIED, 1, 2);

SPI_INSTRUCTION_ALIAS(spi_clv, IMPLIED, 1, 2);

SPI_INSTRUCTION_ALIAS(spi_nop, IMPLIED, 1, 2);

SPI_INSTRUCTION_ALIAS(spi_sec, IMPLIED, 1, 2);

SPI_INSTRUCTION_ALIAS(spi_sed, IMPLIED, 1, 2);

SPI_INSTRUCTION_ALIAS(spi_sei, IMPLIED, 1, 2);

SPI_INSTRUCTION_ALIAS(spi_tax, IMPLIED, 1, 2);

SPI_INSTRUCTION_ALIAS(spi_tay, IMPLIED, 1, 2);

SPI_INSTRUCTION_ALIAS(spi_tsx, IMPLIED, 1, 2);

SPI_INSTRUCTION_ALIAS(spi_txa, IMPLIED, 1, 2);

SPI_INSTRUCTION_ALIAS(spi_txs, IMPLIED, 1, 2);

SPI_INSTRUCTION_ALIAS(spi_tya, IMPLIED, 1, 2);

void spi_register_cpu_opcodes(spi_cpu_t *cpu) {
    cpu->opcode_table[0x18] = &SPI_GET_INSTRUCTION_ALIAS(spi_clc, IMPLIED);

    cpu->opcode_table[0xD8] = &SPI_GET_INSTRUCTION_ALIAS(spi_cld, IMPLIED);

    cpu->opcode_table[0x58] = &SPI_GET_INSTRUCTION_ALIAS(spi_cli, IMPLIED);

    cpu->opcode_table[0xB8] = &SPI_GET_INSTRUCTION_ALIAS(spi_clv, IMPLIED);

    cpu->opcode_table[0xEA] = &SPI_GET_INSTRUCTION_ALIAS(spi_nop, IMPLIED);

    cpu->opcode_table[0x38] = &SPI_GET_INSTRUCTION_ALIAS(spi_sec, IMPLIED);

    cpu->opcode_table[0xF8] = &SPI_GET_INSTRUCTION_ALIAS(spi_sed, IMPLIED);

    cpu->opcode_table[0x78] = &SPI_GET_INSTRUCTION_ALIAS(spi_sei, IMPLIED);

    cpu->opcode_table[0xAA] = &SPI_GET_INSTRUCTION_ALIAS(spi_tax, IMPLIED);

    cpu->opcode_table[0xA8] = &SPI_GET_INSTRUCTION_ALIAS(spi_tay, IMPLIED);

    cpu->opcode_table[0xBA] = &SPI_GET_INSTRUCTION_ALIAS(spi_tsx, IMPLIED);

    cpu->opcode_table[0x8A] = &SPI_GET_INSTRUCTION_ALIAS(spi_txa, IMPLIED);

    cpu->opcode_table[0x9A] = &SPI_GET_INSTRUCTION_ALIAS(spi_txs, IMPLIED);

    cpu->opcode_table[0x98] = &SPI_GET_INSTRUCTION_ALIAS(spi_tya, IMPLIED);
}