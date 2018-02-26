#include "stdafx.h"
#include "BigInteger.h"

int main()
{
	CBigInteger fi(1ll);
	CBigInteger se(2ll);
	//std::cout << fi.toString() << ' ' << se.toString() << '\n';

	CBigInteger sum = fi + se;
	std::cout << "asdasdsa\n";
	std::cout << sum.toString() << ' ' << sum.getCapacity() << '\n';

    return 0;
}
