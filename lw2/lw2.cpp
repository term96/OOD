#include "stdafx.h"
#include "BigInteger.h"

int main()
{
	CBigInteger fi(1ll);
	CBigInteger se(99999ll);
	CBigInteger th = fi + se;

	std::cout << fi.toString() << '\n';
	std::cout << se.toString() << '\n';
	std::cout << th.toString() << '\n';
    return 0;
}
