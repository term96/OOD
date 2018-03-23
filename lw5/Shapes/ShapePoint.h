#pragma once
#include "BigInteger.h"

class CShapePoint
{
public:
	CShapePoint(CBigInteger x, CBigInteger y);
	CShapePoint(CShapePoint const & point);

	CBigInteger getX() const;
	CBigInteger getY() const;

	void setX(CBigInteger x);
	void setY(CBigInteger y);

private:
	CBigInteger m_x;
	CBigInteger m_y;
};
