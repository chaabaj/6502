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

#include <assert.h>
#include "test_adc.h"

static void test_adc_immediate(spi_cpu_t *cpu, spi_byte_t *mem) {
    cpu->pc = 0xC000;
    mem[0xC000] = 0x69;
    mem[0xC001] = 40;
    spi_cpu_execute(cpu, mem);
    assert(cpu->registers[A] == 40);
}


static void test_adc_immediate_with_carry(spi_cpu_t *cpu, spi_byte_t *mem) {
    cpu->pc = 0xC000;
    mem[0xC000] = 0x69;
    mem[0xC001] = 40;
    SPI_ENABLE_FLAG(cpu->flags, CARRY);
    cpu->registers[A] = 0;
    spi_cpu_execute(cpu, mem);
    assert(cpu->registers[A] == 41);
}

static void test_adc_immediate_with_decimal_mode(spi_cpu_t *cpu, spi_byte_t *mem) {
    cpu->pc = 0xC000;
    mem[0xC000] = 0x69;
    mem[0xC001] = 50;
}

void spi_run_test_adc(spi_cpu_t *cpu, spi_byte_t *mem) {
    test_adc_immediate(cpu, mem);
    test_adc_immediate_with_carry(cpu, mem);
}