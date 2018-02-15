#pragma once
#include "IShape.h"
#include "ShapePoint.h"

class CTriangle : public IShape
{
public:
	CTriangle(CShapePoint const & point1, CShapePoint const & point2, CShapePoint const & point3);
	
	double getPerimeter() const override;
	double getSquare() const override;
	std::string getShapeType() const override;

	static const std::string SHAPE_TYPE;

private:
	double getDistance(CShapePoint const & point1, CShapePoint const & point2) const;
	
	CShapePoint m_point1;
	CShapePoint m_point2;
	CShapePoint m_point3;
};

