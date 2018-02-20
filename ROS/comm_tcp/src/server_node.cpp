
#include <ros/ros.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "std_msgs/String.h"

using namespace std;

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main (int argc, char** argv)
{
  ros::init(argc, argv, "server_node");
  ros::NodeHandle nh;
  ros::Publisher server_pub = nh.advertise<std_msgs::String>("/server_messages/", 1000);
  //Testing package is working fine
  int sockfd, newsockfd, portno; //Socket file descriptors and port number
  socklen_t clilen; //object clilen of type socklen_t
  char buffer[256]; //buffer array of size 256
  struct sockaddr_in serv_addr, cli_addr; ///two objects to store client and server address
  std_msgs::String message;
  std::stringstream ss;
  int n;
  ros::Duration d(0.01); // 100Hz
  if (argc < 2) {
    fprintf(stderr,"ERROR, no port provided\n");
    exit(1);
  }
  portno = atoi(argv[1]);
  cout << "Hello there! This node is listening on port " << portno << " for incoming connections" << endl;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
      error("ERROR opening socket");
  int enable = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
      error("setsockopt(SO_REUSEADDR) failed");
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  if (bind(sockfd, (struct sockaddr *) &serv_addr,
            sizeof(serv_addr)) < 0)
            error("ERROR on binding");
  listen(sockfd,5);
  clilen = sizeof(cli_addr);
  newsockfd = accept(sockfd,
              (struct sockaddr *) &cli_addr,
              &clilen);
  if (newsockfd < 0)
       error("ERROR on accept");

    double qSoll[6];
	    for(int h=0;h<6;h++){
		qSoll[h] = (double)h;
		std::cout <<  qSoll[h] << "\n";
		send(sockfd, &qSoll[h], sizeof(double),0);
	    }
 

 float qIst[7];
	    recv(sockfd, qIst, sizeof(qIst), 0);
	     for(int h=0;h<7;h++){
                
	      std::cout << qIst[h] << "\n";
	    }
          ros::spinOnce();

  
  return 0;
}
