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

void    spi_register_asl_opcode(spi_cpu_t *cpu) {
    cpu->opcode_table[0x0A] = &SPI_GET_INSTRUCTION_ALIAS(spi_asl, ACCUMULATOR);
    cpu->opcode_table[0x06] = &SPI_GET_INSTRUCTION_ALIAS(spi_asl, ZERO_PAGE);
    cpu->opcode_table[0x16] = &SPI_GET_INSTRUCTION_ALIAS(spi_asl, ZERO_PAGE_INDEXED_X);
    cpu->opcode_table[0x0E] = &SPI_GET_INSTRUCTION_ALIAS(spi_asl, ABSOLUTE);
    cpu->opcode_table[0x1E] = &SPI_GET_INSTRUCTION_ALIAS(spi_asl, ABSOLUTE_INDEXED_X);
}
