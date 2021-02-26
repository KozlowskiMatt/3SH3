#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main (void)
{
	  int fd[2], nbytes;
	  pid_t child_pid;
	  char string [] = "This Pipe Works \n";
	  char readbuffer [80];
	  
	  pipe (fd);
	  
	  if (( child_pid = fork ()) == -1)
	  {
	    perror ("fork");
	    exit (0);
	  }

	  else if(child_pid == 0)
	  {
	    close (fd[0]);
	    write (fd[1],string,(strlen(string)+1));
	    exit (0);
	  
	  }
	  
	  else 
	  {
	    close (fd[1]);
	    nbytes = read(fd[0],readbuffer,sizeof(readbuffer));
	    printf (" Received   string : %s", readbuffer);
	  }
	  return 0;
}

