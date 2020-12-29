cmake_minimum_required(VERSION 2.8.3)
project(adasone_msgs)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  message_generation
  std_msgs
  geometry_msgs
  sensor_msgs
)

## Generate messages in the 'msg' folder
add_message_files(
  FILES
  GpsPoint.msg
  WayPoint.msg
  Lane.msg
  LaneEdge.msg
  LaneEdges.msg
  LaneArray.msg
  VehicleCmd.msg
  Object2D.msg
  Object3D.msg
  ObjectArray.msg
  ObjectRttc.msg
  FinalRttc.msg
  Warning.msg
  DiskStatus.msg
  RadarPoint.msg
  RadarPoints.msg
  ObdParam.msg
  Lkas.msg
  LaneKeeping.msg
  WaypointFollower.msg
  BehaviorState.msg
  Scc.msg
  ActuatorControl.msg
  EkfSol.msg
  CalParam.msg
  VisionWarning.msg
  GuiParam.msg
  GpsNavSatPoint.msg
  ObuData.msg
  Danger.msg
  TL.msg
)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES std_msgs geometry_msgs sensor_msgs
)

catkin_package(
  CATKIN_DEPENDS
  message_runtime
  std_msgs
  message_generation
  geometry_msgs
  sensor_msgs
)
