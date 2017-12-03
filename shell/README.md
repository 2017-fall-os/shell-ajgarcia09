##Shell $ajgarcia09
# source code by Ana J. Garcia

This directory contains:
*code that takes an input string that is the path of a shell command, starts a new process by using the system call fork(), executes the process using
the system call exeve, and the parent process waits for the child process to terminate before proceeding.

This directory contains:
    myToc.h: header file with function instantiations for a tokenizer
    myToc.c: implementation of funcions from myToc
    shell.h: header file with function instantiations for my shell
    shell.c: code to execute shell commands using fork(), execve() and wait()
    shellDemo.c: a test program that runs my shell using
                 my tokenizer and executes Unix commands.

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

I also received helped from Hector Cervantes in executing simple pipes and modularizing my code so that it became more readable and easier to modify.

I used the following websites as references to complete my shell:

To learn about Background Processes:
    https://www.tutorialspoint.com/unix/unix-processes.htm

