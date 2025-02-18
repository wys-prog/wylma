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
    virtual ~exception() = default; // Virtual destructor for proper cleanup
    const char *what() const { return _what; }
    const char *name() const { return _name; }
    const exception *inner() const { return _inner; }

    exception() : _what("exception"), _name("exception"), _inner(nullptr) {}
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

  class underflow 
    : public exception {
  public:
    underflow() : exception("underflow", "underflow", this) {}
    underflow(const char *w) : exception(w, "underflow", this) {}
  };
  
  class overflow 
    : public exception {
  public:
    overflow() : exception("overflow", "overflow", this) {}
    overflow(const char *w) : exception(w, "overflow", this) {}
  };

  class invalid_argument 
  : public exception {
  public:
    invalid_argument() : exception("invalid_argument", "invalid-argument", this) {}
    invalid_argument(const char *w) : exception(w, "invalid-argument", this) {}
  };

  class logic_error 
  : public exception {
  public:
    logic_error() : exception("logic_error", "logic-error", this) {}
    logic_error(const char *w) : exception(w, "logic-error", this) {}
  };

} // namespace wylma
