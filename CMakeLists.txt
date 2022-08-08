cmake_minimum_required(VERSION 3.15)

if ($ENV{GITHUB_RUN_NUMBER})
    project (Async VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
else()
    project (Async VERSION 0.0.1)
endif()

configure_file(version.h.in version.h)

find_package(Threads)
list(APPEND EXTRA_LINKS ${CMAKE_THREAD_LIBS_INIT})


add_executable(${PROJECT_NAME}
    "main.cpp"
)

file(GLOB async_lib_all
 "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.*"
)
add_library(async_lib SHARED ${async_lib_all}
)

# add_executable(g_test_bulk 
# test/g_test_bulk.h 
# test/test.h 
# test/test.cpp)

# set_target_properties(async 
# g_test_async
# PROPERTIES
#     CXX_STANDARD 20
#     CXX_STANDARD_REQUIRED ON
# )

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
set_target_properties(async_lib PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(${PROJECT_NAME}
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib/"
)
target_include_directories(async_lib
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib/"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    async_lib
    ${EXTRA_LINKS}
)

# target_link_libraries(g_test_bulk
#    gtest gtest_main
# )

if (MSVC)
    target_compile_options(${PROJECT_NAME} 
    PRIVATE
    /EHsc /W4 /WX
        )    
    target_compile_options(async_lib 
    PRIVATE
    /EHsc /W4 /WX
    )
    # target_compile_options(g_test_bulk 
    # PRIVATE
    # /EHsc /W4 /WX
    # )   
 else ()
    target_compile_options(${PROJECT_NAME} 
    PRIVATE
    -Wall -Wextra -pedantic -Werror
        )
    target_compile_options(async_lib 
    PRIVATE
    -Wall -Wextra -pedantic -Werror
    )
    # target_compile_options(g_test_bulk 
    # PRIVATE
    # -Wall -Wextra -pedantic -Werror
    #     )
endif()

add_subdirectory(test)
# enable_testing()
# add_test(test_version g_test_bulk)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
 set(CPACK_PACKAGE_CONTACT madim-neodart@rambler.ru)
include(CPack)



