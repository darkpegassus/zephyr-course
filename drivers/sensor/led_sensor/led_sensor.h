#ifndef LED_SENSOR_H
#define LED_SENSOR_H

#include <zephyr/device.h>

int led_sensor_set_value(const struct device *dev, int value);

#endif
