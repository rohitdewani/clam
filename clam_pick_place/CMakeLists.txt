cmake_minimum_required(VERSION 2.8.3)
project(clam_pick_place)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS 
  moveit_core 
  moveit_ros_planning 
  moveit_ros_planning_interface 
  block_grasp_generator
  clam_msgs
)
find_package(Eigen REQUIRED)
find_package(Boost REQUIRED system thread)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES clam_pick_place
  CATKIN_DEPENDS 
    moveit_core
    moveit_ros_planning_interface
)

# Enable gdb to show line numbers
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")
set(CMAKE_BUILD_TYPE Debug)

###########
## Build ##
###########

include_directories(SYSTEM ${Boost_INCLUDE_DIR} ${EIGEN_INCLUDE_DIRS})
include_directories(${catkin_INCLUDE_DIRS})
link_directories(${catkin_LIBRARY_DIRS})

add_executable(simple_pick_place src/simple_pick_place.cpp)
target_link_libraries(simple_pick_place ${catkin_LIBRARIES} ${Boost_LIBRARIES})

#install(TARGETS simple_pick_place DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
