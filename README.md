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
