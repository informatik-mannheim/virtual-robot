cmake_minimum_required(VERSION 2.8.3)

project(gomtec_robot_description)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
sensor_msgs
 tf
)


catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)


add_executable(GelenkStellung src/GelenkStellung.cpp)

target_link_libraries(GelenkStellung
  ${catkin_LIBRARIES}
)

foreach(dir doc launch meshes urdf src)
  install(
    DIRECTORY ${dir}/
    DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach()

install(FILES urdf.rviz DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
