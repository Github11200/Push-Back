#include "../../include/testing/tests.h"
#include "../../include/utils/utils.h"
#include "../../include/types/vector.h"
#include "../../include/types/angle.h"
#include "../../include/types/pose.h"
#include "../../include/types/params.h"
#include "../../include/utils/bezier.h"

#include "../../include/pid/pid.h"

using namespace vex;
using namespace std;

// ====================
// VECTOR2D TESTS
// ====================

TEST(testVectorConstructors)
{
  Vector2D<double> defaultVec;
  ASSERT_EQUAL(defaultVec.x, 0);
  ASSERT_EQUAL(defaultVec.y, 0);

  Vector2D<double> paramVec(3.5, 4.2);
  ASSERT_EQUAL(paramVec.x, 3.5);
  ASSERT_EQUAL(paramVec.y, 4.2);

  return Testing::Result::PASS;
}

TEST(testVectorAddition)
{
  Vector2D<double> a(5, 3);
  Vector2D<double> b(2, 7);
  Vector2D<double> result = a + b;

  ASSERT_EQUAL(result.x, 7);
  ASSERT_EQUAL(result.y, 10);

  return Testing::Result::PASS;
}

TEST(testVectorSubtraction)
{
  Vector2D<double> a(10, 8);
  Vector2D<double> b(3, 2);
  Vector2D<double> result = a - b;

  ASSERT_EQUAL(result.x, 7);
  ASSERT_EQUAL(result.y, 6);

  return Testing::Result::PASS;
}

TEST(testVectorScalarMultiplication)
{
  Vector2D<double> a(4, 6);
  Vector2D<double> result = a * 2.5;

  ASSERT_EQUAL(result.x, 10);
  ASSERT_EQUAL(result.y, 15);

  return Testing::Result::PASS;
}

TEST(testVectorDotProduct)
{
  Vector2D<double> a(3, 4);
  Vector2D<double> b(2, 1);
  double result = a * b; // operator* for dot product

  ASSERT_EQUAL(result, 10); // 3*2 + 4*1 = 10

  return Testing::Result::PASS;
}

TEST(testVectorDotProductMethod)
{
  Vector2D<double> a(3, 4);
  Vector2D<double> b(2, 1);
  double result = a.dot(b);

  ASSERT_EQUAL(result, 10); // 3*2 + 4*1 = 10

  return Testing::Result::PASS;
}

TEST(testVectorScalarDivision)
{
  Vector2D<double> a(10, 20);
  Vector2D<double> result = a / 5;

  ASSERT_EQUAL(result.x, 2);
  ASSERT_EQUAL(result.y, 4);

  return Testing::Result::PASS;
}

TEST(testVectorEquality)
{
  Vector2D<double> a(5, 5);
  Vector2D<double> b(5, 5);
  Vector2D<double> c(5, 6);

  ASSERT_TRUE(a == b);
  ASSERT_FALSE(a == c);

  return Testing::Result::PASS;
}

TEST(testVectorInequality)
{
  Vector2D<double> a(5, 5);
  Vector2D<double> b(5, 6);
  Vector2D<double> c(5, 5);

  ASSERT_TRUE(a != b);
  ASSERT_FALSE(a != c);

  return Testing::Result::PASS;
}

TEST(testVectorMagnitude)
{
  Vector2D<double> a(3, 4);
  double magnitude = a.magnitude();

  ASSERT_EQUAL(magnitude, 5); // sqrt(3^2 + 4^2) = 5

  return Testing::Result::PASS;
}

TEST(testVectorDistanceTo)
{
  Vector2D<double> a(0, 0);
  Vector2D<double> b(3, 4);
  double distance = a.distanceTo(b);

  ASSERT_EQUAL(distance, 5); // sqrt((3-0)^2 + (4-0)^2) = 5

  return Testing::Result::PASS;
}

