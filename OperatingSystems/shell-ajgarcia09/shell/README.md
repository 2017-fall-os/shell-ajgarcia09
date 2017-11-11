#Shell -ajgarcia09
# source code by Ana J. Garcia

This directory contains:
*code that takes an input string that is the path of a shell command, starts a new process by using the system call fork(), executes the process using
the system call exeve, and the parent process waits for the child process to terminate before proceeding.

This directory contains:
    myToc.h: header file with function instantiations
    myToc.c: implementation of funcions from myToc.h
    shell.h: header file with function instantiations
    shell.c: code to execute shell commands using fork(), execve() and wait()

To compile:

~~~
$ make
~~~

To test it:
~~~
$ make demo
~~~

To delete binaries:
~~~
$ make clean
~~~

For the completion of this assignment, I received help from Ulises Martinez to understand the general algorithm to write this program.
He helped me create the pseudocode I followed in the completion of this assignment.

I helped Hector Cervantes in using the stat struc to check whether an executable file exists.

I used these websites as references for using stat:

pubs.opengroup.org/onlinepubs/009695399/functions/stat.html

https://stackoverflow.com/questions/13098620/using-stat-to-check-if-a-file-is-executable-in-c
