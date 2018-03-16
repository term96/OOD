#include "stdafx.h"
#include "RectangleParser.h"

CRectangleParser & CRectangleParser::getInstance()
{
	static CRectangleParser instance;
	return instance;
}

IShape * CRectangleParser::parseShape(std::string const & inputLine) const
{
	std::smatch match;
	std::regex regex("[0-9]+");
	std::string matchSuffix = inputLine;

	int coords[4];
	int currentCoord = 0;

	while (std::regex_search(matchSuffix, match, regex))
	{
		int matchPosition = match.position(0);
		if (matchSuffix[matchPosition - 1] != 'P')
		{
			coords[currentCoord] = std::stoi(match.str(0));
			currentCoord++;
		}
		matchSuffix = match.suffix().str();
	}

	return new CRectangle(CShapePoint(coords[0], coords[1]), CShapePoint(coords[2], coords[3]));
}
