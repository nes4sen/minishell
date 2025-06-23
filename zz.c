#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int *glob(void)
{
	static int var = 0;
	printf("[%d]\n", var);
	return (&var);
}


int main()
{
	int *a = glob();

	*a = 4;
	printf("--> %d\n", *a);
	glob();
	*a = 4;
	printf("--> %d\n", *a);
	glob();

}