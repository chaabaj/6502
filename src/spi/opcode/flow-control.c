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
#include "spi/cpu/convert.h"

SPI_OPCODE_CONDITIONAL_BRANCH(spi_bcc, SPI_GET_FLAG(cpu->flags, CARRY) == 0);
SPI_OPCODE_CONDITIONAL_BRANCH(spi_bcs, SPI_GET_FLAG(cpu->flags, CARRY) == 1);
SPI_OPCODE_CONDITIONAL_BRANCH(spi_beq, SPI_GET_FLAG(cpu->flags, ZERO) == 1);
SPI_OPCODE_CONDITIONAL_BRANCH(spi_bne, SPI_GET_FLAG(cpu->flags, ZERO) == 0);
SPI_OPCODE_CONDITIONAL_BRANCH(spi_bmi, SPI_GET_FLAG(cpu->flags, NEGATIVE) == 1);
SPI_OPCODE_CONDITIONAL_BRANCH(spi_bpl, SPI_GET_FLAG(cpu->flags, NEGATIVE) == 0);
SPI_OPCODE_CONDITIONAL_BRANCH(spi_bvc, SPI_GET_FLAG(cpu->flags, OVERFLOW) == 0);
SPI_OPCODE_CONDITIONAL_BRANCH(spi_bvs, SPI_GET_FLAG(cpu->flags, OVERFLOW) == 1);

void    spi_jmp(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    PRINT_DEBUG("JUMP TO ADDR : %d",  spi_cpu_get_addr(cpu, mode, mem));
    cpu->pc = spi_cpu_get_addr(cpu, mode, mem);
    cpu->jmp_occured = 1;
}

void    spi_jsr(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_cpu_push_stack(cpu, mem, (spi_byte_t )((cpu->pc + 2) >> 8));
    spi_cpu_push_stack(cpu, mem, (spi_byte_t)((cpu->pc + 2) & 0x00FF));
    cpu->pc = spi_cpu_get_addr(cpu, mode, mem);
    cpu->jmp_occured = 1;
}

void spi_rti(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_byte_t h_addr;
    spi_byte_t l_addr;

    cpu->flags = spi_cpu_pull_stack(cpu, mem);
    l_addr = spi_cpu_pull_stack(cpu, mem);
    h_addr = spi_cpu_pull_stack(cpu, mem);
    cpu->pc = SPI_TO_UINT16(h_addr, l_addr);
}

void spi_rts(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    spi_byte_t h_addr;
    spi_byte_t l_addr;

    l_addr = spi_cpu_pull_stack(cpu, mem);
    h_addr = spi_cpu_pull_stack(cpu, mem);
    cpu->pc = (spi_mem_addr_t )(SPI_TO_UINT16(h_addr, l_addr));
}

SPI_INSTRUCTION_ALIAS(spi_bcc, RELATIVE, 2, 2);

SPI_INSTRUCTION_ALIAS(spi_bcs, RELATIVE, 2, 2);

SPI_INSTRUCTION_ALIAS(spi_beq, RELATIVE, 2, 2);

SPI_INSTRUCTION_ALIAS(spi_bmi, RELATIVE, 2, 2);

SPI_INSTRUCTION_ALIAS(spi_bne, RELATIVE, 2, 2);

SPI_INSTRUCTION_ALIAS(spi_bpl, RELATIVE, 2, 2);

SPI_INSTRUCTION_ALIAS(spi_bvc, RELATIVE, 2, 2);

SPI_INSTRUCTION_ALIAS(spi_bvs, RELATIVE, 2, 2);

SPI_INSTRUCTION_ALIAS(spi_jmp, ABSOLUTE, 3, 3);
SPI_INSTRUCTION_ALIAS(spi_jmp, INDIRECT, 3, 5);

SPI_INSTRUCTION_ALIAS(spi_jsr, ABSOLUTE, 3, 6);

SPI_INSTRUCTION_ALIAS(spi_rti, IMPLIED, 1, 6);

SPI_INSTRUCTION_ALIAS(spi_rts, IMPLIED, 1, 6);

void    spi_register_flow_control_opcodes(spi_cpu_t *cpu) {
    cpu->opcode_table[0x90] = &SPI_GET_INSTRUCTION_ALIAS(spi_bcc, RELATIVE);

    cpu->opcode_table[0xB0] = &SPI_GET_INSTRUCTION_ALIAS(spi_bcs, RELATIVE);

    cpu->opcode_table[0xF0] = &SPI_GET_INSTRUCTION_ALIAS(spi_beq, RELATIVE);

    cpu->opcode_table[0x30] = &SPI_GET_INSTRUCTION_ALIAS(spi_bmi, RELATIVE);

    cpu->opcode_table[0xD0] = &SPI_GET_INSTRUCTION_ALIAS(spi_bne, RELATIVE);

    cpu->opcode_table[0x10] = &SPI_GET_INSTRUCTION_ALIAS(spi_bpl, RELATIVE);

    cpu->opcode_table[0x50] = &SPI_GET_INSTRUCTION_ALIAS(spi_bvc, RELATIVE);

    cpu->opcode_table[0x70] = &SPI_GET_INSTRUCTION_ALIAS(spi_bvs, RELATIVE);

    cpu->opcode_table[0x4C] = &SPI_GET_INSTRUCTION_ALIAS(spi_jmp, ABSOLUTE);
    cpu->opcode_table[0x6C] = &SPI_GET_INSTRUCTION_ALIAS(spi_jmp, INDIRECT);

    cpu->opcode_table[0x20] = &SPI_GET_INSTRUCTION_ALIAS(spi_jsr, ABSOLUTE);

    cpu->opcode_table[0x40] = &SPI_GET_INSTRUCTION_ALIAS(spi_rti, IMPLIED);

    cpu->opcode_table[0x60] = &SPI_GET_INSTRUCTION_ALIAS(spi_rts, IMPLIED);
}
