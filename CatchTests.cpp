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

TEST_CASE("Copy Semantics")
{
  std::string filename = "Lenna_standard.pgm";
  std::string output = "catchtest.pgm";
  Image testImage(filename, output);
  Image testImage2 = testImage;

  Image copy (testImage);
  auto testi = testImage.begin();
  auto test2i = testImage2.begin();
  auto copyi = copy.begin();
  while (copyi != copy.end())
  {
    REQUIRE(*testi == *copyi);
    REQUIRE(*testi == *test2i);
    ++testi;
    ++copyi;
    ++test2i;
  }
}

TEST_CASE("Move Semantics")
{
  std::string filename = "Lenna_standard.pgm";
  std::string output = "catchtest.pgm";
  Image testImage(Image(filename, output));
  Image testImage2 = Image(filename, output);
  Image control(filename, output);

  auto testi = testImage.begin();
  auto test2i = testImage2.begin();
  auto controli = control.begin();
  while (testi != testImage.end())
  {
    REQUIRE(*testi == *controli);
    REQUIRE(*test2i == *controli);
    ++testi;
    ++controli;
    ++test2i;
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

TEST_CASE("Invert Operator")
{
  std::string filename = "Lenna_standard.pgm";
  std::string output = "catchtest.pgm";
  Image testImage1(filename, output);
  Image testImage2(filename, output);

  testImage1 = !testImage1;

  auto test1i = testImage1.begin();
  auto test2i = testImage2.begin();
  while (test2i != testImage2.end())
  {
    int testint1 = (int)*test1i;
    int testint2 = 255 - (int)*test2i;
    if (testint2 < 0)
    {
      testint2 = 0;
    }

    REQUIRE(testint1 == testint2);

    ++test1i;
    ++test2i;
  }


}

TEST_CASE("Mask Operator")
{
  std::string filename = "Lenna_standard.pgm";
  std::string mask = "Lenna_hat_mask.pgm";
  std::string output = "catchtest.pgm";

  Image testImage1(filename, output);
  Image control(filename, output);
  Image testImage2(mask, output);

  testImage1 = testImage1/testImage2;

  auto test1i = testImage1.begin();
  auto controli = control.begin();
  auto test2i = testImage2.begin();

  while(test1i != testImage1.end())
  {
    int propervalue;
    if ((int)(*test2i) == 255)
    {
      propervalue = (int) (*controli);
    }
    else
    {
      propervalue = 0;
    }

    REQUIRE(propervalue == (int)(*test1i));

    ++test1i;
    ++test2i;
    ++controli;
  }
}

TEST_CASE("Threshold Operator")
  {
    std::string filename = "Lenna_standard.pgm";
    std::string output = "catchtest.pgm";
    Image testImage1(filename, output);
    Image testImage2(filename, output);

    testImage1 = testImage1 * 125;

    auto test1i = testImage1.begin();
    auto test2i = testImage2.begin();

    while(test1i != testImage1.end())
    {
      int propervalue;
      if ((int)(*test2i) > 125)
      {
        propervalue = 255;
      }
      else
      {
        propervalue = 0;
      }

      REQUIRE(propervalue == (int)(*test1i));

      ++test1i;
      ++test2i;
    }

  }
