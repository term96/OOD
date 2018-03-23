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

	return left * integer + left * fractional / CBigInteger(static_cast<long long>(pow(10, fractionalPartLength)));
}

CBigInteger operator*(double left, CBigInteger const & right)
{
	return right * left;
}

CAdvancedBigInteger::CAdvancedBigInteger(CBigInteger const & copy)
	: CBigInteger(copy)
{
}

CBigInteger CAdvancedBigInteger::sqrt(CBigInteger const & value)
{
	CBigInteger s, t;
	CBigInteger two(2);

	s = 1;  t = value;
	while (s < t) {
		s = s * two;
		t = t / two;
	}

	do {
		t = s;
		s = (value / s + s) / two;//x1=(N / x0 + x0)/2 : recurrence formula
	} while (s < t);

	return t;
}
