ROS2CV
======

Receive an image via ros Middleware (image_transport), convert it into an OpenCV image and finally -- republish it

Dependencies: 
--------------

* Install ROS as described here: http://wiki.ros.org/indigo/Installation/Ubuntu
* This should also work with ROS "Groovy"


Installation:
--------------

* git clone https://github.com/warp1337/ros_image_to_cv_image.git
* cd ros_image_to_cv_image
* mkdir build && cd build
* source /opt/ros/indigo/setup.bash [or groovy]
* cmake ..
* make

Usage:
------

* source /opt/ros/indigo/setup.bash [or groovy]
* USAGE: ros2cv "/some/input/topic" "/some/output/topic"
* For example: ros2cv /usb_cam/image_raw /ros2cv/image


 

