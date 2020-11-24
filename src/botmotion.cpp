#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/LaserScan.h>
#include "geometry_msgs/Twist.h"
#include "botmotion.hpp"

void mtb::Motion::laserCallback(const sensor_msgs::LaserScan::ConstPtr& data) {
    dist = data->ranges[180];
    ROS_INFO_STREAM("Distance from the obstacle is: " << dist);
}

    mtb::Motion::Motion(ros::NodeHandle node) {
    ros::Subscriber laserSubscriber = node.subscribe("/scan", 1000, &Motion::laserCallback, this);
    ros::Publisher velocityPublisher = node.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

    ros::Rate rate(4);

    while (ros::ok()) {
        geometry_msgs::Twist twist;
        twist.linear.x = 0.0;
        twist.linear.y = 0.0;
        twist.linear.z = 0.0;
        twist.angular.x = 0.0;
        twist.angular.y = 0.0;
        twist.angular.z = 0.0;

        if (dist > 0.45) {
            ROS_INFO_STREAM("Moving ahead...");
            twist.linear.x = -0.12;
        } else {
            ROS_INFO_STREAM("Obstacle Detected; Changing direction...");
            twist.angular.z = 1.4;
        }
        velocityPublisher.publish(twist);
        ros::spinOnce();
        rate.sleep();
    }
}
