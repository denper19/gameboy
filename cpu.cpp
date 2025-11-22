#include "cpu.hpp"

u8 gb_cpu::get_register(u8 reg){
    
    switch(reg){
        case REG_A:
            return 0;
        case REG_B:
            return 0;
        case REG_C:
            return 0;
        default:
            return 0;
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


void gb_cpu::decode_and_execute_opcode(u8 opcode) {

    switch(opcode) {
        case 0x00: break; // NOP
        // LD BC, d16
        case 0x01: bc.reg16 = read16(progcount); progcount += 2; break;
        // LD de, d16
        case 0x11: de.reg16 = read16(progcount); progcount += 2; break;
        //LD hl, d16
        case 0x21: hl.reg16 = read16(progcount); progcount += 2; break;
        //LD sp, d16
        case 0x31: stackptr = read16(progcount); progcount += 2; break;
        // LD B, X
        case 0x40: bc.reg8_hi = bc.reg8_hi; break; // X = B
        case 0x41: bc.reg8_hi = bc.reg8_lo; break; // X = C
        case 0x42: bc.reg8_hi = de.reg8_hi; break; // X = D
        case 0x43: bc.reg8_hi = de.reg8_lo; break; // X = E
        case 0x44: bc.reg8_hi = hl.reg8_hi; break; // X = H
        case 0x45: bc.reg8_hi = hl.reg8_lo; break; // X = L
        case 0x46: bc.reg8_hi = read(hl.reg16); break; // X = [HL]
        case 0x47: bc.reg8_hi = af.reg8_hi; break; // X = A
        // LD C, X
        case 0x48: bc.reg8_lo = bc.reg8_hi; break; // X = B
        case 0x49: bc.reg8_lo = bc.reg8_lo; break; // X = C
        case 0x4A: bc.reg8_lo = de.reg8_hi; break; // X = D
        case 0x4B: bc.reg8_lo = de.reg8_lo; break; // X = E
        case 0x4C: bc.reg8_lo = hl.reg8_hi; break; // X = H
        case 0x4D: bc.reg8_lo = hl.reg8_lo; break; // X = L
        case 0x4E: bc.reg8_lo = read(hl.reg16); break; // X = [HL]
        case 0x4F: bc.reg8_lo = af.reg8_hi; break; // X = A
        // LD D, X
        case 0x50: de.reg8_hi = bc.reg8_hi; break; // X = B
        case 0x51: de.reg8_hi = bc.reg8_lo; break; // X = C
        case 0x52: de.reg8_hi = de.reg8_hi; break; // X = D
        case 0x53: de.reg8_hi = de.reg8_lo; break; // X = E
        case 0x54: de.reg8_hi = hl.reg8_hi; break; // X = H
        case 0x55: de.reg8_hi = hl.reg8_lo; break; // X = L
        case 0x56: de.reg8_hi = read(hl.reg16); break; // X = [HL]
        case 0x57: de.reg8_hi = af.reg8_hi; break; // X = A
        // LD E, X
        case 0x58: de.reg8_lo = bc.reg8_hi; break; // X = B
        case 0x59: de.reg8_lo = bc.reg8_lo; break; // X = C
        case 0x5A: de.reg8_lo = de.reg8_hi; break; // X = D
        case 0x5B: de.reg8_lo = de.reg8_lo; break; // X = E
        case 0x5C: de.reg8_lo = hl.reg8_hi; break; // X = H
        case 0x5D: de.reg8_lo = hl.reg8_lo; break; // X = L
        case 0x5E: de.reg8_lo = read(hl.reg16); break; // X = [HL]
        case 0x5F: de.reg8_lo = af.reg8_hi; break; // X = A
        // LD H, X
        case 0x60: hl.reg8_hi = bc.reg8_hi; break; // X = B
        case 0x61: hl.reg8_hi = bc.reg8_lo; break; // X = C
        case 0x62: hl.reg8_hi = de.reg8_hi; break; // X = D
        case 0x63: hl.reg8_hi = de.reg8_lo; break; // X = E
        case 0x64: hl.reg8_hi = hl.reg8_hi; break; // X = H
        case 0x65: hl.reg8_hi = hl.reg8_lo; break; // X = L
        case 0x66: hl.reg8_hi = read(hl.reg16); break; // X = [HL]
        case 0x67: hl.reg8_hi = af.reg8_hi; break; // X = A
        // LD L, X
        case 0x68: hl.reg8_lo = bc.reg8_hi; break; // X = B
        case 0x69: hl.reg8_lo = bc.reg8_lo; break; // X = C
        case 0x6A: hl.reg8_lo = de.reg8_hi; break; // X = D
        case 0x6B: hl.reg8_lo = de.reg8_lo; break; // X = E
        case 0x6C: hl.reg8_lo = hl.reg8_hi; break; // X = H
        case 0x6D: hl.reg8_lo = hl.reg8_lo; break; // X = L
        case 0x6E: hl.reg8_lo = read(hl.reg16); break; // X = [HL]
        case 0x6F: hl.reg8_lo = af.reg8_hi; break; // X = A
        // LD [HL], X
        case 0x70: write(hl.reg16, bc.reg8_hi); break; // X = B
        case 0x71: write(hl.reg16, bc.reg8_lo); break; // X = C
        case 0x72: write(hl.reg16, de.reg8_hi); break; // X = D
        case 0x73: write(hl.reg16, de.reg8_lo); break; // X = E
        case 0x74: write(hl.reg16, hl.reg8_hi); break; // X = H
        case 0x75: write(hl.reg16, hl.reg8_lo); break; // X = L
        case 0x76: break; // HALT
        case 0x77: write(hl.reg16, af.reg8_hi); break; // X = A
        // LD A, X
        case 0x78: af.reg8_hi = bc.reg8_hi; break; // X = B
        case 0x79: af.reg8_hi = bc.reg8_lo; break; // X = C
        case 0x7A: af.reg8_hi = de.reg8_hi; break; // X = D
        case 0x7B: af.reg8_hi = de.reg8_lo; break; // X = E
        case 0x7C: af.reg8_hi = hl.reg8_hi; break; // X = H
        case 0x7D: af.reg8_hi = hl.reg8_lo; break; // X = L
        case 0x7E: af.reg8_hi = read(hl.reg16); break; // X = [HL]
        case 0x7F: af.reg8_hi = af.reg8_hi; break; // X = A
        // ADD A, B

        default: std::cout << "Massive error. Nothing with this opcode exists" << std::endl;
    }

}