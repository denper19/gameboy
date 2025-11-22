#include <gtest/gtest.h>
#include "cpu.cpp"

TEST(GBCPU, LD_BC_d16) {

  gb_cpu cpu;
  cpu.write(0, 0x01); //LD bc, d16
  cpu.write(1, 0x01);
  cpu.write(2, 0x02);
  cpu.step_cpu(1);
  EXPECT_EQ(cpu.bc.reg16, 0x201);
}

TEST(GBCPU, LD_DE_d16) {

  gb_cpu cpu;
  cpu.write(0, 0x11); //LD de, d16
  cpu.write(1, 0x01);
  cpu.write(2, 0x02);
  cpu.step_cpu(1);
  EXPECT_EQ(cpu.de.reg16, 0x201);
}

TEST(GBCPU, LD_HL_d16) {

  gb_cpu cpu;
  cpu.write(0, 0x21); //LD hl, d16
  cpu.write(1, 0x01);
  cpu.write(2, 0x02);
  cpu.step_cpu(1);
  EXPECT_EQ(cpu.hl.reg16, 0x201);
}

TEST(GBCPU, LD_STACKPTR_d16) {

  gb_cpu cpu;
  cpu.write(0, 0x31); //LD stackptr, d16
  cpu.write(1, 0x01);
  cpu.write(2, 0x02);
  cpu.step_cpu(1);
  EXPECT_EQ(cpu.stackptr, 0x201);
}