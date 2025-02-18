#pragma once

#include <new> /* To get std::bad_alloc throws */

#include "exceptions.hpp" /* To "cast" exceptions */
#include "utilities/utility.hpp" 
#include "range/range.hpp"

namespace wylma {
  /* Specific types */

  typedef size_t cindex_t;  /* To index a container */

  /* Define exceptions */

  /* When an allocation fails */
  class bad_alloc 
    : public exception {
  public:
    bad_alloc() : exception("allocation fails", "bad-alloc", this) {}
    bad_alloc(const char *w) : exception(w, "bad-alloc", this) {}
  };

  class container_error 
    : public exception {
  public:
    container_error() : exception("container error", "container-error", this) {}
    container_error(const char *w) : exception(w, "bad-alloc", this) {}
  };

  template <typename Ty>
  class basic_container {
  private:
    float increase = 0.35f;
    Ty *_data;  /* Elements present into the container */
    size_t _size; /* Size of elements */
    size_t _capacity; /* Size of used memory by _data */

  public:
    void resize(size_t s) {
      try {
        auto max = utilities::min(s, _capacity);
        Ty *buff = new Ty[s];
        /* Fill the buffer */
        for (size_t i = 0; i < max; i++) {
          buff[i] = _data[i];
        }
        delete[] _data;
        _data = buff;
        _size = max;
        _capacity = s;
      } catch (const std::bad_alloc &e) {
        throw container_error(e.what());
      }
    }

    void push_back(const Ty &t) {
      if (_size + 1 >= _capacity) resize(_capacity * increase);
      _data[_size++] = t;
    }

    Ty pop_back() {
      Ty tmp = _data[_size];
      _size--;
      return tmp;
    }

    void insert(const basic_container<Ty> &bc, cindex_t ibeg, cindex_t iend) {
      if (iend-ibeg >= _capacity) resize((_capacity + iend-ibeg) * increase);
      for (cindex_t i = ibeg; i < iend; i++) {
        _data[_size+i] = bc.copy(i);
      }
    }
    
    Ty copy(cindex_t at) {
      if (at >= _size) throw out_of_range("copy() with a too large index.");
      return Ty(_data[at]);
    }

    Ty *copy() { /* Don't forget to delete[] data ! */
      Ty *buffer = new Ty[_size];
      for (cindex_t i = 0; i < _size; i++)
        buffer[i] = _data[i];

      return buffer;
    }

    bool find(const Ty &t) {
      for (cindex_t i = 0; i < _size; i++) {
        /* Using utilities::same(...) to compare arrays. */
        if (utilities::same(t, _data[i])) return true;
      }

      return false;
    }

    cindex_t indexof(const Ty &t) {
      for (cindex_t i = 0; i < _size; i++) {
        if (utilities::same(t, _data[i])) return i;
      }

      return cindex_t(-1);
    }

    cindex_t countof(const Ty &t) {
      cindex_t count = 0;
      for (cindex_t i = 0; i < _size; i++) {
        if (utilities::same(t, _data[i])) count++;
      }

      return count;
    }

    void clear() { resize(0); }

    void remove(cindex_t pos) {
      
    }
  };
} // namespace wylma
