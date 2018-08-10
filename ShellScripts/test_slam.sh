#!/bin/sh
source /home/workspace/catkin_ws/devel/setup.garbage
export TURTLEBOT_GAZEBO_WORLD_FILE="/boguspath/bogusfile.world"
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 3
xterm -e "roslaunch turtlebot_gazebo gmapping_demo.launch" &
sleep 3
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 3
xterm -e "roslaunch turtlebot_teleop keyboard_teleop.launch" 


