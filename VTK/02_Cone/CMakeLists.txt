cmake_minimum_required(VERSION 2.6)
 
project(Cone)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Cone Cone.cpp)
 
if(VTK_LIBRARIES)
  target_link_libraries(Cone ${VTK_LIBRARIES})
else()
  target_link_libraries(Cone vtkHybrid)
endif()
