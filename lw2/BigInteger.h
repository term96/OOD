#pragma once

class CBigInteger
{
public:
	CBigInteger();
	CBigInteger(long long value);
	CBigInteger(unsigned long long value);
	~CBigInteger();

	unsigned int getCapacity() const;
	std::string toString() const;

	CBigInteger operator+(CBigInteger const & operand) const;

protected:
	CBigInteger(char * digits, unsigned int capacity, bool positive);
	void setPositive(bool positive);

private:
	char * m_digits;
	unsigned int m_capacity;
	bool m_positive;
};
