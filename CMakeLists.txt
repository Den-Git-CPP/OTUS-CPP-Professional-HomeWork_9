cmake_minimum_required(VERSION 3.15)

if ($ENV{GITHUB_RUN_NUMBER})
    project (async VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
else()
    project (async VERSION 0.0.1)
endif()

configure_file(version.h.in ${PROJECT_SOURCE_DIR}/version.h)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_subdirectory(source)
add_subdirectory(example)
add_subdirectory(test)