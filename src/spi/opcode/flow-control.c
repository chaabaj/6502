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

#include "spi/opcode/flow-control.h"

SPI_OPCODE_CONDITIONAL_BRANCH(spi_bcc, SPI_GET_BIT(cpu->flags, CARRY) == 0);
SPI_OPCODE_CONDITIONAL_BRANCH(spi_bcs, SPI_GET_BIT(cpu->flags, CARRY) == 1);
SPI_OPCODE_CONDITIONAL_BRANCH(spi_beq, SPI_GET_BIT(cpu->flags, ZERO) == 1);
SPI_OPCODE_CONDITIONAL_BRANCH(spi_bne, SPI_GET_BIT(cpu->flags, ZERO) == 0);
SPI_OPCODE_CONDITIONAL_BRANCH(spi_bmi, SPI_GET_BIT(cpu->flags, NEGATIVE) == 1);
SPI_OPCODE_CONDITIONAL_BRANCH(spi_bpl, SPI_GET_BIT(cpu->flags, NEGATIVE) == 0);
SPI_OPCODE_CONDITIONAL_BRANCH(spi_bvc, SPI_GET_BIT(cpu->flags, OVERFLOW) == 0);
SPI_OPCODE_CONDITIONAL_BRANCH(spi_bvs, SPI_GET_BIT(cpu->flags, OVERFLOW) == 1);

SPI_INSTRUCTION_ALIAS(spi_bcc, RELATIVE, 2, 2);
SPI_INSTRUCTION_ALIAS(spi_bcs, RELATIVE, 2, 2);
SPI_INSTRUCTION_ALIAS(spi_beq, RELATIVE, 2, 2);
SPI_INSTRUCTION_ALIAS(spi_bmi, RELATIVE, 2, 2);
SPI_INSTRUCTION_ALIAS(spi_bne, RELATIVE, 2, 2);
SPI_INSTRUCTION_ALIAS(spi_bpl, RELATIVE, 2, 2);
SPI_INSTRUCTION_ALIAS(spi_bvc, RELATIVE, 2, 2);
SPI_INSTRUCTION_ALIAS(spi_bvs, RELATIVE, 2, 2);

void    spi_register_flow_control_opcodes(spi_cpu_t *cpu) {
    cpu->opcode_table[0x90] = &SPI_GET_INSTRUCTION_ALIAS(spi_bcc, RELATIVE);
    cpu->opcode_table[0xF0] = &SPI_GET_INSTRUCTION_ALIAS(spi_bcs, RELATIVE);
    cpu->opcode_table[0xB0] = &SPI_GET_INSTRUCTION_ALIAS(spi_beq, RELATIVE);
    cpu->opcode_table[0x30] = &SPI_GET_INSTRUCTION_ALIAS(spi_bmi, RELATIVE);
    cpu->opcode_table[0xD0] = &SPI_GET_INSTRUCTION_ALIAS(spi_bne, RELATIVE);
    cpu->opcode_table[0x10] = &SPI_GET_INSTRUCTION_ALIAS(spi_bpl, RELATIVE);
    cpu->opcode_table[0x50] = &SPI_GET_INSTRUCTION_ALIAS(spi_bvc, RELATIVE);
    cpu->opcode_table[0x70] = &SPI_GET_INSTRUCTION_ALIAS(spi_bvs, RELATIVE);
}
