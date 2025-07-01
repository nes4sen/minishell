#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s{

char arr[9];
char a;
char arr2[9];
}p;


int main()
{
	size_t a;
	p st;

	printf("%p\n%p%p\n%zu\n",&st, &st.arr, &st.a, sizeof(st));

}