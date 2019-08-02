template<typename T>
class shared_ptr {
public:
  shared_ptr(T* ptr) {
    helper_ = new Helper(ptr, 0);
    if (std::is_base_of<T, std::enable_shared_from_this<T>>::value) {
      ptr_->weak_this = *this;
    }
  }

  shared_ptr(const shared_ptr& other) : helper_(other.helper_) {
    helper_->counter_++;
  }

  shared_ptr(shared_ptr&& other) noexcept : helper_(other.helper_) {
    other.helper_ = nullptr;
  }

  shared_ptr& operator=(const shared_ptr& other) {
    if (this == &other) {
      return *this;
    }
    ~shared_ptr();
    helper_ = other->helper_;
    helper_->counter_++;
    return *this;
  }

  shared_ptr& operator=(shared_ptr&& other) noexcept {
    if (this == &other) {
      return *this;
    }
    ~shared_ptr();
    helper_ = other.helper_;
    other_.helper_ = nullptr;
    return *this;
  }

  ~shared_ptr() {
    helper_->counter_--;
    if (helper_->counter_ == 0) {
      delete helper_->ptr_;
      delete helper_;
    }
  }

  T& operator*() {
    return *(helper_->ptr_);
  }

  T* operator->() {
    return helper_->ptr_;
  }

private:
  struct Helper {
    Helper(T* ptr) : ptr_(ptr), counter_(1) {}

    T* ptr_;
    size_t counter_;
  };

  Helper* helper_;
};
