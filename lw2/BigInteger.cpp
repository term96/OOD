#include "stdafx.h"
#include "BigInteger.h"

CBigInteger::CBigInteger()
{
	m_capacity = 32;
	m_positive = true;
	m_digits = new char[m_capacity];
	for (unsigned int i = 0; i < m_capacity; i++)
	{
		m_digits[i] = 0;
	}
}

CBigInteger::CBigInteger(long long value)
	: CBigInteger(static_cast<unsigned long long>(abs(value)))
{
	if (value < 0)
	{
		m_positive = false;
	}
}

CBigInteger::CBigInteger(unsigned long long value)
	: CBigInteger()
{
	unsigned long long remaining = value;
	unsigned int currentDigit = m_capacity - 1;
	while (remaining > 0)
	{
		m_digits[currentDigit] = remaining % 10;
		remaining /= 10;
		currentDigit--;
	}
}

CBigInteger::~CBigInteger()
{
	delete[] m_digits;
}

unsigned int CBigInteger::getCapacity() const
{
	return m_capacity;
}

std::string CBigInteger::toString() const
{
	std::stringstream stream;
	unsigned int currentDigit = 0;
	while (currentDigit < m_capacity && m_digits[currentDigit] == 0)
	{
		currentDigit++;
	}
	while (currentDigit < m_capacity)
	{
		stream << (int) m_digits[currentDigit];
		currentDigit++;
	}
	std::string value = stream.str();
	if (value.empty())
	{
		return "0";
	}
	return m_positive ? value : '-' + value;
}

CBigInteger CBigInteger::operator+(CBigInteger const & operand) const
{
	// TODO: Один отрицательный
	// TODO: Два отрицательных

	unsigned int maxCapacity = m_capacity > operand.m_capacity ? m_capacity : operand.m_capacity;
	unsigned int newCapacity = maxCapacity + 1;
	unsigned int currentDigit = newCapacity - 1;
	char remaining = 0;
	char * newDigits = new char[newCapacity];

	int leftDigit;
	int rightDigit;
	int sum;

	for (unsigned int i = maxCapacity - 1; i >= 0; i--)
	{
		leftDigit = i < m_capacity ? m_digits[i] : 0;
		rightDigit = i < operand.m_capacity ? operand.m_digits[i] : 0;
		sum = leftDigit + rightDigit + remaining;

		newDigits[i] = sum % 10;
		remaining = sum / 10;
	}
	newDigits[0] = remaining;

	return CBigInteger(newDigits, newCapacity, true); 
}

CBigInteger::CBigInteger(char * digits, unsigned int capacity, bool positive)
{
	m_digits = digits;
	m_capacity = capacity;
	m_positive = positive;
}

void CBigInteger::setPositive(bool positive)
{
	m_positive = positive;
}
