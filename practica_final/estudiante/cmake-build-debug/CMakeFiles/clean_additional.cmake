# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/quienesquien_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/quienesquien_autogen.dir/ParseCache.txt"
  "quienesquien_autogen"
  )
endif()
