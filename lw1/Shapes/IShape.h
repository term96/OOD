#pragma once

class IShape
{
public:
	virtual double getSquare() const = 0;
	virtual double getPerimeter() const = 0;
	virtual std::string getShapeType() const = 0;
	virtual ~IShape() = default;
};

