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

	bool operator==(CBigInteger const & operand) const;
	bool operator<(CBigInteger const & operand) const;
	bool operator>(CBigInteger const & operand) const;

protected:
	CBigInteger(std::vector<char> && digits, bool positive);
	static void trim(std::vector<char> & digits);

private:
	std::vector<char> m_digits;
	bool m_positive;
};
