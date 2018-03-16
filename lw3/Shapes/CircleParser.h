#pragma once
#include "IShapeParser.h"
#include "Circle.h"

class CCircleParser : public IShapeParser
{
public:
	static CCircleParser & getInstance();
	IShape * parseShape(std::string const & inputLine) const override;

	CCircleParser(CCircleParser const &) = delete;
	void operator=(CCircleParser const &) = delete;
private:
	CCircleParser() {}
};
