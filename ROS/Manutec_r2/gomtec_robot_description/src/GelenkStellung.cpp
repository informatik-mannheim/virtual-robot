#include <ros/ros.h>
#include <stdio.h>
#include "sensor_msgs/JointState.h"
#include "std_msgs/Float64.h"
#include <tf/transform_broadcaster.h>

int main(int argc, char *argv[]) {
	ros::init(argc, argv, "GelenkStellung");
	ros::NodeHandle nh;

	

	ros::Publisher  chatter_pub = nh.advertise<sensor_msgs::JointState>("joint_states", 1000);
	tf::TransformBroadcaster broadcaster;	
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

	 
     		/*msg.position[0] = 0;
     	 	msg.position[1] = 0;
		msg.position[2] = 0;
		msg.position[3] = 0;
		msg.position[4] = 0;
		msg.position[5] = 0;
		msg.position[6] = 0;
		msg.position[7] = 0;*/
  float qSoll[7];
  const double degree = M_PI/180; 
ros::Rate rate(1);
	while(ros::ok()){
	printf("Enter q1: ");
	scanf("%f",&qSoll[0]);
	printf("Enter q2: ");
	scanf("%f",&qSoll[1]);
	printf("Enter q3: ");
	scanf("%f",&qSoll[2]);
	printf("Enter q4: ");
	scanf("%f",&qSoll[3]);
	printf("Enter q5: ");
	scanf("%f",&qSoll[4]);
	printf("Enter q6: ");
	scanf("%f",&qSoll[5]);
	printf("Enter Finger1: ");
	scanf("%f",&qSoll[6]);
	printf("Enter Finger2: ");
	scanf("%f",&qSoll[7]);
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
	return 0;
}
