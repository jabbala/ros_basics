#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "mastering_ros_demo_pkg/demo_srv.h"

#include <iostream>
#include <sstream>


int main(int argc, char **argv)
{
	ros::init(argc, argv, "demo_msg_subscriber");
	ros::NodeHandle node_obj;
	ros::Rate loop_rate(10);
	ros::ServiceClient client = node_obj.serviceClient<mastering_ros_demo_pkg::demo_srv>("/demo_service");
	while(ros::ok())
	{
		mastering_ros_demo_pkg::demo_srv service;
		std::stringstream ss;
		ss << "Sending from Here";
		service.request.in = ss.str();
		if(client.call(service))
		{
			ROS_INFO("From client [%s], Server says [%s]", service.request.in.c_str(), service.response.out.c_str());
		}else{
			ROS_ERROR("Failed to call service");
			return 1;
		}
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
