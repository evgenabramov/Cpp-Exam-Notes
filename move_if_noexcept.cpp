template<typename T>
struct is_nothrow_move_constructible {
private:
  template<typename...>
  char f(...) {return 0;}

  template<typename C>
  typename std::conditional_t<noexcept(T(std::move(declval<C>()))), int, char> f(int) {return 0;}

public:
  static const bool value = (sizeof(f<T>(0)) == sizeof(int));
};

template<typename T>
typename std::conditional_t<!std::is_nothrow_move_constructible<T> && std::is_copy_constructible<T>, const T&, T&&> f(T& x) {
  return static_cast<std::conditional_t<!std::is_nothrow_move_constructible<T> && std::is_copy_constructible<T>, const T&, T&&>>(x);
}
