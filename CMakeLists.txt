cmake_minimum_required(VERSION 3.0.2)
project(pcd_rviz_viewer)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
    geometry_msgs
    nav_msgs
    message_generation
    pcl_conversions
    pcl_ros
    roscpp
    rospy
    sensor_msgs
    std_msgs
    tf
    eigen_conversions
    tf_conversions
    roslib
)


catkin_package(
  INCLUDE_DIRS
  CATKIN_DEPENDS std_msgs sensor_msgs message_runtime
)

###########
## Build ##
###########

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
)

# Set link libraries used by all binaries
list(APPEND thirdparty_libraries
        ${Boost_LIBRARIES}
        ${catkin_LIBRARIES}
        ${PCL_LIBRARIES}
        ${YAML_CPP_LIBRARIES}
)

add_executable(view_pcd_node node/view_pcd_node.cpp)
target_link_libraries(view_pcd_node ${thirdparty_libraries})
