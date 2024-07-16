// The template has always been one of C++'s unique Black Magic. In traditional C++, both a class template and 
// a function template could only accept a fixed set of template parameters as specified; C++11 added a new representation, 
// allowing any number, template parameters of any category, and there is no need to fix the number of parameters when defining.

#include <gtest/gtest.h>

template <class... Ts>
static auto GetNumberOfVaridaticArguments(Ts... args) {
    return  sizeof...(args);
}

TEST(VariadicTemplte, DefineTempateWithVariableNumberOfArugments) {
    EXPECT_EQ(1, GetNumberOfVaridaticArguments(1));
    EXPECT_EQ(3, GetNumberOfVaridaticArguments(1, "another argument", -3.4));
}

template<typename T0, typename... T>
static std::string ExpandTemplateParameters(T0 t0, T... t) {
    std::ostringstream oss;
    
    oss << t0 << ";";
    if constexpr (sizeof...(t) > 0) {
        oss << ExpandTemplateParameters(t...);
    } 

    return oss.str();
}

TEST(VariadicTemplte, RecursiveParameterTemplateExpansion_Cpp17 ) {
    EXPECT_EQ("1;", ExpandTemplateParameters(1));
    EXPECT_EQ("1;another argument;-3.4;", ExpandTemplateParameters(1, "another argument", -3.4));
}

template<typename... T>
static auto sum(T... t) {
    return (t + ...);
}

TEST(VariadicTemplte, FoldExpression_Cpp17 ) {
    EXPECT_EQ(21, sum(1, 2, 3, 4, 5, 6));
}