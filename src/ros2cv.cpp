#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

/*

#######################################################

    Author:
        Florian Lier [flier@techfak.uni-bielefeld.de

#######################################################

*/

static const std::string OPENCV_WINDOW = "OPEN CV IMAGE";

class ImageConverter
{
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;

  public:
  ImageConverter( std::string input, std::string output ) : it_(nh_) {
    // Subscribe to input video feed and publish output video feed
    image_sub_ = it_.subscribe(input, 1, &ImageConverter::imageCb, this);
    image_pub_ = it_.advertise(output, 1);
    cv::namedWindow(OPENCV_WINDOW);
  }

  ~ImageConverter() {
    cv::destroyWindow(OPENCV_WINDOW);
    // std::cout << "Object ImageConverter Deleted" << std::endl;
  }

  void imageCb(const sensor_msgs::ImageConstPtr& msg) {
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge Exception: %s", e.what());
      return;
    }

    // Update GUI window
    cv::imshow(OPENCV_WINDOW, cv_ptr->image);
    cv::waitKey(3);

    // Output modified video stream
    image_pub_.publish(cv_ptr->toImageMsg());
  }

};

int main(int argc, char** argv) {

    // Check the number of parameters
    if (argc < 3) {
        std::cerr << ">> No input/output topic provided...Exiting." << std::endl;
        std::cerr << ">> USAGE: ros2cv </some/input/topic> </some/output/topic>" << std::endl;
        return 1;
    } else {
        ros::init(argc, argv, "ros2cv");
        ImageConverter ic(argv[1], argv[2]);
        ros::spin();
    }
    return 0;
}
