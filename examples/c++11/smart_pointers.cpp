#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

using ::testing::_;
using ::testing::Invoke;
using ::testing::MockFunction;

TEST(SmartPointers, SharedPtr_IncreaseRefCountWhenPointerIsCopied) {
  auto pointer = std::make_shared<int>(10);
  auto pointer1 = pointer;
  EXPECT_EQ(2, pointer.use_count());
  EXPECT_EQ(2, pointer1.use_count());
  pointer.reset();
  EXPECT_EQ(0, pointer.use_count());
  EXPECT_EQ(1, pointer1.use_count());
  pointer1.reset();
  EXPECT_EQ(0, pointer.use_count());
  EXPECT_EQ(0, pointer1.use_count());
}

TEST(SmartPointers, SharedPtr_Aliasing) {
  struct MyStruct {
    int a;
    char b;
    std::string str;
  };

  MockFunction<void(MyStruct*)> customDeleterMock;
  auto shared = std::shared_ptr<MyStruct>(new MyStruct{1, 2, "secret string"}, customDeleterMock.AsStdFunction());
  auto alias = std::shared_ptr<std::string>(shared, &shared->str);
  shared.reset();
  // The custom deleter should be called after destroying the alias object
  EXPECT_CALL(customDeleterMock, Call(_)).Times(1).WillOnce(Invoke([](auto ptr) { delete ptr; }));
}

TEST(SmartPointers, SharedPtr_WithCustomDeleter) {
  MockFunction<void(int*)> customDeleterMock;
  EXPECT_CALL(customDeleterMock, Call(_)).Times(1).WillOnce(Invoke([](auto ptr) { delete ptr; }));
  std::shared_ptr<int>(new int{10}, customDeleterMock.AsStdFunction()).reset();
}

TEST(SmartPointers, UniquePtr_MoveOwnership) {
  auto uniqe_ptr = std::make_unique<int>(10);
  auto new_ptr = std::move(uniqe_ptr);
  EXPECT_FALSE(uniqe_ptr.get()) << "Ownership is moved to another pointer";
  EXPECT_TRUE(new_ptr.get()) << "I have the ownership";
}

TEST(SmartPointers, WeakPtr_ANoOwningPointer) {
  auto shared_ptr = std::make_shared<int>(10);
  std::weak_ptr<int> weak_ptr = shared_ptr;
  EXPECT_TRUE(weak_ptr.lock().get()) << "It point to valid shared pointer";
  shared_ptr.reset();
  EXPECT_FALSE(weak_ptr.lock().get()) << "It doesn't extend the lifespan of object";
}

TEST(SmartPointers, UniquePtr_SingleOwnershipPtr) {
  auto unique_ptr = std::make_unique<int>(10);
  auto new_owner = std::move(unique_ptr);
  EXPECT_FALSE(unique_ptr.get()) << "The memory is not owned by this object anymore";
  EXPECT_TRUE(new_owner.get()) << "The ownership is moved to this object";
}

TEST(SmartPointers, UniquePtr_To_Shared) {
  auto unique_ptr = std::make_unique<int>(10);
  std::shared_ptr<int> shared_ownership = std::move(unique_ptr);
  EXPECT_FALSE(unique_ptr.get()) << "The memory is not owned by this object anymore";
  EXPECT_TRUE(shared_ownership.get()) << "But ownership is shared now";
}
