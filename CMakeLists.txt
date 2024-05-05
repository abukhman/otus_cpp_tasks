cmake_minimum_required(VERSION 3.16)

set(LOCAL_PROJECT_VERSION "0.0.${PATCH_VERSION}")

project(helloworld VERSION ${LOCAL_PROJECT_VERSION})

configure_file(version.h.in version.h)

add_executable(helloworld_cli main.cpp)
add_library(mylibversion mylibversion.cpp)
add_executable(test_version test_version.cpp)

set_target_properties(helloworld_cli PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
)

target_link_libraries(helloworld_cli mylibversion)

find_package(GTest REQUIRED)
target_link_libraries(test_version GTest::gtest GTest::gtest_main mylibversion)

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT antvbx@gmail.com)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

include(CPack)

enable_testing()

add_test(test_version test_version)
