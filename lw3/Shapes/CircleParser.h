#pragma once
#include "IShapeParser.h"
#include "Circle.h"

class CCircleParser : public IShapeParser
{
public:
	IShape * parseShape(std::string const & inputLine) const override;
};
