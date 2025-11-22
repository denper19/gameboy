#include <iostream>
#include "cpu.hpp"

int main(){
    
  gb_cpu cpu;
  cpu.write(0, 0x01); //LD bc, d16
  cpu.write(1, 0x01);
  cpu.write(2, 0x02);
  return 0;
}