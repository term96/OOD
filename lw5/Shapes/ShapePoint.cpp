#include "stdafx.h"
#include "ShapePoint.h"

CShapePoint::CShapePoint(CBigInteger x, CBigInteger y)
	: m_x(x),
	m_y(y)
{
}

CShapePoint::CShapePoint(CShapePoint const & point)
	: m_x(point.getX()),
	m_y(point.getY())
{
}

CBigInteger CShapePoint::getX() const
{
	return m_x;
}

CBigInteger CShapePoint::getY() const
{
	return m_y;
}

void CShapePoint::setX(CBigInteger x)
{
	m_x = x;
}

void CShapePoint::setY(CBigInteger y)
{
	m_y = y;
}
