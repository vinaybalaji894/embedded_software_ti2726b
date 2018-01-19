

// CAN USE TELEOP TWIST KEYBOARD AS WELL ! INCREASE W TO MORE THAN 0.5 and then PRESS U


#include <ros.h>
#include <std_msgs/Empty.h>
#include<geometry_msgs/Twist.h>
#include <math.h>


ros::NodeHandle  nh;


void messageCb( const geometry_msgs::Twist& msg){
  if(msg.linear.x>0&&msg.angular.z==0)
  {
            digitalWrite(3,LOW); //forward
            digitalWrite(7,LOW);
            analogWrite(2,((int)msg.linear.x < 255) ? (int)msg.linear.x : 255);
            analogWrite(6,((int)msg.linear.x < 255) ? (int)msg.linear.x : 255);

}
else  if(msg.linear.x<0&&msg.angular.z==0)
{
 
            digitalWrite(2,LOW); //reverse
            digitalWrite(6,LOW);
            analogWrite(3,(-(int)msg.linear.x < 255) ? -(int)msg.linear.x : 255);
            analogWrite(7,(-(int)msg.linear.x < 255) ? -(int)msg.linear.x : 255);
  
}
else if(msg.linear.x==0 &&msg.angular.z>1.0)
{
 digitalWrite(3,LOW);
 analogWrite(2,((int)msg.angular.z < 255) ? (int)msg.angular.z : 255);
 
}
else if(msg.linear.x==0 &&msg.angular.z<-1.0)
{
 digitalWrite(7,LOW);
 analogWrite(6,(-(int)msg.angular.z < 255) ? -(int)msg.angular.z : 255);
 
}
else
{
  digitalWrite(7,LOW);
  digitalWrite(6,LOW);
  digitalWrite(3,LOW);
  digitalWrite(2,LOW);
}
}


ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &messageCb );


void setup() {
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(24,OUTPUT);

  pinMode(3,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(25,OUTPUT);

 
  nh.initNode();
  nh.subscribe(sub);

}

void loop() {
  digitalWrite(24,HIGH);
  digitalWrite(25,HIGH);
   nh.spinOnce();
   delay(10);


  
  


  }
  



  
  


