template <typename T, typename Container = std::vector<T>, typename Cmp = std::less<T>>
class PriorityQueue {
public:
  PriorityQueue(const Container& array) : size_(array.size())
                                          cmp_(Cmp()) {
    buf_ = array;
    for (int i = size_ / 2 - 1; i >= 0; --i) {
      SiftDown(i);
    }
  }

  void Push(const T& value) {
    buf_[size_] = value;
    SiftUp(size_);
    size_++;
  }

  const T Top() {
    return buf_[0];
  }

  void Pop() {
    buf_[0] = buf_[size_ - 1];
    size_--;
    if (size_ != 0) {
      SiftDown(0);
    }
  }

private:
  int GetLeftChildIndex(int index) const { return 2 * index + 1; }

  int GetRightChildIndex(int index) const { return 2 * index + 2; }

  int GetParentIndex(int index) const { return (index - 1) / 2; }

   void SiftUp(int index) {
     while (index > 0) {
       int parent = GetParentIndex(index);
       if (cmp_(buf_[index], buf_[parent])) {
         return;
       }
       std::swap(buf_[index], buf_[parent]);
       index = parent;
     }
   }

   void SiftDown(int index) {
     int left = GetLeftChildIndex(index);
     int right = GetRightChildIndex(index);
     int maximum = index;
     if (left < size_ && cmp_(buf_[index], buf_[left])) {
       maximum = left;
     }
     if (right < size_ && cmp_(buf_[maximum], buf_[right])) {
       maximum = right;
     }
     if (maximum != index) {
       std::swap(buf_[index], buf_[maximum]);
       SiftDown(maximum);
     }
   }

  Container buf_;
  int size_;
  Cmp cmp_;
};
