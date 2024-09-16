#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <exception>
#include <future>
#include <thread>

using namespace std::chrono_literals;

TEST(Future, Async_LaunchPolicies) {
  EXPECT_NE(std::thread::id{}, std::async([]() { return std::this_thread::get_id(); }).get()) << "compiler may choose the execution policy";
  EXPECT_EQ(std::this_thread::get_id(), std::async(std::launch::deferred, []() { return std::this_thread::get_id(); }).get())
      << "deferred, it should be executed by the same thread when the feature.get method is called";
  EXPECT_NE(std::this_thread::get_id(), std::async(std::launch::async, []() { return std::this_thread::get_id(); }).get()) << "asyc, it should be executed asynchroniously";
}

TEST(Future, Async_FeatureDestructorIsBlockedUntilTaskIsNotCompleted) {
  const auto start_t = clock();
  {
    auto future = std::async(std::launch::async, []() { std::this_thread::sleep_for(10ms); });
    (void)future;
  }
  const auto end_t = clock();
  EXPECT_LE(10, end_t - start_t);
}

TEST(Future, PackagedTask_FeatureDestructorDoesntWaitTaskToBeCompleted) {
  const auto start_t = clock();
  {
    auto future = std::packaged_task<void()>([]() { std::this_thread::sleep_for(10ms); });
    (void)future;
  }
  const auto end_t = clock();
  EXPECT_GE(10, end_t - start_t);
}

TEST(Future, PackagedTask_UsedAsAFutureFactory) {
  auto task = std::packaged_task<std::thread::id()>([]() { return std::this_thread::get_id(); });
  auto future = task.get_future();
  EXPECT_EQ(std::future_status::timeout, future.wait_for(1ms));
  task();
  EXPECT_EQ(std::this_thread::get_id(), future.get());
}

TEST(Future, Promise_UsedAsAFutureFactory) {
  std::promise<int> my_promise;
  auto task = [&my_promise]() { my_promise.set_value(1); };
  auto future = my_promise.get_future();
  EXPECT_EQ(std::future_status::timeout, future.wait_for(1ms));
  task();
  EXPECT_EQ(1, future.get());
}

TEST(Future, Promise_HandleExceptions) {
  std::promise<int> my_promise;
  auto task = [&my_promise]() {
    // in normal usecase std::current_exception(); should be used instead of make_exception_ptr
    my_promise.set_exception(std::make_exception_ptr(std::runtime_error{"async exception"}));
  };
  auto future = my_promise.get_future();
  EXPECT_EQ(std::future_status::timeout, future.wait_for(1ms));
  task();
  EXPECT_THROW(future.get(), std::runtime_error);
}