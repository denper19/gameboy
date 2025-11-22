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


void decode(u8 opcode) {
    
    u8 x = (opcode >> 6) & 0x3; // bits 7-6
    u8 y = (opcode >> 2) & 0x7; // bits 5-3
    u8 z = (opcode >> 0) & 0x3; // bits 0-2
    u8 p = (opcode >> 3) & 0x3; // bits 5-4
    u8 q = (opcode >> 2) & 0x1; // bit 3


    switch (x)
    {
        case 0:
        {
            switch (z) {

                case 0:



            }
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