This example code does hte following:

Three difrent threads runing, 
Two of the treads, thread 1 and 2 is used to blink onboard LED's at difrent intervals.
Thea last thread is uesd to run a tenserfloww sine exampel, it runes intfernace on a model and prints out a value that corespond to a point in the sine. from 0 to 250. Use Arduino seriel plotter to see a sine being printed or som other seriall plotter.


West build -b board_name
west flash

conect to device over uart\comport\tty and see the values of x and y.

