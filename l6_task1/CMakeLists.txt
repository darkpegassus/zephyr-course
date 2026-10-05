cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(l6_task1)

target_sources(app PRIVATE src/main.c)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../drivers/sensor/led_sensor
                 ${CMAKE_CURRENT_BINARY_DIR}/led_sensor)
