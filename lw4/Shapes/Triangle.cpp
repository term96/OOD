#include "stdafx.h"
#include "Triangle.h"

const std::string CTriangle::SHAPE_TYPE = "TRIANGLE";

CTriangle::CTriangle(CShapePoint const & point1, CShapePoint const & point2, CShapePoint const & point3)
	: m_point1(point1),
	m_point2(point2),
	m_point3(point3)
{
}

double CTriangle::getPerimeter() const
{
	double side1 = getDistance(m_point1, m_point2);
	double side2 = getDistance(m_point2, m_point3);
	double side3 = getDistance(m_point3, m_point1);

	return side1 + side2 + side3;
}

double CTriangle::getSquare() const
{
	double side1 = getDistance(m_point1, m_point2);
	double side2 = getDistance(m_point2, m_point3);
	double side3 = getDistance(m_point3, m_point1);
	double halfPerimeter = getPerimeter() / 2;

	return sqrt(halfPerimeter * (halfPerimeter - side1) * (halfPerimeter - side2) * (halfPerimeter - side3));
}

std::string CTriangle::getShapeType() const
{
	return SHAPE_TYPE;
}

double CTriangle::getDistance(CShapePoint const & point1, CShapePoint const & point2) const
{
	double x = point1.getX() - point2.getX();
	double y = point1.getY() - point2.getY();
	return sqrt(x * x + y * y);
}
