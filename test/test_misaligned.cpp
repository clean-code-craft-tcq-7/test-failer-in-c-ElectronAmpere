#include "../src/misaligned.h"
#include "gtest/gtest.h"
#include <cstdio> // For tmpfile, fflush, rewind, fgets
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Defines
#define MAX_COLORS (5)
#define HEADER_COLORS (1)
#define MAX_COLOR_PAIRS (MAX_COLORS * MAX_COLORS + HEADER_COLORS)
#define TEST_INPUT_FILE (TEST_SOURCE_DIR "/test/expected_pairs.txt")

// Macros
#define CHECK_STREQ_MAJOR(index, value)                                        \
  EXPECT_STREQ(getMajorColor(index), value)
#define CHECK_STREQ_MINOR(index, value)                                        \
  EXPECT_STREQ(getMinorColor(index), value)
#define PAIR_SWEEPER_START(majorIndex, minorIndex, expectedPairNumber)         \
  for (majorIndex = 0; majorIndex < MAX_COLORS; majorIndex++) {                \
    for (minorIndex = 0; minorIndex < MAX_COLORS; minorIndex++) {              \
      expectedPairNumber = 1 + (majorIndex * MAX_COLORS) + minorIndex;
#define PAIR_SWEEPER_END()                                                     \
  }                                                                            \
  }

static const char *majorColors[MAX_COLORS] = {"White", "Red", "Black", "Yellow",
                                              "Violet"};
static const char *minorColors[MAX_COLORS] = {"Blue", "Orange", "Green",
                                              "Brown", "Slate"};

// To load the expected color pairs from a file
std::vector<std::string> loadExpectedLines(const std::string &filename) {
  std::vector<std::string> expectedLines;
  std::ifstream file(filename);
  if (!file.is_open()) {
    ADD_FAILURE() << "Failed to open file: " << filename;
    return expectedLines;
  }
  std::string line;
  while (std::getline(file, line)) {
    // Trim trailing whitespace/CRLF
    size_t end = line.find_last_not_of(" \t\r\n");
    if (end != std::string::npos) {
      line = line.substr(0, end + 1);
    }
    if (!line.empty()) { // Skip empty lines for robustness
      expectedLines.push_back(line);
    }
  }
  file.close();
  if (expectedLines.size() != MAX_COLOR_PAIRS) {
    ADD_FAILURE() << "Expected " << MAX_COLOR_PAIRS
                  << " lines (header + pairs), loaded " << expectedLines.size();
  }
  return expectedLines;
}

void testGetMajorColor() {
  // Iteration of valid set
  for (int index = 0; index < MAX_COLORS; index++) {
    CHECK_STREQ_MAJOR(index, majorColors[index]);
  }
  // Invalid set (comprehensive: negative, max+1)
  CHECK_STREQ_MAJOR(-1, "Unknown");
  CHECK_STREQ_MAJOR(5, "Invalid");
  CHECK_STREQ_MAJOR(6, "Invalid");
}

void testGetMinorColor() {
  // Iteration of valid set
  for (int index = 0; index < MAX_COLORS; index++) {
    CHECK_STREQ_MINOR(index, minorColors[index]);
  }
  // Invalid set (comprehensive)
  CHECK_STREQ_MINOR(-1, "Unknown");
  CHECK_STREQ_MINOR(5, "Invalid");
  CHECK_STREQ_MINOR(6, "Invalid");
}

void testGetPairNumber() {
  int expectedPairNumber = 0;
  int majorIndex = 0;
  int minorIndex = 0;
  PAIR_SWEEPER_START(majorIndex, minorIndex, expectedPairNumber);
  EXPECT_EQ(getPairNumber(majorIndex, minorIndex), expectedPairNumber);
  PAIR_SWEEPER_END();
  // Comprehensive edges
  EXPECT_EQ(getPairNumber(-1, 0), -1); // Invalid
  EXPECT_EQ(getPairNumber(0, -1), -1);
  // Overflow? But per code, no clamp, so test actual
  EXPECT_EQ(getPairNumber(5, 0), getPairNumber(4, 4) + 1);
}

void testMapColorPair() {
  std::vector<std::string> expectedLines = loadExpectedLines(TEST_INPUT_FILE);
  if (expectedLines.size() < MAX_COLOR_PAIRS) {
    ADD_FAILURE() << "Insufficient expected lines; skipping comparisons";
    return;
  }
  char buffer[COLOR_MAP_LENGTH_MAX];
  int expectedPairNumber = 0;
  int majorIndex = 0;
  int minorIndex = 0;
  PAIR_SWEEPER_START(majorIndex, minorIndex, expectedPairNumber);
  mapColorPair(buffer, sizeof(buffer), expectedPairNumber,
               majorColors[majorIndex], minorColors[minorIndex]);
  EXPECT_STREQ(buffer, expectedLines[expectedPairNumber].c_str());
  PAIR_SWEEPER_END();
  // Comprehensive: Header format test
  mapColorHeader(buffer, sizeof(buffer));
  EXPECT_STREQ(buffer, expectedLines[0].c_str());
  char smallBuffer[COLOR_MAP_LENGTH_MIN];
  mapColorPair(smallBuffer, sizeof(smallBuffer), 1, "White", "Blue");
  // Truncated, fails if not handled
  EXPECT_STRNE(smallBuffer, " 1 | White | Blue");
}

void testMapColorPairWithHeader() {
  std::vector<std::string> expectedLines = loadExpectedLines(TEST_INPUT_FILE);
  if (expectedLines.size() < MAX_COLOR_PAIRS) {
    ADD_FAILURE() << "Insufficient expected lines; skipping";
    return;
  }
  std::string expectedOutput;
  for (const auto &line : expectedLines) {
    expectedOutput += line + "\n";
  }
  // Trim trailing \n from expected to match actual
  if (!expectedOutput.empty() && expectedOutput.back() == '\n') {
    expectedOutput.pop_back();
  }

  // Capture printf output using temporary file
  FILE *tempFile = tmpfile();
  if (!tempFile) {
    ADD_FAILURE() << "Failed to create temporary file for output capture";
    return;
  }

  // Redirect stdout to temp file
  FILE *oldStdout = stdout;
  stdout = tempFile;

  printColorMap();

  // Flush to ensure all output is written
  fflush(stdout);

  // Restore stdout
  stdout = oldStdout;

  // Read from temp file
  rewind(tempFile);
  std::string actualOutput;
  char buf[1024];
  while (fgets(buf, sizeof(buf), tempFile)) {
    // Trim trailing \n if needed
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n')
      buf[len - 1] = '\0';
    actualOutput += std::string(buf) + "\n";
  }
  fclose(tempFile);

  // Trim trailing \n from actual to match expected
  if (!actualOutput.empty() && actualOutput.back() == '\n')
    actualOutput.pop_back();

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
