#pragma once
#include "IShape.h"
#include "ShapePoint.h"

class CRectangle : public IShape
{
public:
	CRectangle(CShapePoint const & point1, CShapePoint const & point2);

	double getSquare() const override;
	double getPerimeter() const override;
	std::string getShapeType() const override;

	static const std::string SHAPE_TYPE;

private:
	CShapePoint m_point1;
	CShapePoint m_point2;
};
