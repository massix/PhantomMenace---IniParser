# src folder

include_directories(.)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)

add_definitions(-Wall -dynamiclib)

link_libraries(boost_regex-mt)
add_library(PmIniParser SHARED ${SOURCES})
add_library(PmIniParser-static STATIC ${SOURCES})

# Set the version of the library
set_target_properties(PmIniParser PmIniParser-static
    PROPERTIES SOVERSION 1 VERSION 1.3.24)

install(TARGETS PmIniParser LIBRARY DESTINATION lib)
install(TARGETS PmIniParser-static ARCHIVE DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include) 

