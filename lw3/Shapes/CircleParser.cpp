#include "stdafx.h"
#include "CircleParser.h"

CCircleParser & CCircleParser::getInstance()
{
	static CCircleParser instance;
	return instance;
}

IShape * CCircleParser::parseShape(std::string const & inputLine) const
{
	std::smatch match;
	std::regex regex("[0-9]+");
	std::string matchSuffix = inputLine;

	int params[3];
	int currentParam = 0;

	while (std::regex_search(matchSuffix, match, regex))
	{
		params[currentParam] = std::stoi(match.str(0));
		currentParam++;
		matchSuffix = match.suffix().str();
	}

	return new CCircle(CShapePoint(params[0], params[1]), params[2]);
}
