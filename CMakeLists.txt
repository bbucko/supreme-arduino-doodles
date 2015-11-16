cmake_minimum_required(VERSION 3.3.0)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME arduino)
project(${PROJECT_NAME})

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries)
link_directories(/Users/sg0209999/Documents/Arduino/libraries)


set(${CMAKE_PROJECT_NAME}_SKETCH arduino.ino)
set(${CMAKE_PROJECT_NAME}_BOARD uno)
set(${CMAKE_PROJECT_NAME}_PORT /dev/cu.usbmodem1421)

set(mega.build.mcu atmega2560)
set(mega.upload.protocol wiring)
set(mega.upload.speed 115200)


generate_arduino_firmware(${CMAKE_PROJECT_NAME})
