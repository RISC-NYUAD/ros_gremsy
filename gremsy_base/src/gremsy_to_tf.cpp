#include <cstring>
#include <ros/ros.h>
#include <tf/tf.h>
#include <geometry_msgs/Quaternion.h>
#include <tf/transform_broadcaster.h>

tf::TransformBroadcaster *br;

void gremsy_cb(const geometry_msgs::Quaternion&);

int main(int argc, char** argv)
{
  ros::init(argc, argv, "gremsy_tf");		
  ros::NodeHandle n_h;
  ros::Rate loop_rate(50);

  br = new tf::TransformBroadcaster();
  ros::Subscriber gremsy_sub = n_h.subscribe("/ros_gremsy/mount_orientation_local_yaw", 1, gremsy_cb);

  while(ros::ok()){
	ros::spinOnce();
	loop_rate.sleep();
  }
  delete br;
}

void gremsy_cb(const geometry_msgs::Quaternion& msg){
    tf::Transform transform;
    transform.setOrigin(tf::Vector3(0.0, 0.0, 0.2));
    tf::Quaternion q(-msg.y, -msg.x, msg.w, msg.z);
    transform.setRotation(q);
	br->sendTransform(tf::StampedTransform(transform, ros::Time::now(),
                                          "map",
                                          "velodyne"));
}

