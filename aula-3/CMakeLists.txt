cmake_minimum_required(VERSION 3.12)
project(aula-3)

set(CMAKE_CXX_STANDARD 14)

# Get the system architecture
execute_process(COMMAND uname -m OUTPUT_VARIABLE ARCH OUTPUT_STRIP_TRAILING_WHITESPACE)

# If the architecture is x86_64, use the x86_64 flags
if(ARCH STREQUAL "x86_64")
    set(CXXFLAGS "-fmax-errors=2 -L/home/${USER}/cekeikon5/opencv2cpu/lib -I/home/${USER}/cekeikon5/opencv2cpu/include `pkg-config /home/${USER}/cekeikon5/opencv2cpu/lib/pkgconfig/opencv.pc --libs --cflags` -lcekeikon2 -L/home/${USER}/cekeikon5/cekeikon/bin -I/home/${USER}/cekeikon5/cekeikon/src -I${INCLUDE_PATH} -O3 -s")
else()
    set(CXXFLAGS "-fmax-errors=2 `pkg-config opencv --libs --cflags` -lcekeikon -L/home/${USER}/cekeikon5/cekeikon/bin -I/home/${USER}/cekeikon5/cekeikon/src -I${INCLUDE_PATH} -O3 -s")
endif()

set(INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/include)
set(SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/source)
set(OBJS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/objs)
set(CEKEIKON_PATH /home/${USER}/cekeikon5/cekeikon/bin)

set(OBJS_CAMCLIENT1 ${SRC_PATH}/device.cpp ${SRC_PATH}/client.cpp ${SRC_PATH}/camclient1.cpp)
set(OBJS_CAMSERVER1 ${SRC_PATH}/device.cpp ${SRC_PATH}/server.cpp ${SRC_PATH}/camserver1.cpp)
set(OBJS_CAMCLIENT2 ${SRC_PATH}/device.cpp ${SRC_PATH}/client.cpp ${SRC_PATH}/camclient2.cpp)
set(OBJS_CAMSERVER2 ${SRC_PATH}/device.cpp ${SRC_PATH}/server.cpp ${SRC_PATH}/camserver2.cpp)

add_library(LibDevice SHARED ${SRC_PATH}/device.cpp ${INCLUDE_PATH}/device.hpp)
add_library(LibClient SHARED ${SRC_PATH}/client.cpp ${INCLUDE_PATH}/client.hpp)
add_library(LibServer SHARED ${SRC_PATH}/server.cpp ${INCLUDE_PATH}/server.hpp)

add_executable(camclient1 ${OBJS_CAMCLIENT1})
target_include_directories(camclient1 PUBLIC ${INCLUDE_PATH})
target_include_directories(camclient1 PUBLIC ${CEKEIKON_PATH})
target_link_libraries(camclient1 -lcekeikon)
target_link_libraries(camclient1 ${CXXFLAGS})

add_executable(camserver1 ${OBJS_CAMSERVER1})
target_include_directories(camserver1 PUBLIC ${INCLUDE_PATH})
target_include_directories(camserver1 PUBLIC ${CEKEIKON_PATH})
target_link_libraries(camserver1 ${CXXFLAGS})

add_executable(camclient2 ${OBJS_CAMCLIENT2})
target_link_directories(camclient2 PUBLIC ${INCLUDE_PATH})
target_link_directories(camclient2 PUBLIC ${CEKEIKON_PATH})
target_link_libraries(camclient2 ${CXXFLAGS})

add_executable(camserver2 ${OBJS_CAMSERVER2})
target_link_directories(camserver2 PUBLIC ${INCLUDE_PATH})
target_link_directories(camserver2 PUBLIC ${CEKEIKON_PATH})
target_link_libraries(camserver2 ${CXXFLAGS})

add_custom_target(server DEPENDS camserver1 camserver2)
add_custom_target(client DEPENDS camclient1 camclient2)

add_custom_command(TARGET camclient1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:camclient1> ${SRC_PATH}/camclient1)

add_custom_command(TARGET camserver1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:camserver1> ${SRC_PATH}/camserver1)

add_custom_command(TARGET camclient2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:camclient2> ${SRC_PATH}/camclient2)

add_custom_command(TARGET camserver2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:camserver2> ${SRC_PATH}/camserver2)

add_custom_target(make_all DEPENDS server client)

add_custom_target(make_clean
    COMMAND ${CMAKE_COMMAND} -E remove ${SRC_PATH}/*.o ${SRC_PATH}/camclient1 ${SRC_PATH}/camclient2 ${SRC_PATH}/camserver1 ${SRC_PATH}/camserver2)
