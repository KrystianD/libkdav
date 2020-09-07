add_library(kdav STATIC
  "${CMAKE_CURRENT_LIST_DIR}/src/KDAV.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/src/KDAVCodec.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/src/KDAVParser.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/src/KDAVFrame.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/src/KDAVCodecContext.cpp"
)

target_include_directories(kdav PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include/")

target_link_libraries(kdav PUBLIC -lavformat -lswscale -lavcodec -lavutil)