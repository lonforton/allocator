#include <cstdint>

constexpr uint64_t factorial(uint64_t n){
  return n == 0 ? 1 : n * factorial(n - 1);
}