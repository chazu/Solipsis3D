#ifndef UlxrIdlTestFuncsUlxrClient_H
#define UlxrIdlTestFuncsUlxrClient_H

///////////////////////////////////////////////////////////////////
// Automatically generated by xml2ulxr v1.7.3.
//
// xml2ulxr is part of Ultra Lightweight XML RPC for C++.
// See also http://ulxmlrpcpp.sourceforge.net
//
// Don't edit manually unless you know what you are doing
///////////////////////////////////////////////////////////////////


//#define ULXR_UNICODE_ONLY_HELPERS
#include <ulxmlrpcpp/ulxmlrpcpp.h> // always first

namespace ulxr
{
  class Requester;
}

namespace funcs {
// mapped to funcs__free_function1_ovr0 (there are overloaded methods)
void free_function1(int i);
}

namespace funcs {
// mapped to funcs__free_function1_ovr1 (there are overloaded methods)
long int free_function1(long int i, float f);
}

namespace inline_func {
// mapped to inline_func__free_function2 (there are overloaded methods)
std::string * free_function2(long int * i, float f);
}

void UlxrIdlTestFuncs_setClientCredentials
  (ulxr::Requester &in_requester, const ulxr::CppString &realm,
   const ulxr::CppString &user, const ulxr::CppString &pass);

#endif // UlxrIdlTestFuncsUlxrClient_H

