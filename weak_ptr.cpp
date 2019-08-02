temlate<typename T>
struct inner_ptr {
  T* ptr;
  int weak_counter;
  int shared_counter;
};

template<typename T>
class weak_ptr {
public:
  weak_ptr() : inner(nullptr) {}

  weak_ptr(const shared_ptr<T>& sptr) : inner(sptr.inner) {
    inner->weak_counter++;
  }

  bool expired() {
    return inner->shared_counter == 0;
  }

  shared_ptr<T> lock() {
    if (inner == nullptr) {
      throw std::bad_weak_ptr();
    }
    if (inner->shared_counter == 0) {
      return shared_ptr<T>();
    }
    return shared_ptr<T>(inner);
  }

  ~weak_ptr() {
    inner->weak_counter--;
    if (weak_counter == 0 && shared_counter == 0) {
      delete inner;
    }
  }

private:
  inner_ptr<T>* inner;
};

template<typename T>
class shared_ptr {
public:
  shared_ptr(inner_ptr* new_inner) : inner(new_inner) {
    inner->shared_counter++;
  }

  ~shared_ptr() {
    inner->shared_counter--;
    if (inner->shared_counter == 0) {
      delete inner->ptr;
      if (inner->weak_counter == 0) {
        delete inner;
      }
    }
  }

private:
  inner_ptr<T>* inner;
};
