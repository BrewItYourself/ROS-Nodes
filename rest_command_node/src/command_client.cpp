#include "ros/ros.h"
#include "rest_command_node/client_command.h"
#include <cstdlib>

#include <iostream>
#include <string>
#include <sstream>
using namespace std;
int main(int argc, char **argv)
{
  ros::init(argc, argv, "Send_request");
  if (argc != 2)
  {
    ROS_INFO("usage: send commands from RESTful SErver");
    return 1;
  }

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<rest_command_node::client_command>("processing_request");
  rest_command_node::client_command srv;
  srv.request.from = (argv[1])
  srv.request.command = (argv[2]);
  if (client.call(srv))
  {
    ROS_INFO("Sum: %s", srv.response.response.c_str());
  }
  else
  {
    ROS_ERROR("Failed to call service add_two_ints");
    return 1;
  }

  return 0;
}
