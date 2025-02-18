#pragma once

#include "exceptions.hpp"

namespace wylma {
  /* Out of range exception. 
     When the index is biggest
     than the capacity. */
  
  class out_of_range 
    : public exception {
  private:
  public:
    out_of_range() : exception("out of range", "out-of-range", this) {}
    out_of_range(const char *w) : exception(w, "out-of-range", this) {}
  };

  
} // namespace wylma
