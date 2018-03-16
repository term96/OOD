#include "stdafx.h"
#include "IShape.h"
#include "IShapeParser.h"
#include "Triangle.h"
#include "TriangleParser.h"
#include "Circle.h"
#include "CircleParser.h"
#include "Rectangle.h"
#include "RectangleParser.h"

int main()
{
	std::ifstream inputFile("input.txt");
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open input.txt\n";
		return 1;
	}

	std::ofstream outputFile("output.txt", std::ios::out);
	if (!outputFile.is_open())
	{
		std::cout << "Failed to create output.txt\n";
		return 1;
	}

	std::string inputLine;
	IShape * shape = nullptr;
	IShapeParser & triangleParser = CTriangleParser::getInstance();
	IShapeParser & circleParser = CCircleParser::getInstance();
	IShapeParser & rectangleParser = CRectangleParser::getInstance();
	outputFile << std::fixed;

	while (std::getline(inputFile, inputLine))
	{
		if (inputLine.find(CTriangle::SHAPE_TYPE) != std::string::npos) { shape = triangleParser.parseShape(inputLine); }
		else if (inputLine.find(CCircle::SHAPE_TYPE) != std::string::npos) { shape = circleParser.parseShape(inputLine); }
		else if (inputLine.find(CRectangle::SHAPE_TYPE) != std::string::npos) { shape = rectangleParser.parseShape(inputLine); }

		if (shape != nullptr)
		{
			outputFile << shape->getShapeType() << ": P = " << shape->getPerimeter() << "; S = " << shape->getSquare() << '\n';
			delete shape;
			shape = nullptr;
		}
	}

	outputFile.close();
	return 0;
}

