cmake_minimum_required(VERSION 3.8)

project("Intrusion Detection")

find_package(OpenCV REQUIRED)

#set(SOURCES ${PROJECT_SOURCE_DIR}/main.cpp)

file(GLOB SOURCES
     "*.h"
     "*.cpp"
)

message(SOURCES="${SOURCES}")

add_executable(ID ${SOURCES})

target_link_libraries(ID ${OpenCV_LIBS})