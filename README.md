The task is to create a console application that accepts TCP connections and processes
requests. Each request has the following syntax:
Request = 1*DIGIT CRLF
So, it is a decimal number with a trailing \r\n. For example,
12345\r\n
The application calculates the sum of all numbers received during the last period and reports
this sum in response to each request.
So, the response has the same format as the request.
NOTE: The sum is calculated per connection. So, each connection is handled separately.
Command-line arguments:
-d <period duration (seconds)>. By default, 60 seconds
-p <local port to listen>. If 0, then any available port is used. By default, 0.


Requirements
The server must be able to receive and process multiple requests through a single
connection
The implementation must use an approach that is ready to handle a big number of
connections simultaneously (e.g., 100,000).
It must be written in c++ and be compilable with one of the following compilers: msvc,
g++, clang.
It must compile/run at least under one of the following OS: Microsoft Windows, Linux
Ubuntu, Mac OS X.
Any free publicly-available software library can be used
The completed task must contain:
    The source code.
    Build files. Any of the following: CMakeLists.txt, Makefile, *vcprojx, *.pro.
    Readme.txt with instructions on how to build/run the program.

Additional notes:
Only integers allowed.
No worry about int overflow.