TEST(testVectorCrossProduct)
{
  Vector2D<double> a(5, 5);
  Vector2D<double> b(10, 10);
  double cross = a.crossProduct(b);

  ASSERT_EQUAL(cross, 0); // 5*10 - 10*5 = 0 (parallel vectors)

  Vector2D<double> c(1, 0);
  Vector2D<double> d(0, 1);
  double cross2 = c.crossProduct(d);

  ASSERT_EQUAL(cross2, 1); // 1*1 - 0*0 = 1

  return Testing::Result::PASS;
}

TEST(testVectorNormalize)
{
  Vector2D<double> a(3, 4);
  Vector2D<double> normalized = a.normalize();

  ASSERT_EQUAL(normalized.x, 0.6);         // 3/5
  ASSERT_EQUAL(normalized.y, 0.8);         // 4/5
  ASSERT_EQUAL(normalized.magnitude(), 1); // normalized vector should have magnitude 1

  return Testing::Result::PASS;
}

// ====================
// ANGLE TESTS
// ====================

TEST(testAngleConstructors)
{
  Angle<double> defaultAngle;
  ASSERT_EQUAL(defaultAngle.angle, 0);

  Angle<double> paramAngle(45);
  ASSERT_EQUAL(paramAngle.angle, 45);

  return Testing::Result::PASS;
}

TEST(testAngleAddition)
{
  Angle<double> a(30);
  Angle<double> b(45);
  Angle<double> result = a + b;

  ASSERT_EQUAL(result.angle, 75);

  return Testing::Result::PASS;
}

TEST(testAngleSubtraction)
{
  Angle<double> a(90);
  Angle<double> b(30);
  Angle<double> result = a - b;

  ASSERT_EQUAL(result.angle, 60);

  return Testing::Result::PASS;
}

TEST(testAngleConstrain0To360)
{
  Angle<double> a(450); // 450 degrees
  Angle<double> constrained = a.constrain0To360();
  ASSERT_EQUAL(constrained.angle, 90);

  Angle<double> b(-90); // -90 degrees
  Angle<double> constrained2 = b.constrain0To360();
  ASSERT_EQUAL(constrained2.angle, 270);

  Angle<double> c(0); // 0 degrees (edge case)
  Angle<double> constrained3 = c.constrain0To360();
  ASSERT_EQUAL(constrained3.angle, 0);

  Angle<double> d(359); // 359 degrees (edge case)
  Angle<double> constrained4 = d.constrain0To360();
  ASSERT_EQUAL(constrained4.angle, 359);

  return Testing::Result::PASS;
}

TEST(testAngleConstrainNegative180To180)
{
  Angle<double> a(270); // 270 degrees
  Angle<double> constrained = a.constrainNegative180To180();
  ASSERT_EQUAL(constrained.angle, -90);

  Angle<double> b(-270); // -270 degrees
  Angle<double> constrained2 = b.constrainNegative180To180();
  ASSERT_EQUAL(constrained2.angle, 90);

  Angle<double> c(180); // 180 degrees (edge case)
  Angle<double> constrained3 = c.constrainNegative180To180();
  ASSERT_EQUAL(constrained3.angle, -180);

  Angle<double> d(-180); // -180 degrees (edge case)
  Angle<double> constrained4 = d.constrainNegative180To180();
  ASSERT_EQUAL(constrained4.angle, -180);

  return Testing::Result::PASS;
}

TEST(testAngleConversions)
{
  Angle<double> radAngle(M_PI); // π radians
  Angle<double> degAngle = radAngle.toDeg();
  ASSERT_EQUAL(degAngle.angle, 180);

  Angle<double> deg180(180); // 180 degrees
  Angle<double> radConverted = deg180.toRad();
  ASSERT_EQUAL(radConverted.angle, M_PI);

  return Testing::Result::PASS;
}

TEST(testAngleTo)
{
  Angle<double> a(30);
  Angle<double> b(90);
  Angle<double> diff = a.angleTo(b);

  ASSERT_EQUAL(diff.angle, 60); // 90 - 30 = 60, constrained

  return Testing::Result::PASS;
}

// ====================
// POSE TESTS
// ====================

