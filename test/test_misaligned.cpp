#include "../src/misaligned.h"
#include "gtest/gtest.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Defines
#define MAX_COLORS (5)
#define HEADER_COLORS (1)
#define MAX_COLOR_PAIRS (MAX_COLORS * MAX_COLORS + HEADER_COLORS)

// Macros
#define CHECK_STREQ_MAJOR(index, value)                                        \
  EXPECT_STREQ(getMajorColor(index), value)
#define CHECK_STREQ_MINOR(index, value)                                        \
  EXPECT_STREQ(getMinorColor(index), value)
#define PAIR_SWEEPER_START(majorIndex, minorIndex, maxIndex,                   \
                           expectedPairNumber)                                 \
  for (majorIndex = 0; majorIndex < maxIndex; majorIndex++) {                  \
    for (minorIndex = 0; minorIndex < maxIndex; minorIndex++) {                \
      expectedPairNumber = 1 + (majorIndex * maxIndex) + minorIndex;
#define PAIR_SWEEPER_END()                                                     \
  }                                                                            \
  }

static const char *majorColors[MAX_COLORS] = {"White", "Red", "Black", "Yellow",
                                              "Violet"};
static const char *minorColors[MAX_COLORS] = {"Blue", "Orange", "Green",
                                              "Brown", "Slate"};

// To load the expected color pairs from a file
std::vector<std::string> loadExpectedPairs(const std::string &filename) {
  std::vector<std::string> expectedPairs;
  std::ifstream file(filename);
  if (!file.is_open()) {
    ADD_FAILURE() << "Failed to open file: " << filename;
    return expectedPairs;
  }
  std::string line;
  while (std::getline(file, line)) {
    // Trim trailing newline
    if (!line.empty() && line.back() == '\r')
      line.pop_back();
    expectedPairs.push_back(line);
  }
  file.close();
  if (expectedPairs.size() != MAX_COLORS * MAX_COLORS + HEADER_COLORS) {
    ADD_FAILURE() << "Expected " << MAX_COLORS * MAX_COLORS + HEADER_COLORS
                  << " pairs, but loaded " << expectedPairs.size();
  }

  return expectedPairs;
}

void testGetMajorColor() {
  // Iteration of valid set
  for (int index = 0; index < MAX_COLORS; index++) {
    CHECK_STREQ_MAJOR(index, majorColors[index]);
  }
  // Invalid set
  CHECK_STREQ_MAJOR(5, "Invalid");
  CHECK_STREQ_MAJOR(6, "Invalid");
}

void testGetMinorColor() {
  // Iteration of valid set
  for (int index = 0; index < MAX_COLORS; index++) {
    CHECK_STREQ_MINOR(index, minorColors[index]);
  }
  // Invalid set
  CHECK_STREQ_MINOR(5, "Invalid");
  CHECK_STREQ_MINOR(6, "Invalid");
}

void testGetPairNumber() {
  int expectedPairNumber = 0;
  int majorIndex = 0;
  int minorIndex = 0;
  PAIR_SWEEPER_START(majorIndex, minorIndex, MAX_COLORS, expectedPairNumber);
  EXPECT_EQ(getPairNumber(majorIndex, minorIndex), expectedPairNumber);
  PAIR_SWEEPER_END();
}

void testMapColorPair() {
  char buffer[50];
  int expectedPairNumber = 0;
  int majorIndex = 0;
  int minorIndex = 0;
  std::vector<std::string> expectedColorPair =
      loadExpectedPairs("expected_pairs.txt");

  if (expectedColorPair.empty()) {
    ADD_FAILURE()
        << "No expected pairs loaded (file missing or empty?), skip comparison";
    return;
  }
  if (expectedColorPair.size() < MAX_COLOR_PAIRS) {
    ADD_FAILURE() << "Insufficient expected pairs from file, skip comparison";
    return;
  }

  PAIR_SWEEPER_START(majorIndex, minorIndex, MAX_COLORS, expectedPairNumber);
  mapColorPair(buffer, sizeof(buffer), expectedPairNumber,
               majorColors[majorIndex], minorColors[minorIndex]);
  EXPECT_STREQ(buffer, expectedColorPair[expectedPairNumber].c_str());
  PAIR_SWEEPER_END();
}

void testMapColorPairWithHeader() {
  // Loading the full output from the file
  std::vector<std::string> expectedLines =
      loadExpectedPairs("expected_pairs.txt");

  if (expectedLines.size() < MAX_COLOR_PAIRS) {
    ADD_FAILURE() << "Insufficient expected pairs from file, skip comparison";
    return;
  }

  std::string expectedOutput;

  for (const auto &line : expectedLines) {
    expectedOutput += line + "\n";
  }

  // Capture printColorMap output
  std::stringstream buffer;
  std::streambuf *oldCoutBuf = std::cout.rdbuf(buffer.rdbuf()); // Redirect cout
  printColorMap();
  std::cout.rdbuf(oldCoutBuf); // Restore

  // Compare (trim trailing \n if needed)
  std::string actualOutput = buffer.str();
  if (!actualOutput.empty() && actualOutput.back() == '\n')
    actualOutput.pop_back(); // Optional trim

  EXPECT_EQ(actualOutput, expectedOutput);
}

void testPrintColorMap() { EXPECT_EQ(printColorMap(), 25); }

int testMisaligned() {
  std::cout << "\nPrint color map test\n";

  testGetMajorColor();
  testGetMinorColor();
  testGetPairNumber();
  testMapColorPair();
  testMapColorPairWithHeader();
  testPrintColorMap();

  std::cout << "All is well (maybe!)\n";
  return 0;
}
