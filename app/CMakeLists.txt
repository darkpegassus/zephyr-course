cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS "C:/Users/darkp/deps/zephyr/share/zephyr-package/cmake")
project(my_zephyr_app)

target_sources(app PRIVATE src/main.cpp)