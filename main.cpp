#include <iostream>


template <size_t n, typename T1, typename... Ts>
auto & get_value(T1 && t1, Ts &&... ts) {
  return t1;
}

int main() {
  std::cout << "hello" << std::endl;
  std::cout << get_value<2>(9, 5, 6) << std::endl;
  return 0;
}
