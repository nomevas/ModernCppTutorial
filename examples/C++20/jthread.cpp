#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <thread>

using ::testing::MockFunction;

TEST(JThread, JThread_AutoJoinOnDestroy) {
  MockFunction<void()> threadEntryPoint;
  EXPECT_CALL(threadEntryPoint, Call()).Times(1);
  std::jthread{threadEntryPoint.AsStdFunction()};
}