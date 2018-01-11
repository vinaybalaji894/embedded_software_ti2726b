#include <ros.h>
#include <std_msgs/Empty.h>


ros::NodeHandle  nh;


void messageCb( const std_msgs::Empty& toggle_msg){
            digitalWrite(3,LOW); //forward
            digitalWrite(2,HIGH);
            digitalWrite(7,LOW);
            digitalWrite(6,HIGH);
}
void messageCb1( const std_msgs::Empty& toggle_msg){
              digitalWrite(3,HIGH);//reverse
              digitalWrite(2,LOW);
              digitalWrite(7,HIGH);
              digitalWrite(6,LOW); 
}
void messageCb2( const std_msgs::Empty& toggle_msg){
  
              digitalWrite(3,HIGH); //right
               digitalWrite(2,LOW);
               digitalWrite(7,LOW);
                digitalWrite(6,HIGH);
}

void messageCb3( const std_msgs::Empty& toggle_msg){
             digitalWrite(3,LOW); //left
             digitalWrite(2,HIGH);
             digitalWrite(7,HIGH);
             digitalWrite(6,LOW);
  
              
}

ros::Subscriber<std_msgs::Empty> sub("w", &messageCb );
ros::Subscriber<std_msgs::Empty> sub1("s", &messageCb1 );
ros::Subscriber<std_msgs::Empty> sub2("d", &messageCb2 );
ros::Subscriber<std_msgs::Empty> sub3("a", &messageCb3 );

void setup() {
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(24,OUTPUT);

  pinMode(3,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(25,OUTPUT);

  Serial1.begin(38400);
  Serial.begin(38400);
   nh.initNode();
  nh.subscribe(sub);
  nh.subscribe(sub1);
  nh.subscribe(sub2);
  nh.subscribe(sub3);
}

void loop() {
  digitalWrite(24,HIGH);
  digitalWrite(25,HIGH);
   nh.spinOnce();
   delay(1000);


  
  


  }
  



  
  


