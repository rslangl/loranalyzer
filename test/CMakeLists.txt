cmake_minimum_required(VERSION 3.14)

project(LoRaNALYZERTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(LoRaNALYZER REQUIRED)
  enable_testing()
endif()

find_package(Catch2 REQUIRED)
include(Catch)

# ---- Tests ----

add_executable(LoRaNALYZER_test source/LoRaNALYZER_test.cpp)
target_link_libraries(
    LoRaNALYZER_test PRIVATE
    LoRaNALYZER::LoRaNALYZER
    Catch2::Catch2WithMain
)
target_compile_features(LoRaNALYZER_test PRIVATE cxx_std_20)

catch_discover_tests(LoRaNALYZER_test)

# ---- End-of-file commands ----

add_folders(Test)
