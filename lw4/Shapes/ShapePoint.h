#pragma once

class CShapePoint
{
public:
	CShapePoint(int x, int y);
	CShapePoint(CShapePoint const & point);

	int getX() const;
	int getY() const;

	void setX(int x);
	void setY(int y);

private:
	int m_x;
	int m_y;
};
