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
    float _increase = 0.35f;
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
      if (_size + 1 >= _capacity) resize(_capacity * _increase);
      _data[_size++] = t;
    }

    Ty pop_back() {
      if (_size - 1 < 0) throw underflow("pop_back() on an empty container.");
      Ty tmp = _data[_size];
      _size--;
      return tmp;
    }

    void insert(const basic_container<Ty> &bc, cindex_t ibeg, cindex_t iend) {
      if (iend-ibeg >= _capacity) resize((_capacity + iend-ibeg) * _increase);
      for (cindex_t i = ibeg; i < iend; i++) {
        _data[_size+i] = bc.copy(i);
      }
    }

    void insert(const Ty *t, cindex_t s) {
      for (cindex_t i = 0; i < s; i++) push_back(t[i]);
    }
    
    Ty copy(cindex_t at) const {
      if (at >= _size) throw out_of_range("copy() with a too large index.");
      return Ty(_data[at]);
    }

    Ty *copy() const { /* Don't forget to delete[] data ! */
      Ty *buffer = new Ty[_size];
      for (cindex_t i = 0; i < _size; i++)
        buffer[i] = _data[i];

      return buffer;
    }

    bool find(const Ty &t) const {
      for (cindex_t i = 0; i < _size; i++) {
        /* Using utilities::same(...) to compare arrays. */
        if (utilities::same(t, _data[i])) return true;
      }

      return false;
    }

    cindex_t indexof(const Ty &t) const {
      for (cindex_t i = 0; i < _size; i++) {
        if (utilities::same(t, _data[i])) return i;
      }

      return cindex_t(-1);
    }

    cindex_t countof(const Ty &t) const {
      cindex_t count = 0;
      for (cindex_t i = 0; i < _size; i++) {
        if (utilities::same(t, _data[i])) count++;
      }

      return count;
    }

    void remove(cindex_t pos) {
      if (pos >= _size) throw out_of_range("remove() used with a too large index");
      for (cindex_t i = pos; i < _size; i++) {
        _data[i] = _data[i-1];
      }
    }

    void removeall(const Ty &t) {
      for (cindex_t i = 0; i < _size; i++) {
        if (utilities::same(_data[i], t)) remove(i);
      }
    }

    void reverse() {
      try {
        Ty *buff = new Ty[_size];
        cindex_t dec = _size;
        for (cindex_t i = 0; i < _size; i++) {
          buff[i] = _data[dec--];
        }
        delete[] data;
        data = buff;
      } catch (const std::bad_alloc &e) {
        throw container_error(e.what());
      }
    }

    bool empty() const { return _size == 0; }
    
    cindex_t size() const { return _size; }

    cindex_t capacity() const { return _capacity; }

    void shrink_to_fit() { resize(_size); }

    Ty *data() const { return _data;  }

    float increase() const { return _increase; }

    void increase(float f) { _increase = f; }

    void clear() { resize(0); }

    void destroy() {
      _size = 0;
      _capacity = 0;
      delete[] _data;
    }

    bool null() const {
      if (empty()) return true;
      for (cindex_t i = 0; i < _size; i++) {
        if (_data[i] != Ty(0)) return false;
      }

      return true;
    }

    void build_from(const Ty *another, cindex_t it_size) {
      reisze(it_size);
      for (cindex_t = 0; i < it_size; i++) {
        _data[i] = another[i];
      }
    }

    Ty &operator[](cindex_t i) {
      if (i >= _size) throw out_of_range("operator[] with a too large index.");

      return _data[i];
    }

    basic_container &operator=(const basic_container<Ty> &another) {
      if (another != this) {
        this->build_from(another.copy());
      }

      return *this;
    }

    basic_container &operator+=(const basic_container<Ty> &another) {
      this->insert(another, 0, another.size());
      return *this;
    }

    cindex_t begin() const { return 0; }
    cindex_t end() const { return _size; }

    /* Constructors */
    basic_container() : _data(nullptr), _size(0), _capacity(0) { }

    basic_container(const Ty *another, cindex_t it_size) 
      : _data(nullptr), _size(0), _capacity(0) {
      build_from(another, it_size);
    }

    basic_container(cindex_t s) 
      : _data(nullptr), _size(0), _capacity(0) {
      resize(s);
    }

    ~basic_container() { delete[] _data; }
  };


  /* Definition of wylma::utilities function, for containers */
  namespace utilities {
    template <typename Ty>
    size_t lenof(const basic_container<Ty> &bc) {
      return bc.size(); 
    }

    template <typename Ty>
    size_t memof(const basic_container<Ty> &bc) {
      return sizeof(bc) + (bc.capacity() * sizeof(Ty));
    }
  } // namespace utilities
  
} // namespace wylma
