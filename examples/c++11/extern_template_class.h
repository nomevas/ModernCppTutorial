#pragma once 

template <class T>
struct ExternTemplateClass {
    static const char* type_info();
};

// Suppresses implicit instantiation below
// ExternTemplateClass<T> will be explicitly instantiated elsewhere
extern template class ExternTemplateClass<int>;
extern template class ExternTemplateClass<char>; 