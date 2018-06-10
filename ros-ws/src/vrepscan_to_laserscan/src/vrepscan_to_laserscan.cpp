#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

#include <geometry_msgs/Twist.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>

#define PI 3.1415926535897932384626433f

class ScanConverter
{
    ros::Subscriber cloudSubs;
    ros::Publisher scanPub;
    ros::NodeHandle nh;
    pcl::PointCloud<pcl::PointXYZ> lastpc;

public:
    ScanConverter()
    {
        cloudSubs=nh.subscribe("/vrep/hokuyoSensor",100,
                &ScanConverter::pc_callback,this);
        scanPub=nh.advertise<sensor_msgs::LaserScan> ("/scan",100);
    }

    void pc_callback(const sensor_msgs::PointCloud2ConstPtr msg)
    {
        pcl::fromROSMsg(*msg, lastpc);
        // n=684
        // <=0.063
        // ang=240 4.1887902 rad
        // stepsize=0.0061359232 rad 0.3515625 deg

        //        Frame: /Hokuyo published by /vrep Average Delay: 0.00248396 Max Delay: 0.00433646
        //        Frame: /frontCamera published by /vrep Average Delay: 0.00250298 Max Delay: 0.00434716
        //        Frame: /rosControlledBubbleRob published by /vrep Average Delay: 0.00252315 Max Delay: 0.00435284
        sensor_msgs::LaserScanPtr output(new sensor_msgs::LaserScan());
        output->header=msg->header;
        output->header.frame_id="/Hokuyo";
        output->angle_min=-120.0*PI/180.0;
        output->angle_max=120.0*PI/180.0;
        output->angle_increment=0.0061359232;
        output->time_increment=0;
        output->scan_time=1.0/30.0;
        output->range_min=0.1;
        output->range_max=5;

        uint32_t ranges_size=684;
        output->ranges.assign(ranges_size,output->range_max+1.0);
        float rangeMinSq=output->range_min*output->range_min;
        float rangeMaxSq=output->range_max*output->range_max;

        for(int i=0;i<lastpc.points.size();i++)
        {
            float x=lastpc.points[i].x;
            float y=lastpc.points[i].y;
            float z=lastpc.points[i].z;

            if(std::isnan(x)||std::isnan(y)||std::isnan(z))
            {
                continue;
            }
            if(z<0.0001)
            {
                continue;
            }
            double range_sq=y*y+x*x;
            if(range_sq<rangeMinSq||range_sq>rangeMaxSq)
            {
                continue;
            }
            output->ranges[i]=sqrt(range_sq);
        }
        scanPub.publish(output);
    }
};

int main(int argc,char **argv)
{
    std::cout<<"vrepscan_to_laserscan Start..."<<std::endl;
    ros::init(argc,argv,"vrepscan_to_laserscan");
	//ros::Rate rate(30);
	ScanConverter tp;
    while(ros::ok())
    {
    	ros::spin();
	    //rate.sleep();
    }
   
    printf("vrepscan_to_laserscan Finish...");
    return 0;
}
