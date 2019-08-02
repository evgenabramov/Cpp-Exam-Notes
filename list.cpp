template<typename T, typename Alloc = std::allocator<T>>
class List {
public:
  List() : size_(0), front_(nullptr), back_(nullptr) {}

  List(const List& other) : alloc_(std::select_on_container_copy_construction(other.alloc_))
                            size_(other.size_) {
    Node* current = other.front_;
    front_ = traits::allocate(alloc_, 1);
    traits::construct(alloc_, front_, current);
    Node* prev = current;
    while (current != nullptr) {
      next = traits::allocate(alloc_, 1);
      traits::construct(alloc_, next, current);
      next_->prev_ = prev;
      prev->next_ = next;
      prev = next;
      current = current->next_;
    }
    back_ = prev;
  }

  List(List&& other) : alloc_(std::move(alloc_))
                       size_(other.size_)
                       front_(other.front_)
                       back_(other.back_) {
    other.size_ = 0;
    other.front_ = nullptr;
    other.back_ = nullptr;
  }

  List& operator=(const List& other) {
    if (this == &other) {
      return *this;
    }

    ~List();

    size_ = other.size_;
    Node* current = other.front_;
    front_ = traits::allocate(alloc_, 1);
    traits::construct(alloc_, front_, current);
    Node* prev = current;
    while (current != nullptr) {
      next = traits::allocate(alloc_, 1);
      traits::construct(alloc_, next, current);
      next_->prev_ = prev;
      prev->next_ = next;
      prev = next;
      current = current->next_;
    }
    back_ = prev;
  }

  List& operator=(List&& other) {
     size_ = other.size_;
     alloc_ = std::move(other.alloc_);
     front_ = other.front_;
     back_ = other.back_;

     other.back_ = nullptr;
     other.front_ = nullptr;
     other.size_ = 0;
  }

  struct Iterator {
    Iterator(Node* data) : data_(data) {}

    Iterator& operator++() {
      data_ = data_->next_;
      return *this;
    }

    const Iterator operator++(int) {
      Iterator it(data_);
      data_ = data_->next_;
      return it;
    }

    Node* data_;
  };

  Iterator begin() {
    return Iterator(front_);
  }

  Iterator end() {
    return Iterator(back_);
  }

  void Insert(const Iterator& it, const T& value) {
    Node* new_node = traits::allocate(alloc_, 1);
    traits::construct(alloc_, new_node, value);
    new_node->prev_ = it.data_->prev_;
    new_node->next_ = it.data_;
    it.data_->prev_ = new_node;
  }

  void Erase(Iterator& it) {
    it.data_->next_->prev_ = it.data_->prev_;
    it.data_->prev_->next_ = it.data_->next_;
  }

  ~List() {
    Node* current = front_;
    while (current != nullptr) {
      Node* next = current->next_;
      traits::destroy(current);
      traits::deallocate(current, 1);
      current = next;
    }
  }

private:
  template<typename T>
  struct Node {
    Node(const T& data) : data_(data),
                          next_(nullptr),
                          prev_(nullptr) {}

    Node(const Node& other) : Node(other.data_) {}

    Node* next_;
    Nede* prev_;
    T data_;
  };

  Node* front_;
  Node* back_;
  size_t size;
  NodeAlloc alloc_;

  using NodeAlloc = std::allocator_traits<Alloc>::rebind_alloc<Node<T>>;
  using traits = std::allocator_traits<NodeAlloc>;
};
