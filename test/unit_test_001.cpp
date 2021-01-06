//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-06
// PURPOSE: unit tests for the PulsePattern library
//          https://github.com/RobTillaart/PulsePattern
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual);               // a == b
// assertNotEqual(unwanted, actual);            // a != b
// assertComparativeEquivalent(expected, actual);    // abs(a - b) == 0 or (!(a > b) && !(a < b))
// assertComparativeNotEquivalent(unwanted, actual); // abs(a - b) > 0  or ((a > b) || (a < b))
// assertLess(upperBound, actual);              // a < b
// assertMore(lowerBound, actual);              // a > b
// assertLessOrEqual(upperBound, actual);       // a <= b
// assertMoreOrEqual(lowerBound, actual);       // a >= b
// assertTrue(actual);
// assertFalse(actual);
// assertNull(actual);

// // special cases for floats
// assertEqualFloat(expected, actual, epsilon);    // fabs(a - b) <= epsilon
// assertNotEqualFloat(unwanted, actual, epsilon); // fabs(a - b) >= epsilon
// assertInfinity(actual);                         // isinf(a)
// assertNotInfinity(actual);                      // !isinf(a)
// assertNAN(arg);                                 // isnan(a)
// assertNotNAN(arg);                              // !isnan(a)

#include <ArduinoUnitTests.h>

#define assertEqualFloat(arg1, arg2, arg3)  assertOp("assertEqualFloat", "expected", fabs(arg1 - arg2), compareLessOrEqual, "<=", "actual", arg3)
// #define assertEqualINF(arg)  assertOp("assertEqualINF", "expected", INFINITY, compareEqual, "==", "actual", arg)
// #define assertEqualNAN(arg)  assertOp("assertEqualNAN", "expected", true, compareEqual, "==", "actual", isnan(arg))


#include "Arduino.h"
#include "PulsePattern.h"

uint16_t pattern[] =
{
  1500, 1500, 1400, 1400, 1300, 1300, 1200, 1200, 1100, 1100,
  1000, 1000, 900, 900, 800, 800, 700, 700, 600, 600,
  500, 500, 400, 400, 300, 300, 200, 200, 100, 100
};
uint8_t patternSize = 30;
uint8_t startLevel = LOW;


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  fprintf(stderr, "VERSION: %s\n", PULSEPATTERN_LIB_VERSION);

  PPGenerator.init(13, pattern, patternSize, startLevel, PRESCALE_1024);

  assertFalse(PPGenerator.isRunning());
  
  PPGenerator.start();
  assertTrue(PPGenerator.isRunning());
  
  PPGenerator.stop();
  assertFalse(PPGenerator.isRunning());
  
  PPGenerator.cont();
  assertTrue(PPGenerator.isRunning());
  
  PPGenerator.stop();
  assertFalse(PPGenerator.isRunning());

}


unittest(test_setFactor)
{
  fprintf(stderr, "VERSION: %s\n", PULSEPATTERN_LIB_VERSION);

  PPGenerator.init(13, pattern, patternSize, startLevel, PRESCALE_1024);

  PPGenerator.setFactor(42.42);
  assertEqualFloat(42.42, PPGenerator.getFactor(), 0.0001);
  
  PPGenerator.setFactor(0);
  assertEqualFloat(0, PPGenerator.getFactor(), 0.0001);
  
  PPGenerator.setFactor(100);
  assertEqualFloat(100, PPGenerator.getFactor(), 0.0001);
}


unittest_main()

// --------
