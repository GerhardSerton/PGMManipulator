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
  std::cout << j << "\n";
  REQUIRE(j == 512*512);
}
