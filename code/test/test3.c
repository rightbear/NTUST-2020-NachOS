#include "syscall.h"
main()
	{
		int	n;
		for (n=9;n>5;n--)
			PrintInt(OSAdd(n,n+1));
	}
