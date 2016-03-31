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

#include "spi/opcode/stack.h"

void spi_pha(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_cpu_push_stack(cpu, mem, cpu->registers[X]);
}

void spi_php(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_cpu_push_stack(cpu, mem, cpu->flags);
}

void spi_pla(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    cpu->registers[A] = spi_cpu_pull_stack(cpu, mem);
    SPI_SET_FLAGS(cpu->flags, NEGATIVE, SPI_GET_BIT(cpu->registers[A], 7));
    SPI_SET_FLAGS(cpu->flags, ZERO, cpu->registers[A] == 0);
}

void spi_plp(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    cpu->flags = spi_cpu_pull_stack(cpu, mem);
}

SPI_INSTRUCTION_ALIAS(spi_pha, IMPLIED, 1, 3);

SPI_INSTRUCTION_ALIAS(spi_php, IMPLIED, 1, 3);

SPI_INSTRUCTION_ALIAS(spi_pla, IMPLIED, 1, 3);

SPI_INSTRUCTION_ALIAS(spi_plp, IMPLIED, 1, 3);

void spi_register_stack_opcodes(spi_cpu_t *cpu) {
    cpu->opcode_table[0x48] = &SPI_GET_INSTRUCTION_ALIAS(spi_pha, IMPLIED);

    cpu->opcode_table[0x08] = &SPI_GET_INSTRUCTION_ALIAS(spi_php, IMPLIED);

    cpu->opcode_table[0x68] = &SPI_GET_INSTRUCTION_ALIAS(spi_pla, IMPLIED);

    cpu->opcode_table[0x28] = &SPI_GET_INSTRUCTION_ALIAS(spi_plp, IMPLIED);
}
