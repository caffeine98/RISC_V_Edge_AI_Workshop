/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <metal/cpu.h>
#include <metal/led.h>
#include <metal/button.h>
#include <metal/switch.h>

#include "scaler.h"
#include "svm_model.h"

#define RTC_FREQ    32768

#define x1 2.36992324e-16
#define x2 1.00000000e+00
#define x3 -2.22044605e-16
#define b -5.820766091346741e-11

void scale_input(double *x) {
	for (int i = 0; i < NUM_FEATURES; ++i) {
		x[i] = (x[i] - mean[i]) / scale[i];
	}
}

float predict(float in1, float in2, float in3) {
	return x1 * in1 + x2 * in2 + x3 * in3 + b;
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
	float rDSpend = 165349.2;
	float aDSpend = 136897.8;
	float mKSpend = 471784.1;

	float profit; // 192261.83

	profit = predict(rDSpend, aDSpend, mKSpend);
	printf("The profit is: ");
	print_float(profit);
	printf("\n");

    return 0;
}







