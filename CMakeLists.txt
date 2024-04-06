cmake_minimum_required(VERSION 3.27)
project(code_generator)

set(CMAKE_CXX_STANDARD 20)

set(OPENSSL_ROOT_DIR "OpenSSL")

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(code_generator main.cpp)

target_link_libraries(code_generator OpenSSL::Crypto)

file(COPY ${OPENSSL_ROOT_DIR}/bin/libcrypto-3-x64.dll DESTINATION ${CMAKE_BINARY_DIR})
