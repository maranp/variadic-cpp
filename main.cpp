#include <iostream>


template <size_t n, typename T1, typename... Ts>
struct Get_value {
  // I thought a static member that captures the
  // nth params value will be the way to go.
  // But that does not fit the objective.
  // So, using operator() to retrieve the nth pos' value
  // static auto value = Get_value<n -1, Ts>;
  auto & operator()(T1 &&, Ts&&... ts) {
    return Get_value<n - 1, Ts...>()(std::forward<Ts>(ts)...);
  }
};

template <typename T1, typename... Ts>
struct Get_value<0, T1, Ts...> {
  auto & operator()(T1 && t, Ts&&...) {
    return t;
  }
};

template <size_t n, typename T1, typename... Ts>
auto & get_value(T1 && t1, Ts &&... ts) {
  // almost correct but 2 issues here.
  // variadic type Ts needs to follow ellipses
  // t1 and ts are forwarding references.
  // so pass then to another function with std::forward
  //return Get_value<n, T1, Ts>()(t1, ts);
  return Get_value<n, T1, Ts...>()(std::forward<T1>(t1),
      // Ts is variadic type and ts is variadic value. so
      // add the ellips at end of call to make it common to
      // both of them. My inference.
                                   std::forward<Ts>(ts)...);
}

int main() {
  std::cout << "hello" << std::endl;
  std::cout << get_value<0>(9, 5, 6) << std::endl;
  return 0;
}
