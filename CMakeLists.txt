cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    LoRaNALYZER
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    LoRaNALYZER_LoRaNALYZER
    source/config.cpp
    source/device.cpp
    #source/LoRaNALYZER.cpp
)
add_library(LoRaNALYZER::LoRaNALYZER ALIAS LoRaNALYZER_LoRaNALYZER)

include(GenerateExportHeader)
generate_export_header(
    LoRaNALYZER_LoRaNALYZER
    BASE_NAME LoRaNALYZER
    EXPORT_FILE_NAME export/LoRaNALYZER/LoRaNALYZER_export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(LoRaNALYZER_LoRaNALYZER PUBLIC LORANALYZER_STATIC_DEFINE)
endif()

set_target_properties(
    LoRaNALYZER_LoRaNALYZER PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME LoRaNALYZER
    OUTPUT_NAME LoRaNALYZER
)

target_include_directories(
    LoRaNALYZER_LoRaNALYZER ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    LoRaNALYZER_LoRaNALYZER SYSTEM
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(LoRaNALYZER_LoRaNALYZER PUBLIC cxx_std_20)

find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(SoapySDR REQUIRED)

target_link_libraries(
  LoRaNALYZER_LoRaNALYZER PRIVATE
  fmt::fmt
  spdlog::spdlog
  SoapySDR
  fftw3)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Examples ----

if(PROJECT_IS_TOP_LEVEL)
  option(BUILD_EXAMPLES "Build examples tree." "${LoRaNALYZER_DEVELOPER_MODE}")
  if(BUILD_EXAMPLES)
    add_subdirectory(example)
  endif()
endif()

# ---- Developer mode ----

if(NOT LoRaNALYZER_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of LoRaNALYZER"
  )
endif()

include(cmake/dev-mode.cmake)
