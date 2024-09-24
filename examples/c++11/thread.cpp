#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <thread>

using ::testing::MockFunction;

TEST(Thread, CreateAThread) {
  MockFunction<void()> threadEntryPoint;
  EXPECT_CALL(threadEntryPoint, Call()).Times(1);
  std::thread{threadEntryPoint.AsStdFunction()}.join();
}

TEST(Thread, Thread_TerminatesTheAppInCaseForgetToJoinOrDetach) {
  ASSERT_DEATH(std::thread{[]() {}}, "terminate called without an active exception");
}

TEST(Thread, Thread_ThrowAnException_TerminateTheApp) {
  ASSERT_DEATH(std::thread{[]() { throw std::runtime_error{"Unhandled thread exception"}; }}.join(), "terminate called after throwing an instance of 'std::runtime_error'");
}

TEST(Thread, HardwareConcurrency_GetTheNumberOfConcurrentThreadsSupportedByTheImplementation) {
  EXPECT_LT(0u, std::thread::hardware_concurrency()) << "It has to be bigger than 0";
}

TEST(Thread, ThisThread_GetInformationAboutCurrentThread) { EXPECT_NE(0, std::hash<std::thread::id>{}(std::this_thread::get_id())) << "Current thread has a valid thread id"; }