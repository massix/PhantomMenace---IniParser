# src folder

include_directories(.)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)

add_definitions(-Wall -dynamiclib)

link_libraries(boost_regex-mt)
add_library(PmIniParser SHARED ${SOURCES})
add_library(PmIniParser-static STATIC ${SOURCES})

install(TARGETS PmIniParser LIBRARY DESTINATION lib)
install(TARGETS PmIniParser-static ARCHIVE DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include) 

