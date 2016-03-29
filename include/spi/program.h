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

#ifndef SPI_PROGRAM_H
# define SPI_PROGRAM_H

# include <stddef.h>
# include "spi/cpu/types.h"

struct spi_program_config_s {
    size_t          prg_size;
    spi_mem_addr_t  reset_vector_offset;
    spi_mem_addr_t  load_addr;
};

typedef struct spi_program_config_s spi_program_config_t;

/*
 * Load a 6502 program
 * You must specify a program configuration to tell where to put the program
 * and tell the cpu where is the reset vector
 */
int spi_load_program(const char *file, spi_byte_t *mem, const spi_program_config_t *config);

#endif //SPI_PROGRAM_H
