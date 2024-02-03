
file(GLOB APP_PHONG_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.hh ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
# message("APP_PHONG_SRC: ${APP_PHONG_SRC}")
add_executable(${PROJECT_NAME}_phong ${APP_SRC} ${APP_PHONG_SRC})

target_include_directories( ${PROJECT_NAME}_phong 
                            PUBLIC ${CMAKE_SOURCE_DIR}/vendor/stb/include
                            PUBLIC ${CMAKE_SOURCE_DIR}/vendor/spdlog/include
                            PUBLIC ${CMAKE_SOURCE_DIR}/vendor/glfw/include
                            PUBLIC ${CMAKE_SOURCE_DIR}/vendor/glm/include
                            )

target_link_libraries(${PROJECT_NAME}_phong PUBLIC glfw3)
target_link_directories(${PROJECT_NAME}_phong PUBLIC  ${CMAKE_SOURCE_DIR}/vendor/glfw/lib)