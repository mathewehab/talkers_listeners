#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <random>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	// name of the node is "talker"
	ros::init(argc, argv, "talker");

	ros::NodeHandle n;

	// message queue = 1000
	ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

	// small number means larger delay
	ros::Rate loop_rate(1);

	std_msgs::String msg;
	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<mt19937::result_type> dist100(1, 100);
	uniform_int_distribution<mt19937::result_type> dist40(30, 40);

	while (ros::ok())
	{
		stringstream ss;
		ss << "\nspeed is " << (float)dist100(rng) / dist100(rng);
		ss << "\ntempreture is " << (float)dist40(rng) / dist40(rng);
		ss << "\nhumidity is " << dist100(rng);
		ss << "\n";
		msg.data = ss.str();
		ROS_INFO("%s", msg.data.c_str());
		chatter_pub.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();
  	}

  return 0;
}
