# test folder

include_directories(. ../src)

file (GLOB SOURCES *.cpp)

link_directories(${PROJECT_BINARY_DIR})
link_libraries(PmIniParser)

add_executable(simple_element simpleElement.cpp)
add_executable(double_element doubleElement.cpp)
add_executable(repeating_attribute repeatingAttribute.cpp)

enable_testing()
add_test(SimpleElement simple_element)
add_test(DoubleElement double_element)
add_test(RepeatingAttribute repeating_attribute)
