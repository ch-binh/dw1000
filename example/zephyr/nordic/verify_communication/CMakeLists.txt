cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(basic)

# NORDIC SDK APP START
### INCLUDE ###

# own sources
target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/inc)
# common sources

# peripherals sources

# sensor driver sources
target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/../../../../inc)


### SOURCE ###
# own sources
FILE(GLOB app_sources src/*.c)
# common sources
FILE(GLOB dw1000_sources ../../../../src/*.c)
# peripherals sources

# sensor driver



### INCLUDE TO BUILD ###
target_sources(app PRIVATE ${app_sources})
target_sources(app PRIVATE ${dw1000_sources})

# NORDIC SDK APP END
