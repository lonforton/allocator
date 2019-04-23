#include <iostream>

namespace simple_list
{

template <class T, class Allocator = std::allocator<T>>
class slist
{
public:
  typedef Allocator allocator_type;
  typedef typename Allocator::value_type value_type;
  typedef typename Allocator::reference reference;
  typedef typename Allocator::const_reference const_reference;
  
  struct Node
  {
    T data;
    Node *next;

    Node(T value)
    {
      data = value;
      next = nullptr;
    }
  };

  typedef typename Allocator::template 
  rebind<Node>::other rebinded_allocator_type;

  rebinded_allocator_type _rebinded_allocator;

  ~slist(){
     Node *walk_node = _head;
     while(walk_node->next != nullptr){
       Node * temp_node = walk_node;    
       walk_node = walk_node->next;    
       _rebinded_allocator.destroy(temp_node);
       _rebinded_allocator.deallocate(temp_node, 1);          
     }
     _rebinded_allocator.destroy(walk_node);
     _rebinded_allocator.deallocate(walk_node, 1);
  }

  Node *_head = nullptr;

  Node* create_node(T value){       
    Node *node = _rebinded_allocator.allocate(1);
    _rebinded_allocator.construct(node, value);
    return node;
  }

  void insert(const T &value)
  {    
    if (_head == nullptr)
    {
      _head = create_node(value);
    }
    else
    {
      Node *node = _head;
      while (node->next != nullptr)
      {
        node = node->next;
      }
      Node *new_node = create_node(value);
      node->next = new_node;
    }
  }

  class iterator
  {
  public:
    typedef iterator self_type;
    typedef T value_type;
    typedef T &reference;
    typedef T *pointer;
    typedef std::forward_iterator_tag iterator_category;

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