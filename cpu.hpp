#pragma once

#include <iostream>

#define REG_A 0
#define REG_B 1
#define REG_C 2
#define REG_D 3
#define REG_E 4
#define REG_H 5
#define REG_L 6

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

    void opcode_row1(u8 q, u8 y, u8 p);
    //************************************************** */

    u8 read(u16 addr);

    u16 read16(u16 addr);

    void write(u16 addr, u8 data);

    void step_cpu(int cycles);

    void decode_and_execute_opcode(u8 opcode);

    void execute_prefix_cb(u8 opcode);

};