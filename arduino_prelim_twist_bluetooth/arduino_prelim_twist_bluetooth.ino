#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <ArduinoHardware.h>

//INCLUDING BLUETOOTH IN THE ARDUINO SKETCH

//#include <ros.h>
//#include <Arduino.h>
//#include <std_msgs/Empty.h>



class NewHardware : public ArduinoHardware
{
   public:
   NewHardware():ArduinoHardware(&Serial1,57600){};
};

ros::NodeHandle_<NewHardware> nh;



//ros::NodeHandle  nh;


void messageCb( const geometry_msgs::Twist& msg){
  if(msg.linear.x>0.5)
  {
    
             //digitalWrite(LED_BUILTIN,HIGH);
            digitalWrite(3,LOW); //forward
            digitalWrite(2,HIGH);
            //digitalWrite(7,LOW);
            //digitalWrite(6,HIGH);
  }
  else
  {         //digitalWrite(3,LOW); //stop
            //digitalWrite(2,LOW);
            //digitalWrite(7,LOW);
            //digitalWrite(6,LOW);
            digitalWrite(LED_BUILTIN,LOW);
  }
}
/*
void messageCb1( const geometry_msgs::Twist& msg){

    if(msg.linear.y>0.5)
  {
    
  
             digitalWrite(3,HIGH);//reverse
              digitalWrite(2,LOW);
              digitalWrite(7,HIGH);
              digitalWrite(6,LOW); 
  }
  else
  {         digitalWrite(3,LOW); //stop
            digitalWrite(2,LOW);
            digitalWrite(7,LOW);
            digitalWrite(6,LOW);
    
  }
             
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
*/
ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &messageCb );
//ros::Subscriber<geometry_msgs::Twist> sub1("cmd_vel", &messageCb1 );
//ros::Subscriber<std_msgs::Empty> sub2("d", &messageCb2 );
//ros::Subscriber<std_msgs::Empty> sub3("a", &messageCb3 );

void setup() {
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(24,OUTPUT);

  pinMode(3,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(25,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  //Serial1.begin(57600);
  //Serial.begin(38400);
  nh.getHardware()->setBaud(115200);
   nh.initNode();
  nh.subscribe(sub);
 // nh.subscribe(sub1);
 // nh.subscribe(sub2);
 // nh.subscribe(sub3);
}

void loop() {
  digitalWrite(24,HIGH);
  digitalWrite(25,HIGH);
   nh.spinOnce();
   delay(10);


  
  


  }
