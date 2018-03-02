#include "stdafx.h"
#include "BigInteger.h"
#include <exception>

void test()
{
	std::string checked;
	std::string correct;
	CBigInteger left;
	CBigInteger right;
	try
	{
		for (int i = -1000; i <= 1000; i++)
		{
			left = CBigInteger((long long)i);
			for (int j = -1000; j <= 1000; j++)
			{
				right = CBigInteger((long long)j);

				//correct = std::to_string(i - j);
				//checked = (left - right).toString();
				//if (correct.compare(checked) != 0)
				//{
				//	throw std::exception();
				//}

				//correct = std::to_string(i + j);
				//checked = (left + right).toString();
				//if (correct.compare(checked) != 0)
				//{
				//	throw std::exception();
				//}

				correct = std::to_string(i * j);
				checked = (left * right).toString();
				if (correct.compare(checked) != 0)
				{
					std::cout << correct << ' ' << checked << '\n';
					throw std::exception();
				}
			}
		}
	}
	catch (std::exception e)
	{
		std::cout << "Failed\n";
	}
}

int main()
{
	test();
    return 0;
}
