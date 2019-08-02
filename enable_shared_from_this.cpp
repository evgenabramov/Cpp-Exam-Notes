template<typename T>
class enable_shared_from_this {
public:
  shared_ptr<T>& shared_from_this() {
    return weak_this.lock();
  }

public:
  weak_ptr weak_this;
};
