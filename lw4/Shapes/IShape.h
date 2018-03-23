#pragma once
#include "AdvancedBigInteger.h"

class IShape
{
public:
	virtual CBigInteger getSquare() const = 0;
	virtual CBigInteger getPerimeter() const = 0;
	virtual std::string getShapeType() const = 0;
	virtual ~IShape() = default;
};

