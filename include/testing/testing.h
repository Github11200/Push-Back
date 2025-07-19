#ifndef TESTING_H
#define TESTING_H

#include "../vex.h"

using namespace std;
using namespace vex;

namespace Testing
{
  enum Result
  {
    FAIL = 0,
    PASS = 1
  };

  struct TestCase
  {
    string name;
    function<Result(string &)> func;
  };

  struct AssertionFailure : public exception
  {
    string message;
    AssertionFailure(const string &message) : message(message) {}
    const char *what() const noexcept override { return message.c_str(); }
  };

  inline vector<TestCase> &getAllTestCases()
  {
    static vector<TestCase> testCases;
    return testCases;
  }

  inline void registerTest(const string &name, function<Result(string &)> func)
  {
    getAllTestCases().push_back({name, func});
  }

  inline void runAllTests()
  {
    int numberFailed = 0, numberPassed = 0, numberOfTestCases = 0;
    for (const auto &testCase : getAllTestCases())
    {
      ++numberOfTestCases;
      string errorMessage;
      if (testCase.func(errorMessage) == Result::PASS)
      {
        cout << "[PASSED] " << testCase.name << "\n";
        ++numberPassed;
      }
      else
      {
        cout << "[FAILED] " << testCase.name << ": " << errorMessage << "\n";
        ++numberFailed;
      }
    }

    cout << "\n\nRESULTS:\n";
    cout << "\t[# PASSED] " << numberPassed << "\n";
    cout << "\t[# FAILED] " << numberFailed << "\n";
    cout << "\t[TOTAL] " << numberOfTestCases << "\n";
  }
};

#define TEST(name)                                   \
  Testing::Result test_##name(string &errorMessage); \
  struct testRegistrar_##name                        \
  {                                                  \
    testRegistrar_##name()                           \
    {                                                \
      Testing::registerTest(#name, test_##name);     \
    }                                                \
  } testRegistrarInstance_##name;                    \
  Testing::Result test_##name(string &errorMessage)

#define ASSERT_EQUAL(actual, expected)                            \
  if ((actual) != (expected))                                     \
  {                                                               \
    errorMessage = "\tEXPECTED: " #expected "\n\tACTUAL" #actual; \
    return Testing::Result::FAIL;                                 \
  }

#define ASSERT_TRUE(value)                                          \
  if (!(value))                                                     \
  {                                                                 \
    errorMessage = "\t" #value " is FALSE, expected it to be TRUE"; \
    return Testing::Result::FAIL;                                   \
  }

#define ASSERT_FALSE(value)                                         \
  if ((value))                                                      \
  {                                                                 \
    errorMessage = "\t" #value " is TRUE, expected it to be FALSE"; \
    return Testing::Result::FAIL;                                   \
  }

#endif