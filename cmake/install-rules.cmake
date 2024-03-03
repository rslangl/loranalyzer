if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/LoRaNALYZER-${PROJECT_VERSION}"
      CACHE STRING ""
  )
  set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package LoRaNALYZER)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT LoRaNALYZER_Development
)

install(
    TARGETS LoRaNALYZER_LoRaNALYZER
    EXPORT LoRaNALYZERTargets
    RUNTIME #
    COMPONENT LoRaNALYZER_Runtime
    LIBRARY #
    COMPONENT LoRaNALYZER_Runtime
    NAMELINK_COMPONENT LoRaNALYZER_Development
    ARCHIVE #
    COMPONENT LoRaNALYZER_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    LoRaNALYZER_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE STRING "CMake package config location relative to the install prefix"
)
set_property(CACHE LoRaNALYZER_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(LoRaNALYZER_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${LoRaNALYZER_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT LoRaNALYZER_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${LoRaNALYZER_INSTALL_CMAKEDIR}"
    COMPONENT LoRaNALYZER_Development
)

install(
    EXPORT LoRaNALYZERTargets
    NAMESPACE LoRaNALYZER::
    DESTINATION "${LoRaNALYZER_INSTALL_CMAKEDIR}"
    COMPONENT LoRaNALYZER_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
