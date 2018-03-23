#include "stdafx.h"
#include "Triangle.h"

const std::string CTriangle::SHAPE_TYPE = "TRIANGLE";

CTriangle::CTriangle(CShapePoint const & point1, CShapePoint const & point2, CShapePoint const & point3)
	: m_point1(point1),
	m_point2(point2),
	m_point3(point3)
{
}

CBigInteger CTriangle::getPerimeter() const
{
	CBigInteger side1 = getDistance(m_point1, m_point2);
	CBigInteger side2 = getDistance(m_point2, m_point3);
	CBigInteger side3 = getDistance(m_point3, m_point1);

	return side1 + side2 + side3;
}

CBigInteger CTriangle::getSquare() const
{
	CBigInteger side1 = getDistance(m_point1, m_point2);
	CBigInteger side2 = getDistance(m_point2, m_point3);
	CBigInteger side3 = getDistance(m_point3, m_point1);
	CBigInteger halfPerimeter = getPerimeter() / CBigInteger(2);

	return CAdvancedBigInteger::sqrt(halfPerimeter * (halfPerimeter - side1) * (halfPerimeter - side2) * (halfPerimeter - side3));
}

std::string CTriangle::getShapeType() const
{
	return SHAPE_TYPE;
}

CBigInteger CTriangle::getDistance(CShapePoint const & point1, CShapePoint const & point2) const
{
	CBigInteger x = point1.getX() - point2.getX();
	CBigInteger y = point1.getY() - point2.getY();

	return CAdvancedBigInteger::sqrt(x * x + y * y);
}
