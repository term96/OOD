#pragma once
#include "AdvancedBigInteger.h"
#include "IElement.h"

class IShape : public IElement
{
public:
	virtual CBigInteger getSquare() const = 0;
	virtual CBigInteger getPerimeter() const = 0;
	virtual std::string getShapeType() const = 0;
	virtual ~IShape() = default;
};

