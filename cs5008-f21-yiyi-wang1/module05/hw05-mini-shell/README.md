# Homework 5

This is the starting readme for this assignment.  Please edit the following information by removing the "*edit me*" and replace it with appropriate information your assignment. If it is asking you a question, please provide a response.

- Name: Yiyi Wang
- Description: Student
- How many hours did it take you to complete this assignment? 12 hours
- Did you collaborate with any other students/TAs/Professors? If so, tell us who and in what capacity.
  - I discussed with Victoria about the signal function.
- Did you use any external resources? (Cite them below)
  - *edit me*
  - *edit me and add more rows if needed*
- (Optional) What was your favorite part of the assignment? 
  - *edit me*
- (Optional) How would you improve the assignment? 
  - *edit me*

## User-Defined Built-In Command

NAME: 

echo
history

SYNOPSIS: 

-echo: print out the commands that user enter
-history: display the previous commands that user typed

DESCRIPTION:

-echo: the simplest echo command. It will print out whatever argument passed to it to the stdout.
       For example, command "echo testing" will print out "testing" on the terminal.

-history: it will print out all the previous entered commands. 

NOTES:

-echo: in the parse_line function, I already split the command by whitespace and store in a pointer cmd.
In the echo function, I will just use a for loop to print out the elements from position 1 to the end of cmd array.
Position 0 will be the argument "echo" itself and it was checked before in run_comm function (only if the argument is equal to 'echo' then the echo function could be called.)
 

-history: I create a char pointer in main function to store the line user entered. This will be pointer to char since we need to store the line every time my do-while loop run and my buffer pointer is freed inside the loop. Therefore, I could not use pointer to char pointer but have to copy the line to my history string. I use the strcat function from string libray (add the null terminator so the function could work without uninitialised issue.
 
## Logistics

For this assignment (and every assignment/lab), you must login into the servers through `your_khoury_name@login.khoury.neu.edu` to complete and test your work. The reason is the examples I will provide below are compiled strictly for our machines architecture, and this is a consistent architecture where your submission will be graded.

## Important notes

* Your code **must compile and run** on the Khoury machines to earn credit. Make sure you test your programs on these machines, as this is where we grade your assignments.
* You must commit any additional files(if any) into your repository so we can test your code.
  * Points will be lost if you forget!
* Do not forget, once you have pushed your changes to your repo make sure that you **submit them to Gradescope before the assignment deadline!**

