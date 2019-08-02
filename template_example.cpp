#include <iostream>

template<bool, typename T>
struct enable_if{};

template<typename T>
struct enable_if<true, T> {
  typedef T type;
};

constexpr int x = 5;

enable_if<x == 5, void>::type f(int a) {
  std::cout << a << std::endl;
}

int main() {
  f(10);
  return 0;
}
