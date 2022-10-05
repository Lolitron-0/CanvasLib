if(PROJECT_IS_TOP_LEVEL)
  set(CMAKE_INSTALL_INCLUDEDIR include/CanvasLib CACHE PATH "")
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package CanvasLib)

install(
    DIRECTORY
    include/CanvasLib/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT CanvasLib_Development
)

install(
    TARGETS ${CMAKE_PROJECT_NAME}
    EXPORT CanvasLibTargets
    RUNTIME #
    COMPONENT CanvasLib_Runtime
    LIBRARY #
    COMPONENT CanvasLib_Runtime
    NAMELINK_COMPONENT CanvasLib_Development
    ARCHIVE #
    COMPONENT CanvasLib_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    CanvasLib_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
mark_as_advanced(CanvasLib_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${CanvasLib_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT CanvasLib_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${CanvasLib_INSTALL_CMAKEDIR}"
    COMPONENT CanvasLib_Development
)

install(
    EXPORT CanvasLibTargets
    NAMESPACE CanvasLib::
    DESTINATION "${CanvasLib_INSTALL_CMAKEDIR}"
    COMPONENT CanvasLib_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
