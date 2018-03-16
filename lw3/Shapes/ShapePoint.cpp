#include "stdafx.h"
#include "ShapePoint.h"

CShapePoint::CShapePoint(int x, int y)
	: m_x(x),
	m_y(y)
{
}

CShapePoint::CShapePoint(CShapePoint const & point)
	: m_x(point.getX()),
	m_y(point.getY())
{
}

int CShapePoint::getX() const
{
	return m_x;
}

int CShapePoint::getY() const
{
	return m_y;
}

void CShapePoint::setX(int x)
{
	m_x = x;
}

void CShapePoint::setY(int y)
{
	m_y = y;
}
