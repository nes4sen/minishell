#include <unistd.h>

int main()
{
	char *arg[] = {"/usr/bin/ls", NULL};
	char *env[] = {"toto",NULL};
	execve("toto", NULL, env);
}