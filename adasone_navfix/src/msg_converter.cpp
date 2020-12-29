#include <ros/ros.h>
#include <adasone_msgs/GpsNavSatPoint.h>
#include <sensor_msgs/NavSatFix.h>

ros::Publisher gps_pub;

void adasoneCallback(adasone_msgs::GpsNavSatPoint msg){
    sensor_msgs::NavSatFix gps_msg;
    gps_msg.header = msg.header;
    gps_msg.status = msg.status;
    gps_msg.latitude = msg.latitude;
    gps_msg.longitude = msg.longitude;
    gps_msg.altitude = msg.altitude;
    gps_msg.position_covariance = msg.position_covariance;
    gps_msg.position_covariance_type = msg.position_covariance_type;
    gps_pub.publish(gps_msg);
}

int main(int argc, char **argv){
    ros::init(argc, argv, "msg_converter");
    ros::NodeHandle n;
    gps_pub = n.advertise<sensor_msgs::NavSatFix>("/gps/fix", 1000);
    ros::Subscriber adasone_sub = n.subscribe("/gps_map_point", 1000, adasoneCallback);
    ros::spin();
}