cmake_minimum_required(VERSION 3.27)
project(xml2pdf C)

set(CMAKE_C_STANDARD 11)

find_package(LibXml2 REQUIRED)
find_package(LibXslt REQUIRED)

include_directories(${LIBXML2_INCLUDE_DIR})
include_directories(${LIBXSLT_INCLUDE_DIR})

add_executable(xml2pdf src/main.c)

target_link_libraries(xml2pdf
        ${LIBXML2_LIBRARIES}
        ${LIBXSLT_LIBRARIES}
)
