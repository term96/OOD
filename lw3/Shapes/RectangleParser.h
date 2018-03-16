#pragma once
#include "IShapeParser.h"
#include "Rectangle.h"

class CRectangleParser : public IShapeParser
{
public:
	static CRectangleParser & getInstance();
	IShape * parseShape(std::string const & inputLine) const override;

	CRectangleParser(CRectangleParser const &) = delete;
	void operator=(CRectangleParser const &) = delete;
private:
	CRectangleParser() {}
};
