#include <iostream>
#include <map>

#include "fact.cpp"

int main()
{
  std::map<int, int> map_default;
  for(int i = 0; i < 9; ++i){
      map_default.insert(std::make_pair(i, factorial(i)));
  }

  for(const auto& item : map_default){
    std::cout << item.first << " " << item.second << std::endl;
  }

  return 0;
}