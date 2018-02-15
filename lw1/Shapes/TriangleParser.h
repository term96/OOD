#pragma once
#include "IShapeParser.h"
#include "Triangle.h"

class CTriangleParser : public IShapeParser
{
public:
	IShape * parseShape(std::string const & inputLine) const override;
};

