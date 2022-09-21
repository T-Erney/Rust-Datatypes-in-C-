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
  auto s = sum(arr, 9).ok().unwrap();

  std::cout << "auto s = sum(arr, 9).ok().unwrap() = " << s << "\n";

  return 0;
}