TEST(testPoseDefaultConstructor)
{
  Pose<double> defaultPose;
  ASSERT_EQUAL(defaultPose.position.x, 0);
  ASSERT_EQUAL(defaultPose.position.y, 0);
  ASSERT_EQUAL(defaultPose.orientation.angle, 0);

  return Testing::Result::PASS;
}

TEST(testPoseVectorConstructor)
{
  Vector2D<double> vec(5, 10);
  Pose<double> pose(vec);

  ASSERT_EQUAL(pose.position.x, 5);
  ASSERT_EQUAL(pose.position.y, 10);
  ASSERT_EQUAL(pose.orientation.angle, 0);

  return Testing::Result::PASS;
}

TEST(testPoseVectorOrientationConstructor)
{
  Vector2D<double> vec(3, 7);
  Pose<double> pose(vec, 45);

  ASSERT_EQUAL(pose.position.x, 3);
  ASSERT_EQUAL(pose.position.y, 7);
  ASSERT_EQUAL(pose.orientation.angle, 45);

  return Testing::Result::PASS;
}

TEST(testPoseXYConstructor)
{
  Pose<double> pose(2.5, 8.3);

  ASSERT_EQUAL(pose.position.x, 2.5);
  ASSERT_EQUAL(pose.position.y, 8.3);
  ASSERT_EQUAL(pose.orientation.angle, 0);

  return Testing::Result::PASS;
}

TEST(testPoseXYOrientationConstructor)
{
  Pose<double> pose(1.5, 2.5, 90);

  ASSERT_EQUAL(pose.position.x, 1.5);
  ASSERT_EQUAL(pose.position.y, 2.5);
  ASSERT_EQUAL(pose.orientation.angle, 90);

  return Testing::Result::PASS;
}

TEST(testPoseXYAngleConstructor)
{
  Angle<double> angle(135);
  Pose<double> pose(4, 6, angle);

  ASSERT_EQUAL(pose.position.x, 4);
  ASSERT_EQUAL(pose.position.y, 6);
  ASSERT_EQUAL(pose.orientation.angle, 135);

  return Testing::Result::PASS;
}

// ====================
// UTILITY FUNCTION TESTS
// ====================

TEST(testSgnPositive)
{
  ASSERT_EQUAL(sgn<int>(5), 1);
  ASSERT_EQUAL(sgn<double>(10.5), 1);
  ASSERT_EQUAL(sgn<double>(0.1), 1);

  return Testing::Result::PASS;
}

TEST(testSgnNegative)
{
  ASSERT_EQUAL(sgn<int>(-5), -1);
  ASSERT_EQUAL(sgn<double>(-10.5), -1);
  ASSERT_EQUAL(sgn<double>(-0.1), -1);

  return Testing::Result::PASS;
}

TEST(testSgnZero)
{
  ASSERT_EQUAL(sgn<int>(0), 0);
  ASSERT_EQUAL(sgn<double>(0.0), 0);

  return Testing::Result::PASS;
}

TEST(testClampInRange)
{
  // Value within range should remain unchanged
  ASSERT_EQUAL(clamp<int>(5, 0, 10), 5);
  ASSERT_EQUAL(clamp<double>(2.5, 0.0, 10.0), 2.5);
  ASSERT_EQUAL(clamp<int>(-3, -5, 5), -3);

  return Testing::Result::PASS;
}

TEST(testClampBelowMin)
{
  // Value below minimum should be clamped to minimum
  ASSERT_EQUAL(clamp<int>(-5, 0, 10), 0);
  ASSERT_EQUAL(clamp<double>(-2.5, 0.0, 10.0), 0.0);
  ASSERT_EQUAL(clamp<int>(-10, -5, 5), -5);

  return Testing::Result::PASS;
}

TEST(testClampAboveMax)
{
  // Value above maximum should be clamped to maximum
  ASSERT_EQUAL(clamp<int>(15, 0, 10), 10);
  ASSERT_EQUAL(clamp<double>(12.5, 0.0, 10.0), 10.0);
  ASSERT_EQUAL(clamp<int>(10, -5, 5), 5);

  return Testing::Result::PASS;
}

