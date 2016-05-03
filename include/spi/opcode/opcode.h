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

#ifndef SPI_OPCODE_OPCODE_H
# define SPI_OPCODE_OPCODE_H

# include "spi/opcode/arithmetic.h"
# include "spi/opcode/flow-control.h"
# include "spi/opcode/interrupt.h"
# include "spi/opcode/cpu.h"
# include "spi/opcode/comparator.h"
# include "spi/opcode/bitwise.h"
# include "spi/opcode/memory.h"
# include "spi/opcode/stack.h"
# include "spi/dll_export.h"

# ifdef __cplusplus
extern "C" {
# endif

DLL_EXPORT void spi_register_opcodes(spi_cpu_t *cpu);

# ifdef __cplusplus
 }
# endif

#endif //SPI_OPCODE_OPCODE_H
