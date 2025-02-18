#pragma once

/* Wylma's Standard Library
   wylma::exception base class's implementation, 
   and some useful exceptions class. */

namespace wylma {
  class exception {
  private:
    const char *_what;
    const char *_name;
    const exception *_inner;

  public:
    const char *what() { return _what; }
    const char *name() { return _name; }
    const exception *inner() { return _inner; }

    exception() : _what("Exception"), _name("exception"), _inner(nullptr) {}
    exception(const char *w) : _what(w), _name("exception"), _inner(nullptr) {}
    exception(const char *w, const char *n) : _what(w), _name(n), _inner(nullptr) {}
    exception(const char *w, const char *n, const exception *e) 
      : _what(w), _name(n), _inner(e) {}
  };

  class runtime_error 
    : public exception {
  public:
    runtime_error() : exception("runtime_error", "runtime-error", this) {}
    runtime_error(const char *w) : exception(w, "runtime-error", this) {}
  };

  
} // namespace wylma
