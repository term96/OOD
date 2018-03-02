#include "stdafx.h"
#include "BigInteger.h"

CBigInteger::CBigInteger()
	: m_digits({ 0 })
	, m_positive(true)
{
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
	: m_digits(19, 0)
	, m_positive(true)
{
	unsigned long long remaining = value;
	size_t currentDigit = m_digits.size() - 1;
	while (remaining > 0)
	{
		m_digits[currentDigit] = remaining % 10;
		remaining /= 10;
		currentDigit--;
	}
	trim(m_digits);
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

std::string CBigInteger::toString() const
{
	if (m_digits.size() == 1 && m_digits.front() == 0)
	{
		return "0";
	}
	std::stringstream stream;
	for (char digit : m_digits)
	{
		stream << (short) digit;
	}
	return m_positive ? stream.str() : '-' + stream.str();
}

CBigInteger CBigInteger::operator+(CBigInteger const & operand) const
{
	if (!m_positive && !operand.m_positive)
	{
		return std::move(getNegative(getPositive(*this) + getPositive(operand)));
	}
	if (m_positive && !operand.m_positive)
	{
		return std::move(*this - getPositive(operand));
	}
	if (!m_positive && operand.m_positive)
	{
		return std::move(operand - getPositive(*this));
	}

	return add(*this, operand);
}

CBigInteger CBigInteger::operator-(CBigInteger const & operand) const
{
	if (!m_positive && operand.m_positive)
	{
		return getNegative(getPositive(*this) + operand);
	}
	if (m_positive && !operand.m_positive)
	{
		return *this + getPositive(operand);
	}
	if (!m_positive && !operand.m_positive)
	{
		return getPositive(operand) - getPositive(*this);
	}

	return *this > operand ? sub(*this, operand) : getNegative(sub(operand, *this));
}

CBigInteger CBigInteger::operator*(CBigInteger const & operand) const
{
	return std::move(mul(*this, operand));
}

bool CBigInteger::operator==(CBigInteger const & operand) const
{
	if (m_digits.size() != operand.m_digits.size())
	{
		return false;
	}
	for (size_t i = 0; i < m_digits.size(); i++)
	{
		if (m_digits[i] != operand.m_digits[i])
		{
			return false;
		}
	}
	return true;
}

bool CBigInteger::operator<(CBigInteger const & operand) const
{
	if (m_digits.size() < operand.m_digits.size())
	{
		return true;
	}
	else if (m_digits.size() > operand.m_digits.size())
	{
		return false;
	}
	for (size_t i = 0; i < m_digits.size(); i++)
	{
		if (m_digits[i] < operand.m_digits[i])
		{
			return true;
		}
		else if (m_digits[i] > operand.m_digits[i])
		{
			return false;
		}
	}
	return false;
}

bool CBigInteger::operator>(CBigInteger const & operand) const
{
	return !(*this == operand) && !(*this < operand);
}

CBigInteger::CBigInteger(std::vector<char> && digits, bool positive)
	: m_digits(digits)
	, m_positive(positive)
{
}

void CBigInteger::trim(std::vector<char> & digits)
{
	size_t zeros = 0;
	for (size_t i = 0; i < digits.size() - 1; i++)
	{
		if (digits[i] == 0)
		{
			zeros++;
		}
		else
		{
			break;
		}
	}
	digits.erase(digits.begin(), digits.begin() + zeros);
}

CBigInteger CBigInteger::add(CBigInteger const & left, CBigInteger const & right)
{
	int maxSize = left.m_digits.size() > right.m_digits.size() ? left.m_digits.size() : right.m_digits.size();
	std::vector<char> newDigits(maxSize);

	int currentLeft = left.m_digits.size() - 1;
	int currentRight = right.m_digits.size() - 1;
	char leftDigit;
	char rightDigit;
	char sum;
	char remaining = 0;

	for (int i = maxSize - 1; i >= 0; i--)
	{
		leftDigit = currentLeft >= 0 ? left.m_digits[currentLeft] : 0;
		rightDigit = currentRight >= 0 ? right.m_digits[currentRight] : 0;
		sum = leftDigit + rightDigit + remaining;

		newDigits[i] = sum % 10;
		remaining = sum / 10;

		currentLeft--;
		currentRight--;
	}

	if (remaining != 0)
	{
		newDigits.insert(newDigits.begin(), remaining);
	}

	return std::move(CBigInteger(std::move(newDigits), true));
}

CBigInteger CBigInteger::sub(CBigInteger const & left, CBigInteger const & right)
{
	std::vector<char> newDigits(left.m_digits);
	int currentRight = right.m_digits.size() - 1;

	char leftDigit;
	char rightDigit;

	for (int i = newDigits.size() - 1; i >= 0; i--)
	{
		leftDigit = newDigits[i];
		rightDigit = currentRight >= 0 ? right.m_digits[currentRight] : 0;

		if (leftDigit >= rightDigit)
		{
			newDigits[i] = leftDigit - rightDigit;
		}
		else
		{
			newDigits[i] = 10 + leftDigit - rightDigit;
			newDigits[i - 1]--;
		}

		currentRight--;
	}

	trim(newDigits);
	return std::move(CBigInteger(std::move(newDigits), true));
}

CBigInteger CBigInteger::mul(CBigInteger const & left, CBigInteger const & right)
{
	std::vector<char> newDigits(left.m_digits.size() + right.m_digits.size(), 0);

	for (int i = right.m_digits.size() - 1; i >= 0; i--)
	{
		if (right.m_digits[i] == 0)
		{
			newDigits[i] = 0;
			continue;
		}
		int carry = 0;
		for (int j = left.m_digits.size() - 1; j >= 0; j--)
		{
			int mul = left.m_digits[j] * right.m_digits[i] + newDigits[i + j + 1] + carry;
			newDigits[i + j + 1] = mul % 10;
			carry = mul / 10;
		}
		newDigits[i] = carry;
	}

	trim(newDigits);
	return CBigInteger(std::move(newDigits), left.m_positive == right.m_positive);
}
