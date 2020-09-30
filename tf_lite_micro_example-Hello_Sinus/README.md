# Description:

This example code does the following:

Three difrent threads runing, 
Two of the treads, thread 1 and 2 is used to blink onboard LED's at difrent intervals.
Thea last thread is uesd to run a tenserfloww sine exampel, it runes intfernace on a model and prints out a value that corespond to a point in the sine. from 0 to 250. Use Arduino seriel plotter to see a sine being printed or som other seriall plotter.

## How to build
open terminal in diractory and run the following comands:
``west build -b board_name``
``west flash``

## How to connect to device port
conect to device over uart\comport\tty and see the values of x and y.

## how to train and test models
Include is one model

Link to train model guide from google: https://github.com/tensorflow/tensorflow/tree/master/tensorflow/lite/micro/examples/hello_world/train
