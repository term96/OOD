#include "stdafx.h"
#include "PerimeterVisitor.h"

CPerimeterVisitor::CPerimeterVisitor(std::ofstream & stream)
	: m_stream(stream)
{
}

void CPerimeterVisitor::visit(CCircle & circle)
{
	m_stream << "P: " << circle.getPerimeter().toString();
}

void CPerimeterVisitor::visit(CTriangle & triangle)
{
	m_stream << "P: " << triangle.getPerimeter().toString();
}

void CPerimeterVisitor::visit(CRectangle & rectangle)
{
	m_stream << "P: " << rectangle.getPerimeter().toString();
}
