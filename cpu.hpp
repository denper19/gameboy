#pragma once

#include <iostream>

#define FLAGS_NZ 0
#define FLAGS_Z  1
#define FLAGS_NC 2
#define FLAGS_C  3

using u8 = std::uint8_t;
using u16 = std::uint16_t;

union gb_reg {
    struct {
        u8 reg8_hi;
        u8 reg8_lo;
    };
    u16 reg16;
};

class gb_cpu {

    public:

    gb_reg af {0};
    gb_reg bc {0};
    gb_reg de {0};
    gb_reg hl {0};
    u16 stackptr = 0;
    u16 progcount = 0;

    u8 memory[0xffff];

    public:

    /**
    * The algorithmic approach to decode the opcodes is being used 
    * It requires certain 'tables' to be defined
    * https://archive.gbdev.io/salvage/decoding_gbz80_opcodes/Decoding%20Gamboy%20Z80%20Opcodes.html
    */
    u8 get_table_r(u8 reg);

    u8 get_table_rp(u8 reg);

    u8 get_table_rp2(u8 reg);

    bool get_flags_cc(u8 y);

    void opcode_row1(u8 q, u8 y, u8 p);
    void opcode_row2(u8 q, u8 y, u8 p);
    //************************************************** */

    u8 read(u16 addr);

    u16 read16(u16 addr);

    void write(u16 addr, u8 data);

    void step_cpu(int cycles);

    void decode_and_execute_opcode(u8 opcode);

    void execute_prefix_cb(u8 opcode);

};