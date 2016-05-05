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

#ifndef SPI_OPCODE_FLOW_CONTROL_H
# define SPI_OPCODE_FLOW_CONTROL_H

# include "spi/cpu/cpu_6502.h"
# include "spi/dll_export.h"

# define SPI_OPCODE_CONDITIONAL_BRANCH(name, condition) \
    void name(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem) {   \
        int8_t  rel_addr = spi_cpu_get_addr(cpu, mode, mem);                \
                                                                            \
        if (condition) {                                                    \
            cpu->jmp_occured = 1;                                           \
            cpu->pc += rel_addr + 1;                                        \
        }                                                                   \
    }

# ifdef __cplusplus
extern "C" {
# endif

DLL_EXPORT void spi_bcs(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem);

DLL_EXPORT void spi_bcc(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem);

DLL_EXPORT void spi_beq(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem);

DLL_EXPORT void spi_bmi(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem);

DLL_EXPORT void spi_bne(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem);

DLL_EXPORT void spi_bpl(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem);

DLL_EXPORT void spi_bvc(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem);

DLL_EXPORT void spi_bvs(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem);

DLL_EXPORT void spi_jmp(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem);

DLL_EXPORT void spi_jsr(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem);

DLL_EXPORT void spi_rti(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem);

DLL_EXPORT void spi_rts(spi_cpu_t *cpu, spi_address_mode_t mode, spi_byte_t *mem);

DLL_EXPORT void spi_register_flow_control_opcodes(spi_cpu_t *cpu);

# ifdef __cplusplus
 }
# endif

#endif //SPI_OPCODE_FLOW_CONTROL_H
