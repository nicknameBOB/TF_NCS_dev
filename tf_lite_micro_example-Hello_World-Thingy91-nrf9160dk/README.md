This example code does hte following:

Three difrent threads runing, 
Two of the treads, thread 1 and 2 is used to blink onboard LED's at difrent intervals.
Thea last thread is uesd to run a tenserfloww hello world exampel, it runes intfernace on a model and prints out x and y values over uart.


West build -b board_name
west flash

conect to device over uart\comport\tty and see the values of x and y.

