# The Prototype Shell For Project Ripon

This is currently reliant on POSIX and ISO C libraries and system calls, so those must be implemented into the OS before we can consider implanting the shell. 

There are several commands, as well as I/O redirection implemented at present, more details on these can be found using the "help" command when running inside the shell.

To run the shell, first you must run "make" in your standard terminal (assuming you have gcc). You then simply navigate to /build, and run ./main. you can move the shell to any location on the device, however the compiled main must be in the same directory as /bin, which contains all command binaries.
