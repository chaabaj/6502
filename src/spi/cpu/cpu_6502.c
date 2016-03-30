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

#include <string.h>
#include "spi/cpu/cpu_6502.h"
#include "spi/cpu/convert.h"
#include "spi/opcode/opcode.h"
#include "spi/debug.h"

spi_mem_addr_t  spi_cpu_get_addr(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    switch (mode) {
        case IMMEDIATE : return cpu->pc;
        case RELATIVE : return cpu->pc;
        case ABSOLUTE : return SPI_TO_UINT16(mem[cpu->pc + 1], mem[cpu->pc]);
        case ABSOLUTE_INDEXED_X : {
            return (uint16_t)((SPI_TO_UINT16(mem[cpu->pc + 1], (mem[cpu->pc] + cpu->registers[X]))) & 0xFFFF);
        }
        case ABSOLUTE_INDEXED_Y : {
            return (uint16_t)((SPI_TO_UINT16(mem[cpu->pc + 1], (mem[cpu->pc] + cpu->registers[Y]))) & 0xFFFF);
        }
        case ZERO_PAGE : return mem[cpu->pc];
        case ZERO_PAGE_INDEXED_X : return (uint16_t)((mem[cpu->pc] + cpu->registers[X]) & 0xFF);
        case ZERO_PAGE_INDEXED_Y : return (uint16_t)((mem[cpu->pc] + cpu->registers[Y]) & 0xFF);
        case INDIRECT : return SPI_TO_UINT16(mem[cpu->pc + 1], mem[cpu->pc]);
        case INDEXED_INDIRECT : {
            return SPI_TO_UINT16((mem[cpu->pc] + cpu->registers[X] + 1), (mem[cpu->pc] + cpu->registers[X]));
        }
        case INDIRECT_INDEXED : {
            spi_mem_addr_t addr = SPI_TO_UINT16(mem[cpu->pc + 1], mem[cpu->pc]);

            return (spi_mem_addr_t)((addr + cpu->registers[Y]) & 0xFFFF);
        }
        default: {
            // Other case have no sense to read a value in the memory
            return 0;
        }
    }
}

spi_byte_t  spi_cpu_read_value(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {
    return mem[spi_cpu_get_addr(cpu, mode, mem)];
}

void    spi_cpu_write_value(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem, spi_byte_t value) {
    mem[spi_cpu_get_addr(cpu, mode, mem)] = value;
}

void    spi_cpu_init(spi_cpu_t *cpu, double speed, enum spi_clock_speed_unit_e unit) {
    PRINT_DEBUG("INITIALIZE CPU", "");
    cpu->flags = 0;
    bzero(cpu->registers, SPI_NB_OPCODE);
    bzero(cpu->opcode_table, 0);
    cpu->total_cycles = (uint32_t )((speed * unit) / SPI_FREQUENCY);
    cpu->available_cycles = cpu->total_cycles;
    spi_register_opcodes(cpu);
}

void    spi_cpu_reset(spi_cpu_t *cpu, spi_byte_t *mem, const spi_program_config_t *cfg) {
    PRINT_DEBUG("RESET CPU", "");
    cpu->pc = SPI_TO_UINT16(mem[cfg->reset_vector_offset + 1], mem[cfg->reset_vector_offset]);
    printf("PC iIS INITIALIZED AT : %X\n", cpu->pc);
    cpu->sp = 0x1FF;
    SPI_ENABLE_FLAGS(cpu->flags, BLOCK_INTERRUPTS);
}

void    spi_cpu_execute(spi_cpu_t *cpu, spi_byte_t *mem) {
    spi_byte_t  opcode = (spi_byte_t)mem[cpu->pc];

    PRINT_DEBUG("CURRENT PROGRAM COUNTER : %d", cpu->pc);
    PRINT_DEBUG("SEARCH OPCODE : %d", opcode);
    if (cpu->opcode_table[opcode]) {
        PRINT_DEBUG("EXECUTE OPCODE : %d", opcode);
        cpu->opcode_table[opcode](cpu, mem);
    }
}
