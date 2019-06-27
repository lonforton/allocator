#include <iostream>
#include <map>
#include <list>

#include "fact.cpp"
#include "reserve_allocator.cpp"
#include "simple_list.cpp"

int main()
{
  const int map_reserve_size = 10;

  std::map<int, int> map_default_alloc;
  for (int i = 0; i < map_reserve_size; ++i)
  {
    map_default_alloc.insert(std::make_pair(i, factorial(i)));
  }

  auto map_custom_alloc = std::map<int, int, std::less<int>, reserve_allocator<std::pair<const int, int>, map_reserve_size>>{};
  for (int i = 0; i < map_reserve_size; ++i)
  {
    map_custom_alloc.insert(std::make_pair(i, factorial(i)));
  }

  for (const auto &item : map_custom_alloc)
  {
    std::cout << item.first << " " << item.second << std::endl;
  }

  simple_list::slist<int> simple_list_default_alloc;
  for (int i = 0; i < map_reserve_size; ++i)
  {
    simple_list_default_alloc.insert(std::move(i));
  }

  auto simple_list_custom_alloc = simple_list::slist<int, reserve_allocator<int, map_reserve_size>>{};
  for (int i = 0; i < map_reserve_size; ++i)
  {
    simple_list_custom_alloc.insert(std::move(i));
  }

  for (auto it = simple_list_custom_alloc.begin(); it != simple_list_custom_alloc.end(); it++)
  {
    std::cout << *it << std::endl;
  }

  auto simple_list_custom_alloc_hard = simple_list::slist<hard, reserve_allocator<hard, map_reserve_size>>{};
  simple_list_custom_alloc_hard.insert("one", 1);

  return 0;
}