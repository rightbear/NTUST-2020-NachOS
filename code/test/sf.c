#include "syscall.h"
main()
	{
		int	n[1024 * 1024], p = 0;
		for (p = 0; p < 1024 * 1024; p++) {
			n[p] = p;
			PrintInt(n);
		}
	}
