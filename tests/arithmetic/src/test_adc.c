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

#include <strings.h>
#include <assert.h>
#include "constants.h"
#include "test_adc.h"
#include "tools/instruction.h"

static void test_adc_basic(spi_cpu_t *cpu, spi_byte_t *mem) {
    (void)mem;
    assert(cpu->registers[A] == 0x40);
}


static void test_adc_with_carry(spi_cpu_t *cpu, spi_byte_t *mem) {
    (void)mem;
    assert(cpu->registers[A] == 0x41);
}

static void test_adc_with_overflow(spi_cpu_t *cpu, spi_byte_t *mem) {
    (void)mem;
    assert(cpu->registers[A] == 0x39);
    assert(SPI_GET_FLAG(cpu->flags, CARRY) == 1);
    assert(SPI_GET_FLAG(cpu->flags, OVERFLOW) == 1);
}

void spi_run_test_adc(spi_cpu_t *cpu, spi_byte_t *mem) {
    spi_byte_t  opcodes[8] = {0x69, 0x65, 0x75, 0x6D, 0x7D, 0x79, 0x61, 0x71};
    uint16_t    value = 0x40;

    SPI_UNIT_TEST(cpu, mem, MEM_SIZE, {
        bzero(env.mem, MEM_SIZE);
        env.mem[0x40] = 0x40;
        env.mem[0x41] = 0x40;
        env.mem[0x4040] = 0x40;
        env.mem[0x4041] = 0x40;
        env.mem[0x4141] = 0x40;
        env.cpu.registers[X] = 1;
        env.cpu.registers[Y] = 1;
        spi_test_instruction(opcodes, value, 8,
                             &test_adc_basic, &env);
    });

    SPI_UNIT_TEST(cpu, mem, MEM_SIZE, {
        bzero(env.mem, MEM_SIZE);
        env.mem[0x40] = 0x40;
        env.mem[0x41] = 0x40;
        env.mem[0x4040] = 0x40;
        env.mem[0x4041] = 0x40;
        env.mem[0x4141] = 0x40;
        env.cpu.registers[X] = 1;
        env.cpu.registers[Y] = 1;
        SPI_ENABLE_FLAG(env.cpu.flags, CARRY);
        spi_test_instruction(opcodes, value, 8,
                             &test_adc_with_carry, &env);
    });

    /*spi_test_instruction(opcodes, values, 8, &test_adc_with_carry,
                         cpu, 1 << CARRY, mem); */

    /*spi_test_init_registers(cpu, 0xFF, 0, 0);

    spi_test_instruction(opcodes, values, 8, &test_adc_with_overflow,
                         cpu, 1 << DISABLE_INTERRUPTS, mem);*/
}