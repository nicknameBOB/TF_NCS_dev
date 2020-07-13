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


#include <devicetree.h>
#include <drivers/gpio.h>



/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#define LED0	DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN	DT_GPIO_PIN(LED0_NODE, gpios)
#if DT_PHA_HAS_CELL(LED0_NODE, gpios, flags)
#define FLAGS	DT_GPIO_FLAGS(LED0_NODE, gpios)
#endif
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: led0 devicetree alias is not defined"
#define LED0	""
#define PIN	0
#endif

#ifndef FLAGS
#define FLAGS	0
#endif


struct device *dev;
bool led_is_on = true;
int ret;


static u32_t period;
static u32_t new_period;


// void outputInit()
// {
// 	dev = device_get_binding(LED0);
// 	if (dev == NULL) {
// 		return;
// 	}
// 
// 	ret = gpio_pin_configure(dev, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
// 	if (ret < 0) {
// 		return;
// 	};
// 
// 	// LED Blink ?
// 	gpio_pin_set(dev, PIN, (int)led_is_on);
// 			//led_is_on = !led_is_on;
// }





void HandleOutput(tflite::ErrorReporter *error_reporter, float x_value,
		  float y_value)
{
new_period = (u32_t)((period * (y_value + 1) )/2);
    if( new_period >= period){
        new_period = period;
    } 
    

	// Log the current X and Y values
 	TF_LITE_REPORT_ERROR(error_reporter, "x_value: %f, y_value: %f\n",
			     static_cast<double>(x_value),
			     static_cast<double>(y_value)); 
	

	dev = device_get_binding(LED0);
	if (dev == NULL) {
		return;
	}

	ret = gpio_pin_configure(dev, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
	if (ret < 0) {
		return;
	};


	gpio_pin_set(dev, PIN, (int)led_is_on);
			//led_is_on = !led_is_on;
	
}