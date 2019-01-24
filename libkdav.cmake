get_filename_component(LIBKDAV_CUR_DIR ${CMAKE_CURRENT_LIST_FILE} PATH) # for cmake before 2.8.3

include_directories("${LIBKDAV_CUR_DIR}/include/")

set(COMMON_SOURCES ${COMMON_SOURCES}
  "${LIBKDAV_CUR_DIR}/src/KDAVCodec.cpp"
)
