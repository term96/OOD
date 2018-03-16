#include "stdafx.h"
#include "Circle.h"

const std::string CCircle::SHAPE_TYPE = "CIRCLE";

CCircle::CCircle(CShapePoint const & center, int radius)
	: m_center(center),
	m_radius(radius)
{
}

double CCircle::getSquare() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::getPerimeter() const
{
	return 2 * M_PI * m_radius;
}

std::string CCircle::getShapeType() const
{
	return SHAPE_TYPE;
}
