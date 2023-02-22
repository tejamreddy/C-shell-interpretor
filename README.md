# C-shell-interpretor



Project description
=> This project is a shell interpreter program that can be used to run commands in a shell environment. The program uses the fork() and execvp() functions to run the commands. It allows the user to run commands both interactively and by providing a file as input.
=> execvp function execute command on the shell and print it on the terminal. execvp(*) should not be returned. If it returns then something is wrong in the command. 
=> The program starts by reading a command line and parsing it into separate commands. If a file is provided as input, it reads the commands from the file and executes them. 
=> For each command, the program creates a child process using fork() and runs the command in the child process using exec*().
=> If the command is successfully executed, the child process terminates, and the parent process continues to run.
=> Additionally, the program supports executing multiple commands in a single line, separated by semicolons or by a new line. In this case, it splits the line into separate commands and executes each one in a separate child process.
=> We use open(), read(), strtok_r(), strtok(), fgets() basic function to fulfill the requirements. 

Compiling instruction
gcc -o test test.c

A sample test run for iterative mode
./shell 
A sample test run for bash mode
./shell data.txt

