#include <iostream>
#include <type_traits>


constexpr bool check(int n) {
  if (n == 1) {
    return false;
  }
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    if (n % i == 0) {
      cnt++;
    }
  }
  return (cnt == 2);
}

int main() {
  constexpr bool is_prime = check(11);
  std::cout << is_prime;
  return 0;
}

#include <iostream>
#include <type_traits>

template<int n, int d>
struct prime_test {
  static const bool is_prime = prime_test<n, d-1>::is_prime ? (n % d != 0) : false;
};

template<int n>
struct prime_test<n, 1> {
  static const bool is_prime = true;
};

template<int n>
struct prime_test<n, 0> {
  static const bool is_prime = true;
};

template<>
struct prime_test<1, 0> {
  static const bool is_prime = true;
};

int main() {
  const int p = 1;
  std::cout << prime_test<p, p - 1>::is_prime;
  return 0;
}
