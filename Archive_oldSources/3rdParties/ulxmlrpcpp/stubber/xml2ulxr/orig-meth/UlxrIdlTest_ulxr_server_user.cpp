///////////////////////////////////////////////////////////////////
// Automatically generated by xml2ulxr v1.7.3.
//
// xml2ulxr is part of Ultra Lightweight XML RPC for C++.
// See also http://ulxmlrpcpp.sourceforge.net
//
// Intended for manual and persistent changes 
/////////////////////////////////////////////////

//#define ULXR_UNICODE_ONLY_HELPERS
#include <ulxmlrpcpp/ulxmlrpcpp.h> // always first

#include <ulxmlrpcpp/ulxr_value.h>
#include "UlxrIdlTest_ulxr_server.h"

#include <ulxmlrpcpp/ulxr_response.h>
#include <ulxmlrpcpp/ulxr_method_adder.h>
#include <ulxmlrpcpp/ulxr_signature.h>

#include "/home/ea/Documents/src/ulxmlrpcpp/trunk/ulxmlrpcpp/stubber/ulxr2xml/ulxridl_test.h"
#include "UlxrIdlTest_ulxr_names.h"


void UlxrIdlTestServer::setupServerMethods()
{
  // mapped to: void first_url4();   (there are overloaded methods)
  method_adder.addMethod(ulxr::make_method(*this, &UlxrIdlTestServer::first_url4_ovr4),
                         ulxr::Void::getValueName(),
                         ULXR_CALLTO_UlxrIdlTest_first_url4_ovr4,
                         ulxr::Signature(),
                         ulxr_i18n(ULXR_PCHAR("Some descriptive comment about 'void UlxrIdlTest::first_url4()'."))); // TODO adjust comment

  // mapped to: std::string * first_url4(int i);   (there are overloaded methods)
  method_adder.addMethod(ulxr::make_method(*this, &UlxrIdlTestServer::first_url4_ovr3),
                         ulxr::RpcString::getValueName(),
                         ULXR_CALLTO_UlxrIdlTest_first_url4_ovr3,
                         ulxr::Signature()
                           << ulxr::Integer::getValueName(),
                         ulxr_i18n(ULXR_PCHAR("Some descriptive comment about 'std::string * UlxrIdlTest::first_url4(int i)'."))); // TODO adjust comment

  // mapped to: std::string * first_url4(long int li);   (there are overloaded methods)
  method_adder.addMethod(ulxr::make_method(*this, &UlxrIdlTestServer::first_url4_ovr2),
                         ulxr::RpcString::getValueName(),
                         ULXR_CALLTO_UlxrIdlTest_first_url4_ovr2,
                         ulxr::Signature()
                           << ulxr::Integer::getValueName(),
                         ulxr_i18n(ULXR_PCHAR("Some descriptive comment about 'std::string * UlxrIdlTest::first_url4(long int li)'."))); // TODO adjust comment

  // mapped to: const char * first_url4(float li);   (there are overloaded methods)
  method_adder.addMethod(ulxr::make_method(*this, &UlxrIdlTestServer::first_url4_ovr1),
                         ulxr::RpcString::getValueName(),
                         ULXR_CALLTO_UlxrIdlTest_first_url4_ovr1,
                         ulxr::Signature()
                           << ulxr::Double::getValueName(),
                         ulxr_i18n(ULXR_PCHAR("Some descriptive comment about 'const char * UlxrIdlTest::first_url4(float li)'."))); // TODO adjust comment

  // mapped to: wchar_t * const first_url4(double li);   (there are overloaded methods)
  method_adder.addMethod(ulxr::make_method(*this, &UlxrIdlTestServer::first_url4_ovr0),
                         ulxr::RpcString::getValueName(),
                         ULXR_CALLTO_UlxrIdlTest_first_url4_ovr0,
                         ulxr::Signature()
                           << ulxr::Double::getValueName(),
                         ulxr_i18n(ULXR_PCHAR("Some descriptive comment about 'wchar_t * const UlxrIdlTest::first_url4(double li)'."))); // TODO adjust comment

  // mapped to: std::string constTest() const;
  method_adder.addMethod(ulxr::make_method(*this, &UlxrIdlTestServer::constTest),
                         ulxr::RpcString::getValueName(),
                         ULXR_CALLTO_UlxrIdlTest_constTest,
                         ulxr::Signature(),
                         ulxr_i18n(ULXR_PCHAR("Some descriptive comment about 'std::string UlxrIdlTest::constTest() const'."))); // TODO adjust comment

  // mapped to: std::string & constRefTest() const;
  method_adder.addMethod(ulxr::make_method(*this, &UlxrIdlTestServer::constRefTest),
                         ulxr::RpcString::getValueName(),
                         ULXR_CALLTO_UlxrIdlTest_constRefTest,
                         ulxr::Signature(),
                         ulxr_i18n(ULXR_PCHAR("Some descriptive comment about 'std::string & UlxrIdlTest::constRefTest() const'."))); // TODO adjust comment

  // mapped to: long int * firstViewConst() const;
  method_adder.addMethod(ulxr::make_method(*this, &UlxrIdlTestServer::firstViewConst),
                         ulxr::Integer::getValueName(),
                         ULXR_CALLTO_UlxrIdlTest_firstViewConst,
                         ulxr::Signature(),
                         ulxr_i18n(ULXR_PCHAR("Some descriptive comment about 'long int * UlxrIdlTest::firstViewConst() const'."))); // TODO adjust comment

  // mapped to: std::string * firstView();
  method_adder.addMethod(ulxr::make_method(*this, &UlxrIdlTestServer::firstView),
                         ulxr::RpcString::getValueName(),
                         ULXR_CALLTO_UlxrIdlTest_firstView,
                         ulxr::Signature(),
                         ulxr_i18n(ULXR_PCHAR("Some descriptive comment about 'std::string * UlxrIdlTest::firstView()'."))); // TODO adjust comment

  // mapped to: std::wstring * nextView1(int i, long int * l, std::string & s, const bool * b, char c) const;
  method_adder.addMethod(ulxr::make_method(*this, &UlxrIdlTestServer::nextView1),
                         ulxr::RpcString::getValueName(),
                         ULXR_CALLTO_UlxrIdlTest_nextView1,
                         ulxr::Signature()
                           << ulxr::Integer::getValueName()
                           << ulxr::Integer::getValueName()
                           << ulxr::RpcString::getValueName()
                           << ulxr::Boolean::getValueName()
                           << ulxr::Integer::getValueName(),
                         ulxr_i18n(ULXR_PCHAR("Some descriptive comment about 'std::wstring * UlxrIdlTest::nextView1(int i, long int * l, std::string & s, const bool * b, char c) const'."))); // TODO adjust comment

  // mapped to: std::basic_string<char> * nextView2(int i, long int l, std::string & s, bool * const b, char c) const;
  method_adder.addMethod(ulxr::make_method(*this, &UlxrIdlTestServer::nextView2),
                         ulxr::RpcString::getValueName(),
                         ULXR_CALLTO_UlxrIdlTest_nextView2,
                         ulxr::Signature()
                           << ulxr::Integer::getValueName()
                           << ulxr::Integer::getValueName()
                           << ulxr::RpcString::getValueName()
                           << ulxr::Boolean::getValueName()
                           << ulxr::Integer::getValueName(),
                         ulxr_i18n(ULXR_PCHAR("Some descriptive comment about 'std::basic_string<char> * UlxrIdlTest::nextView2(int i, long int l, std::string & s, bool * const b, char c) const'."))); // TODO adjust comment

  // mapped to: void getNumObjects(std::string s);
  method_adder.addMethod(ulxr::make_method(*this, &UlxrIdlTestServer::getNumObjects),
                         ulxr::Void::getValueName(),
                         ULXR_CALLTO_UlxrIdlTest_getNumObjects,
                         ulxr::Signature()
                           << ulxr::RpcString::getValueName(),
                         ulxr_i18n(ULXR_PCHAR("Some descriptive comment about 'void UlxrIdlTest::getNumObjects(std::string s)'."))); // TODO adjust comment

  // mapped to: const std::basic_string<wchar_t> * getObject(const std::string & s);
  method_adder.addMethod(ulxr::make_method(*this, &UlxrIdlTestServer::getObject),
                         ulxr::RpcString::getValueName(),
                         ULXR_CALLTO_UlxrIdlTest_getObject,
                         ulxr::Signature()
                           << ulxr::RpcString::getValueName(),
                         ulxr_i18n(ULXR_PCHAR("Some descriptive comment about 'const std::basic_string<wchar_t> * UlxrIdlTest::getObject(const std::string & s)'."))); // TODO adjust comment

  // mapped to: int getNumPages(const std::wstring & s);
  method_adder.addMethod(ulxr::make_method(*this, &UlxrIdlTestServer::getNumPages),
                         ulxr::Integer::getValueName(),
                         ULXR_CALLTO_UlxrIdlTest_getNumPages,
                         ulxr::Signature()
                           << ulxr::RpcString::getValueName(),
                         ulxr_i18n(ULXR_PCHAR("Some descriptive comment about 'int UlxrIdlTest::getNumPages(const std::wstring & s)'."))); // TODO adjust comment

  // mapped to: const std::string * last_url4();   (there are overloaded methods)
  method_adder.addMethod(ulxr::make_method(*this, &UlxrIdlTestServer::last_url4_ovr0),
                         ulxr::RpcString::getValueName(),
                         ULXR_CALLTO_UlxrIdlTest_last_url4_ovr0,
                         ulxr::Signature(),
                         ulxr_i18n(ULXR_PCHAR("Some descriptive comment about 'const std::string * UlxrIdlTest::last_url4()'."))); // TODO adjust comment

  // mapped to: std::string * last_url4(int i);   (there are overloaded methods)
  method_adder.addMethod(ulxr::make_method(*this, &UlxrIdlTestServer::last_url4_ovr1),
                         ulxr::RpcString::getValueName(),
                         ULXR_CALLTO_UlxrIdlTest_last_url4_ovr1,
                         ulxr::Signature()
                           << ulxr::Integer::getValueName(),
                         ulxr_i18n(ULXR_PCHAR("Some descriptive comment about 'std::string * UlxrIdlTest::last_url4(int i)'."))); // TODO adjust comment

  // mapped to: std::string * last_url4(long int li);   (there are overloaded methods)
  method_adder.addMethod(ulxr::make_method(*this, &UlxrIdlTestServer::last_url4_ovr2),
                         ulxr::RpcString::getValueName(),
                         ULXR_CALLTO_UlxrIdlTest_last_url4_ovr2,
                         ulxr::Signature()
                           << ulxr::Integer::getValueName(),
                         ulxr_i18n(ULXR_PCHAR("Some descriptive comment about 'std::string * UlxrIdlTest::last_url4(long int li)'."))); // TODO adjust comment
}