TEST(testClampMinPositiveValue)
{
  // Positive values below minimum should be clamped to minimum
  ASSERT_EQUAL(clampMin<int>(2, 5), 5);
  ASSERT_EQUAL(clampMin<double>(3.5, 4.0), 4.0);

  return Testing::Result::PASS;
}

TEST(testClampMinNegativeValue)
{
  // Negative values above -minimum should be clamped to -minimum
  ASSERT_EQUAL(clampMin<int>(-2, 5), -5);
  ASSERT_EQUAL(clampMin<double>(-3.5, 4.0), -4.0);

  return Testing::Result::PASS;
}

TEST(testClampMinValueAtThreshold)
{
  // Values at or beyond threshold should remain unchanged
  ASSERT_EQUAL(clampMin<int>(5, 5), 5);
  ASSERT_EQUAL(clampMin<int>(-5, 5), -5);
  ASSERT_EQUAL(clampMin<int>(10, 5), 10);
  ASSERT_EQUAL(clampMin<int>(-10, 5), -10);

  return Testing::Result::PASS;
}

TEST(testSlewWithinLimit)
{
  // Change within limit should reach target
  ASSERT_EQUAL(slew<int>(0, 5, 10), 5);
  ASSERT_EQUAL(slew<double>(10.0, 12.0, 5.0), 12.0);
  ASSERT_EQUAL(slew<int>(-5, -2, 5), -2);

  return Testing::Result::PASS;
}

TEST(testSlewExceedsPositiveLimit)
{
  // Change exceeding positive limit should be limited
  ASSERT_EQUAL(slew<int>(0, 15, 10), 10);
  ASSERT_EQUAL(slew<double>(5.0, 20.0, 8.0), 13.0);

  return Testing::Result::PASS;
}

TEST(testSlewExceedsNegativeLimit)
{
  // Change exceeding negative limit should be limited
  ASSERT_EQUAL(slew<int>(10, -5, 8), 2);
  ASSERT_EQUAL(slew<double>(20.0, 5.0, 10.0), 10.0);

  return Testing::Result::PASS;
}

TEST(testSlewZeroChange)
{
  // Zero change should remain at current value
  ASSERT_EQUAL(slew<int>(5, 5, 10), 5);
  ASSERT_EQUAL(slew<double>(-3.5, -3.5, 2.0), -3.5);

  return Testing::Result::PASS;
}

TEST(testToVoltagePositive)
{
  // Positive percentages
  ASSERT_EQUAL(toVoltage<int>(100), 12);
  ASSERT_EQUAL(toVoltage<int>(50), 6);
  ASSERT_EQUAL(toVoltage<int>(25), 3);

  return Testing::Result::PASS;
}

TEST(testToVoltageNegative)
{
  // Negative percentages
  ASSERT_EQUAL(toVoltage<int>(-100), -12);
  ASSERT_EQUAL(toVoltage<int>(-50), -6);
  ASSERT_EQUAL(toVoltage<int>(-25), -3);

  return Testing::Result::PASS;
}

TEST(testToVoltageZero)
{
  // Zero percentage
  ASSERT_EQUAL(toVoltage<int>(0), 0);

  return Testing::Result::PASS;
}

TEST(testToVoltageFloat)
{
  // Float percentages
  ASSERT_EQUAL(toVoltage<double>(33.33), 3.9996);
  ASSERT_EQUAL(toVoltage<double>(75.0), 9.0);

  return Testing::Result::PASS;
}

TEST(testGetSignedTangentArcCurvatureParallelPath)
{
  // Test with a straight path (no curvature)
  Pose<double> start(0, 0, 0); // Starting at origin, facing right (0 degrees)
  Vector2D<double> end(10, 0); // End point straight ahead

  double curvature = getSignedTangentArcCurvature(start, end);
  ASSERT_EQUAL(curvature, 0); // Should be zero curvature for straight line

  return Testing::Result::PASS;
}

