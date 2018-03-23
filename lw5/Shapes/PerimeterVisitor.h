#pragma once

#include "IVisitor.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"

class CPerimeterVisitor :
	public IVisitor
{
public:
	CPerimeterVisitor(std::ofstream & stream);
	void visit(CCircle & circle) override;
	void visit(CTriangle & triangle) override;
	void visit(CRectangle & rectangle) override;

private:
	std::ofstream & m_stream;
};

