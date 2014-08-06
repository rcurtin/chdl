#ifndef __TRISIMPL_H
#define __TRISIMPL_H

#include "node.h"
#include "nodeimpl.h"
#include "cdomain.h"

#include <vector>

#include <iostream>

namespace chdl {
  class tristateimpl : public nodeimpl {
   public:
    void connect(node in, node enable);

    bool eval(evaluator_t &e);

    void print(std::ostream &os);
    void print_vl(std::ostream &os);
  };
}

#endif
