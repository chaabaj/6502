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

# include "tools/instruction.h"

void spi_test_init_registers(spi_cpu_t *cpu, spi_byte_t va,
                             spi_byte_t vx, spi_byte_t vy) {
    cpu->registers[A] = va;
    cpu->registers[X] = vx;
    cpu->registers[Y] = vy;
}

void spi_test_instruction(const spi_byte_t *opcodes, const uint16_t *values,
                          size_t nb_opcodes, spi_test_fn_t fn,
                          spi_cpu_t *cpu, spi_byte_t *mem) {

    for (size_t i = 0; i < nb_opcodes; ++i) {
        cpu->flags = 0;
        cpu->pc = 0xC000;
        cpu->sp = 0xFF;
        SPI_ENABLE_FLAG(cpu->flags, DISABLE_INTERRUPTS);
        mem[0xC000] = opcodes[i];
        mem[0xC001] = (spi_byte_t)(values[i] & 0xFF);
        mem[0xC002] = (spi_byte_t)(values[i] >> 8);
        spi_cpu_execute(cpu, mem);
        (*fn)(cpu, mem);
    }

}