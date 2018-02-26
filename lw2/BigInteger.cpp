#include "stdafx.h"
#include "BigInteger.h"

CBigInteger::CBigInteger()
{
	m_capacity = 19;
	m_positive = true;
	m_digits = new char[m_capacity];
	for (int i = 0; i < m_capacity; i++)
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
	int currentDigit = m_capacity - 1;
	while (remaining > 0)
	{
		m_digits[currentDigit] = remaining % 10;
		remaining /= 10;
		currentDigit--;
	}
}

CBigInteger::CBigInteger(CBigInteger const & bigInteger)
{
	m_capacity = bigInteger.m_capacity;
	m_positive = bigInteger.m_positive;
	m_digits = new char[m_capacity];
	for (int i = 0; i < m_capacity; i++)
	{
		m_digits[i] = bigInteger.m_digits[i];
	}
}

CBigInteger::CBigInteger(CBigInteger && bigInteger)
{
	m_capacity = bigInteger.m_capacity;
	m_positive = bigInteger.m_positive;
	m_digits = bigInteger.m_digits;
	bigInteger.m_digits = nullptr;
}

CBigInteger::~CBigInteger()
{
	if (m_digits != nullptr)
	{
		delete[] m_digits;
	}
}

CBigInteger CBigInteger::getPositive(CBigInteger const & bigInteger)
{
	CBigInteger copy(bigInteger);
	copy.m_positive = true;
	return std::move(copy);
}

CBigInteger CBigInteger::getNegative(CBigInteger const & bigInteger)
{
	CBigInteger copy(bigInteger);
	copy.m_positive = false;
	return std::move(copy);
}

int CBigInteger::getCapacity() const
{
	return m_capacity;
}

bool CBigInteger::isPositive() const
{
	return m_positive;
}

std::string CBigInteger::toString() const
{
	std::stringstream stream;
	int currentDigit = 0;
	while (currentDigit < m_capacity && m_digits[currentDigit] == 0)
	{
		currentDigit++;
	}
	while (currentDigit < m_capacity)
	{
		stream << (short) m_digits[currentDigit];
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
	if (!isPositive() && !operand.isPositive())
	{
		return std::move(getNegative(getPositive(*this) + getPositive(operand)));
	}
	if (isPositive() && !operand.isPositive())
	{
		return std::move(*this - getPositive(operand));
	}
	if (!isPositive() && operand.isPositive())
	{
		return std::move(operand - getPositive(*this));
	}

	int maxCapacity = m_capacity > operand.m_capacity ? m_capacity : operand.m_capacity;
	int newCapacity = maxCapacity + 1;
	char * newDigits = new char[newCapacity];

	int currentLeft = m_capacity - 1;
	int currentRight = operand.m_capacity - 1;
	int leftDigit;
	int rightDigit;
	int sum;
	int remaining = 0;

	for (int i = newCapacity - 1; i >= 0; i--)
	{
		leftDigit = currentLeft >= 0 ? m_digits[currentLeft] : 0;
		rightDigit = currentRight >= 0 ? operand.m_digits[currentRight] : 0;
		sum = leftDigit + rightDigit + remaining;

		newDigits[i] = sum % 10;
		remaining = sum / 10;

		currentLeft--;
		currentRight--;
	}

	return std::move(CBigInteger(newDigits, newCapacity, true));
}

CBigInteger CBigInteger::operator-(CBigInteger const & operand) const
{
	return std::move(CBigInteger());
}

bool CBigInteger::operator==(CBigInteger const & operand) const
{
	int currentLeft = 0;
	int currentRight = 0;
	while (currentLeft < m_capacity && m_digits[currentLeft] == 0)
	{
		currentLeft++;
	}
	while (currentRight < operand.m_capacity && operand.m_digits[currentRight] == 0)
	{
		currentRight++;
	}
	if (m_capacity - currentLeft != operand.m_capacity - currentRight)
	{
		return false;
	}

	while (currentLeft < m_capacity && currentRight < operand.m_capacity)
	{
		if (m_digits[currentLeft] != operand.m_digits[currentRight])
		{
			return false;
		}
		currentLeft++;
		currentRight++;
	}

	return true;
}

bool CBigInteger::operator<(CBigInteger const & operand) const
{
	int currentLeft = 0;
	int currentRight = 0;
	while (currentLeft < m_capacity && m_digits[currentLeft] == 0)
	{
		currentLeft++;
	}
	while (currentRight < operand.m_capacity && operand.m_digits[currentRight] == 0)
	{
		currentRight++;
	}
	if (m_capacity - currentLeft != operand.m_capacity - currentRight)
	{
		return m_capacity - currentLeft < operand.m_capacity - currentRight;
	}

	while (currentLeft < m_capacity && currentRight < operand.m_capacity)
	{
		if (m_digits[currentLeft] != operand.m_digits[currentRight])
		{
			return m_digits[currentLeft] < operand.m_digits[currentRight];
		}
		currentLeft++;
		currentRight++;
	}

	return false;
}

bool CBigInteger::operator>(CBigInteger const & operand) const
{
	return !(*this == operand) && !(*this < operand);
}

CBigInteger::CBigInteger(char * digits, int capacity, bool positive)
{
	m_digits = digits;
	m_capacity = capacity;
	m_positive = positive;
}
