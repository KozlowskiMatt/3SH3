#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int running = 1; // Temp var to see whether to keep program running

// user - defined signal handler for alarm .
void alarm_handler ( int signo )
{
	if ( signo == SIGALRM )
		printf ("\tAlarm\n");
	else if (signo == SIGINT)		//Signal handler for CTRL+C
		printf("\tCTRL+C pressed !");
	else if (signo == SIGTSTP)		//Signal handler for CTRL+Z
	{
		printf("\tCTRL+Z pressed!\n");
		running = 0; // Once CTRL+Z is pressed the program will end
	}
}

int main ( void )
{
	// register the signal handler
	if ( signal ( SIGALRM , alarm_handler ) == SIG_ERR |signal ( SIGINT , alarm_handler ) == SIG_ERR |signal ( SIGTSTP , alarm_handler ) == SIG_ERR )
	{
		printf (" failed to register alarm handler .") ;
		exit (1);
	}
	while (1)
	{
		raise(SIGALRM); //Have the SIGALARM triggered every 2 seconds
		sleep(2);
		if (running ==0)
			break;
	}
}
