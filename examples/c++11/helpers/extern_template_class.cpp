#include "extern_template_class.h"

#include <typeinfo>

template <class T>
const char* ExternTemplateClass<T>::type_info() {
  return typeid(T).name();
}

// force instantiation
template class ExternTemplateClass<int>;
template class ExternTemplateClass<char>;