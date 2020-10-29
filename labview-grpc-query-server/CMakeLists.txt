#----------------------------------------------------------------------
#----------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5.1)

if(NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
  cmake_policy(SET CMP0091 NEW)
  add_definitions(-D_WIN32_WINNT=0x600)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

project(check_for_sizeof_void_p C)
message( ${CMAKE_SIZEOF_VOID_P} )

project(labview-query-server C CXX)

add_definitions(-D_PS_${CMAKE_SIZEOF_VOID_P})

find_package(Threads REQUIRED)

#----------------------------------------------------------------------
# Include the gRPC's cmake build
#----------------------------------------------------------------------
add_subdirectory(third_party/grpc ${CMAKE_CURRENT_BINARY_DIR}/grpc EXCLUDE_FROM_ALL)

#----------------------------------------------------------------------
# Use the grpc targets directly from this build.
#----------------------------------------------------------------------
set(_PROTOBUF_LIBPROTOBUF libprotobuf)
set(_REFLECTION grpc++_reflection)
if(CMAKE_CROSSCOMPILING)
  find_program(_PROTOBUF_PROTOC protoc)
else()
  set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
endif()
set(_GRPC_GRPCPP grpc++)
if(CMAKE_CROSSCOMPILING)
  find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
  set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)
endif()

#----------------------------------------------------------------------
# Proto file
#----------------------------------------------------------------------
get_filename_component(ms_proto "measurement_service.proto" ABSOLUTE)
get_filename_component(ms_proto_path "${ms_proto}" PATH)

#----------------------------------------------------------------------
# Generated sources
#----------------------------------------------------------------------
set(ms_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/measurement_service.pb.cc")
set(ms_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/measurement_service.pb.h")
set(ms_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/measurement_service.grpc.pb.cc")
set(ms_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/measurement_service.grpc.pb.h")
add_custom_command(
  OUTPUT "${ms_proto_srcs}" "${ms_proto_hdrs}" "${ms_grpc_srcs}" "${ms_grpc_hdrs}"
  COMMAND ${_PROTOBUF_PROTOC}
  ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
    --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
    -I "${ms_proto_path}"
    --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
    "${ms_proto}"
  DEPENDS "${ms_proto}")

#----------------------------------------------------------------------
# Include generated *.pb.h files
#----------------------------------------------------------------------
include_directories("${CMAKE_CURRENT_BINARY_DIR}" "./src")

#----------------------------------------------------------------------
# LabVIEW client support to connect to the query server
#----------------------------------------------------------------------
add_library(labview_measurement_client SHARED
   "src/measurement_client.cc"
   ${ms_proto_srcs}
   ${ms_grpc_srcs}
   )
target_link_libraries(labview_measurement_client
   ${_REFLECTION}
   ${_GRPC_GRPCPP}
   ${_PROTOBUF_LIBPROTOBUF})

#----------------------------------------------------------------------
# LabVIEW server support for implementing the query server
#----------------------------------------------------------------------
add_library(labview_measurement_server SHARED
  src/measurement_server.cc
  src/server_interop.cc
  src/event_data.cc
  ${ms_proto_srcs}
  ${ms_grpc_srcs}
  )
target_link_libraries(labview_measurement_server
   ${_REFLECTION}
   ${_GRPC_GRPCPP}
   ${_PROTOBUF_LIBPROTOBUF})

#----------------------------------------------------------------------
# Example C++ application to talk to the example query server
#----------------------------------------------------------------------
add_executable(example_client
  "src/example_client.cc"
  ${ms_proto_srcs}
  ${ms_grpc_srcs}
  )
target_link_libraries(example_client
   ${_REFLECTION}
   ${_GRPC_GRPCPP}
   ${_PROTOBUF_LIBPROTOBUF})
