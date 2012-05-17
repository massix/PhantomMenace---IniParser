# test folder

include_directories(. ..)

file (GLOB SOURCES *.cpp)

find_package(CppUnit REQUIRED)

link_directories(${PROJECT_BINARY_DIR})
add_executable(unittest
    main.cpp
    ParserTest.cpp)

target_link_libraries(unittest 
    ${CPPUNIT_LIBRARY} 
    PmIniParser)

#link_libraries(PmIniParser)

#add_executable(simple_element simpleElement.cpp)
#add_executable(double_element doubleElement.cpp)
#add_executable(repeating_attribute repeatingAttribute.cpp)
#add_executable(multiple_elements multipleElements.cpp)
#add_executable(parse_from_file parseFromFile.cpp)
#add_executable(spaces_around spacesAround.cpp)

#enable_testing()
#add_test(SimpleElement simple_element)
#add_test(DoubleElement double_element)
#add_test(MultipleElements multiple_elements)
#add_test(RepeatingAttribute repeating_attribute)
#add_test(ParseFromFile parse_from_file)
#add_test(SpacesAround spaces_around)
