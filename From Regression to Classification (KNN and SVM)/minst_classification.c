/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <metal/cpu.h>
#include <metal/led.h>
#include <metal/button.h>
#include <metal/switch.h>
#include <math.h>
#include <stdint.h>

#include "scaler.h"
#include "svm_model.h"
#include "test_images.h"

#define RTC_FREQ    32768

#define x1 2.36992324e-16
#define x2 1.00000000e+00
#define x3 -2.22044605e-16
#define b -5.820766091346741e-11

void scale_input(int8_t *x) {
	for (int i = 0; i < NUM_FEATURES; ++i) {
		x[i] = (x[i] - (mean[i] * mean_scale)) / (scale[i] * scale_scale);
	}
}

int predict(int8_t *x) {
	int best_class = 0;
	float max_score = -INFINITY;

	for (int c = 0; c < NUM_CLASSES; c++) {
		float score = bias[c] * bias_scale;
		for (int i = 0; i < NUM_FEATURES; i++) {
			score += weights[c][i] * x[i] * weight_scale;
		}
		if (score > max_score) {
			max_score = score;
			best_class = c;
		}
	}

	return best_class;
}

// VSDSquadron can't print float values, so we use this function
void print_float(float value) {
	 int int_part = (int)value;
	 int frac_part = (int)((value - int_part) * 100); //2 decimal places
	 if (frac_part < 0)
		 frac_part = -frac_part;
	 printf("%d.%02d", int_part, frac_part);

}

int main (void)
{
	for (int i = 0; i < NUM_TEST_IMAGES; i++) {
		scale_input(test_images[i]);
		int predicted = predict(test_images[i]);
		int actual = test_labels[i];
		printf("Image: %d, Predicted: %d, Actual: %d\n", i, predicted, actual);
	}

	    return 0;
}







