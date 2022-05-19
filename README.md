**HOW TO RUN**  
1. make
2. ./a.out
3. type your commands  

# shell.h : 
    Contains all the headers used. It also contains function definition and some global variables.  

# main.c : 
    Start the shell and "Q" is pressed then return from this function and program ends.

# input.h and input.c :  
    Takes the input given by user. Here space handling and command breaking according to ";" also take place.

# commandCall.c :
    All the functions called from here. From input() function in input.c; functionCall() function is called in commandCall.c to run the requested function by user.

# prompt.c :
    Prompt shows that shell is ready to execute the next task.

# changeDir.c :
    cd() function is implemented here which handles all cd commands.

# ls.h, ls.c : 
    ls() function is implemented here which handles all ls commands here.

# systemCommand.c : 
    implement the systemCommand function which handles the inbuilt command and direct input for foreground and background process according to given '&' flag.

# fProcess.c : 
    Process run in foreground.

# bProcess.c : 
    Process run in background.

# pinfo.c : 
    Shows the process information like process id, status, virtual memory size, and process execution path.

# repeat.c : 
    repeat process is implemented here.

# history.c :
    Stores the history of input given by user. It stores atmost 20 inputs and print 10 inputs in general.
    If user gives number of commands to be printed then latest 'num' commands will be printed if 'num' is less than commands stored in history else it prints all the commands.
    
# echo.c : 
    echo() functionality is implemented here. DO NOT HANDLE THE MULTILINE INPUT.


# replay.c: 
    Bonus part
    Command: replay -command <command name> -interval <num> -period <num>
    Run the command in given interval within given period

# redirection.c: 
    Redirecting input/output into file.
    > for output into file
    < for input from file
    >> for append into file

# pipe.c: 
    Interprocess communication through pipe
    p1 | p2 | .....
    Output of p1 act input for p2 and so on.
    Also handle file redirection in this.

# jobs.c: 
    print the jobNumber, status, jobName, pid of background process

# sig.c: 
    Signal send to process to given Pid
    Command: sig <jobNumber> <pid>

# fg.c: 
    Convert background process into foreground process
    Command: fg <jobNumber>

# bg.c: 
    Change stopped background process into running status
    Command: bg <jobNumber>

# signal.c:
    1. Ctrl+C: Quit the foreground program if exist else no change.
    2. Ctrl+D: Quit the shell if no foreground process running currently
    3. Ctrl+Z: Change foreground process into background process.
