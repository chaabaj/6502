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
#include "spi/program.h"
#include "spi/error.h"

int spi_load_program(const char *path, spi_byte_t *mem, const spi_program_config_t *config) {
    FILE            *file = fopen(path, "rb");
    size_t          len = 0;
    size_t          ret = 1;

    if (!file) {
        return SPI_FILE_NOT_FOUND;
    }
    while (ret != 0) {
        ret = fread(&mem[config->load_addr], 1, config->prg_size, file);
        len += ret;
    }
    if (ferror(file)) {
        return SPI_CANNOT_READ_FILE;
    }
    else if (len != config->prg_size) {
        return SPI_INVALID_ROM_SIZE;
    }
    fclose(file);
    return 0;
}
