cmake_minimum_required(VERSION 3.16)

project(helloworld)

add_executable(helloworld_cli main.cpp)

set_target_properties(helloworld_cli PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
)

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT antvbx@gmail.com)

include(CPack)

