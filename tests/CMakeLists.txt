set(TARGET_NAME matrix_tests)
add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME} PRIVATE
    test_matrix.cpp 
    ../src/matrix.h
)
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

if(DEFINED ENV{HW3_DEPS}) # local builds, use gtest from ext/gtest
    file(TO_CMAKE_PATH "$ENV{HW3_DEPS}/ext/gtest/output/${PLATFORM_BUILD_DIR}" gtest_DIR)
    message(STATUS "Package GTest::gtest root: ${gtest_DIR}")
    include(${gtest_DIR}/lib/cmake/GTest/GTestConfig.cmake)
else()
    find_package(GTest REQUIRED)
endif()

target_link_libraries(${TARGET_NAME} PRIVATE GTest::gtest_main)

if(MSVC) # for vs debugging
    set_property(TARGET ${TARGET_NAME} PROPERTY
        VS_DEBUGGER_WORKING_DIRECTORY $(OutDir)
    )
endif()

add_test(MatrixTest "${CMAKE_INSTALL_PREFIX}/tests/matrix-tests")

include(GNUInstallDirs)
install(
    TARGETS ${TARGET_NAME} COMPONENT tests
    PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    RUNTIME DESTINATION tests
)
