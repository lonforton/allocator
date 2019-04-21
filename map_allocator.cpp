#include <iostream>

template <typename T, int container_size>
struct map_allocator{
  using value_type = T;
  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;

  void *p = std::malloc(sizeof(T) * container_size);
  int element_counter = 0;

template <typename U>
struct rebind {
  using other = map_allocator<U, container_size>;
};

T *allocate(std::size_t n)
{
  T *mem = reinterpret_cast<T *>(p);
  if (!mem)
    throw std::bad_cast();
    
  mem = mem + element_counter;
  element_counter += n;
  std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]"  << "[p = " << p << "]" << "[mem = " << mem << "]" << std::endl;

  return mem;
}

void deallocate(T *p, std::size_t n){
  std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
  element_counter -= n;
  if(element_counter == 0){
    std::cout << "Free memory at [p = " << p << "]" << std::endl;
    std::free(p);
  }
}

template <typename U, typename ... Args>
void construct(U *p, Args&& ... args){
 std::cout << __PRETTY_FUNCTION__ << std::endl;
  new(p) U(std::forward<Args>(args) ...);
}

void destroy(T *p) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  p->~T();
}

};


