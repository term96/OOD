#pragma once
#include "BigInteger.h"
class CAdvancedBigInteger :
	public CBigInteger
{
public:
	friend CBigInteger operator*(CBigInteger const & left, double right);
	friend CBigInteger operator*(double left, CBigInteger const & right);
};

