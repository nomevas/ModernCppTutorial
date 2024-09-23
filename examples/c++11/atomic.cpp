#include <gtest/gtest.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

TEST(Atomic, Atomic_DoAtomicFetchAndOpOperations) {
  std::atomic<int> test = 0;
  EXPECT_EQ(0, test) << "Fetch works as ususal";
  test.fetch_add(1);
  EXPECT_EQ(1, test) << "atomic fatch and add";
  EXPECT_EQ(2, ++test) << "atomic fatch and add";
  EXPECT_EQ(2, test++) << "atomic fatch and add";
  test.fetch_sub(1);
  EXPECT_EQ(2, test) << "atomic fatch and sub";
  test.fetch_or(1);
  EXPECT_EQ(3, test) << "atomic fatch and or";
  test.fetch_xor(1);
  EXPECT_EQ(2, test) << "atomic fatch and xor";
  test.fetch_and(0);
  EXPECT_EQ(0, test) << "atomic fatch and and";
}

TEST(Atomic, Atomic_CheckIfAtomicObjectIsLockFree) {
  struct A {
    int a[100];
  };
  struct B {
    int x, y;
  };
  // EXPECT_FALSE(std::atomic<A>{}.is_lock_free()); // this is a linker error
  EXPECT_TRUE(std::atomic<B>{}.is_lock_free());
}

TEST(Atomic, MemoryOrder_Relaxed_GoodForRefCounting) {
  std::atomic<int> cnt = {0};
  auto incrementCounter = [&cnt]() { cnt.fetch_add(1, std::memory_order_relaxed); };
  constexpr int N = 1000;
  std::array<std::thread, N> threads;
  std::ranges::generate(threads, [incrementCounter]() { return std::thread(incrementCounter); });
  std::ranges::for_each(threads, [](auto&& thread) { thread.join(); });
  EXPECT_EQ(N, cnt) << "No data races while reading/writing to cnt. The increment is an atomic operation";
}

TEST(Atomic, MemoryOrder_Release_Acquire__ConsumerTreadIsGuaranteedToSeeEverythingThatProducerThreadWroteToMemory) {
  // Mutual exclusion locks, such as std::mutex or atomic spinlock, are an example of release-acquire synchronization: when the lock
  // is released by thread A and acquired by thread B, everything that took place in the critical section (before the release) in
  // the context of thread A has to be visible to thread B (after the acquire) which is executing the same critical section.

  std::atomic<bool> flag{false};
  int non_atomic_data{0};
  int deliveredValue{0};

  std::thread producer([&]() {
    non_atomic_data = 1;
    flag.store(true, std::memory_order_release);
  });

  std::thread consumer([&]() {
    while (!flag.load(std::memory_order_acquire)) {
      std::this_thread::sleep_for(1ms);
    }
    deliveredValue = non_atomic_data;
  });

  producer.join();
  consumer.join();
  EXPECT_EQ(1, deliveredValue) << "Syncing of non_atomic_data written before releasing it at the Consumer side is guaranteed";
}

TEST(Atomic, MemoryOrder_Release_Consume__ConsumerTreadIsGuaranteedToSeeEverythingThatProducerThreadWroteToMemory) {
  // Typical use cases for this ordering involve read access to rarely written concurrent data structures
  // (routing tables, configuration, security policies, firewall rules, etc) and publisher-subscriber situations
  // with pointer-mediated publication, that is, when the producer publishes a pointer through which the consumer
  // can access information: there is no need to make everything else the producer wrote to memory visible to
  // the consumer (which may be an expensive operation on weakly-ordered architectures).

  std::atomic<bool> flag{false};
  int non_atomic_data{0};
  int deliveredValue{0};

  std::thread producer([&]() {
    non_atomic_data = 1;
    flag.store(true, std::memory_order_release);
  });

  std::thread consumer([&]() {
    while (!flag.load(std::memory_order_consume)) {
      std::this_thread::sleep_for(1ms);
    }
    deliveredValue = non_atomic_data;
  });

  producer.join();
  consumer.join();
  EXPECT_EQ(1, deliveredValue) << "Syncing of non_atomic_data written before releasing it at the Consumer side is guaranteed";
}

TEST(Atomic, MemoryOrder_Sequentially_Consistent__MultipleProducersMultipleObservers) {
  std::atomic<bool> x = {false};
  std::atomic<bool> y = {false};
  std::atomic<int> z = {0};

  auto write_x = [&]() { x.store(true, std::memory_order_seq_cst); };
  auto write_y = [&]() { y.store(true, std::memory_order_seq_cst); };

  auto read_x_then_y = [&]() {
    while (!x.load(std::memory_order_seq_cst)) {
      std::this_thread::sleep_for(1ms);
    };
    if (y.load(std::memory_order_seq_cst)) ++z;
  };

  auto read_y_then_x = [&]() {
    while (!y.load(std::memory_order_seq_cst)) {
      std::this_thread::sleep_for(1ms);
    };
    if (x.load(std::memory_order_seq_cst)) ++z;
  };

  auto threads = std::array<std::thread, 4>{std::thread(write_x), std::thread(write_y), std::thread(read_x_then_y), std::thread(read_y_then_x)};
  for (auto&& thread : threads) {
    thread.join();
  }

  EXPECT_NE(0, z) << "Z store will be never reordered";
}
