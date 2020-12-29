# global id
int32 gid
# local id
int32 lid
# driving data (0: gps_following, 1: lane_keeping)
uint8 driving_data
uint8 scenario
float32 driving_angle
geometry_msgs/PoseStamped pose
geometry_msgs/TwistStamped twist
