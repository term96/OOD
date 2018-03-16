#include "stdafx.h"
#include "BigInteger.h"

CBigInteger::CBigInteger()
	: m_digits({ 0 })
	, m_positive(true)
{
}

CBigInteger::CBigInteger(long long value)
	: m_digits(19, 0)
	, m_positive(value >= 0)
{
	long long remaining = abs(value);
	size_t currentDigit = m_digits.size() - 1;
	while (remaining > 0)
	{
		m_digits[currentDigit] = remaining % 10;
		remaining /= 10;
		currentDigit--;
	}
	trim(m_digits);
}

CBigInteger::CBigInteger(std::string value)
	: m_digits(value.length())
	, m_positive(value[0] != '-')
{
	m_digits[0] = value[0] == '-' ? 0 : value[0] - '0';
	for (size_t i = 1; i < value.length(); i++)
	{
		m_digits[i] = value[i] - '0';
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
	for (int digit : m_digits)
	{
		stream << (int) digit;
	}
	return m_positive ? stream.str() : '-' + stream.str();
}

CBigInteger CBigInteger::operator+(CBigInteger const & operand) const
{
	CBigInteger result;
	if (!m_positive && !operand.m_positive)
	{
		result = std::move(getNegative(getPositive(*this) + getPositive(operand)));
	}
	else if (m_positive && !operand.m_positive)
	{
		result = std::move(*this - getPositive(operand));
	}
	else if (!m_positive && operand.m_positive)
	{
		result = std::move(operand - getPositive(*this));
	}
	else
	{
		result = add(*this, operand);
	}

	if (result.m_digits.size() == 1 && result.m_digits.front() == 0)
	{
		result.m_positive = true;
	}

	return std::move(result);
}

CBigInteger CBigInteger::operator-(CBigInteger const & operand) const
{
	CBigInteger result;
	if (!m_positive && operand.m_positive)
	{
		result = getNegative(getPositive(*this) + operand);
	}
	else if (m_positive && !operand.m_positive)
	{
		result = *this + getPositive(operand);
	}
	else if (!m_positive && !operand.m_positive)
	{
		result = getPositive(operand) - getPositive(*this);
	}
	else
	{
		result = operand < *this ? sub(*this, operand) : getNegative(sub(operand, *this));
	}

	if (result.m_digits.size() == 1 && result.m_digits.front() == 0)
	{
		result.m_positive = true;
	}

	return std::move(result);
}

CBigInteger CBigInteger::operator*(CBigInteger const & operand) const
{
	std::vector<char> newDigits(m_digits.size() + operand.m_digits.size(), 0);

	for (int i = operand.m_digits.size() - 1; i >= 0; i--)
	{
		if (operand.m_digits[i] == 0)
		{
			newDigits[i] = 0;
			continue;
		}
		int carry = 0;
		for (int j = m_digits.size() - 1; j >= 0; j--)
		{
			int mul = m_digits[j] * operand.m_digits[i] + newDigits[i + j + 1] + carry;
			newDigits[i + j + 1] = mul % 10;
			carry = mul / 10;
		}
		newDigits[i] = carry;
	}

	trim(newDigits);
	CBigInteger result(std::move(newDigits), m_positive == operand.m_positive);
	if (newDigits.size() == 1 && newDigits.front() == 0)
	{
		result.m_positive = true;
	}
	return std::move(result);
}

CBigInteger CBigInteger::operator/(CBigInteger & operand) const
{
	if (operand.m_digits.size() == 1 && operand.m_digits.front() == 0)
	{
		throw std::logic_error("Division by zero");
	}
	if (getPositive(*this) < getPositive(operand))
	{
		return CBigInteger();
	}

	CBigInteger absOperand(std::vector<char>(operand.m_digits), true);
	CBigInteger partOfLeft(std::vector<char>(m_digits.begin(), m_digits.begin() + operand.m_digits.size()), true);
	CBigInteger result(std::vector<char>(), m_positive == operand.m_positive);
	CBigInteger sumOfRight(absOperand);
	size_t available = m_digits.size() - partOfLeft.m_digits.size();
	
	do
	{
		bool carry = false;
		while (partOfLeft < absOperand && available > 0)
		{
			partOfLeft.m_digits.push_back(m_digits[m_digits.size() - available]);
			result.m_digits.push_back(0);
			available--;
			carry = true;
		}
		if (carry)
		{
			result.m_digits.pop_back();
			trim(partOfLeft.m_digits);
		}

		char count = 1;
		while (sumOfRight < partOfLeft || sumOfRight == partOfLeft)
		{
			sumOfRight = sumOfRight + absOperand;
			count++;
		}
		count--;

		partOfLeft = partOfLeft;
		partOfLeft = partOfLeft - sumOfRight + absOperand;
		sumOfRight = absOperand;

		result.m_digits.push_back(count);
	} while (available > 0);

	trim(result.m_digits);
	if (result.m_digits.size() == 1 && result.m_digits.front() == 0)
	{
		result.m_positive = true;
	}

	return std::move(result);
}

bool CBigInteger::operator==(CBigInteger const & operand) const
{
	if (m_positive != operand.m_positive || m_digits.size() != operand.m_digits.size())
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
	if (*this == operand)
	{
		return false;
	}
	if (!m_positive && operand.m_positive)
	{
		return true;
	}
	if (m_positive && !operand.m_positive)
	{
		return false;
	}
	if (!m_positive && !operand.m_positive)
	{
		return !less(getPositive(*this), getPositive(operand));
	}

	return less(*this, operand);
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

bool CBigInteger::less(CBigInteger const & left, CBigInteger const & right)
{
	if (left.m_digits.size() < right.m_digits.size())
	{
		return true;
	}
	else if (left.m_digits.size() > right.m_digits.size())
	{
		return false;
	}
	for (size_t i = 0; i < left.m_digits.size(); i++)
	{
		if (left.m_digits[i] < right.m_digits[i])
		{
			return true;
		}
		else if (left.m_digits[i] > right.m_digits[i])
		{
			return false;
		}
	}
	return false;
}
