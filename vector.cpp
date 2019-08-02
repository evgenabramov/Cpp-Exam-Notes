#include <iostream>
#include <memory>

template<typename T, typename Alloc = std::allocator<T>>
class Vector {
public:
  Vector() : size_(0), capacity_(8), alloc_(Alloc()) {
    buff_ = traits::allocate(alloc_, 8);
  }

  // нельзя просто забирать аллокатор у другого объекта
  Vector(const Vector& other) : alloc_(traits::select_on_container_copy_construction(other.alloc_)) {
    buff_ = traits::allocate(alloc_, other.capacity_);
    capacity_ = other.capacity_;
    size_ = other.size_;
    for (size_t i = 0; i < size_; ++i) {
      traits::construct(alloc_, buff_ + i, other.buff_[i]);
    }
  }

  Vector(Vector&& other) : alloc_(std::move(other.alloc_)),
  capacity_(other.capacity_),
  size_(other.size_),
  buff_(other.buff_) {
    other.buff_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  Vector& operator=(const Vector& other) {
    if (this == &other) {
      return *this;
    }

    for (size_t i = 0; i < size_; ++i) {
      traits::destroy(alloc_, buff_ + i);
    }
    traits::deallocate(alloc_, buff_, capacity_);

    alloc_ = traits::select_on_container_copy_construction(other.alloc_);
    buff_ = traits::allocate(alloc_, other.capacity_);
    capacity_ = other.capacity_;
    size_ = other.size_;
    for (size_t i = 0; i < size_; ++i) {
      traits::construct(alloc_, buff_ + i, other.buff_[i]);
    }

    return *this;
  }

  Vector& operator=(Vector&& other) {
    if (this == &other) {
      return *this;
    }

    for (size_t i = 0; i < size_; ++i) {
      traits::destroy(alloc_, buff_ + i);
    }
    traits::deallocate(alloc_, buff_, capacity_);

    alloc_ = std::move(other.alloc_);
    buff_ = other.buff_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    other.buff_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;

    return *this;
  }

  T& operator[](int index) {
    return buff_[index];
  }

  T& At(int index) {
    assert(index >= 0 && index <= size_);
    return buff_[index];
  }

  // capacity_ можно не менять
  void Resize(int size) {
    for (size_t i = size; i < size_; ++i) {
      traits::destroy(alloc_, buff_ + i);
    }

    for (size_t i = size_; i < size; ++i) {
      PushBack(T());
    }

    size_ = size;
  }

  void Reserve(int size) {
    if (size < size_) {
      return;
    }

    T* new_buff = traits::allocate(alloc_, size);
    for (size_t i = 0; i < size_; ++i) {
      traits::construct(alloc_, new_buff + i, std::move_if_noexcept(buff_[i]));
    }

    this->~Vector();

    buff_ = new_buff;
    capacity_ = size;
  }

  T& Front() { return buff_[0];  }

  T& Back() { return buff_[size_ - 1]; }

  void PushBack(const T& x) {
    if (size_ < capacity_) {
      traits::construct(alloc_, buff_ + size_, x);
      size_++;
      return;
    }
    T* new_buff = traits::allocate(alloc_, capacity_ * 2);

    traits::construct(alloc_, new_buff + size_, x);
    for (size_t i = 0; i < size_; ++i) {
      traits::construct(alloc_, new_buff + i, std::move_if_noexcept(buff_[i]));
    }

    for (size_t i = 0; i < size_; ++i) {
      traits::destroy(alloc_, buff_ + i);
    }
    traits::deallocate(alloc_, buff_, size_);

    size_++;
    buff_ = new_buff;
    capacity_ *= 2;
  }

  void PopBack() {
    assert(size_ > 0);
    traits::destroy(alloc_, buff_ + size_ - 1);
    size_--;
  }

  ~Vector() {
    for (size_t i = 0; i < size_; ++i) {
      traits::destroy(alloc_, buff_ + i);
    }
    traits::deallocate(alloc_, buff_, capacity_);
  }

private:
  T* buff_;
  size_t size_;
  size_t capacity_;
  Alloc alloc_;

  using traits = std::allocator_traits<Alloc>;
};
