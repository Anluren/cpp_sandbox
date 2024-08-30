#include <iostream>
#include <type_traits>

// Helper to check if a type has a member function `call`
template <typename T>
auto has_call_impl(int) -> decltype(std::declval<T>().call(), std::true_type{});

template <typename> auto has_call_impl(...) -> std::false_type;

template <typename T> using has_call = decltype(has_call_impl<T>(0));

// Template class with a member function that uses SFINAE
template <typename T> class MyClass {
public:
  // Member function enabled if T has a member function `call`
  template <typename U = T>
  auto callIfCallable() ->
      typename std::enable_if<has_call<U>::value, void>::type {
    t.call();
  }

  // Member function enabled if T does not have a member function `call`
  template <typename U = T>
  auto callIfCallable() ->
      typename std::enable_if<!has_call<U>::value, void>::type {
    std::cout << "T does not have a member function `call`" << std::endl;
  }

  MyClass(T t) : t(t) {}

private:
  T t;
};

// Test structures
struct Callable {
  void call() const { std::cout << "Callable::call()" << std::endl; }
};

struct NotCallable {};

int main() {
  Callable c;
  NotCallable nc;

  MyClass<Callable> mc(c);
  MyClass<NotCallable> mnc(nc);

  mc.callIfCallable();  // Output: Callable::call()
  mnc.callIfCallable(); // Output: T does not have a member function `call`

  return 0;
}
