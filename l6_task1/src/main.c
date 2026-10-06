#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/shell/shell.h>
#include <zephyr/sys/printk.h>

#include "../../drivers/sensor/led_sensor/led_sensor.h"

DEVICE_DECLARE(led_sensor);

static const struct device *sensor = DEVICE_GET(led_sensor);

static int cmd_sensor_fetch(const struct shell *sh,
                            size_t argc, char **argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    int ret = sensor_sample_fetch(sensor);

    if (ret == 0) {
        shell_print(sh, "Sensor fetch successful");
    } else {
        shell_error(sh, "Fetch failed: %d", ret);
    }

    return ret;
}

static int cmd_sensor_read(const struct shell *sh,
                           size_t argc, char **argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    struct sensor_value val;
    int ret = sensor_channel_get(sensor, SENSOR_CHAN_LIGHT, &val);

    if (ret == 0) {
        shell_print(sh, "Sensor value: %d.%06d",
                    val.val1, val.val2);
    } else {
        shell_error(sh, "Read failed: %d", ret);
    }

    return ret;
}

static int cmd_sensor_info(const struct shell *sh,
                           size_t argc, char **argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    shell_print(sh, "Device: %s", sensor->name);
    shell_print(sh, "Ready: %s",
                device_is_ready(sensor) ? "yes" : "no");

    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sensor_cmds,
    SHELL_CMD(fetch, NULL, "Fetch sensor sample", cmd_sensor_fetch),
    SHELL_CMD(read, NULL, "Read sensor value", cmd_sensor_read),
    SHELL_CMD(info, NULL, "Show sensor information", cmd_sensor_info),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor, &sensor_cmds, "Sensor commands", NULL);

int main(void)
{
    printk("L7 Task 1 - Sensor Shell\n");

    return 0;
}
