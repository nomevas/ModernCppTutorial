#include <gtest/gtest.h>

namespace {
template <typename Observable, typename Observer>
concept ObservableObject = requires(Observable&& observable, Observer* observer) {
  { observable.addObserver(observer) } -> std::same_as<void>;
  { observable.removeObserver(observer) } -> std::same_as<void>;
};

template <typename Observable, typename Observer>
concept NoObservableObject = !ObservableObject<Observable, Observer>;

template <typename Observable, typename Observer>
  requires ObservableObject<Observable, Observer>
bool runtimeCheck() {
  return true;
}

template <typename Observable, typename Observer>
  requires NoObservableObject<Observable, Observer>
bool runtimeCheck() {
  return false;
}
}  // namespace

TEST(Concept, CheckIfObjectHasMethods) {
  struct Observer {};
  struct Observable {
    void addObserver(Observer*) {}
    void removeObserver(Observer*) {}
  };

  static_assert(ObservableObject<Observable, Observer>);
  EXPECT_TRUE((runtimeCheck<Observable, Observer>()));
  EXPECT_FALSE((runtimeCheck<Observer, Observer>()));
}

namespace {
template <class T>
concept Integral = std::is_integral<T>::value;
template <class T>
concept SignedIntegral = Integral<T> && std::is_signed<T>::value;
template <class T>
concept UnsignedIntegral = Integral<T> && !SignedIntegral<T>;
}  // namespace

TEST(Concept, Conjuctions) {
  static_assert(Integral<int>);
  static_assert(SignedIntegral<int>);
  static_assert(UnsignedIntegral<uint>);
}

namespace {
template <typename T>
concept Decrementable = requires(T t) { --t; };
template <typename T>
concept Addable = requires(T a, T b) { a + b; };
}  // namespace

TEST(Concept, Operators) {
  static_assert(Decrementable<int>);
  static_assert(Addable<int>);
}