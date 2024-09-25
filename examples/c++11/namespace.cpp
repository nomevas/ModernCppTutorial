#include <gtest/gtest.h>

namespace ParentNamespace {
namespace NestedNamespace {
static int Value = 10;
}
}  // namespace ParentNamespace

namespace CombinedNamespace {
namespace NestedNamespace = ParentNamespace::NestedNamespace;
using ParentNamespace::NestedNamespace::Value;
}  // namespace CombinedNamespace

TEST(Namespace, AvoidDefiningNamspacesInCppFiles) {
  using namespace ParentNamespace::NestedNamespace;
  EXPECT_EQ(10, Value) << "Value is visible in this scope";
}

TEST(Namespace, UsingWithScopeOperator) { EXPECT_EQ(10, ParentNamespace::NestedNamespace::Value); }

TEST(Namespace, NamespaceAliases) {
  namespace Alias = ParentNamespace::NestedNamespace;
  EXPECT_EQ(10, Alias::Value);
}

TEST(Namespace, CombinedNamespace) {
  EXPECT_EQ(10, CombinedNamespace::Value);
  EXPECT_EQ(10, CombinedNamespace::NestedNamespace::Value);
}

namespace NamespaceWithIninleNestedNamespace {
inline namespace v2 {
static constexpr int Version = 2;
}
namespace v1 {
static constexpr int Version = 1;
}
}  // namespace NamespaceWithIninleNestedNamespace

TEST(Namespace, InlineNamespace) {
  EXPECT_EQ(2, NamespaceWithIninleNestedNamespace::Version) << "v2 symbols are visible also on the parent scope";
  EXPECT_EQ(1, NamespaceWithIninleNestedNamespace::v1::Version) << "and you can still use the v1 version";
}