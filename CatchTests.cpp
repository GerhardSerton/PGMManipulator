#define CATCH_CONFIG_MAIN
#include <iostream>
#include <fstream>
#include <string>
#include "catch.hpp"
#include "Image.h"

TEST_CASE("Iterator Tests")
{
  std::string filename = "Lenna_standard.pgm";
  std::string output = "catchtest.pgm";
  Image testImage(filename, output);
  int j = 0;
  unsigned char testArray [512*512];
  for (auto i = testImage.begin(); i != testImage.end(); ++i)
  {
    testArray[j] = *i;
    j++;
  }
  unsigned char * control = testImage.getContents();
  for (int f = 0; f < 512*512; ++f)
  {
    REQUIRE(testArray[f] == control[f]);
  }

  REQUIRE(j == 512*512);
}

TEST_CASE("Copy Constructor")
{
  std::string filename = "Lenna_standard.pgm";
  std::string output = "catchtest.pgm";
  Image testImage(filename, output);

  Image copy (testImage);
  auto testi = testImage.begin();
  auto copyi = copy.begin();
  while (copyi != copy.end())
  {
    REQUIRE(*testi == *copyi);
    ++testi;
    ++copyi;
  }
}

TEST_CASE("Addition Operator")
{
  std::string filename = "Lenna_standard.pgm";
  std::string output = "catchtest.pgm";
  Image testImage1(filename, output);
  Image testImage2(filename, output);

  testImage1 = testImage1 + testImage2;

  auto test1i = testImage1.begin();
  auto test2i = testImage2.begin();
  while (test2i != testImage2.end())
  {
    int testint1 = (int)*test1i;
    int testint2 = (int)*test2i + (int)*test2i;
    if (testint2 > 255)
    {
      testint2 = 255;
    }

    REQUIRE(testint1 == testint2);

    ++test1i;
    ++test2i;
  }

}

TEST_CASE("Subtract Operator")
{
  std::string filename = "Lenna_standard.pgm";
  std::string output = "catchtest.pgm";
  Image testImage1(filename, output);
  Image testImage2(filename, output);

  testImage1 = testImage1 - testImage2;

  auto test1i = testImage1.begin();
  auto test2i = testImage2.begin();
  while (test2i != testImage2.end())
  {
    int testint1 = (int)*test1i;
    int testint2 = (int)*test2i - (int)*test2i;
    if (testint2 < 0)
    {
      testint2 = 0;
    }

    REQUIRE(testint1 == testint2);

    ++test1i;
    ++test2i;
  }

}
