# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(hello_world)

target_sources(app PRIVATE src/main.c)

target_sources(app PRIVATE src/led_control.c)

target_sources(app PRIVATE src/button_handler.c)

target_sources(app PRIVATE src/watchdog_management.c)
