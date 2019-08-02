#include <iostream>
#include <vector>
#include <string>

using std::vector;

template<typename T>
void f(T x) {
  std::cout << 1 << std::endl;
}

template<typename ...>
void f(int) {
  std::cout << 2 << std::endl;
}

template<typename T>
using my_type = std::vector<std::vector<T>>;

typedef vector<vector<std::pair<int, long long>>> mytype;

class C {
public:
  int a;
  double d;
};

template<typename T>
class Cc {
  typedef T type;
};

template<typename T>
void Pr(T x) {
  std::cout << x << std::endl;
}

template<typename ...>
void Print() {}

template<typename Head, typename... Tail>
void Print(const Head& h, const Tail&... t) {
  std::cout << h << " " << sizeof...(t) << std::endl;
  Print(t...);
}

int main() {
  //f(5.0);
  //int C::* p = &C::a;
  std::string s = "big joke";
  int a = 5;
  double d = 3.01;
  Print(s, a, d);
  return 0;
}
