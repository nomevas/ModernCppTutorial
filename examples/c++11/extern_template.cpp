// In traditional C++, templates are instantiated by the compiler only when they are used. In other words,
// as long as a fully defined template is encountered in the code compiled in each compilation unit (file), it will be instantiated.
// This results in an increase in compile time due to repeated instantiations. Also, we have no way to tell the
// compiler not to trigger the instantiation of the template.

#include <gtest/gtest.h>

#include "helpers/extern_template_class.h"

TEST(ExternTemplate, IncludeTemplateWithoutDefinition) {
  EXPECT_STREQ("i", ExternTemplateClass<int>::type_info());
  EXPECT_STREQ("c", ExternTemplateClass<char>::type_info());
  // EXPECT_STREQ("c", ExternTemplateClass<double>::type_info());  This is a compiler error
}
