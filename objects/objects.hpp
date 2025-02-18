#pragma once

#include "exceptions.hpp"

#include "libs/unordered_map.hpp"

namespace wylma {
  /* object class is a class wich helps
     you to store/load data from a file.
     Data is stored in a file, and can be loaded 
     in memory by using the 'properties' map.
     Storing & loading many times can have 
     several impacts in memory usage. 
     In fact, loading an object need to parse 
     an entire file, and while parsing, loading
     parsed elements into memory. */
  class object {
  private:
  public:
    
  };
} // namespace wylma