TEST(testGetSignedTangentArcCurvatureLeftTurn)
{
  // Test with a left turn (negative curvature)
  Pose<double> start(0, 0, 0); // Starting at origin, facing right
  Vector2D<double> end(0, 10); // End point to the left

  double curvature = getSignedTangentArcCurvature(start, end);
  ASSERT_TRUE(curvature < 0); // Should be negative for left turn

  return Testing::Result::PASS;
}

TEST(testGetSignedTangentArcCurvatureRightTurn)
{
  // Test with a right turn (positive curvature)
  Pose<double> start(0, 0, 0);  // Starting at origin, facing right
  Vector2D<double> end(0, -10); // End point to the right

  double curvature = getSignedTangentArcCurvature(start, end);
  ASSERT_TRUE(curvature > 0); // Should be positive for right turn

  return Testing::Result::PASS;
}

// ====================
// PID TESTS
// ====================

TEST(testPIDBasicResponse)
{
  PID pid(10, DriveParams{1.0, 0.1, 0.01, 1000, 100, 0.5, 50});
  double output = pid.compute(10);
  ASSERT_TRUE(output != 0);
  return Testing::Result::PASS;
}

TEST(testPIDIntegralResetOnSignChange)
{
  PID pid(10, DriveParams{1.0, 0.5, 0.0, 1000, 100, 0.5, 50});
  pid.compute(10);                // positive error
  double out1 = pid.compute(-10); // sign change, should reset integral
  ASSERT_TRUE(out1 < 0);
  return Testing::Result::PASS;
}

TEST(testPIDAccumulatedErrorLimit)
{
  PID pid(10, DriveParams{1.0, 0.5, 0.0, 5, 100, 0.5, 50});
  pid.compute(10);
  double out1 = pid.compute(10);
  double out2 = pid.compute(2);
  ASSERT_TRUE(out2 != out1);
  return Testing::Result::PASS;
}

TEST(testPIDReset)
{
  PID pid(10, DriveParams{1.0, 0.5, 0.0, 1000, 100, 0.5, 50});
  pid.compute(10);
  pid.resetPID();
  double out = pid.compute(0);
  ASSERT_EQUAL(out, 0);
  return Testing::Result::PASS;
}

TEST(testPIDIsSettled)
{
  PID pid(10, DriveParams{1.0, 0.5, 0.0, 1000, 20, 0.5, 30});
  for (int i = 0; i < 4; ++i)
  {
    pid.compute(0.1);
  }
  ASSERT_TRUE(pid.isSettled());
  return Testing::Result::PASS;
}

// ====================
// LERP FUNCTION TESTS
// ====================

TEST(testLerpStartPoint)
{
  // Test lerp at t=0 (should return start point)
  Vector2D<double> start(0, 0);
  Vector2D<double> end(10, 10);
  Vector2D<double> result = lerp(start, end, 0.0);

  ASSERT_EQUAL(result.x, 0);
  ASSERT_EQUAL(result.y, 0);

  return Testing::Result::PASS;
}

TEST(testLerpEndPoint)
{
  // Test lerp at t=1 (should return end point)
  Vector2D<double> start(2, 3);
  Vector2D<double> end(8, 9);
  Vector2D<double> result = lerp(start, end, 1.0);

  ASSERT_EQUAL(result.x, 8);
  ASSERT_EQUAL(result.y, 9);

  return Testing::Result::PASS;
}

TEST(testLerpMidpoint)
{
  // Test lerp at t=0.5 (should return midpoint)
  Vector2D<double> start(0, 0);
  Vector2D<double> end(10, 20);
  Vector2D<double> result = lerp(start, end, 0.5);

  ASSERT_EQUAL(result.x, 5);
  ASSERT_EQUAL(result.y, 10);

  return Testing::Result::PASS;
}

TEST(testLerpQuarterPoint)
{
  // Test lerp at t=0.25
  Vector2D<double> start(0, 0);
  Vector2D<double> end(8, 12);
  Vector2D<double> result = lerp(start, end, 0.25);

  ASSERT_EQUAL(result.x, 2);
  ASSERT_EQUAL(result.y, 3);

  return Testing::Result::PASS;
}

