# Welcome to My Readline
***

## Task
The assignment was to create a my_readline function in C that reads from a stream represented by fd and returns a string that ends at a newline character or end of file.

## Description
The assignment requires that a global variable "READLINE_READ_SIZE" dictate the size of the read buffer/size, so a while loop was used to read in READLINE_READ_SIZE chunks while 
checking for '\n' characters and checking the number of bytes read.  The malloc function was used extensively to allocate memory for the string to be returned by the my_readline function. 

## Installation
Since a Makefile was not required for this assignment, one can simply edit the main function inside the my_readline.c file and compile to read files, stdin, redirection, etc. 

## Usage
TODO - How does it work?
```
./my_readline 
```

### The Core Team
Alan Chang

<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px'></span>
