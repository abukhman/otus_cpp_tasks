cmake_minimum_required(VERSION 3.16)

set(LOCAL_PROJECT_VERSION "0.0.${PATCH_VERSION}")

project(helloworld VERSION ${LOCAL_PROJECT_VERSION})

add_executable(helloworld_cli main.cpp)

set_target_properties(helloworld_cli PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
)

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT antvbx@gmail.com)

include(CMakePrintHelpers)



set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

include(CPack)

