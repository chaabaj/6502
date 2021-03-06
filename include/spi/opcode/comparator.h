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


#ifndef SPI_OPCODE_COMPARATOR_H
# define SPI_OPCODE_COMPARATOR_H

# include "spi/cpu/cpu_6502.h"
# include "spi/dll_export.h"

# ifdef __cplusplus
extern "C" {
# endif

DLL_EXPORT void spi_cmp(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem);

DLL_EXPORT void spi_cpx(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem);

DLL_EXPORT void spi_cpy(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem);

DLL_EXPORT void spi_register_comparator_opcodes(spi_cpu_t *cpu);

# ifdef __cplusplus
 }
# endif

#endif //SPI_OPCODE_COMPARATOR_H
