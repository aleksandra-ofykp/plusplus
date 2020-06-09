cmake_minimum_required (VERSION 3.8)

project (ServChat)

add_executable(ServChat ServerQ.cpp)
add_executable(Chat ClientQ.cpp)
add_executable(ClientHC_test ClientQ.cpp ClientHC_test.cpp)
enable_testing()
add_test(ClientHC_test ClientHC_test)
