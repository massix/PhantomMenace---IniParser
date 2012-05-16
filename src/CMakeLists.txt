# src folder

include_directories(.)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS ${libPmIniParser_SOURCE_DIR}/include/*.h)

set(MajorVersion  1)
set(BinaryVersion 4)
set(MinorVersion  3)
set(FullVersion ${MajorVersion}.${BinaryVersion}.${MinorVersion})

add_definitions(
    -Wall
    -DMAJORVERSION=${MajorVersion}
    -DBINARYVERSION=${BinaryVersion}
    -DMINORVERSION=${MinorVersion})

find_package(Boost COMPONENTS regex-mt)

include_directories(${Boost_INCLUDE_DIRS} ${libPmIniParser_SOURCE_DIR}/include)

add_library(PmIniParser SHARED ${SOURCES})
add_library(PmIniParser-static STATIC ${SOURCES})

target_link_libraries(PmIniParser ${Boost_LIBRARIES})
target_link_libraries(PmIniParser-static ${Boost_LIBRARIES})

# Set the version of the library
set_target_properties(PmIniParser PmIniParser-static
    PROPERTIES SOVERSION ${MajorVersion} VERSION ${FullVersion})

# Name the static library as the dynamic one
set_target_properties(PmIniParser-static
    PROPERTIES OUTPUT_NAME PmIniParser)

install(TARGETS PmIniParser LIBRARY DESTINATION lib)
install(TARGETS PmIniParser-static ARCHIVE DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include) 

