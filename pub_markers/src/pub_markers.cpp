#include <ros/ros.h>
#include <std_msgs/String.h>


int main(int argc, char** argv){

  // Initialize simple publisher node
  ros::init(argc, argv, "pub_marker");
  ros::NodeHandle n;
  ros::Publisher wp_pub = n.advertise<std_msgs::String>("waypoint", 10);

  ros::Rate loop_rate(10);
  std_msgs::String msg;
  std::stringstream ss;
  ros::Duration(0.5).sleep(); 
  
  ss << "Initializing";
  msg.data = ss.str();
  wp_pub.publish(msg);
  ros::spinOnce();
  ROS_INFO("%s", msg.data.c_str());
 
  // add marker will publish a marker at the pickup location when it gets the startRun msg  
  ss.str(std::string());
  ss << "startRun";
  msg.data = ss.str();
  wp_pub.publish(msg);
  ros::spinOnce();
  ROS_INFO("%s", msg.data.c_str());
  
  // Wait 5 seconds
  ros::Duration(5.0).sleep();  
  
  // add marker will delete all markers when it gets a startLoading message
  ss.str(std::string());
  ss << "startLoading";
  msg.data = ss.str();
  ROS_INFO("%s", msg.data.c_str());
  wp_pub.publish(msg);
  ros::spinOnce();
  
  // Wait 5 seconds
  ros::Duration(5.0).sleep();  
  
  /*/ add marker doesn't currently do anything with doneLoading messages
  ss.str(std::string());
  ss << "doneLoading";
  msg.data = ss.str();
  ROS_INFO("%s", msg.data.c_str());
  wp_pub.publish(msg);
  ros::spinOnce();
  */

  // add marker doesn't currently do anything with doneLoading messages
  ss.str(std::string());
  ss << "dropOff";
  msg.data = ss.str();
  ROS_INFO("%s", msg.data.c_str());
  wp_pub.publish(msg);
  ros::spinOnce();
  
  ros::Duration(0.5).sleep(); 
  /*/ add marker adds a marker at the drop off when it gets the dropOff message
  for (int i = 0; i < 3; i++){
    ss.str(std::string());
    ss << "dropOff";
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    wp_pub.publish(msg);
  }*/
  return 0;
}
