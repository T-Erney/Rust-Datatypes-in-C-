#include "option.hpp"
#include "result.hpp"


Result<Option<int>, const char*> sum(int* arr, int size) {
  if (size <= 0) {
    return Err<Option<int>, const char*>("array needs positive integer greater than 0");
  }

  int s = 0;
  for (int i = 0; i < size; i++) {
    s += arr[i];
  }

  return Ok<Option<int>, const char*>(Some<int>(s));
}


int main() {
  int arr[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9
  };

  // if you like to live dangerously...
  // auto s = sum(arr, 9).ok().unwrap();

  int s = 0;
  auto result = sum(arr, 9);
  if (result.is_ok()) {
    auto option = result.ok();
    s = option.unwrap();
  } else {
    std::cout << "Error: " << result.err() << "\n";
    return -1;
  }

  std::cout << "auto s = sum(arr, 9).ok().unwrap() = " << s << "\n";

  return 0;
}
