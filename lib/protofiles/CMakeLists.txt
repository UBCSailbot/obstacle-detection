INCLUDE(FindProtobuf)
FIND_PACKAGE(Protobuf REQUIRED)
INCLUDE_DIRECTORIES(${PROTOBUF_INCLUDE_DIR})

file(GLOB ProtoFiles "${CMAKE_CURRENT_SOURCE_DIR}/messages/*.proto")
PROTOBUF_GENERATE_CPP(ProtoSources ProtoHeaders ${ProtoFiles})
add_library(protofiles STATIC ${ProtoSources} ${ProtoHeaders})
target_link_libraries(protofiles ${PROTOBUF_LIBRARY})

set(ProtobufIncludePath ${CMAKE_CURRENT_BINARY_DIR}
        CACHE INTERNAL "Path to generated protobuf files.")
