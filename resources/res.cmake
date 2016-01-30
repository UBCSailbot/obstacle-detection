# The following command copies the resources folder into the binary directory,
#  making it possible to load resources from a relative path within the project
add_custom_target(migrateResources
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        ${CMAKE_BINARY_DIR}/resources
        )