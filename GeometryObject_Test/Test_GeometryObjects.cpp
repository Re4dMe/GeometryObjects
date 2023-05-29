#include "pch.h"
#include "C:\Users\user\source\repos\GeometryTools\GeometryObjects.h"
#include <vector>
#include <random>
using namespace std;

TEST(Test_ObjectOperation_ShouldThrowExceptionWithDifferentDimension, TestName) {
    /* 
    *   Test to do operation with two objects with different dimension 
    *   Expect: The  function throw invalid_argument exception
    */
    GeometryObjects::Point<double> testPoint1(std::vector<int>{1, 2, 3});
    GeometryObjects::Point<double> testPoint2(std::vector<int>{1, 2});
    EXPECT_THROW({ GeometryObjects::Vector<double>(testPoint1, testPoint2); }, std::invalid_argument);

    GeometryObjects::Vector<double> testVector1(std::vector<int>{1, 2, 3});
    GeometryObjects::Vector<double> testVector2(std::vector<int>{1, 2});
    EXPECT_THROW({testVector1.dot(testVector2);}, std::invalid_argument);
}

TEST(Test_ObjectConstruction_ValuesShouldBeDesiredValues, TestName) {
    /* 
    *   Test to construct/modify objects and verify the values
    *   Input: A point (or Vector) with dimension 2, A point (or Vector) with dimension 3
    *   Expect: The  function throw invalid_argument exception
    */

    //  Point
    std::vector<double> testInitCoordinates({1, 2, 3});
    std::vector<double> testInitCoordinates2({4, 5, 6});
    GeometryObjects::Point<double> testPoint(testInitCoordinates);
    testInitCoordinates[0] = 3;
    EXPECT_EQ(testPoint.getCoordinates()[0], 1);
    testInitCoordinates[0] = 4;
    EXPECT_EQ(testPoint.getCoordinates()[0], 1);

    //  Vector
    std::vector<int> testInitComponents({ 1, 2, 3 });
    std::vector<int> testInitComponents2({ 4, 5, 6 });
    GeometryObjects::Vector<double> testVector(testInitComponents);
    GeometryObjects::Vector<double> testVector2(testInitComponents2);
    testInitComponents[0] = 3;
    EXPECT_EQ(testVector.getComponents()[0], 1);
    testVector = testVector2;
    EXPECT_EQ(testVector.getComponents()[0], 4);

    //Line
    testInitCoordinates =  vector<double>({1, 2, 3});
    testInitCoordinates2 = vector<double>({4, 5, 6});
    GeometryObjects::Point<double> testPointForLine(testInitCoordinates);
    GeometryObjects::Point<double> testPointForLine2(testInitCoordinates2);
    GeometryObjects::Line<double> testLine(testPointForLine, testPointForLine2);
    testInitCoordinates[0] = 3;
    EXPECT_EQ(testLine.getPoint().getCoordinates()[0], 1);
}

TEST(Test_SetAttributesOfLine_AttributesShouldBeDesiredValues, TestName) {
    /*
    *   Test to set components of the Vector by two new points
    *   Input: Two points with random values, a Vector
    *   Expect: The component i of Vector is given by Point_i - Point2_i
    */
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<double> unif(0.0, 1.0);

    std::vector<double> testInitCoordinates({ 1, 2, 3 });
    std::vector<double> testInitCoordinates2({ 4, 5, 6 });
    GeometryObjects::Point<double> testPoint(testInitCoordinates);
    GeometryObjects::Point<double> testPoint2(testInitCoordinates2);
    GeometryObjects::Vector<double> testVector(testPoint, testPoint2);

    testInitCoordinates = vector<double>({ unif(generator), unif(generator), unif(generator) });
    testInitCoordinates2 = vector<double>({ unif(generator), unif(generator), unif(generator) });
    testPoint = testInitCoordinates;
    testPoint2 = testInitCoordinates2;
    testVector.setComponentsByTwoPoints(testPoint, testPoint2);
    
    EXPECT_EQ(testVector.getComponents()[0], testInitCoordinates[0] - testInitCoordinates2[0]);
    EXPECT_EQ(testVector.getComponents()[1], testInitCoordinates[1] - testInitCoordinates2[1]);
    EXPECT_EQ(testVector.getComponents()[2], testInitCoordinates[2] - testInitCoordinates2[2]);
}