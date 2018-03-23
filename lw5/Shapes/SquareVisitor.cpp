#include "stdafx.h"
#include "SquareVisitor.h"

CSquareVisitor::CSquareVisitor(std::ofstream & stream)
	: m_stream(stream)
{
}

void CSquareVisitor::visit(CCircle & circle)
{
	m_stream << "P: " << circle.getSquare().toString();
}

void CSquareVisitor::visit(CTriangle & triangle)
{
	m_stream << "P: " << triangle.getSquare().toString();
}

void CSquareVisitor::visit(CRectangle & rectangle)
{
	m_stream << "P: " << rectangle.getSquare().toString();
}
