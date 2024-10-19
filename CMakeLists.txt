cmake_minimum_required(VERSION 3.16)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(LOCAL_PROJECT_VERSION "0.0.${PATCH_VERSION}")

project(fashion_mnist VERSION ${LOCAL_PROJECT_VERSION})

configure_file(version.h.in version.h)

find_package(Eigen3 REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(fashion_mnist main.cpp)

set_target_properties(fashion_mnist PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

#target_link_libraries(fashion_mnist libeigen3)

install(TARGETS fashion_mnist RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT antvbx@gmail.com)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

include(CPack)
