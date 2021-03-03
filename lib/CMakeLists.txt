
add_library(lib INTERFACE)

# tbb
# TODO open issue on xpp github site
find_package(TBB COMPONENTS tbbmalloc tbbmalloc_proxy tbb_preview)
target_link_libraries(lib INTERFACE tbb)

# xpp {
set(XCB_PROTOS xproto)

list(APPEND XCB_PROTOS randr damage render)
list(APPEND XCB_PROTOS composite)
if(WITH_XKB)
    list(APPEND XCB_PROTOS xkb)
endif()

message("Generating target xpp")
add_subdirectory(xpp)
if(NOT TARGET xpp)
    message(FATAL_ERROR "Target xpp not generated")
else()
    get_target_property(_xpp_includes xpp INCLUDE_DIRECTORIES)
    set_target_properties(xpp PROPERTIES INCLUDE_DIRECTORIES "")
    target_include_directories(xpp SYSTEM PUBLIC ${_xpp_includes})
    target_link_libraries(lib INTERFACE xpp)
endif()

# }
