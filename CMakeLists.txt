### simplified copy of the CMakeLists.txt file of the HElib examples
cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)
## Use -std=c++17 as default.
set(CMAKE_CXX_STANDARD 17)
## Disable C++ extensions
set(CMAKE_CXX_EXTENSIONS OFF)
## Require full C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(HELibDemo VERSION 1.0)
add_executable(client_test client.cpp)
add_executable(server_test server.cpp)
find_package(helib ${HELIB_VERSION} REQUIRED)
target_link_libraries(client_test helib)
target_link_libraries(server_test helib)
