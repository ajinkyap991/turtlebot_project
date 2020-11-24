#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/LaserScan.h>

namespace mtb {

class Motion {
 private:
    double dist;

 public:

    Motion(ros::NodeHandle node);

    void laserCallback(const sensor_msgs::LaserScan::ConstPtr& data);
};
}