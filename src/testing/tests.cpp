#include "../../include/testing/tests.h"
#include "../../include/utils.h"
#include "../../include/types/vector.h"
#include "../../include/types/angle.h"
#include "../../include/types/pose.h"
#include "../../include/types/params.h"

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