TEST(testLerpThreeQuarterPoint)
{
  // Test lerp at t=0.75
  Vector2D<double> start(0, 0);
  Vector2D<double> end(8, 12);
  Vector2D<double> result = lerp(start, end, 0.75);

  ASSERT_EQUAL(result.x, 6);
  ASSERT_EQUAL(result.y, 9);

  return Testing::Result::PASS;
}

TEST(testLerpNegativeCoordinates)
{
  // Test lerp with negative coordinates
  Vector2D<double> start(-5, -10);
  Vector2D<double> end(5, 10);
  Vector2D<double> result = lerp(start, end, 0.5);

  ASSERT_EQUAL(result.x, 0);
  ASSERT_EQUAL(result.y, 0);

  return Testing::Result::PASS;
}

TEST(testLerpExtrapolation)
{
  // Test lerp with t > 1 (extrapolation)
  Vector2D<double> start(0, 0);
  Vector2D<double> end(5, 5);
  Vector2D<double> result = lerp(start, end, 2.0);

  ASSERT_EQUAL(result.x, 10);
  ASSERT_EQUAL(result.y, 10);

  return Testing::Result::PASS;
}

TEST(testLerpNegativeExtrapolation)
{
  // Test lerp with t < 0 (negative extrapolation)
  Vector2D<double> start(5, 5);
  Vector2D<double> end(10, 10);
  Vector2D<double> result = lerp(start, end, -1.0);

  ASSERT_EQUAL(result.x, 0);
  ASSERT_EQUAL(result.y, 0);

  return Testing::Result::PASS;
}

TEST(testLerpIdenticalPoints)
{
  // Test lerp with identical start and end points
  Vector2D<double> start(7, 3);
  Vector2D<double> end(7, 3);
  Vector2D<double> result = lerp(start, end, 0.7);

  ASSERT_EQUAL(result.x, 7);
  ASSERT_EQUAL(result.y, 3);

  return Testing::Result::PASS;
}

TEST(testLerpFloatPrecision)
{
  // Test lerp with floating point values
  Vector2D<double> start(1.5, 2.5);
  Vector2D<double> end(3.5, 6.5);
  Vector2D<double> result = lerp(start, end, 0.5);

  ASSERT_EQUAL(result.x, 2.5);
  ASSERT_EQUAL(result.y, 4.5);

  return Testing::Result::PASS;
}

// ====================
// SIGMOID TESTS
// ====================

TEST(testSigmoidDefaultAtZero)
{
  // With default coefficients, sigmoid(0) should be exactly 0.5
  ASSERT_EQUAL(sigmoid(0.0), 0.5);
  return Testing::Result::PASS;
}

TEST(testSigmoidDefaultMonotonicLimits)
{
  // With definition 1/(1+exp(x)), large x -> 0, large -x -> 1
  ASSERT_TRUE(sigmoid(10.0) < 0.001);
  ASSERT_TRUE(sigmoid(-10.0) > 0.999);
  return Testing::Result::PASS;
}

TEST(testSigmoidWithFractionalCoefficient)
{
  // fractionalCoefficient scales output linearly
  ASSERT_EQUAL(sigmoid(0.0, 2.0), 1.0); // 2 * 0.5
  ASSERT_EQUAL(sigmoid(0.0, 4.0), 2.0); // 4 * 0.5
  return Testing::Result::PASS;
}

TEST(testSigmoidWithConstantOffset)
{
  // constant shifts output downward
  ASSERT_EQUAL(sigmoid(0.0, 1.0, 1.0, 0.5), 0.0); // 0.5 - 0.5
  return Testing::Result::PASS;
}

TEST(testSigmoidWithZeroExponentialCoefficient)
{
  // exponentialCoefficient = 0 forces exp(0) -> 1, so output is 0.5 (then scaled/offset)
  ASSERT_EQUAL(sigmoid(3.14, 1.0, 0.0, 0.0), 0.5);
  ASSERT_EQUAL(sigmoid(-7.0, 2.0, 0.0, 0.5), 0.5); // 2*0.5 - 0.5 = 0.5
  return Testing::Result::PASS;
}

