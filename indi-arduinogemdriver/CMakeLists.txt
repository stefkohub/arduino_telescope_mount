PROJECT(indi-arduino_gem_driver C CXX)
cmake_minimum_required(VERSION 2.8)

include(GNUInstallDirs)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/")

set(BIN_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/bin")

set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")

find_package(INDI REQUIRED)
find_package(Nova REQUIRED)

# these will be used to set the version number in config.h and our driver's xml file
set(CDRIVER_VERSION_MAJOR 0)
set(CDRIVER_VERSION_MINOR 2)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h )
# do the replacement in the driver's xml file
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}//indi-arduinogemdriver.xml.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/indi-arduinogemdriver.xml
)
set(INDI_DATA_DIR "${CMAKE_INSTALL_PREFIX}/share/indi")

include_directories( ${CMAKE_CURRENT_BINARY_DIR})
include_directories( ${CMAKE_CURRENT_SOURCE_DIR})
include_directories( ${INDI_INCLUDE_DIR})
# include_directories( ${INDI_INCLUDE_DIR}/drivers/telescope)
include_directories( ${NOVA_INCLUDE_DIR})
include_directories( ${NOVA_INCLUDE_DIR}/..)
include(CMakeCommon)

set(arduino_gem_driver_SRCS
   ${CMAKE_CURRENT_SOURCE_DIR}/indi_arduino_gem_driver.cpp)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(arduino_gem_driver_SRCS ${arduino_gem_driver_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/mach_gettime.cpp)
endif()

add_executable(indi_arduino_gem_driver ${arduino_gem_driver_SRCS})

target_link_libraries(indi_arduino_gem_driver ${INDI_LIBRARIES} ${INDI_DRIVER_LIBRARIES} ${NOVA_LIBRARIES})

if (CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "arm*")
target_link_libraries(indi_arduino_gem_driver rt)
endif (CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "arm*")

install(TARGETS indi_arduino_gem_driver RUNTIME DESTINATION bin )

install( FILES  ${CMAKE_CURRENT_BINARY_DIR}/indi-arduinogemdriver.xml DESTINATION ${INDI_DATA_DIR})


