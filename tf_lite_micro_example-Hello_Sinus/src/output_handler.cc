/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "output_handler.h"

#include <zephyr.h>
#include <sys/printk.h>
#include <device.h>

void HandleOutput(tflite::ErrorReporter *error_reporter, float x_value,
		   float y_value)
{


	// // Log the current X and Y values
 	TF_LITE_REPORT_ERROR(error_reporter, "x_value: %f,  y_value: %f\n",
			     static_cast<double>(x_value),
			     static_cast<double>(y_value));
				 //static_cast<double>(brightness)); 

	// // Calculate the brightness of the LED such that y=-1 is fully off
    // // and y=1 is fully on. The LED's brightness can range from 0-255.
    // int brightness = (int)(127.5f * (y_value + 1));

	// TF_LITE_REPORT_ERROR(error_reporter, "%d\n", 
	// 			 static_cast<double>(brightness));
    
	//printk("%d\n", brightness);
}