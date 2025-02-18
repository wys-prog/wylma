#pragma once

#include <stddef.h>

namespace wylma {
  namespace utilities {
    /* Returns the len of smth */
    template <typename T>
    size_t lenof(const T &) {
      return sizeof(T);
    }

    size_t lenof(const char *a) {
      size_t l = 0;
      while (a--) l++;
      return l;
    }

    /* Returns the biggest between a and b */
    template <typename T>
    T max(const T &a, const T &b) {
      return (a > b ? a : b);
    }

    /* Returns the smallest between a and b */
    template <typename T>
    T min(const T &a, const T &b) {
      return (a < b ? a : b);
    }

    /* Returns true if all arguments are same. */
    template <typename T, typename ...Args>
    bool same(const T &a, const T &b, const Args&... args) {
      return ((a == b) && ... && (b == args));
    }

    bool same(const char *a, const char *b) {
      size_t lenA = lenof(a);
      if (lenA != lenof(b)) return false;
      for (size_t i = 0; i < lenA; i++) 
        if (a[i] != b[i]) return false;
      
      return true;
    }
  }
} // namespace wylma
