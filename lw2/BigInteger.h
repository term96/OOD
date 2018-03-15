#pragma once

class CBigInteger
{
public:
	CBigInteger();
	CBigInteger(long long value);
	CBigInteger(unsigned long long value);

	static CBigInteger getPositive(CBigInteger const & bigInteger);
	static CBigInteger getNegative(CBigInteger const & bigInteger);

	std::string toString() const;

	CBigInteger operator+(CBigInteger const & operand) const;
	CBigInteger operator-(CBigInteger const & operand) const;
	CBigInteger operator*(CBigInteger const & operand) const;
	CBigInteger operator/(CBigInteger  & operand) const;

	bool operator==(CBigInteger const & operand) const;
	bool operator<(CBigInteger const & operand) const;

private:
	CBigInteger(std::vector<char> && digits, bool positive);
	static void trim(std::vector<char> & digits);
	static CBigInteger add(CBigInteger const & left, CBigInteger const & right);
	static CBigInteger sub(CBigInteger const & left, CBigInteger const & right);
	static bool less(CBigInteger const & left, CBigInteger const & right);

	std::vector<char> m_digits;
	bool m_positive;
};
