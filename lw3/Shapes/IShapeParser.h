#pragma once
#include "IShape.h"

class IShapeParser
{
public:
	virtual IShape * parseShape(std::string const & inputLine) const = 0;
	virtual ~IShapeParser() = default;
};

