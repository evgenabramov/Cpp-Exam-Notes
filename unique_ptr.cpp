template<typename T>
class unique_ptr {
public:
  unique_ptr(T* ptr) : ptr_(ptr) {}

  unique_ptr(const unique_ptr& other) = delete;
  unique_ptr(unique_ptr&& other) : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
  }

  unique_ptr& operator=(const unique_ptr& other) = delete;
  unique_ptr& operator=(unique_ptr&& other) {
    if (this == &other) {
      return *this;
    }
    ~unique_ptr();
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
    return *this;
  }

  ~unique_ptr() {
    delete ptr_;
  }

  T& operator*() {
    return *ptr_;
  }

  T* operator->() {
    return ptr_;
  }

private:
  T* ptr_;
};
