//
//  test.cpp
//  tiny_stl
//
//  Created by junl on 2020/11/9.
//  Copyright © 2020 junl. All rights reserved.
//

#include "test.h"
namespace tiny {
namespace test{
UnitTest* UnitTest::GetInstance()
{
  static UnitTest instance;
  return &instance;
}

TestCase* UnitTest::RegisterTestCase(TestCase* testcase)
{
  testcases_.push_back(testcase);
  return testcase;
}

void UnitTest::Run()
{
  for (auto it : testcases_)
  {
    TestCase* testcase = it;
    CurrentTestCase = testcase;
    testcase->nTestResult = 1;
    testcase->nFailed = 0;
    testcase->nPassed = 0;
    std::cout << green << "============================================\n";
    std::cout << green << " Run TestCase:" << testcase->testcase_name << "\n";
    testcase->Run();
    if (testcase->nFailed == 0)
      std::cout << green;
    else
      std::cout << red;
    std::cout << " " << testcase->nPassed << " / " << testcase->nFailed + testcase->nPassed
      << " Cases passed. ( " << testcase->nPassed /
      (testcase->nFailed + testcase->nPassed) * 100 << "% )\n";
    std::cout << green << " End TestCase:" << testcase->testcase_name << "\n";
    if (testcase->nTestResult)
      ++nPassed;
    else
      ++nFailed;
  }
  std::cout << green << "============================================\n";
  std::cout << green << " Total TestCase : " << nPassed + nFailed << "\n";
  std::cout << green << " Total Passed : " << nPassed << "\n";
  std::cout << red << " Total Failed : " << nFailed << "\n";
  std::cout << green << " " << nPassed << " / " << nFailed + nPassed
    << " TestCases passed. ( " << nPassed / (nFailed + nPassed) * 100 << "% )\n";
}

void test_len(size_t len1, size_t len2, size_t len3, size_t wide)
{
  std::string str1, str2, str3;
  std::stringstream ss;
  ss << len1 << " " << len2 << " " << len3;
  ss >> str1 >> str2 >> str3;
  str1 += "   |";
  std::cout << std::setw(wide) << str1;
  str2 += "   |";
  std::cout << std::setw(wide) << str2;
  str3 += "   |";
  std::cout << std::setw(wide) << str3 << "\n";
}
}
}
