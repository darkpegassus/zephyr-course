cmake_minimum_required(VERSION 3.20.0)

set(DTC_OVERLAY_FILE
    "${CMAKE_CURRENT_SOURCE_DIR}/boards/esp32_devkitc_esp32_procpu.overlay;${CMAKE_CURRENT_SOURCE_DIR}/app.overlay"
)

find_package(Zephyr REQUIRED HINTS "C:/Users/darkp/deps/zephyr/share/zephyr-package/cmake")
project(my_zephyr_app)

target_sources(app PRIVATE src/main.cpp)