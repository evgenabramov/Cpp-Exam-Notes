#include <iostream>

class String {
public:
  String(const char* str, size_t size) : size_(size) {
    str_ = new char[size];
    for (size_t index = 0; index < size_; ++index) {
      str_[index] = str[index];
    }
  }

  String(const String& other) : size_(other.size_) {
    str_ = new char[other.size_];
    for (size_t index = 0; index < size_; ++index) {
      str_[index] = other.str_[index];
    }
  }

  String(String&& other) : str_(other.str_),
                           size_(other.size_) {
    other.str_ = nullptr;
    other.size_ = 0;
  }

  String& operator=(const String& other) {
    if (&other == this) {
      return *this;
    }
    delete[] str_;
    size_ = other.size_;
    str_ = new char[size_];
    for (size_t index = 0; index < size_; ++index) {
      str_[index] = other.str_[index];
    }
    return *this;
  }

  String& operator=(String&& other) {
    if (&other == this) {
      return *this;
    }
    delete[] str_;
    str_ = other.str_;
    size_ = other.size_;
    other.str_ = nullptr;
    other.size_ = 0;
    return *this;
  }

  ~String() {
    delete[] str_;
  }

private:
  char* str_;
  size_t size_;
};

int main() {
  String s("abc", 3);
  String s1(s);
  String s2 = std::move(s);
  s = std::move(s2);
  return 0;
}
