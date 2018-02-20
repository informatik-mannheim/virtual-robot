 /*************************************************************************
 * Author: Abbas Khoobyari
 * Contact: abbas_khoobiary@yahoo.com
 ***************************************************************************/
#include <ros/ros.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "std_msgs/String.h"
#include "sensor_msgs/JointState.h"
#include "std_msgs/Float64.h"
#include <tf/transform_broadcaster.h>



#define MESSAGE_FREQ 1

void error(const char *msg) {
    perror(msg);
    exit(0);
}
void indiceCallback(const sensor_msgs::JointState::ConstPtr& msg)
{
  
}
void 	sendTransform (const geometry_msgs::TransformStamped &odom_trans)
{
  
}



int main(int argc, char *argv[]) {
	ros::init(argc, argv, "client_node");
	ros::NodeHandle nh;
    ros::Rate loop_rate(MESSAGE_FREQ); // set the rate as defined in the macro MESSAGE_FREQ
	/*Listener listener;*/
       
        ros::Subscriber client_sub = nh.subscribe("/client_messages", 500, indiceCallback);
     ros::Publisher  chatter_pub = nh.advertise<sensor_msgs::JointState>("joint_states", 1000);
     tf::TransformBroadcaster broadcaster;

      
    int sockfd, portno, n, choice = 1;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];
    bool echoMode = false;
    if (argc < 3) {
       fprintf(stderr,"Usage: $ rosrun comm_tcp client_node <hostname> <port> --arguments\nArguments:\n -e : Echo mode\n");
       exit(0);
    }
    if (argc > 3)
		if (strcmp(argv[3], "-e") == 0)
			echoMode = true;
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    std::cout << "Verbunden.\n\n\n";

      ros::Rate rate(1);
    
	  while(ros::ok())
        {

          const double degree = M_PI/180; 
          sensor_msgs::JointState msg;
          geometry_msgs::TransformStamped odom_trans;
                     odom_trans.header.frame_id = "";
                    // odom_trans.child_frame_id = "";

    odom_trans.header.stamp = ros::Time::now();
    odom_trans.transform.translation.x = 0;
    odom_trans.transform.translation.y = 0;
    odom_trans.transform.translation.z = 0;
    odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(0);

         msg.name.resize(8);
         msg.position.resize(8);
              	 	msg.name[0] ="joint_1";
       			msg.name[1] ="joint_2";
			msg.name[2] ="joint_3";
			msg.name[3] ="joint_4";
			msg.name[4] ="joint_5";
			msg.name[5] ="joint_6";
			msg.name[6] ="joint_f1_linear";
			msg.name[7] ="joint_f2_linear";
	    //receive code
            double qSoll[7];
	    recv(sockfd, &qSoll, sizeof(qSoll), 0);
	    
             for(int h=1;h<7;h++){
                
		std::cout << "qSoll[" << h << "] = " << qSoll[h] << "\n";
	    }
                msg.header.stamp = ros::Time::now();  
     		msg.position[0] = qSoll[0]*degree;
     	 	msg.position[1] = qSoll[1]*degree;
		msg.position[2] = qSoll[2]*degree;
		msg.position[3] = qSoll[3]*degree;
		msg.position[4] = qSoll[4]*degree;
		msg.position[5] = qSoll[5]*degree;
		msg.position[6] = qSoll[6]*degree;
		msg.position[7] = qSoll[7]*degree;
		
		
   
  
   chatter_pub.publish(msg);
  broadcaster.sendTransform(odom_trans);
   rate.sleep();
     
        }
 
           std::cout << "\n\n";

	    //senden code 
	    float pSoll[7]; 
         
	   for(int h=0;h<7;h++){
		pSoll[h] = (float)h;
		if (h>0 ) std::cout << "pSoll[" << h << "] = " << pSoll[h] << "\n";
		send(sockfd, &pSoll[h], sizeof(float),0);
	    }
	    ros::spinOnce();
	return 0;
}

