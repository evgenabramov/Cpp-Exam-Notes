#include <iterator>

template<class Container>
class insert_iterator {
public:
  explicit insert_iterator(Container& container, typename Container::iterator it) : container(&container),
                                                                                    iter(it) {}

  insert_iterator& operator++()    noexcept { return *this; };
  insert_iterator& operator++(int) noexcept { return *this; };
  // Поскольку в алгоритмах, например std::copy пишется *it_new = *it_old;
  insert_iterator& operator*()     noexcept { return *this; };

  insert_iterator& operator=(const typename Container::value_type& value) {
    iter = container->insert(iter, value);
    ++iter;
    return *this;
  }

  insert_iterator& operator=(typename Container::value_type&& value) {
    iter = container->insert(iter, std::move(value));
    ++iter;
    return *this;
  }

protected:
  Container* container;
  typename Container::iterator iter;
};

template <typename Container>
insert_iterator<Container> inserter(Container& container, typename Container::iterator it) {
  return insert_iterator<Container>(container, it);
}
