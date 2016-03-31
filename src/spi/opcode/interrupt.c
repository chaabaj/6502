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

#include "spi/opcode/interrupt.h"
#include "spi/cpu/convert.h"

void    spi_brk(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    if (SPI_GET_FLAG(cpu->flags, DISABLE_INTERRUPTS) == 0) {
        spi_mem_addr_t brk_addr = SPI_TO_UINT16(mem[0xFFFF], mem[0xFFFE]);

        spi_cpu_push_stack(cpu, mem, (spi_byte_t)(cpu->pc >> 8));
        spi_cpu_push_stack(cpu, mem, (spi_byte_t)(cpu->pc & 0x00FF));
        spi_cpu_push_stack(cpu, mem, (spi_byte_t )(cpu->flags | 0x10));
        cpu->pc = brk_addr;
    }
}

SPI_INSTRUCTION_ALIAS(spi_brk, IMPLIED, 1, 7);

void    spi_register_interrupt_opcodes(spi_cpu_t *cpu) {
    cpu->opcode_table[0x00] = &SPI_GET_INSTRUCTION_ALIAS(spi_brk, IMPLIED);
}