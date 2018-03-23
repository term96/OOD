#include "stdafx.h"
#include "Rectangle.h"

const std::string CRectangle::SHAPE_TYPE = "RECTANGLE";

CRectangle::CRectangle(CShapePoint const & point1, CShapePoint const & point2)
	: m_point1(point1),
	m_point2(point2)
{
}

CBigInteger CRectangle::getSquare() const
{
	CBigInteger width = CBigInteger::getPositive(m_point1.getX() - m_point2.getX());
	CBigInteger height = CBigInteger::getPositive(m_point1.getY() - m_point2.getY());
	return width * height;
}

CBigInteger CRectangle::getPerimeter() const
{
	CBigInteger width = CBigInteger::getPositive(m_point1.getX() - m_point2.getX());
	CBigInteger height = CBigInteger::getPositive(m_point1.getY() - m_point2.getY());
	return (width + height) * 2;
}

std::string CRectangle::getShapeType() const
{
	return SHAPE_TYPE;
}
