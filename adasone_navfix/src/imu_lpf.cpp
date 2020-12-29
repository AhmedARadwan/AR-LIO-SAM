#include <ros/ros.h>
#include <sensor_msgs/Imu.h>

float acc_x_filtered = 0;
float acc_y_filtered = 0;
float acc_z_filtered = 0;

float av_x_filtered = 0;
float av_y_filtered = 0;
float av_z_filtered = 0;

float q_x_filtered = 0;
float q_y_filtered = 0;
float q_z_filtered = 0;
float q_w_filtered = 1;



bool flag = false;

sensor_msgs::Imu msg_old;

void IMUCallback(sensor_msgs::Imu msg){
    flag = true;
    msg_old = msg;

}

int main(int argc, char **argv){
    ros::init(argc, argv, "msg_converter");
    ros::NodeHandle n;
    ros::Publisher imu_correct_pub = n.advertise<sensor_msgs::Imu>("/imu_corrected", 1000);
    ros::Subscriber IMU_sub = n.subscribe("/imu/data", 1000, IMUCallback);
    ros::Rate loop_rate(20);
    while (ros::ok()){
        if (flag){
            acc_x_filtered = 0.95*acc_x_filtered + 0.05*msg_old.linear_acceleration.x;
            acc_y_filtered = 0.95*acc_y_filtered + 0.05*msg_old.linear_acceleration.y;
            acc_z_filtered = 0.95*acc_z_filtered + 0.05*msg_old.linear_acceleration.z;

            av_x_filtered = 0.95*av_x_filtered + 0.05*msg_old.angular_velocity.x;
            av_y_filtered = 0.95*av_y_filtered + 0.05*msg_old.angular_velocity.y;
            av_z_filtered = 0.95*av_z_filtered + 0.05*msg_old.angular_velocity.z;

            q_x_filtered = 0.95*q_x_filtered + 0.05*msg_old.orientation.x;
            q_y_filtered = 0.95*q_y_filtered + 0.05*msg_old.orientation.y;
            q_z_filtered = 0.95*q_z_filtered + 0.05*msg_old.orientation.z;
            q_w_filtered = 0.95*q_w_filtered + 0.05*msg_old.orientation.w;

            sensor_msgs::Imu IMU_corrected_msg;
            IMU_corrected_msg.header.stamp = ros::Time::now();
            IMU_corrected_msg.header.frame_id = msg_old.header.frame_id;
            IMU_corrected_msg.linear_acceleration.x = acc_x_filtered;
            IMU_corrected_msg.linear_acceleration.y = acc_y_filtered;
            IMU_corrected_msg.linear_acceleration.z = acc_z_filtered;
            
            IMU_corrected_msg.angular_velocity = msg_old.angular_velocity;
            

            //IMU_corrected_msg.angular_velocity.x = av_x_filtered;
            //IMU_corrected_msg.angular_velocity.y = av_y_filtered;
            //IMU_corrected_msg.angular_velocity.z = av_z_filtered;

            IMU_corrected_msg.orientation = msg_old.orientation;
            //IMU_corrected_msg.orientation.x = msg_old.orientation.x;
            //IMU_corrected_msg.orientation.y = msg_old.orientation.y;
            //IMU_corrected_msg.orientation.z = msg_old.orientation.z;
            //IMU_corrected_msg.orientation.z = msg_old.orientation.w;

            IMU_corrected_msg.orientation_covariance = msg_old.orientation_covariance;
            IMU_corrected_msg.angular_velocity_covariance = msg_old.angular_velocity_covariance;
            IMU_corrected_msg.linear_acceleration_covariance = msg_old.linear_acceleration_covariance;

            imu_correct_pub.publish(IMU_corrected_msg);

        }
        
        
        loop_rate.sleep();
        ros::spinOnce();
        //ros::Duration().sleep();
    }
}