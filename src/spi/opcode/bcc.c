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

#include "spi/opcode/bcc.h"

void    spi_bcc(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    int8_t rel_addr = spi_cpu_read_value(cpu, mode, mem);

    if (SPI_GET_BIT(cpu->flags, CARRY) == 0) {
        cpu->pc += rel_addr;
    }
}

SPI_INSTRUCTION_ALIAS(spi_bcc, RELATIVE, 2, 2);

void    spi_register_bcc_opcode(spi_cpu_t *cpu) {
    cpu->opcode_table[0x90] = &SPI_GET_INSTRUCTION_ALIAS(spi_bcc, RELATIVE);
}