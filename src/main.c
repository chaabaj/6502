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
#include <stdlib.h>
#include <string.h>
#include "spi/cpu/cpu_6502.h"
#include "spi/error.h"
#include "spi/debug.h"

#define MEM_SIZE 64 * 1024

static void print_usage() {
    puts("./6502 <binary>");
}

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
    int                         err;
    const spi_program_config_t  cfg = prg_16k();

    bzero(memory, MEM_SIZE);
    if (ac > 1) {
        PRINT_DEBUG("START LOADING PROGRAM %s", av[1]);
        if ((err = spi_load_program(av[1], memory, &cfg, IGNORE_PRG_SIZE)) != 0) {
            spi_print_error(err);
            return EXIT_FAILURE;
        }
        PRINT_DEBUG("PROGRAM LOADED", "")
        spi_cpu_init(&cpu, 20, MHZ);
        spi_dump_memory(memory, MEM_SIZE, 0xFFFC, 0xFFFF);
        spi_cpu_reset(&cpu, memory, &cfg);

        while (1) {
            spi_cpu_execute(&cpu, memory);
            getchar();
        }
    } else {
        print_usage();
    }
    return 0;
}
