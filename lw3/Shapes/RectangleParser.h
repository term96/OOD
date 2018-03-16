#pragma once
#include "IShapeParser.h"
#include "Rectangle.h"

class CRectangleParser : public IShapeParser
{
public:
	IShape * parseShape(std::string const & inputLine) const override;
};
