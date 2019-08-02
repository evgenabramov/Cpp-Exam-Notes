template<typename Alloc = std::allocator<bool>>
class Vector<bool, Alloc> {
public:
  void PushBack(const bool& value) {
    if (size_ < capacity_) {
      buff_[size_ / 8].SetAt(size % 8, value);
      size_++;
      return;
    }
    buff_.PushBack(BoolProxy());
    buff_[size_ / 8].SetAt(size % 8, value);
    size_++;
    capacity_ += 8;
  }

  // самый важный метод
  BoolProxy& operator[](int index) {
    buff_[index / 8].offset_ = index % 8;
    return buff_[index / 8];
  }

private:
  struct BoolProxy {
    BoolProxy() : bucket_(0), offset_(0) {}

    bool GetAt(int position) {
      return static_cast<bool>((bucket_ >> position) & 1);
    }

    void SetAt(int position, bool value) {
      uint8_t mask;
      if (value) {
        mask = (1 << position);
      } else {
        mask = std::numeric_limits<uint8_t>::max - (1 << position);
      }
      bucket_ = bucket_ & mask;
    }

    BoolProxy& operator=(const bool& value) {
      SetAt(offset_, value);
      return *this;
    }

    //Решает проблему, когда значения из одного бакета
    BoolProxy& operator=(const BoolProxy& other) {
      offset_ = other.offset_;
      SetAt(offset_, other.GetAt(offset_));
      return *this;
    }

    uint8_t bucket_;
    size_t offset_;
  }

  std::vector<BoolProxy> buff_;
  size_t size_;
  size_t capacity_;
  Alloc alloc_;

  using traits = std::allocator_traits<Alloc>;
};
