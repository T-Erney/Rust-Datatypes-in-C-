#ifndef OPTION_TYPE
#define OPTION_TYPE 

#include <iostream>

enum __option_type__ { option_some, option_none };

template <typename T>
struct Option {
  __option_type__ __type__;
  union {
    T   __some__;
    int __none__;
  }; 

  bool is_some() {
    return (__type__ == option_some);
  }

  bool is_none() {
    return (__type__ == option_none);
  }

  T unwrap() {
    if (this->__type__ == option_some) {
      return this->__some__;
    } else {
      std::cout << "panic: attempt to unwrap 'None' Option type" << "\n";
      exit(-1);
    }
  }
};

template <typename T> Option<T> Some(T data) {
  return Option<T> {
    .__type__ = option_some,
    .__some__ = data
  };
}

template <typename T> Option<T> None() {
  return Option<T> {
    .__type__ = option_none,
    .__none__ = 0
  };
}

#endif // OPTION_TYPE
