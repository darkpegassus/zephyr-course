#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>

#define LED_NODE DT_ALIAS(led0)

#if !DT_NODE_HAS_STATUS(LED_NODE, okay)
#error "led0 alias is required"
#endif

static const struct gpio_dt_spec led =
    GPIO_DT_SPEC_GET(LED_NODE, gpios);

struct led_sensor_data {
    struct sensor_value value;
};

static struct led_sensor_data led_sensor_data;

static int led_sensor_init(const struct device *dev)
{
    ARG_UNUSED(dev);

    if (!gpio_is_ready_dt(&led)) {
        return -ENODEV;
    }

    return gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
}

static int led_sensor_sample_fetch(const struct device *dev,
                                   enum sensor_channel chan)
{
    ARG_UNUSED(dev);
    ARG_UNUSED(chan);

    return gpio_pin_set_dt(&led, 1);
}

static int led_sensor_channel_get(const struct device *dev,
                                  enum sensor_channel chan,
                                  struct sensor_value *val)
{
    ARG_UNUSED(dev);
    ARG_UNUSED(chan);
    ARG_UNUSED(val);

    return gpio_pin_set_dt(&led, 0);
}

static const struct sensor_driver_api led_sensor_api = {
    .sample_fetch = led_sensor_sample_fetch,
    .channel_get = led_sensor_channel_get,
};

DEVICE_DEFINE(led_sensor, "led_sensor",
              led_sensor_init, NULL,
              &led_sensor_data, NULL,
              POST_KERNEL,
              CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
              &led_sensor_api);

const struct device *led_sensor_dev = DEVICE_GET(led_sensor);
