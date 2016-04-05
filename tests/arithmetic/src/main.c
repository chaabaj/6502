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

#include <stdio.h>
#include <string.h>
#include "spi/cpu/cpu_6502.h"
#include "constants.h"
#include "test_adc.h"


static spi_program_config_t prg_16k() {
    spi_program_config_t    cfg;

    cfg.load_addr = 0xC000;
    cfg.prg_size = 16 * 1024;
    cfg.reset_vector_offset = 0xFFFC;
    cfg.stack_addr = 0x100;
    return cfg;
}



int main(int ac, char **av) {
    spi_byte_t                  memory[MEM_SIZE];
    spi_cpu_t                   cpu;
    const spi_program_config_t  cfg = prg_16k();

    bzero(memory, MEM_SIZE);
    spi_cpu_init(&cpu, 20, MHZ);
    spi_dump_memory(memory, MEM_SIZE, 0xFFFC, 0xFFFF);
    spi_cpu_reset(&cpu, memory, &cfg);
    spi_run_test_adc(&cpu, memory);
    return 0;
}
