#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <future>
#include <mutex>
#include <shared_mutex>
#include <thread>

using namespace std::chrono_literals;

TEST(Mutex, Mutex_ProtectSharedDataFromBeingSimultaneouslyAccessed) {
  std::mutex mutex;
  ASSERT_NO_THROW(mutex.lock()) << "mutex may throw std::system_error";
  EXPECT_FALSE(mutex.try_lock()) << "mutex is already lock, don't lock it once again";
  mutex.unlock();  // unlock doesn't throw exceptions
  EXPECT_TRUE(mutex.try_lock()) << "the mutex is availalbe once again, it can be locked";
}

TEST(Mutex, RecursiveMutex_LockMutexRecursivly) {
  std::recursive_mutex mutex;
  ASSERT_NO_THROW(mutex.lock()) << "mutex may throw std::system_error";
  EXPECT_TRUE(mutex.try_lock()) << "mutex can be locked recursively";
  EXPECT_FALSE(std::async(std::launch::async, [&]() { return mutex.try_lock(); }).get());
  mutex.unlock();  // unlock doesn't throw exceptions
  EXPECT_FALSE(std::async(std::launch::async, [&]() { return mutex.try_lock(); }).get()) << "the mutex was locked twice, it is still in locked state";
  mutex.unlock();
  EXPECT_TRUE(std::async(std::launch::async, [&]() { return mutex.try_lock(); }).get()) << "mutex can be locked from another thread";
}

TEST(Mutex, TimedMutex_TryToLockForACertainPointOfTime) {
  std::timed_mutex mutex;
  ASSERT_NO_THROW(mutex.lock()) << "mutex may throw std::system_error";
  EXPECT_FALSE(mutex.try_lock()) << "mutex can't be locked recursively";
  auto unlock_mutex_future = std::async(std::launch::async, [&mutex]() { mutex.unlock(); });
  EXPECT_TRUE(mutex.try_lock_for(100ms)) << "mutex should be released";
  unlock_mutex_future = std::async(std::launch::async, [&mutex]() { mutex.unlock(); });
  EXPECT_TRUE(mutex.try_lock_until(std::chrono::system_clock::now() + 100ms)) << "mutex should be released";
}

TEST(Mutex, SharedMutex_LockForWrite) {
  std::shared_mutex mutex;
  EXPECT_TRUE(mutex.try_lock_shared()) << "lock for reading";
  EXPECT_TRUE(mutex.try_lock_shared()) << "you can lock the one more time for reading";
  EXPECT_FALSE(mutex.try_lock()) << "but not for writing";
  mutex.unlock_shared();
  EXPECT_FALSE(mutex.try_lock()) << "still writing is not allowed, there is one more shared lock";
  mutex.unlock_shared();
  EXPECT_TRUE(mutex.try_lock()) << "finally the write lock could be acquired";
}

TEST(Mutex, UniqueLock_UnlocksTheMutexWhenObjectIsDestroyed) {
  std::mutex mutex;
  auto unique_lock = std::make_unique<std::unique_lock<std::mutex>>(mutex);
  EXPECT_THROW(unique_lock->try_lock(), std::system_error) << "lock is already acquired by the unique lock";
  unique_lock->unlock();
  EXPECT_TRUE(unique_lock->try_lock()) << "the mutex is released, try to acquire it once again";
  EXPECT_THROW(unique_lock->try_lock(), std::system_error) << "lock is already acquired";
  unique_lock.reset();
  EXPECT_TRUE(mutex.try_lock()) << "the unique lock is destroyed, the lock can be acquired again";
}

TEST(Mutex, SharedLock_TheSameAsUniqueLockButItUsesLockShared) {
  std::shared_mutex mutex;
  auto shared_lock = std::make_unique<std::shared_lock<std::shared_mutex>>(mutex);
  EXPECT_THROW(shared_lock->try_lock(), std::system_error) << "lock is already acquired by the shared lock, just reading is allowed";
  shared_lock->unlock();
  EXPECT_TRUE(shared_lock->try_lock()) << "the shared lock is destroyed, the lock can be acquired again";
  EXPECT_THROW(shared_lock->try_lock(), std::system_error) << "lock is already acquired";
  shared_lock.reset();
  EXPECT_TRUE(mutex.try_lock()) << "The mutex can be locked once again after destroying the shared lock object";
}

TEST(Mutex, LockGuard_ScopedBasedMutexLock) {
  std::mutex mutex;
  auto lock_guard = std::make_unique<std::lock_guard<std::mutex>>(mutex);
  EXPECT_FALSE(mutex.try_lock()) << "lock is already acquired by the shared lock, just reading is allowed";
  lock_guard.reset();
  EXPECT_TRUE(mutex.try_lock()) << "the shared lock is destroyed, the lock can be acquired again";
}

TEST(Mutex, ScopedLock_WorkWithMultipleMutexes) {
  std::mutex mutex1;
  std::mutex mutex2;
  auto scoped_lock = std::make_unique<std::scoped_lock<std::mutex, std::mutex>>(mutex1, mutex2);
  EXPECT_FALSE(mutex1.try_lock()) << "lock is already acquired by the scoped lock, just reading is allowed";
  EXPECT_FALSE(mutex2.try_lock()) << "lock is already acquired by the scoped lock, just reading is allowed";
  scoped_lock.reset();
  EXPECT_TRUE(mutex1.try_lock()) << "lock is destoyed, the mutex is available again";
  EXPECT_TRUE(mutex2.try_lock()) << "lock is destoyed, the mutex is available again";
}

TEST(Mutex, ConditionalVariable_WaitUntilSomeoneElseTrigger) {
  std::mutex mutex;
  std::unique_lock unique_lock{mutex};
  bool ready = false;
  std::condition_variable condition_variable;

  auto future = std::async(std::launch::async, [&]() {
    std::this_thread::sleep_for(10ms);
    {
      // manual unlocking is done before notifying, to avoid waking up
      // the waiting thread only to block again (see notify_one for details)
      std::lock_guard<std::mutex> lock_guard{mutex};
      ready = true;
    }

    condition_variable.notify_one();
  });

  EXPECT_TRUE(condition_variable.wait_for(unique_lock, 100ms, [&]() { return ready; }));
  EXPECT_TRUE(ready);
}
