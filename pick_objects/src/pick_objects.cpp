#include <ros/ros.h>
#include <std_msgs/String.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  // Initialize simple publisher node
  ros::init(argc, argv, "waypoint_tracker");
  ros::NodeHandle n;
  ros::Publisher wp_pub = n.advertise<std_msgs::String>("waypoint", 10);

  ros::Rate loop_rate(10);
  std_msgs::String msg;
  std::stringstream ss;


  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  
  ss << "startRun";
  msg.data = ss.str();
  wp_pub.publish(msg);
  ros::spinOnce();
  ROS_INFO("%s", msg.data.c_str());
  
  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = -6.0;
  goal.target_pose.pose.position.y = 3.30;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Heading to Pickup Location");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Ready for loading, you've got 5 seconds");
    ss.str(std::string());
    ss << "startLoading";
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    wp_pub.publish(msg);
    ros::spinOnce();
  }
  else
    ROS_INFO("The base failed to move to pickup location. See owner's manual");


  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  ros::Duration(5.0).sleep();  
  ss.str(std::string());
  ss << "doneLoading";
  msg.data = ss.str();
  ROS_INFO("%s", msg.data.c_str());
  wp_pub.publish(msg);
  ros::spinOnce();

  ROS_INFO("Heading to drop off point");

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = .17;
  goal.target_pose.pose.position.y = 3.12;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Starting run");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Arrived at drop off location");
    ss.str(std::string());
    ss << "dropOff";
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    wp_pub.publish(msg);
    ros::spinOnce();
  }
  else
    ROS_INFO("The base failed to move to drop off location. See owner's manual");

  return 0;
}
