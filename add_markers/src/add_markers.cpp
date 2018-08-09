#include <ros/ros.h>
#include <std_msgs/String.h>
#include <visualization_msgs/Marker.h>



ros::Publisher marker_pub;

void waypointCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
  
  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;


  visualization_msgs::Marker marker;
  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();
  
  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "pickup_shape:";
  marker.id = 0;

  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  marker.type = shape;

  if(strcmp(msg->data.c_str(), "startRun") == 0) {
  	// Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
  	marker.action = visualization_msgs::Marker::ADD;

  	// Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
  	marker.pose.position.x = -6.0;
        marker.pose.position.y = 3.3;
        marker.pose.position.z = 0.45;
  	marker.pose.orientation.x = 0.0;
  	marker.pose.orientation.y = 0.0;
  	marker.pose.orientation.z = 0.0;
  	marker.pose.orientation.w = 1.0;

  	// Set the scale of the marker -- 1x1x1 here means 1m on a side
  	marker.scale.x = .10;
  	marker.scale.y = .10;
  	marker.scale.z = .10;

 	 // Set the color -- be sure to set alpha to something non-zero!
  	marker.color.r = 1.0f;
  	marker.color.g = 1.0f;
  	marker.color.b = 0.0f;
  	marker.color.a = 1.0;

  	marker.lifetime = ros::Duration();
  } 
  
  else if(strcmp(msg->data.c_str(), "dropOff") == 0){
        // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
        marker.action = visualization_msgs::Marker::ADD;

        // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
        marker.pose.position.x = 0.1;
        marker.pose.position.y = 3.1;
        marker.pose.position.z = 0.45;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;

        // Set the scale of the marker -- 1x1x1 here means 1m on a side
        marker.scale.x = .10;
        marker.scale.y = .10;
        marker.scale.z = .10;

         // Set the color -- be sure to set alpha to something non-zero!
        marker.color.r = 1.0f;
        marker.color.g = 1.0f;
        marker.color.b = 0.0f;
        marker.color.a = 1.0;

        marker.lifetime = ros::Duration();
 
  }
  
  else if(strcmp(msg->data.c_str(), "startLoading") == 0) {
    marker.action = visualization_msgs::Marker::DELETEALL;
  }	

  // Publish the marker
  while (marker_pub.getNumSubscribers() < 1)
 {
        if (!ros::ok())
    	{
      		;
    	}	
    	ROS_WARN_ONCE("Please create a subscriber to the marker");
    	     sleep(1);
  }
  marker_pub.publish(marker);
  


}



int main( int argc, char** argv )
{

  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  ros::init(argc, argv, "wp_listener");
  ros::NodeHandle w;
  ros::Subscriber sub = w.subscribe("waypoint", 1000, waypointCallback);

  ros::spin();

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "pickup_shape:";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = 0;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 1.0;
    marker.scale.y = 1.0;
    marker.scale.z = 1.0;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    marker_pub.publish(marker);

    // Cycle between different shapes
    switch (shape)
    {
    case visualization_msgs::Marker::CUBE:
      shape = visualization_msgs::Marker::SPHERE;
      break;
    case visualization_msgs::Marker::SPHERE:
      shape = visualization_msgs::Marker::ARROW;
      break;
    case visualization_msgs::Marker::ARROW:
      shape = visualization_msgs::Marker::CYLINDER;
      break;
    case visualization_msgs::Marker::CYLINDER:
      shape = visualization_msgs::Marker::CUBE;
      break;
    }

    r.sleep();
  }
}
