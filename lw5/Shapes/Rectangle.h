#pragma once
#include "IShape.h"
#include "ShapePoint.h"

class CRectangle : public IShape
{
public:
	CRectangle(CShapePoint const & point1, CShapePoint const & point2);

	CBigInteger getSquare() const override;
	CBigInteger getPerimeter() const override;
	std::string getShapeType() const override;

	void accept(IVisitor & visitor) override { visitor.visit(*this); }

	static const std::string SHAPE_TYPE;

private:
	CShapePoint m_point1;
	CShapePoint m_point2;
};
