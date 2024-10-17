
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <AFMotor.h> 

ros::NodeHandle hrik;
geometry_msgs::Twist received_msg;

AF_DCMotor motor1(1);  
AF_DCMotor motor2(2);

void cmd_vel_callback(const geometry_msgs::Twist &msg) {
  received_msg = msg;
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &cmd_vel_callback);


void setup() {
  hrik.initNode(); 
  hrik.subscribe(sub); 

  motor1.setSpeed(255); 
  motor2.setSpeed(255);

}

void loop() {
  hrik.spinOnce();

  if(received_msg.linear.x>0){
    motor1.run(FORWARD); 
    motor2.run(FORWARD);   
  }

  else if(received_msg.linear.x<0){
    motor1.run(BACKWARD); 
    motor2.run(BACKWARD);  
  }

  else if(received_msg.angular.z>0){
    motor1.run(BACKWARD); 
    motor2.run(FORWARD);   
  }

  else if(received_msg.angular.z<0){
    motor1.run(FORWARD); 
    motor2.run(BACKWARD);   
  }

  else{
    motor1.run(RELEASE); 
    motor2.run(RELEASE);
  }

}
