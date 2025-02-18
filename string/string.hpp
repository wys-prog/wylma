#pragma once

#include <cstdint>

#include "container/container.hpp"
#include "utilities/utility.hpp"

namespace wylma {
  template <typename T>
  class basic_string : public basic_container<T> {
  private:
  public:
    const T *c_str() const { return data(); }

    basic_string<T> substr(cindex_t from, cindex_t to = _size) {
      basic_string<T> string;
      
      for (cindex_t i = from; i < to; i++) {
        string.push_back(_data[i]);
      }

      return string;
    }

    basic_string<T> &operator+=(const basic_string<T> &another) {
      this->insert(another, another.begin(), another.end());
      return *this;
    }

    basic_string<T> &operator+=(const T *another) {
      this->insert(another, utilities::lenof(another));
      return *this;
    }

    basic_string<T> &operator+=(const T &c) {
      this->push_back(c);
      return *this;
    }

    basic_container<uint8_t> binary() const {
      basic_containerr<uint8_t> binary_data;
      binary_data.reserve(this->_size * sizeof(T));

      for (cindex_t i = 0; i < this->_size; i++) {
        const uint8_t *byte_ptr = reinterpret_cast<const uint8_t *>(&this->_data[i]);
        for (size_t j = 0; j < sizeof(T); j++) {
          binary_data.push_back(byte_ptr[j]);
        }
      }

      return binary_data;
    }

    /* Constructors */

    basic_string() : basic_container() {}
    basic_string(const T *str) : basic_container<T>(str, lenof(str)) { }
    basic_string(basic_container<uint8_t> &bin) : basic_container<T>((T*)bin.data(), bin.size()) { }
  };

  namespace utilities {
    template <typename T>
    size_t lenof(const basic_string<T> &string) {
      return string.size();
    }

    template <typename T>
    size_t memof(const basic_string<T> &string) {
      return (string.capacity() * sizeof(T)) + sizeof(string);
    }
  } // namespace utilities
  
} // namespace wylma
