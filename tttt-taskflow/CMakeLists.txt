add_executable(taskflow
    taskflow.cpp
)

target_include_directories(taskflow PRIVATE
    ${TASKFLOW_INCLUDE_DIR}
)

target_link_libraries(taskflow PRIVATE
    pthread
)