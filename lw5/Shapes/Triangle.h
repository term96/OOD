#pragma once
#include "IShape.h"
#include "ShapePoint.h"

class CTriangle : public IShape
{
public:
	CTriangle(CShapePoint const & point1, CShapePoint const & point2, CShapePoint const & point3);
	
	CBigInteger getPerimeter() const override;
	CBigInteger getSquare() const override;
	std::string getShapeType() const override;

	void accept(IVisitor & visitor) override { visitor.visit(*this); }

	static const std::string SHAPE_TYPE;

private:
	CBigInteger getDistance(CShapePoint const & point1, CShapePoint const & point2) const;

	
	CShapePoint m_point1;
	CShapePoint m_point2;
	CShapePoint m_point3;
};

