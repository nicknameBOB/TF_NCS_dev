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

#include <device.h>
#include <drivers/sensor.h>
#include <stdio.h>
#include <string.h>
#include <zephyr.h>

#include "motion/motion.h"
#include "adxl362/adxl362.h"
#include <logging/log.h>

#define DT_DRV_COMPAT adi_adxl362

#include <kernel.h>

#include <init.h>
#include <drivers/gpio.h>
#include <sys/byteorder.h>
#include <sys/__assert.h>
#include <drivers/spi.h>

#define BUFLEN 300
int begin_index = 0;
struct device* sensor = NULL;
int current_index = 0;

float bufx[BUFLEN] = {0.0f};
float bufy[BUFLEN] = {0.0f};
float bufz[BUFLEN] = {0.0f};

bool initial = true;


TfLiteStatus SetupAccelerometer(tflite::ErrorReporter* error_reporter) {
  sensor = device_get_binding(DT_LABEL(DT_INST(0, adi_adxl362)));
  if (sensor == NULL) {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Failed to get accelerometer, label: %s\n",
                         DT_LABEL(DT_INST(0, adi_adxl362)));
  } else {
    TF_LITE_REPORT_ERROR(error_reporter, "Got accelerometer, label: %s\n",
                         DT_LABEL(DT_INST(0, adi_adxl362)));
  }
  return kTfLiteOk;
}


bool ReadAccelerometer(tflite::ErrorReporter* error_reporter, float* input,
                       int length) {
  int rc;
  struct sensor_value accel[3];
  int samples_count;

  rc = sensor_sample_fetch(sensor);
  TF_LITE_REPORT_ERROR(error_reporter, "rc = %d \n", rc);
  // if (rc < 0) {
  //   TF_LITE_REPORT_ERROR(error_reporter, "Fetch failed\n");
  //   return false;
  // }
  // // skip if there is no data
  // if (!rc) {
  //   return false;
  // }
  int ab = sensor_channel_get(sensor, SENSOR_CHAN_ACCEL_X, &accel[0]);
  TF_LITE_REPORT_ERROR(error_reporter, "ab = %d \n", ab);

  samples_count = rc;
  TF_LITE_REPORT_ERROR(error_reporter, "samples_count = %d \n", samples_count);
  for (int i = 0; i < samples_count; i++) {
    rc = sensor_channel_get(sensor, SENSOR_CHAN_ACCEL_X, &accel[0]);
    rc = sensor_channel_get(sensor, SENSOR_CHAN_ACCEL_Y, &accel[1]);
    rc = sensor_channel_get(sensor, SENSOR_CHAN_ACCEL_Z, &accel[2]);
    TF_LITE_REPORT_ERROR(error_reporter, "rc = %d \n", rc);
    if (rc < 0) {
      TF_LITE_REPORT_ERROR(error_reporter, "ERROR: Update failed: %d\n", rc);
      return false;
    }
    bufx[begin_index] = (float)sensor_value_to_double(&accel[0]);
    bufy[begin_index] = (float)sensor_value_to_double(&accel[1]);
    bufz[begin_index] = (float)sensor_value_to_double(&accel[2]);
    begin_index++;
    if (begin_index >= BUFLEN) begin_index = 0;
  }

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
  return true;
}

// /* Forward declaration of functions */
// static void motion_handler(motion_data_t  motion_data);

// K_SEM_DEFINE(sem, 0, 1);

// static void trigger_handler(struct device *dev, struct sensor_trigger *trig)
// {
// 	switch (trig->type) {
// 	case SENSOR_TRIG_DATA_READY:
// 		if (sensor_sample_fetch(dev) < 0) {
// 			printf("Sample fetch error\n");
// 			return;
// 		}
// 		k_sem_give(&sem);
// 		break;
// 	case SENSOR_TRIG_THRESHOLD:
// 		printf("Threshold trigger\n");
// 		break;
// 	default:
// 		printf("Unknown trigger\n");
// 	}
// }
