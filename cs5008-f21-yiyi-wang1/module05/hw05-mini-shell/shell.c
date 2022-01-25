// Modify this file for your assignment
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#define MAX_BUFFER_SIZE 80
#define SHELL_NAME "\x1B[31mMini-shell>\x1B[39m"

char *buffer;
char *history;
int history_count;
int history_size;

  //array of built-in command;
  char* arrayOfComm[] = {"cd", "exit", "help", "echo", "history"};
  
  //cd_function
  int fun_cd (char **cmd){
	  if(cmd[1] == NULL){
		  fprintf(stderr, "Path error. Please retry.\n");
	  }else if(chdir(cmd[1]) != 0){
		  fprintf(stderr, "Cannot change directory.\n");
	  }
	   return 1;

  }

 
  //exit_function
  //terminate the program by returning 0
  int fun_exit(char **cmd){
	printf("====================Shell exited====================\n");
	return 0;
  }

  //help_function
  //print out the built-in commands
  int fun_help(char **cmd){
	printf("=====================Mini-Shell=====================\n");
	printf("================The following is built-in===========\n");
	printf("cd: change current directory.\n");
	printf("exit: terminate the mini-shell.\n");
	printf("help: display all built-in commands.\n");
	printf("echo: print out the entered arguments.\n");	
	printf("history: display the history of commands entered.\n");
	return 1;
  }

  //echo_function
  //print out the entered argument
  //print an  error if there is nothing after "echo"
  int fun_echo(char **cmd){
	int i;
      	if(cmd[1] == NULL){
		fprintf(stderr, "Error. Please enter correct command.\n");	
	}else{
		for (i = 1; cmd[i] != NULL; i++){
			fprintf(stdout, "%s ", cmd[i]);
		}
		fprintf(stdout, "\n");
	}
	
	return 1;

 }

 //history_function
 //print out the entered commands
 int fun_history(char **cmd){
	 printf("history of commands entered:\n");
	 printf("%s",history);
	 return 1;
 }

  //array of function pointers
  int (*fun_arr[])(char **) = {&fun_cd, &fun_exit, &fun_help, &fun_echo, &fun_history};


  //signal handler function
  void sigint_handler(int sig){
	 write(1, "\nMini-shell terminated\n", 23);
	 free(buffer);
	 free(history);
	 exit(0);
  }


  //This function will read the input from user;
  //Remove the endline and return a char array; 
  char *read_line(){
	
	buffer = malloc(sizeof(char)*MAX_BUFFER_SIZE);

	if(!buffer){
		fprintf(stderr, "Error:cannot allocate memory.\n");
		free(buffer);
		exit(1);
	}

	fgets(buffer, MAX_BUFFER_SIZE, stdin);	   
	if(history_count >= history_size){
		history_size = history_size *2;	
	       	history = realloc(history, sizeof(char*)*history_size);
		if(!history){
			fprintf(stderr, "Error. Cannot allocate memory.\n");
			exit(1);
		}
	    }
	   strcat(history, buffer);//copy the buffer to history
	   history_count += 1;

	strtok(buffer, "\n");//remove endline for each line;
	return buffer;
  }

  //This function will parse the line
  //split the buffer by whitespace and store arguments in a char array
  //return the array with arguments
  //eg. cmd = {"echo", "testing"} 
  char **parse_line(char *buffer){
  	char *token;
	char **cmd = malloc(sizeof(char*)*MAX_BUFFER_SIZE);
	int i = 0;

	token = strtok(buffer," ");

	while( token != NULL ){
		cmd[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	cmd[i] = NULL;
	return cmd;
  }


 //This function will execute the cmd array by fork and call execvp in child process
 //if the first argument in cmd is not built-in function;
 int exe_comm(char **cmd){
	pid_t pid = fork();

	if(pid < 0){
		fprintf(stderr, "Cannot fork.");
		exit(1);
	}
	if(pid == 0){
		//this is child process;
		if(execvp(cmd[0],cmd) < 0){//this means an error occur when run execvp();
			fprintf(stderr, "Cannot find the command. Try again.\n");
			exit(1);
		}
	}else{
		//this is parent process;
		waitpid(pid, NULL, 0); //wait for this child process to finish	
	}

	return 1;
 }

  //This function will execute the command;
  //if the first argument in cmd is built-in,
  //will run the buily-in function directly;
  //if the first argument is not built-in,
  //will call the exe_comm function;
  int run_comm(char **cmd){
	if(cmd[0] == NULL){
		return 1;//there is no input
	}
	
	int i;
	//there are 5 built-in functions in this shell;
	for(i = 0; i < 5; i++){
		if(strcmp(cmd[0], arrayOfComm[i]) == 0){//this means the first argument is built-in
			return (*fun_arr[i])(cmd);//use function pointer to call;
		}
	}
	return exe_comm(cmd);// if  the first argument is not built-in, we will use fork() and exec();
  }

  //determined if need to use pipe;
  //if the command including |
  //we will need to have pipe
  //return 0 if there is a |
  //return 1 if there is no |
  int check_pipe(char *buffer){
	
	  if(strchr(buffer, 124) != NULL){
		  return 0;
	  }else{
		  return 1;
	  }

  }

  //This function will execute the command with pipe
  int exe_pipe(char *buffer){
  	char  *token;
        char **part = malloc(sizeof(char*)*MAX_BUFFER_SIZE);
        int i = 0;
	
	if(!part){
		fprintf(stderr, "Cannot allocate memory.\n");
		free(part);
		exit(1);
	}

	token = strtok(buffer,"|");//take the first part before pipe
	
	if(token == NULL){
		fprintf(stderr, "Cannot find command. Try again.\n");
		//this means there is nothing before the pipe;
	}else{
		while(token != NULL ){
			part[i] = token;
			i++;
			token = strtok(NULL, "|");//take the arguments after pipe
		}	
	}
	
	//now  have an array of char before and after the pipe
	//part[0] will be command before the pipe
	//part[1] will be command after the pipe
	//assume at most 1 pipe for this program
	
	if(part[1] == NULL){//if there is nothing after the pipe;
		fprintf(stderr, "Missing command. Try again.\n");
		return 1;
	}

	int fd[2];//have two fd for read and write;
	int returnValue = 0;

	if(pipe(fd) == -1){//unable to create pipe;
		return 0;
	}

	pid_t pid = fork();

	if(pid < 0){
		fprintf(stderr, "Cannot fork.\n");
		return 0;

	}else if(pid == 0){
		//this is in child process
		close(STDOUT_FILENO); // close the stdout in child process
		close(fd[0]);//we dont need to read from pipe
		
		dup2(fd[1], STDOUT_FILENO);//change the output side to pipe write side

		char **cmd = parse_line(part[0]);//parse the part before pipe
		if(run_comm(cmd) != 1){
			returnValue = 1;
		}
		close(fd[1]);//close the write side of pipe
		free(cmd);
		exit(returnValue);//need to exit the child process
	}else{
		//this is in parent process
		waitpid(pid,NULL,0);//wait for the child process to finish the command before pipe

		close(STDIN_FILENO);//close the input in parent process
		close(fd[1]);//we dont need to write to pipe
		dup2(fd[0], STDIN_FILENO);//change the input side to pipe read side
  		char **cmd = parse_line(part[1]);//parse the part after pipe
		returnValue = run_comm(cmd);
		close(fd[0]);//close the read side of pipe
		free(cmd);
	}

	free(part);

	return returnValue;
 }


int main(){
  // Please leave in this line as the first statement in your program.
  alarm(120); // This will terminate your shell after 120 seconds,
  signal(SIGINT, sigint_handler);
	
  printf("==============Welcome to mini-shell=================\n");
  printf("========You can enter help to see commands==========\n");
 	  
	  char *line;
	  char **cmd;
	  int status = 1;
	  history_count = 0;
	  history_size = 10 * MAX_BUFFER_SIZE;

	  history = (char*)malloc(sizeof(char*)*history_size);
	  history[0] = '\0';

	  if(!history){
		  printf("Error. Cannot allocate memory.\n");
		  free(history);
		  exit(1);
	  }

	  do{
	   int STDIN_COPY = dup(STDIN_FILENO);//make a copy of stdin
	   int STDOUT_COPY = dup(STDOUT_FILENO);//make a copy of stdout

	   printf(SHELL_NAME);
	   line = read_line();	
	   //check if we need to make pipe
	   if(check_pipe(line) == 0){
	  
		//if we need to have pipe, run the exe_pipe function
	   	status = exe_pipe(line);

	   }else{
	  
	   	//if we do not need pipe, we will just have single command;
	   	//parse the line;  
	   	cmd = parse_line(line);
	   	//and run the run_comm function;
	   	status = run_comm(cmd);
	   	free(cmd);
	   }
	   
	   free(line);
	   dup2(STDIN_COPY, STDIN_FILENO);//change back to STDIN 
	   dup2(STDOUT_COPY, STDOUT_FILENO);//change back to STDOUT

	 }while(status);

	  free(history);
  return 0;
}
