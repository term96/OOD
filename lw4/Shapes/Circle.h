#pragma once
#include "IShape.h"
#include "ShapePoint.h"

class CCircle : public IShape
{
public:
	CCircle(CShapePoint const & center, CBigInteger radius);

	CBigInteger getSquare() const override;
	CBigInteger getPerimeter() const override;
	std::string getShapeType() const override;

	static const std::string SHAPE_TYPE;

private:
	CShapePoint m_center;
	CAdvancedBigInteger m_radius;
};
