# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>

int main()
{
	__pid_t pid;
	int	status;

	// printf("parent pid %d\n", getpid());
	pid = fork();
	int pid2 = fork();
	printf("[%d %d]\n", pid, pid2);
	if (pid < 0)
	{
		// printf("nourddine is gay\n");
		return (1);
	}
	if (pid == 0)
	{
		// printf("hello i'm the child\n");
		printf("pid is %d\n", pid);
	}
	waitpid(pid, &status, 0);
	printf("the child's pid %d\n", pid);
}