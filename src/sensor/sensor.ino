#include <ros.h>
#include <std_msgs/Float32MultiArray.h>

ros::NodeHandle hrik;

std_msgs::Float32MultiArray sensor_data;
ros::Publisher pub("/sensor_data", &sensor_data);

#define potentiometer A0
#define trig 9
#define echo 10


void setup() {
  
  hrik.initNode();
  hrik.advertise(pub);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
   
}


void loop() {
  sensor_data.data.clear();
  sensor_data.data.push_back(potentiometer_value());
  sensor_data.data.push_back(SONAR_value());  

  pub.publish(&sensor_data);
  hrik.spinOnce();

  delay(100); 

}


float SONAR_value() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH);
  float distance = duration * 0.034 / 2; 
  return distance;
}


float potentiometer_value() {
  int h = analogRead(potentiometer);
  return h / 1023.0; 
}
