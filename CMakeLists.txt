cmake_minimum_required(VERSION 3.16)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(LOCAL_PROJECT_VERSION "0.0.${PATCH_VERSION}")

project(print_ip VERSION ${LOCAL_PROJECT_VERSION})

configure_file(version.h.in version.h)

add_executable(print_ip main.cpp)

set_target_properties(helloworld_cli PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT antvbx@gmail.com)
