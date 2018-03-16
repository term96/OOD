#pragma once
#include "IShapeParser.h"
#include "Triangle.h"

class CTriangleParser : public IShapeParser
{
public:
	static CTriangleParser & getInstance();
	IShape * parseShape(std::string const & inputLine) const override;

	CTriangleParser(CTriangleParser const &) = delete;
	void operator=(CTriangleParser const &) = delete;
private:
	CTriangleParser() {}
};

