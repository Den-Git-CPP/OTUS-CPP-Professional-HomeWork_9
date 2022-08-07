cmake_minimum_required(VERSION 3.15)

# Setup testing
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()
option(ENABLE_UNIT_TESTS "Enable unit tests" ON)
message(STATUS "Enable testing: ${ENABLE_UNIT_TESTS}")
if(ENABLE_UNIT_TESTS)
  # the following code to fetch googletest
  # is inspired by and adapted after:
  #   - https://cmake.org/cmake/help/v3.11/module/FetchContent.html
  include(FetchContent)

  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
  )

  FetchContent_GetProperties(googletest)

  if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    # Prevent GoogleTest from overriding our compiler/linker options
    # when building with Visual Studio
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    # Prevent GoogleTest from using PThreads
    set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)

    # adds the targers: gtest, gtest_main, gmock, gmock_main
    add_subdirectory(
      ${googletest_SOURCE_DIR}
      ${googletest_BINARY_DIR}
      )

    # Silence std::tr1 warning on MSVC
    if(MSVC)
      foreach(_tgt gtest gtest_main gmock gmock_main)
        target_compile_definitions(${_tgt}
          PRIVATE
            "_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING"
          )
      endforeach()
    endif()
  endif()
endif()

add_executable(tests test.cpp
                     ${CMAKE_SOURCE_DIR}/source/Bulk.cpp
                     ${CMAKE_SOURCE_DIR}/source/InterpreterCmd.cpp
                     ${CMAKE_SOURCE_DIR}/source/ContextCmd.cpp
                     ${CMAKE_SOURCE_DIR}/source/Metrics.cpp
                     ${CMAKE_SOURCE_DIR}/include/Bulk.h
                     ${CMAKE_SOURCE_DIR}/include/InterpreterCmd.h
                     ${CMAKE_SOURCE_DIR}/include/ContextCmd.h
                     ${CMAKE_SOURCE_DIR}/include/Observer.h
                     ${CMAKE_SOURCE_DIR}/include/StreamWriter.h
                     ${CMAKE_SOURCE_DIR}/include/Metrics.h
                     )

target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/inc)

if (MSVC)
    set_target_properties(tests PROPERTIES
                                CXX_STANDARD 14
                                CXX_STANDARD_REQUIRED ON
    )
else ()
    set_target_properties(tests PROPERTIES
                                CXX_STANDARD 14
                                CXX_STANDARD_REQUIRED ON
                                COMPILE_OPTIONS -Wpedantic -Wall -Wextra
    )
endif ()

target_link_libraries(tests gtest)

enable_testing()

add_test(context_test_case tests)
add_test(bulk_test_case tests)
