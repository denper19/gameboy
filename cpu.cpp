#include "cpu.hpp"

u8 gb_cpu::get_table_r(u8 reg){
    /**
    * Defines table r from the algoritmic decoding 
    */
    switch(reg) {
        case 0: return bc.reg8_lo;
        case 1: return bc.reg8_hi;
        case 2: return de.reg8_lo;
        case 3: return de.reg8_hi;
        case 4: return hl.reg8_lo;
        case 5: return hl.reg8_hi;
        case 6: return read(hl.reg16);
        case 7: return af.reg8_lo;
    };

}


u8 gb_cpu::get_table_rp(u8 reg) {
    /**
    * Defines table rp from algorithmic decoding
    */
    switch(reg) {
        case 0: return bc.reg16;
        case 1: return de.reg16;
        case 2: return hl.reg16;
        case 3: return stackptr;
    };
}


u8 gb_cpu::get_table_rp2(u8 reg) {
    /**
    * Defines table rp2 from algorithmic decoding
    * Similar to table rp but reg == 3 we return af 
    */
    if (reg == 3) { return af.reg16; }
    else { return get_table_rp(reg); }
}

bool gb_cpu::get_flags_cc(u8 y) {
    /**
    * Returns flag values
    */
   switch(y) {
        case 0:
            return;
   };
}


void gb_cpu::opcode_row1(u8 q, u8 y, u8 p) {

    switch (y) {
        case 0: return; // nop
        // ld (nn), sp
        case 1: 
            write(read16(progcount), stackptr); 
            progcount += 2; 
            return;
        case 2: return; // stop
        // jr d
        case 3: 
            progcount += read(progcount);
            return;
        // jr cc[y-4], d
        case 4: 
            bool flag_value = get_flags_cc(y-4);
            if (flag_value == true) {
                progcount += read(progcount);
            }
            return; 
    }

}


void gb_cpu::opcode_row2(u8 q, u8 y, u8 p) {

    if (q == 0) {
        // LD rp[p], nn

    }
    else {
        // ADD HL, rp[p]    
    }

}

void gb_cpu::decode_and_execute_opcode(u8 opcode) {
    
    u8 x = (opcode >> 6) & 0x3; // bits 7-6
    u8 y = (opcode >> 2) & 0x7; // bits 5-3
    u8 z = (opcode >> 0) & 0x3; // bits 0-2
    u8 p = (opcode >> 3) & 0x3; // bits 5-4
    u8 q = (opcode >> 2) & 0x1; // bit 3


    switch (x)
    {
        case 0:{
            switch (z) {
                case 0: opcode_row1(q, y, p); break;
                case 1: opcode_row2(q, y, p); break;
                // case 2: opcode_row3(q, y, p); break;
                // case 3: opcode_row4(q, y, p); break;
                // case 4: opcode_row5(q, y, p); break;
                // case 5: opcode_row6(q, y, p); break;
                // case 6: opcode_row7(q, y, p); break;
            };
        }
    };

}

u8 gb_cpu::read(u16 addr) {
    return memory[addr];
}


u16 gb_cpu::read16(u16 addr) {
    u8 lo = read(addr);
    u8 hi = read(addr+1);
    u16 val = (hi << 8) | lo;
    return val;
}


void gb_cpu::write(u16 addr, u8 data) {
    memory[addr] = data;
}


void gb_cpu::step_cpu(int cycles){

    while (cycles > 0) {

        u8 opcode = read(progcount++);
        decode_and_execute_opcode(opcode);
        cycles--;
    }
}