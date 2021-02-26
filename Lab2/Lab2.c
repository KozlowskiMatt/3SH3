#include <stdio.h>
#include <unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
 
int main(void) 
{ 
	int fd1[2]; 
	int fd2[2]; 
	int total_sum=0; // Store the sum of the numbers from the user
	int temp_number = 0; 
	int number = 0; // 8 bit number --> 1 byte
	int nbytes;
	pid_t childpid;

	pipe(fd1);
	pipe(fd2);


	if((childpid = fork())<0) 
	{ 
		perror("fork"); 
		exit(0);  
	} 


	else if (childpid == 0)  // CHILD PROCESS
	{  

				// *** WRITTING TO PARENT VIA PIPE 1 ***//

		close(fd1[0]); //CLose fd[0] to write to the parent		
		while(number != -1) 
		{ 
		    
		    printf("PLease insert an integer (<256):  "); //Must be 1 byte
		    scanf("%d",&number);  
		    write(fd1[1], &number, 1);  //Write to the parent
		}


			// *** CHILD PROCESS RECEIVES THE TOTAL SUM FROM THE PARENT VIA PIPE 2 ***//
		close(fd2[1]);

		read(fd2[0],&total_sum,sizeof(total_sum)); 
		printf("The total sum received by child is: %d",total_sum); 
		exit(0);
		
	        
	}

	else // PARENT PROCESS
	{
			// *** RECEIVING NUMBERS FROM THE CHILD *** //

		close(fd1[1]);
		while (temp_number != 255) 
		{
			
			read(fd1[0],&temp_number,1); 
			total_sum+=temp_number; 
			
		}

			// *** SENDING TOTAL SUM TO THE CHILD PROCESS *** //
		
		
		total_sum -= 255;
		close(fd2[0]);
		write(fd2[1],&total_sum,sizeof(total_sum));
		exit(0);
		
	 } 
	return 0;
}
