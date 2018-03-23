#pragma once

class IVisitor
{
public:
	virtual void visit(class CCircle & circle) = 0;
	virtual void visit(class CTriangle & circle) = 0;
	virtual void visit(class CRectangle & circle) = 0;
	virtual ~IVisitor() = default;
};

