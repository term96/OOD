#include "stdafx.h"
#include "AdvancedBigInteger.h"

CBigInteger operator*(CBigInteger const & left, double right)
{
	double fractionalPart;
	double integerPart;
	fractionalPart = modf(right, &integerPart);

	CBigInteger integer(static_cast<long long>(integerPart));
	if (fractionalPart == 0)
	{
		return left * integer;
	}

	std::string fractionalWithoutPoint = std::to_string(fractionalPart).substr(2);
	size_t fractionalPartLength = fractionalWithoutPoint.length();
	CBigInteger fractional(fractionalWithoutPoint);

	return left * integer + left * fractional / CBigInteger(pow(10, fractionalPartLength));
}

CBigInteger operator*(double left, CBigInteger const & right)
{
	return right * left;
}
