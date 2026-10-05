#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/sys/printk.h>

#include "../../drivers/sensor/led_sensor/led_sensor.h"

DEVICE_DECLARE(led_sensor);

int main(void)
{
    const struct device *sensor = DEVICE_GET(led_sensor);
    struct sensor_value val;

    if (!device_is_ready(sensor)) {
        printk("LED sensor not ready\n");
        return 0;
    }

    printk("LED sensor test\n");

    while (1) {
        led_sensor_set_value(sensor, 1);

        sensor_sample_fetch(sensor);
        printk("LED ON, value = 1\n");

        k_sleep(K_SECONDS(1));

        led_sensor_set_value(sensor, 0);

        sensor_channel_get(sensor, SENSOR_CHAN_LIGHT, &val);
        printk("LED OFF, value = %d\n", val.val1);

        k_sleep(K_SECONDS(1));
    }

    return 0;
}
