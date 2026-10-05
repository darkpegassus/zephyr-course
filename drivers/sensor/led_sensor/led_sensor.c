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

    led_sensor_data.value.val1 = 0;
    led_sensor_data.value.val2 = 0;

    return gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
}

/* Custom extension API */
int led_sensor_set_value(const struct device *dev, int value)
{
    ARG_UNUSED(dev);

    led_sensor_data.value.val1 = value;

    return 0;
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

    *val = led_sensor_data.value;

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

DEVICE_DECLARE(led_sensor);