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
#include <logging/log.h>




static int accelerometer_poll(motion_acceleration_data_t *sensor_data)
{
	if (sensor_data == NULL) {
		return -EINVAL;
	}

	int err;

	struct sensor_value accel_data[3];

	/* If using the ADXL362 driver, all channels must be fetched */
	if (IS_ENABLED(CONFIG_ADXL362)) {
		err = sensor_sample_fetch_chan(accel_dev,
						SENSOR_CHAN_ALL);
	} else {
		err = sensor_sample_fetch_chan(accel_dev,
						SENSOR_CHAN_ACCEL_XYZ);
	}

	if (err) {
		LOG_ERR("sensor_sample_fetch failed");
		return err;
	}

	err = sensor_channel_get(accel_dev,
			SENSOR_CHAN_ACCEL_X, &accel_data[0]);

	if (err) {
		LOG_ERR("sensor_channel_get failed");
		return err;
	}

	err = sensor_channel_get(accel_dev,
			SENSOR_CHAN_ACCEL_Y, &accel_data[1]);

	if (err) {
		LOG_ERR("sensor_channel_get failed");
		return err;
	}
	err = sensor_channel_get(accel_dev,
			SENSOR_CHAN_ACCEL_Z, &accel_data[2]);

	if (err) {
		LOG_ERR("sensor_channel_get failed");
		return err;
	}

	sensor_data->x = sensor_value_to_double(&accel_data[0]);
	sensor_data->y = sensor_value_to_double(&accel_data[1]);
	sensor_data->z = sensor_value_to_double(&accel_data[2]);

	return 0;
}














#define BUFLEN 300
int begin_index = 0;
struct device* sensor = NULL;
int current_index = 0;

float bufx[BUFLEN] = {0.0f};
float bufy[BUFLEN] = {0.0f};
float bufz[BUFLEN] = {0.0f};

bool initial = true;

TfLiteStatus SetupAccelerometer(tflite::ErrorReporter* error_reporter) {
  sensor = device_get_binding(CONFIG_ADXL362);
  if (sensor == NULL) {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Failed to get accelerometer, label: %s\n",
                         CONFIG_ADXL362);
  } else {
    TF_LITE_REPORT_ERROR(error_reporter, "Got accelerometer, label: %s\n",
                         CONFIG_ADXL362);
  }
  return kTfLiteOk;
}

bool ReadAccelerometer(tflite::ErrorReporter* error_reporter, float* input,
                       int length) {
  int rc;
  struct sensor_value accel[3];
  int samples_count;

  rc = sensor_sample_fetch(sensor);
  if (rc < 0) {
    TF_LITE_REPORT_ERROR(error_reporter, "Fetch failed\n");
    return false;
  }
  // skip if there is no data
  if (!rc) {
    return false;
  }

  samples_count = rc;
  for (int i = 0; i < samples_count; i++) {
    rc = sensor_channel_get(sensor, SENSOR_CHAN_ACCEL_XYZ, accel);
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
