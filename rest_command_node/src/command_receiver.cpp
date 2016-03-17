#include "ros/ros.h"
#include "std_msgs/String.h"
#include "rest_command_node/client_command.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/**
* Computes
*
*
**/
void from_nodes(string command) 
{
  string bash_command = "curl -X PUT -H \"Content-Type: application/json\" -d '{\"brewId\":1,\"brewState\":\"TEST\",\"temperature\":22.1}' http://localhost:8080/brewlog/brew_data/";
  ROS_INFO("command %s", command.c_str();
  ROS_INFO("bash_command: %s", bash_command.c_str());
  system(command.c_str());
}

void from_server() 
{
  ROS_INFO("FROM THE REST SERVER");
  
}

bool process(rest_command_node::client_command::Request  &req,
         rest_command_node::client_command::Response &res)
{
  ROS_INFO("request: x=%s", req.from.c_str());
  if (req.from.compare("FROM_NODE") == 0) 
  {
    from_nodes();
  }
  else if (req.from.compare("FROM_SERVER") == 0)
  {
    from_server();
  }
  else
  { 
    printf("WAAAA");
    ROS_INFO("reqdest: x=%s", req.command.c_str());
    ROS_INFO("SHOULD NOT BE HERE");
  }
  res.response = "Processed";
  ROS_INFO("sending back response: [%s]", res.response.c_str());
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "RESTful_Server");
  ros::NodeHandle n;
  ros::ServiceServer service = n.advertiseService("processing_request", process);
  ROS_INFO("Ready to receive processes.");
  ros::spin();

  return 0;
}
