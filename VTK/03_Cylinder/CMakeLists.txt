cmake_minimum_required(VERSION 2.6)
 
project(Cylinder)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(main main.cpp)
 
if(VTK_LIBRARIES)
  target_link_libraries(main ${VTK_LIBRARIES})
else()
  target_link_libraries(main vtkHybrid)
endif()
