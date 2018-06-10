# ROS-Subsumption-Architecture
Subsumption algorithm on ros that has three levels

cd ros_ws  
sudo apt-get install ros-kinetic-joy  
run "catkin_make" make sure there are no errors.  
edit ~/.bashrc, add "source /home/..../rosws/devel/setup.bash" to the end of the .bashrc file.  
close the terminal and reopen the terminal   
run roscore  
run vrep, open scenes/assignment9.ttt  
. ~/ros-ws/devel/setup.bash  

To test the behaviors : roslaunch my_subsumption behaviortest.launch

To test program : roslaunch my_subsumption findtheball.launch
