#include <ros/ros.h>
#include "../include/botmotion.hpp"

int main(int argc, char** argv) {
    ros::init(argc, argv, "motion");
    ros::NodeHandle node;
    mtb::Motion motion(node);
}