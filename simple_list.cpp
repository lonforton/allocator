#include <iostream>

struct hard {
    hard(const char *, size_t) {};
    hard(const hard &) = delete;
    hard(hard && other) = default;
};

namespace simple_list
{

template <class T, class Allocator = std::allocator<T>>
class slist
{
public:
  using allocator_type = Allocator;
  using value_type = typename Allocator::value_type;
  using reference = typename Allocator::reference;
  using const_reference = typename Allocator::const_reference;

  slist() = default; 
  slist(const slist& other_list){
    Node *walk_node = _head;
    while(walk_node != nullptr) {
      this->insert(walk_node->data);
      walk_node = walk_node->next;
    }
  }

  slist(slist&& other_list){
    this->_head = other_list._head;
    other_list._head = nullptr;
  }

  struct Node
  {
    T data;
    Node *next;

    Node(T&& value) : data(std::move(value))
    {      
      next = nullptr;
    }
  };

  typedef typename Allocator::template 
  rebind<Node>::other rebinded_allocator_type;  

  rebinded_allocator_type _rebinded_allocator;

  ~slist(){
    Node *walk_node = _head;
    while(walk_node != nullptr) {
      Node * temp_node = walk_node;       
      walk_node = walk_node->next;
      _rebinded_allocator.destroy(temp_node);
      _rebinded_allocator.deallocate(temp_node, 1);
    }
  }

  Node *_head = nullptr;

  Node* create_node(T&& value){       
    Node *node = _rebinded_allocator.allocate(1);
    _rebinded_allocator.construct(node, std::forward<T>(value));
    return node;
  }

  void insert(T&& value)
  {    
    if (_head == nullptr)
    {
      _head = create_node(std::move(T(value)));
    }
    else
    {
      Node *node = _head;
      while (node->next != nullptr)
      {
        node = node->next;
      }
      Node *new_node = create_node(std::move(T(value)));
      node->next = new_node;
    }
  }

    template <typename U, typename V>
    void insert(U&& value_1, V&& value_2)
  {    
    if (_head == nullptr)
    {
      _head = create_node(std::move(T(value_1, value_2)));
    }
    else
    {
      Node *node = _head;
      while (node->next != nullptr)
      {
        node = node->next;
      }
      Node *new_node = create_node(std::move(T(value_1, value_2)));
      node->next = new_node;
    }
  }

  class iterator
  {
  public:
    using self_type = iterator;
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using iterator_category = std::forward_iterator_tag;

    iterator();
    iterator(Node *node) : _node(node){};
 
    iterator &operator++() {  _node = _node->next; return *this;}
    self_type operator++(__attribute__((unused)) int junk) { self_type i = *this;  _node = _node->next; return i; }
    reference operator*() { return _node->data; }
    bool operator!=(const self_type& rhs) { return _node != rhs._node; }

    private:
    Node *_node;
  };

  iterator begin()
  {
    return iterator(_head);
  }
  iterator end()
  {
    Node *node = _head;
    while (node->next != nullptr)
    {
      node = node->next;
    }
    return iterator(node->next);
  }

private:
};

} // namespace simple_list