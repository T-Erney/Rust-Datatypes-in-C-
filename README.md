# Recreating Option and Result Types in C++

## Option and Result Types from Rust 

Option is an enumerator type which allows the programmer to create a datatype which can return a Some value of the specified datatype, or return a value of None. This can be useful for a variety of different use cases. In Rust we use this to put wrappers around code which can be error prone when certain conditions are not met. As like the Option type, the Result type can also be used for resolving code which can be error prone, but has the alternative of returning a secondary data type. The functionality of these datatypes are what I think C++ can benefit from to create more safety in the language. 
This got me thinking. Could we create a datatype which can replecate the effect of these types in the C++ language? This project answers that. 

### Option 

Option was the easier of the two to implement. In Rust, the implementation of the Option type is as follows:

``` rust 
pub enum Option<T> {
  Some(T),
  None
}
```

Enumerators in Rust are usually used as a fancy way to write tagged unions, which I find to be a great way to write union types since the alternative to the Option type in C++ is very verbose. Rust makes writing this kind of code very simple and even make implementing various attributes easy to implement as well as we will see later on. 

In C++, we would write the same Rust code as the following:

``` c++
enum __option_type__ { option_some, option_none };
template <class T> 
struct Option {
  __option_type__ __type__;
  union {
    T   __some__;
    int __none__;
  };

  ... code here ...
};

template <class T> Option<T> Some(T data) { ... }
template <class T> Option<T> None()       { ... }
```

So, just wow right off the bat. This finished product does give some of the feel that Rust does when being used in practice. To test the Option type we can write some code which just wraps an integer to see if it works as it should. 

``` c++
#include "option.hpp"

int main() {
  Option<int> some_value = Some<int>(131); 
  // let some_value: Option<i32> = Some(131); 
  
  int value = some_value.unwrap(); 
  // let value = some_value.unwrap();

  std::cout << "value = " << value << "\n";

  return 0;
}
```

From the code above, we can guarentee that `value` will result in a value of `131`. This is only a very elementry level example for this kind of datatype, but you get the idea. 

### Result 

The Result datatype was more of a challenge. The structure of the datatype was essentially the same as the Option type. However, we are now using two templated types instead of one like the Option type. In Rust, we can define the Result type as the following:

``` rust 
pub enum Result<T, E> {
  Ok(T), 
  Err(E)
}
```

Taking the code we wrote for the Option type in C++ into account, we can really begin to appreciate the simplicity provided by the Rust programming language. Now to show the nightmare which is the C++ version of the Result type. 

``` c++
enum __result_type__ { result_ok, result_err };
template <class O, class E> 
struct Result {
  __result_type__ __type__;
  union {
    O __ok__;
    E __err__;
  };

  ... code here ...
};

template <class O, class E> Result<O, E> Ok(O data) { ... }
template <class O, class E> Result<O, E> Err(E err) { ... }
```

Same as before with some additional parts. Just the comparison of the two code snippits is night and day. And once again, we still get a similar feel in the C++ code as we would the Rust code. 

``` c++
typedef const char* error;
Result<int, error> sum(int* arr, int count) {
  if (count <= 0) { 
    return Err<int, error>("count should be positive and greater than 0");
  }

  int s = 0;
  for (int i = 0; i < count; i++) {
    s += arr[i];
  }

  return Ok<int, error>(s);
}
```

If we wanted to as well, we could use both of the types at the same time. Whether we wrap an Option inside of a Result or vice versa it should work. 

## What was learned?

Well, lets start with some of the complications while working on designing these datatypes. C++ and Rust differ quite a bit when it comes to move semantics. With Rust, movement is determined by the borrow checker. Once a variable moves its value to another variable or function it is gone until ownership can be reclaimed. In C++, I had a some fights with the compiler to understand why I was encountering some of the errors which I was facing (all of which were because I needed to implement move semantics between class objects). Once that was figured out, all of the issues I initially had were gone. 
Having these issues in C++ did make me miss temporarily how precise the details of the error messages and warnings of the Rust compiler are. Working in C++ does require more patience when debugging trouble code. In the long run, I was able to get the code working, and I re-upped my appreciation for the people at Mozilla for creating such an amazing next step in the evolution of compiler technologies. That being said however, I do miss the simplicity of being able to manipulate my C++ code to perform the more tricky but necessary operations with memory manipulation and management. 
