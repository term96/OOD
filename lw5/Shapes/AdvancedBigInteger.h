#pragma once
#include "BigInteger.h"
class CAdvancedBigInteger :
	public CBigInteger
{
public:
	CAdvancedBigInteger(CBigInteger const &);

	static CBigInteger sqrt(CBigInteger const & value);

	friend CBigInteger operator*(CBigInteger const & left, double right);
	friend CBigInteger operator*(double left, CBigInteger const & right);
};

