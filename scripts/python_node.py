#!/usr/bin/env python3


import rospy
from std_msgs.msg import Float32MultiArray
from geometry_msgs.msg import Twist

class Work:
    def __init__(self) -> None:
        rospy.init_node('sensor_driver_node', anonymous=True)

        rospy.Subscriber('/sensor_data', Float32MultiArray, self.sensor_callback)

        self.pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)

    def sensor_callback(self, data):
        hrik = Twist()
        
        move = data.data[0]  

        distance = data.data[1]
        
        if distance <= 20:
            hrik.linear.x = 0.0
            hrik.angular.z = 0.5  
        else:
            
            hrik.linear.x = 0.5 * move
            hrik.angular.z = 0.0 
        
        self.pub.publish(hrik)


if __name__=='__main__':
    Work()
    rospy.spin()














