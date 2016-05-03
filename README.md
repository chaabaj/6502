# 6502
6502 8-bit CPU emulator

This is a experimental 6502 cpu emulator.
The implementation is based on the 6502 reference guide : http://homepage.ntlworld.com/cyborgsystems/CS_Main/6502/6502.htm

Actually i only tested the program on my Debian.
It should also compile in Windows and MacOSX.

Goals :

The goals of this project is to learn cpu emulation.
It's also beginning step for other emulator i want to write that are based in 6502.

The 6502 cpu emulator will be purpose as a shared library for reuse purpose in other emulator

Debugger usage:

```sh
./6502_debugger <binary>
```

You can use this assembler to compile your own program : https://hkn.eecs.berkeley.edu/~mcmartin/P65/ophis-ref.html

Roadmap :
* Initialization and loading : Testing
* Instruction implementation : Testing
* Shared library : Todo
* Clock synchronization : Todo
* Debbuging tools like memory dump, cpu state, breakpoint, ... : Todo
