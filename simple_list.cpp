#include <iostream>

struct hard {
    hard(const char *, size_t) {};
    hard(const hard &) = delete;
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
    Node *walk_node = other_list._head;
    while(walk_node != nullptr) {
      this->insert(walk_node->data);
      walk_node = walk_node->next;
    }
  }

   slist(slist&& other_list){
     this->_head = other_list._head;     
     other_list._head = nullptr;
     this->_rebinded_allocator = other_list._rebinded_allocator;     
   }

  struct Node
  {
    T data;
    Node *next;

    template<typename...Args>
    Node(Args&& ...args) : data(args...)
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

  template<typename...Args>
  Node* create_node(Args&& ...args){       
    Node *node = _rebinded_allocator.allocate(1);
    _rebinded_allocator.construct(node, std::forward<Args>(args)...);
    return node;
  }

  template<typename...Args>
  void insert(Args&& ...args)  
  {
    if (_head == nullptr)
    {
      _head = create_node(std::forward<Args>(args)...);
    }
    else
    {
      Node *node = _head;
      while (node->next != nullptr)
      {
        node = node->next;
      }
      Node *new_node = create_node(std::forward<Args>(args)...);
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