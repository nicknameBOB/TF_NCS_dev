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

#include "tensorflow/lite/micro/examples/magic_wand/accelerometer_handler.h"

#include <kernel.h>
#include <device.h>
#include <drivers/sensor.h>
#include <stdio.h>
#include <string.h>
#include <zephyr.h>

#include <init.h>
#include <drivers/gpio.h>
#include <sys/byteorder.h>
#include <sys/__assert.h>
#include <drivers/spi.h>

#include "motion/motion.h"
#include "adxl362/adxl362.h"
#include <logging/log.h>

#define DT_DRV_COMPAT adi_adxl362

#define BUFLEN 300
int begin_index = 0;
struct device* sensor = NULL;
int current_index = 0;

float bufx[BUFLEN] = {0.0f};
float bufy[BUFLEN] = {0.0f};
float bufz[BUFLEN] = {0.0f};

bool initial = true;

K_SEM_DEFINE(sem, 0, 1);
static void trigger_handler(struct device *dev, struct sensor_trigger *trig)
{
	switch (trig->type) {
	case SENSOR_TRIG_DATA_READY:
		if (sensor_sample_fetch(dev) < 0) {
			printf("Sample fetch error\n");
			return;
		}
		k_sem_give(&sem);
		break;
	case SENSOR_TRIG_THRESHOLD:
		printf("Threshold trigger\n");
		break;
	default:
		printf("Unknown trigger\n");
	}
}

TfLiteStatus SetupAccelerometer(tflite::ErrorReporter* error_reporter) {
  sensor = device_get_binding(DT_LABEL(DT_INST(0, adi_adxl362)));
  if (sensor == NULL) {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Failed to get accelerometer, label: %s\n",
                         DT_LABEL(DT_INST(0, adi_adxl362)));
  } else {
    TF_LITE_REPORT_ERROR(error_reporter, "Got accelerometer, label: %s\n",
                         DT_LABEL(DT_INST(0, adi_adxl362)));
    printk("This happend: waht is this, it is the knowlage of achiviing the right sensor");
  }
  return kTfLiteOk;
}


bool ReadAccelerometer(tflite::ErrorReporter* error_reporter, float* input,
                       int length) {

  //length = 0;
  //input = 0;                       
  struct sensor_value accel[3];
  TF_LITE_REPORT_ERROR(error_reporter, "READ Acell start\n");
	struct device *dev = device_get_binding(DT_LABEL(DT_INST(0, adi_adxl362)));
	if (dev == NULL) {
		printf("Device get binding device\n");
		return false;
	}

	if (IS_ENABLED(CONFIG_ADXL362_TRIGGER)) {
		struct sensor_trigger trig = { .chan = SENSOR_CHAN_ACCEL_XYZ };

		trig.type = SENSOR_TRIG_THRESHOLD;
		if (sensor_trigger_set(dev, &trig, trigger_handler)) {
			printf("Trigger set error\n");
			return false;
		}

		trig.type = SENSOR_TRIG_DATA_READY;
		if (sensor_trigger_set(dev, &trig, trigger_handler)) {
			printf("Trigger set error\n");
		}
	}


  if (IS_ENABLED(CONFIG_ADXL362_TRIGGER)) {
    k_sem_take(&sem, K_FOREVER);
  } else {
    k_sleep(K_MSEC(1000));
    if (sensor_sample_fetch(dev) < 0) {
      printf("Sample fetch error\n");
      return false;
    }
  }

  if (sensor_channel_get(dev, SENSOR_CHAN_ACCEL_X, &accel[0]) < 0) {
    printf("Channel get error\n");
    return false;
  }

  if (sensor_channel_get(dev, SENSOR_CHAN_ACCEL_Y, &accel[1]) < 0) {
    printf("Channel get error\n");
    return false;
  }

  if (sensor_channel_get(dev, SENSOR_CHAN_ACCEL_Z, &accel[2]) < 0) {
    printf("Channel get error\n");
    return false;
  }

  // printf("x: %.1f, y: %.1f, z: %.1f (m/s^2)\n",
  // 	sensor_value_to_double(&accel[0]),
  // 	sensor_value_to_double(&accel[1]),
  // 	sensor_value_to_double(&accel[2]));

  bufx[begin_index] = (float)sensor_value_to_double(&accel[0]);
  bufy[begin_index] = (float)sensor_value_to_double(&accel[1]);
  bufz[begin_index] = (float)sensor_value_to_double(&accel[2]);
  begin_index++;
  if (begin_index >= BUFLEN) begin_index = 0;
  
  if (initial && begin_index >= 100) {
    initial = false;
  }

  if (initial) {
    return false;
  }

  int sample = 0;
  for (int i = 0; i < (length - 3); i += 3) {
    int ring_index = begin_index + sample - length / 3;
    if (ring_index < 0) {
      ring_index += BUFLEN;
    }
    input[i] = bufx[ring_index];
    input[i + 1] = bufy[ring_index];
    input[i + 2] = bufz[ring_index];
    sample++;
  }
  printk("ReadAccelerometer Has completed\n");
  return true;
  
}