add_executable(tttt-subprocess
    subprocess.cpp
)

target_include_directories(tttt-subprocess PRIVATE
    ${SUBPROCESS_INCLUDE_DIR}
)

target_link_libraries(tttt-subprocess PRIVATE
    subprocess
)