TEST(testSigmoidWithNegativeExponentialCoefficient)
{
  // Negative exponentialCoefficient flips the curve to increasing; check a plausible range
  double v = sigmoid(1.0, 1.0, -2.0, 0.0); // ~ 1/(1+exp(-2)) ≈ 0.8808
  ASSERT_TRUE(v > 0.85);
  ASSERT_TRUE(v < 0.90);
  return Testing::Result::PASS;
}

TEST(testSigmoidLargeMagnitudeEdges)
{
  // Very large magnitudes should saturate due to exp overflow/underflow
  ASSERT_EQUAL(sigmoid(1e6), 0.0);
  ASSERT_EQUAL(sigmoid(-1e6), 1.0);
  return Testing::Result::PASS;
}

// ====================
// BEZIER TESTS
// ====================

TEST(testBezierEndpoints)
{
  Vector2D<double> p0(0, 0);
  Vector2D<double> p1(0, 1);
  Vector2D<double> p2(1, 1);
  Vector2D<double> p3(1, 0);

  Vector2D<double> pts[4] = {p0, p1, p2, p3};
  CubicBezier bez(pts);

  Vector2D<double> start = bez.point(0.0);
  Vector2D<double> end = bez.point(1.0);

  ASSERT_EQUAL(start.x, p0.x);
  ASSERT_EQUAL(start.y, p0.y);
  ASSERT_EQUAL(end.x, p3.x);
  ASSERT_EQUAL(end.y, p3.y);

  return Testing::Result::PASS;
}

TEST(testBezierMidpoint)
{
  Vector2D<double> p0(0, 0);
  Vector2D<double> p1(0, 1);
  Vector2D<double> p2(1, 1);
  Vector2D<double> p3(1, 0);

  Vector2D<double> pts[4] = {p0, p1, p2, p3};
  CubicBezier bez(pts);

  Vector2D<double> mid = bez.point(0.5);

  ASSERT_EQUAL(mid.x, 0.5);
  ASSERT_EQUAL(mid.y, 0.75);

  return Testing::Result::PASS;
}

TEST(testBezierFirstDerivativeEndpoints)
{
  Vector2D<double> p0(0, 0);
  Vector2D<double> p1(0, 1);
  Vector2D<double> p2(1, 1);
  Vector2D<double> p3(1, 0);

  Vector2D<double> pts[4] = {p0, p1, p2, p3};
  CubicBezier bez(pts);

  Vector2D<double> d0 = bez.firstDerivative(0.0);
  Vector2D<double> d1 = bez.firstDerivative(1.0);

  // P'(0) = 3*(P1 - P0)
  ASSERT_EQUAL(d0.x, (p1.x - p0.x) * 3.0);
  ASSERT_EQUAL(d0.y, (p1.y - p0.y) * 3.0);

  // P'(1) = 3*(P3 - P2)
  ASSERT_EQUAL(d1.x, (p3.x - p2.x) * 3.0);
  ASSERT_EQUAL(d1.y, (p3.y - p2.y) * 3.0);

  return Testing::Result::PASS;
}

TEST(testBezierSecondDerivativeAtZero)
{
  Vector2D<double> p0(0, 0);
  Vector2D<double> p1(0, 1);
  Vector2D<double> p2(1, 1);
  Vector2D<double> p3(1, 0);

  Vector2D<double> pts[4] = {p0, p1, p2, p3};
  CubicBezier bez(pts);

  Vector2D<double> s0 = bez.secondDerivative(0.0);

  // P''(0) = 6 * (P2 - 2*P1 + P0)
  ASSERT_EQUAL(s0.x, (p2.x - 2.0 * p1.x + p0.x) * 6.0);
  ASSERT_EQUAL(s0.y, (p2.y - 2.0 * p1.y + p0.y) * 6.0);

  return Testing::Result::PASS;
}