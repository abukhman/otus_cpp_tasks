cmake_minimum_required(VERSION 3.16)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(LOCAL_PROJECT_VERSION "0.0.${PATCH_VERSION}")

#find_package(Boost COMPONENTS system REQUIRED)
#find_package(Threads)
#include_directories(${Boost_INCLUDE_DIR})

project(async VERSION ${LOCAL_PROJECT_VERSION})

configure_file(version.h.in version.h)

add_executable(bulk_server main.cpp block.cpp)

set_target_properties(bulk_server PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

target_link_libraries(bulk_server
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS bulk_server RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT antvbx@gmail.com)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

include(CPack)
