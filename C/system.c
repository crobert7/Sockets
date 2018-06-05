#include <stdio.h>
#include <stdlib.h>

main ()
{
	int return_value;
	return_value = system ("ls -l /");
	printf("valor devuelto=%d\n", return_value);
}
