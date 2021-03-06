#include <iostream>
#include <fstream>

#include <gateops.h>
#include <bvec-basic.h>
#include <adder.h>
#include <memory.h>

#include <opt.h>
#include <tap.h>
#include <sim.h>
#include <netlist.h>
#include <vis.h>

using namespace std;
using namespace chdl;

int main(int argc, char **argv) {
  // The design
  bvec<5> a;
  bvec<32> q, d(Lit<32>(0));

  q = Memory(a, d, Lit<5>(0), Lit(0), "sample.hex");

  a = Reg(a + Lit<5>(1));

  TAP(a); TAP(d); TAP(q);

  // The simulation (generate .vcd file)
  optimize();

  ofstream wave_file("example3.vcd");
  run(wave_file, 32);

  ofstream netlist_file("example3.nand");
  print_netlist(netlist_file);
  netlist_file.close();

  ofstream dot_file("example3.dot");
  print_dot(dot_file);
  dot_file.close();

  return 0;
}
