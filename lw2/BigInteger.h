#pragma once

class CBigInteger
{
public:
	CBigInteger();
	CBigInteger(long long value);
	CBigInteger(unsigned long long value);
	CBigInteger(CBigInteger const & bigInteger);
	CBigInteger(CBigInteger && bigInteger);
	~CBigInteger();

	static CBigInteger getPositive(CBigInteger const & bigInteger);
	static CBigInteger getNegative(CBigInteger const & bigInteger);

	int getCapacity() const;
	bool isPositive() const;
	std::string toString() const;

	CBigInteger operator+(CBigInteger const & operand) const;
	CBigInteger operator-(CBigInteger const & operand) const;

	bool operator==(CBigInteger const & operand) const;
	bool operator<(CBigInteger const & operand) const;
	bool operator>(CBigInteger const & operand) const;

protected:
	CBigInteger(char * digits, int capacity, bool positive);

private:
	char * m_digits;
	int m_capacity;
	bool m_positive;
};
