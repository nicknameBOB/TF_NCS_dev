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

#include "main_functions.h"

#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <sys/printk.h>
#include <sys/__assert.h>
#include <string.h>


/* size of stack area used by each thread */
#define STACKSIZE 1024

/* scheduling priority used by each thread */
#define PRIORITY 7

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)

#define FLAGS_OR_ZERO(node)						\
	COND_CODE_1(DT_PHA_HAS_CELL(node, gpios, flags),		\
		    (DT_GPIO_FLAGS(node, gpios)),			\
		    (0))


struct led {
	const char *gpio_dev_name;
	const char *gpio_pin_name;
	unsigned int gpio_pin;
	unsigned int gpio_flags;
};

/* Toggle a spesific led aand sleep  */
void blink(const struct led *led, u32_t sleep_ms, u32_t id)
{
	struct device *gpio_dev;
	int cnt = 0;
	int ret;

	gpio_dev = device_get_binding(led->gpio_dev_name);
	if (gpio_dev == NULL) {
		printk("Error: didn't find %s device\n",
		       led->gpio_dev_name);
		return;
	}

	ret = gpio_pin_configure(gpio_dev, led->gpio_pin, led->gpio_flags);
	if (ret != 0) {
		printk("Error %d: failed to configure pin %d '%s'\n",
			ret, led->gpio_pin, led->gpio_pin_name);
		return;
	}

	while (1) {
		gpio_pin_set(gpio_dev, led->gpio_pin,  cnt % 2);
		k_msleep(sleep_ms);
		cnt++;
	}
}

/* Toggle led0, calls blink function on led0  */
void blink0(void)
{
		const struct led led0 = {
	#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
			.gpio_dev_name = DT_GPIO_LABEL(LED0_NODE, gpios),
			.gpio_pin_name = DT_LABEL(LED0_NODE),
			.gpio_pin = DT_GPIO_PIN(LED0_NODE, gpios),
			.gpio_flags = GPIO_OUTPUT | FLAGS_OR_ZERO(LED0_NODE),
	#else
	#error "Unsupported board: led0 devicetree alias is not defined"
	#endif
		};

	blink(&led0, 100, 0);
}

/* Toggle led1, calls blink function on led1  */
void blink1(void)
{
		const struct led led1 = {
	#if DT_NODE_HAS_STATUS(LED1_NODE, okay)
			.gpio_dev_name = DT_GPIO_LABEL(LED1_NODE, gpios),
			.gpio_pin_name = DT_LABEL(LED1_NODE),
			.gpio_pin = DT_GPIO_PIN(LED1_NODE, gpios),
			.gpio_flags = GPIO_OUTPUT | FLAGS_OR_ZERO(LED1_NODE),
	#else
	#error "Unsupported board: led1 devicetree alias is not defined"
	#endif
		};

	blink(&led1, 1000, 1);
}

//u32_t sleep_ms
void tensorflow(u32_t sleep_ms)
{
  int main(int argc, char* argv[]); {
    setup();
    while (true) {
      loop();
	  k_msleep(sleep_ms);
    }
  }
}


void uart_out(void)
{
	tensorflow(10);
}


K_THREAD_DEFINE(blink0_id, STACKSIZE, blink0, NULL, NULL, NULL,
    PRIORITY, 0, 0);
K_THREAD_DEFINE(blink1_id, STACKSIZE, blink1, NULL, NULL, NULL,
    PRIORITY, 0, 0);
K_THREAD_DEFINE(uart_out_id, STACKSIZE, uart_out, NULL, NULL, NULL,
    PRIORITY, 0, 0);
