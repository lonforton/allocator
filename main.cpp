#include <iostream>
#include <map>

#include "fact.cpp"
#include "map_allocator.cpp"

int main()
{
  const int map_reserve_size = 10;

    std::map<int, int> map_default_alloc;
    for(int i = 0; i < map_reserve_size; ++i){
        map_default_alloc.insert(std::make_pair(i, factorial(i)));
    }

  auto map_custom_alloc = std::map<int, int, std::less<int>, map_allocator<std::pair<const int, long>, map_reserve_size>>{};
  for(int i = 0; i < map_reserve_size; ++i){
      map_custom_alloc.insert(std::make_pair(i, factorial(i)));
  }

   for(const auto& item : map_custom_alloc){
     std::cout << item.first << " " << item.second << std::endl;
   }


  return 0;
}