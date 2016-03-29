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

#ifndef SPI_CPU_6502_H
# define SPI_CPU_6502_H

# include <stdint.h>
# include "spi/cpu/types.h"
# include "spi/cpu/bits.h"
# include "spi/program.h"

# define SPI_NB_OPCODE 256
# define SPI_NB_REGISTER 3
# define SPI_FREQUENCY 60

/*
 * Utility macro for setting and getting flags for cpu status flags
 */
# define SPI_GET_FLAGS(flags, index) SPI_GET_BIT(flags, index)
# define SPI_ENABLE_FLAGS(flags, index) SPI_ENABLE_BIT(flags, index)
# define SPI_ENABLE_FLAGS_IF(flags, index, cond) if (cond) { \
        SPI_ENABLE_FLAGS(flags, index); \
    }
# define SPI_DISABLE_FLAGS(flags, index) SPI_DISABLE_BIT(flags, index)
# define SPI_DISABLE_FLGS_IF(flags, index, cond) if (cond) { \
        SPI_DISABLE_FLAGS(flags, index); \
    }
# define SPI_SET_FLAGS(flags, index, val) SPI_SET_BIT(flags, index, val)

/*
 * Converting 8 bits number into bcd number
 */
# define SPI_BCD(x) ((x >> 4) + (x & 0xFFFF))

/*
 * Macro for declaring and getting instruction alias
 * It was designed to avoid code duplication since 6502 have many opcode that doing the same thing
 * but with a different address mode
 * It's an instruction alias code generator
 */
# define SPI_GET_INSTRUCTION_ALIAS(name, address_mode) name##address_mode
# define SPI_INSTRUCTION_ALIAS(name, address_mode, size, nb_cycle) \
    static int32_t SPI_GET_INSTRUCTION_ALIAS(name, address_mode)(spi_cpu_t *cpu, spi_byte_t *mem) { \
        ++cpu->pc;                      \
        name(cpu, address_mode, mem);   \
        cpu->pc += size - 1;            \
        return nb_cycle;                \
    }

enum spi_cpu_register_e {
    X,
    Y,
    A
};

enum spi_clock_speed_unit_e {
    HZ = 1,
    KHZ = HZ * 1000,
    MHZ = KHZ * 1000
};

typedef enum spi_clock_speed_unit_e spi_clock_speed_unit_t;

enum spi_address_mode_e {
    ACCUMULATOR,
    IMPLIED,
    IMMEDIATE,
    ZERO_PAGE,
    ZERO_PAGE_INDEXED_X,
    ZERO_PAGE_INDEXED_Y,
    ABSOLUTE,
    ABSOLUTE_INDEXED_X,
    ABSOLUTE_INDEXED_Y,
    INDIRECT,
    INDEXED_INDIRECT,
    INDIRECT_INDEXED,
    RELATIVE,
};

typedef enum spi_address_mode_e spi_address_mode_t;

enum spi_cpu_status_flags_e {
    NEGATIVE,
    OVERFLOW,
    UNUSED,
    BRK_EXECUTED,
    ENABLE_BCD,
    BLOCK_INTERRUPTS,
    ZERO,
    CARRY
};

typedef enum spi_cpu_status_flags_e spi_cpu_status_flags_t;

struct spi_cpu_s {
    spi_byte_t  registers[SPI_NB_REGISTER];
    spi_byte_t  flags;
    uint16_t    pc;
    uint16_t    sp;
    uint32_t    available_cycles;
    uint32_t    total_cycles;
    int32_t	    (*opcode_table[SPI_NB_OPCODE])(struct spi_cpu_s *cpu, spi_byte_t *mem);
};

typedef struct spi_cpu_s spi_cpu_t;

/*
 * Initialize the cpu
 * reset registers and set the processor speed
 */
void            spi_cpu_init(spi_cpu_t *cpu, double speed, spi_clock_speed_unit_t unit);

/*
 * Reset the cpu
 * Set the stack to the top
 * 6502 processor read the reset vector table in memory to know where the program start
 * The reset vector table is located at 0xFFFD and 0xFFFC
 */
void            spi_cpu_reset(spi_cpu_t *cpu, spi_byte_t *byte, const spi_program_config_t *cfg);

/**
 * Execute the next opcode
 */
void            spi_cpu_execute(spi_cpu_t *cpu, spi_byte_t *mem);

/**
 * Get memory address using addressing mode
 */

spi_mem_addr_t  spi_cpu_get_addr(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem);

/*
 * Read value from memory
 * The addressing mode tell how to calculate the address
 * Please read 6502 addressing mode for more information
 */
spi_byte_t      spi_cpu_read_value(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem);

/*
 * Write value to memory
 * The addressing mode tell how to calculate the address
 * Please read 6502 addressing mode for more information
 */
void            spi_cpu_write_value(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem, spi_byte_t value);

#endif //SPI_CPU_6502_H
