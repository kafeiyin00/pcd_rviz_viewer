#include <ros/ros.h>
#include <pcl/common/common.h>
#include <pcl/common/eigen.h>
#include <pcl/common/transforms.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/transformation_estimation_point_to_plane.h>
#include <pcl_conversions/pcl_conversions.h>

ros::Publisher pub_points;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "view_pcd_node");
    ros::NodeHandle nh("~");

    std::string points_message_name;
    nh.param<std::string>("points_message_name", points_message_name, "/pcd_points");

    if(argc != 2)
    {
        ROS_ERROR("input filename\n");
        return 0;
    }

    std::string filename = argv[1];
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPCDFile(filename,*cloud);

    pub_points = nh.advertise<sensor_msgs::PointCloud2>(points_message_name.c_str(), 10);

    sensor_msgs::PointCloud2 cloud_msg;
    pcl::toROSMsg(*cloud, cloud_msg);
    cloud_msg.header.frame_id = "world";
    
    ros::Rate rate(10);
    while(ros::ok())
    {   
        ros::spinOnce();

        pub_points.publish(cloud_msg);

        rate.sleep();
    }
    return 1;
}