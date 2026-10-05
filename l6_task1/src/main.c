#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/sys/printk.h>

extern const struct device *led_sensor_dev;

int main(void)
{
    const struct device *sensor = led_sensor_dev;
    struct sensor_value val;

    if (!device_is_ready(sensor)) {
        printk("LED sensor not ready\n");
        return 0;
    }

    printk("LED sensor test\n");

    while (1) {
        sensor_sample_fetch(sensor);
        printk("LED ON\n");

        k_sleep(K_SECONDS(1));

        sensor_channel_get(sensor, SENSOR_CHAN_LIGHT, &val);
        printk("LED OFF\n");

        k_sleep(K_SECONDS(1));
    }

    return 0;
}
