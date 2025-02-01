# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\CatNMouse_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CatNMouse_autogen.dir\\ParseCache.txt"
  "CatNMouse_autogen"
  )
endif()
