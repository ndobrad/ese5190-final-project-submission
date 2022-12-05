
cmake_minimum_required(VERSION 3.12)

project(no_ml_exmample C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)


add_executable(no_ml_example_exec "")

target_include_directories(no_ml_example_exec
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/.
  )

set_target_properties(
  no_ml_example_exec
  PROPERTIES
  COMPILE_FLAGS -fno-rtti
  COMPILE_FLAGS -fno-exceptions
  COMPILE_FLAGS -fno-threadsafe-statics
  COMPILE_FLAGS -nostdlib
)

target_sources(no_ml_example_exec
  PRIVATE
  #${CMAKE_CURRENT_LIST_DIR}/detection_responder.cpp
  ${CMAKE_CURRENT_LIST_DIR}/image_provider.cpp
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
  ${CMAKE_CURRENT_LIST_DIR}/main_functions.cpp
  #${CMAKE_CURRENT_LIST_DIR}/model_settings.cpp
  #${CMAKE_CURRENT_LIST_DIR}/tensorflow/lite/micro/tools/make/downloads/person_model_int8/person_detect_model_data.cpp
  #${CMAKE_CURRENT_LIST_DIR}/detection_responder.h
  ${CMAKE_CURRENT_LIST_DIR}/image_provider.h
  ${CMAKE_CURRENT_LIST_DIR}/main_functions.h
  #${CMAKE_CURRENT_LIST_DIR}/model_settings.h
  #${CMAKE_CURRENT_LIST_DIR}/person_detect_model_data.h
  )

target_link_libraries(
  no_ml_example_exec
  #pico-tflmicro
  hardware_pwm
  hardware_pio
  pico_stdlib
  arducam_hm01b0
  LCD_st7735
)

pico_enable_stdio_uart(no_ml_example_exec 0)
pico_enable_stdio_usb(no_ml_example_exec 1)

pico_add_extra_outputs(no_ml_example_exec)

