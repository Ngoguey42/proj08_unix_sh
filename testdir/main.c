

#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void siglol(int i)
{
	dprintf(2, "{{ERR:%d catched}}", i); fflush(stdout);
	
}

int main(void)
{
/* 	printf("{{2}}"); fflush(stdout); */
	kill(getpid(), SIGUSR1);
/* 	signal(SIGPIPE, siglol); */
	while (1);
/* 	{ */
/* 		printf("w"); */
/* 		fflush(stdout); */
/* 	} */
	return (0);
}
