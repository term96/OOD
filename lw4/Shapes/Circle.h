#pragma once
#include "IShape.h"
#include "ShapePoint.h"

class CCircle : public IShape
{
public:
	CCircle(CShapePoint const & center, int radius);

	double getSquare() const override;
	double getPerimeter() const override;
	std::string getShapeType() const override;

	static const std::string SHAPE_TYPE;

private:
	CShapePoint m_center;
	int m_radius;
};
