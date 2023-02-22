#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h> 

int numberOfChildProcess = 0;
pid_t pid;
int isExit = 0; 
int is_batch = 0;

void wait_for_child(){
	while(numberOfChildProcess-- != 0){
    			wait(NULL); 
    	}
    	if(is_batch == 0 && isExit == 0)
    		printf("prompt> ");
}

void shell_command(char *line) {
    pid = 0;
    char *args[16];
    char *command;
    char *ptr;
    char *deli = ";\n";
    int i = 0;
    command = strtok_r(line, deli, &ptr);
    while (command != NULL) {
        // Split the command into separate arguments
        i = 0;
        args[i] = strtok(command, " \t\n");
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " \t\n");
        }

	if(strcmp(args[0], "quit") == 0){
		isExit = 1;
		command = strtok_r(NULL, deli, &ptr);	
		continue;  // Normal return
	}
      
        // Create a child process
        numberOfChildProcess++;
        pid = fork();
        if (pid == 0) {
            // Child process		
            execvp(args[0], args);   
            printf("Error: Command not found\n"); // execvp should not be returned, If it returns something then something is wrong
            exit(1); //  Abnormal return
        } else if (pid < 0) {
            printf("Error while creating child process");
        }else if(is_batch == 0){  //Parent Process as pid > 0
        	numberOfChildProcess++;
        	//wait(NULL);	
        }
        // Get the next command in the line
        command = strtok_r(NULL, deli, &ptr);
    }
}

int main(int argc, char *argv[]) {  
    int maxLine = 256;
    char line[maxLine];  
    
    if (argc == 2) {
      //Bash mode and Open the file
    	is_batch = 1;
    	int bytes_read;
    	int fp = 0;
        fp = open(argv[1], O_RDONLY);
        if (fp == -1) {
            printf("Error while opening a file");
            return 1;
        }
	// Read each line from the file and execute the command
  	while ((bytes_read = read(fp, line, maxLine)) > 0) {
		printf("prompt> %s\n",line);
		shell_command(line);
	}
        // Close the file
        close(fp);
        wait_for_child();    // wait for all child processes to complete  
    } else {
        // Interactive mode
        printf("prompt> ");
        while (fgets(line, maxLine, stdin) != NULL) {
        	shell_command(line);
       		wait_for_child(); // Wait for all the command added with the ; character
        	if(isExit == 1){
       		  	exit(0);
       		}
        }
    } 
    return 0;
}
