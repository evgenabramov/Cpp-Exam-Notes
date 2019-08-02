#include <utility>

template<typename T>
class allocator {
public:
  T* allocate(size_t n) const {
    return static_cast<T*>(::operator new(n * sizeof(T)));
  }

  void deallocate(T* p, size_t n) const {
    ::operator delete(p, n);
  }

  template<typename... Args>
  void construct(T* p, Args&&... args) const {
    ::new (p) T(std::forward<Args>(args)...);
  }

  void destroy(T* p) const {
    p->~T();
  }
};
