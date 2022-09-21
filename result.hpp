#ifndef RESULT_TYPE
#define RESULT_TYPE

#include <iostream>
#include <string>

enum __result_type__ { result_ok, result_err };

template <class O, class E> 
struct Result {
  __result_type__ __type__;
  union {
    O __ok__;
    E __err__;
  };

  Result(__result_type__ t, O ok) {
    __type__ = t;
    __ok__ = ok;
  }
  Result(__result_type__ t, E err) {
    __type__ = t;
    __err__ = err;
  }
  Result(const Result& src) {
    *this = src;
  }

  bool is_ok() {
    return (__type__ == result_ok);
  }

  bool is_err() {
    return (__type__ == result_err);
  }

  O ok() {
    if (is_ok()) {
      return __ok__;
    } else {
      std::cout << "panic: attempt to unwrap 'Err' Result type" << "\n";
      exit(-1);
    }
  }

  E err() {
    if (is_err()) {
      return __err__;
    } else {
      std::cout << "panic: attempt to extract error as 'Ok' Result type" << "\n";
      exit(-1);
    }
  }
};

template <class O, class E> Result<O, E> Ok(O data) {
  return Result<O, E>(result_ok, data);
}

template <class O, class E> Result<O, E> Err(E err) {
  return Result<O, E>(result_err, err);
}

#endif // RESULT_TYPE
