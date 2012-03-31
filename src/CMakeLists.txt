# src folder

include_directories(.)

file (GLOB SOURCES *.cpp)

add_definitions(-Wall -dynamiclib)

link_libraries(boost_regex-mt)
add_library(PmIniParser SHARED ${SOURCES})
add_library(PmIniParser-static STATIC ${SOURCES})
