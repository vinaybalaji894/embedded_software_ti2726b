/* Group 38 , Robot 10
 *  Niket Agrawal - 4719514
 *  Vinay Pathi Balaji -4617363
 */


// CODE TO CONTROL THE ROBOT USING TWIST  KEYBOARD ALONG WITH THE ULTRASONIC INTERRUPT and Time out Functionality


// DECLARATION ON THE HEADER FILES
#include <ros.h>
#include <std_msgs/Empty.h>
#include<geometry_msgs/Twist.h>
#include <math.h>

// DECLARATION OF THE HANDLE FOR THE ROS TELEOP MESSAGES via Cable
ros::NodeHandle  nh;

// Functionality for Bluetooth: It works if you are Lucky!
/*
class NewHardware : public ArduinoHardware
{
   public:
   NewHardware():ArduinoHardware(&Serial1,57600){};
};

ros::NodeHandle_<NewHardware>nh;
*/


//DECLARATION of the Ultrasonic pins
const int trigPin = 23;
const int echoPin = 22;
long duration;
int distance;
static bool flag=false;
static int count=0;


//Declaration of Ultrasonic functions

void initTimer1()
{
  // Using timer1 for ultrasonic sensor as well as the Time out functionality
  cli();
  
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 6260; 
  TCCR1B |= (1 << WGM12); 
  TCCR1B |= (1 << CS12);   
  TIMSK1 |= (1 << OCIE1A); 
  
  sei();
}

ISR(TIMER1_COMPA_vect)        // interrupt service routine 
{
  seize();
}



void seize()
{
//Enabling the counter for the time out
 count=count+10;
 //checking the distance of the ultrasonic sensor
  if(distance < 10)
  {
    flag = true;
    digitalWrite(13, HIGH);   // Set LED high when obsticle detected
    istop();
  }
  else
    {
      flag =false;
    
    digitalWrite(13, LOW);
 
    }// Set LED low when no object is there
//checking if the time-out has achieved 10 secs of receiving no messages
    if(count>1000)
    istop();
}

//Declaration of Motor Functions
void forward(int x1)
{
            digitalWrite(3,LOW); //forward
            digitalWrite(7,LOW);
            analogWrite(2,(x1 < 255) ? x1 : 255);
            analogWrite(6,(x1 < 255) ? x1 : 255);

}

void reverse(int x2)
{
            digitalWrite(2,LOW); //reverse
            digitalWrite(6,LOW);
            analogWrite(3,(-x2 < 255) ? -x2 : 255);
            analogWrite(7,(-x2 < 255) ? -x2 : 255);
}
void left (int z1)
{
  digitalWrite(3,LOW);//left
 analogWrite(2,(z1 < 255) ? z1 : 255);
}

void right (int z2)
{
 digitalWrite(7,LOW);//right
 analogWrite(6,(-z2 < 255) ? -z2 : 255);
  
}
void istop()
{
  //stop
  digitalWrite(7,LOW);
  digitalWrite(6,LOW);
  digitalWrite(3,LOW);
  digitalWrite(2,LOW);
}

// Declaration of CallBack for cmd_vel
void messageCb( const geometry_msgs::Twist& msg)
{ 
  count=0;
  if((msg.linear.x>0)&&(msg.angular.z==0)&&(flag==false))
  {        
            int y=msg.linear.x;
            forward(y);
}
else  if((msg.linear.x<0)&&(msg.angular.z==0))
{
            int y=msg.linear.x;
            reverse(y);
  
}
else if((msg.linear.x==0) &&(msg.angular.z>1.0)&&(flag==false))
{ 
  int y=msg.angular.z;
  left(y); 
}
else if((msg.linear.x==0) &&(msg.angular.z<-1.0)&&(flag==false))
{
  int y=msg.angular.z;
  right(y);
}
else
{
  istop();
}
}

// Subscription to topic
ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &messageCb );


void setup()
{
  //pin setup
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(24,OUTPUT);

  pinMode(3,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(25,OUTPUT);
  pinMode(trigPin,OUTPUT); 
  pinMode(echoPin,INPUT); 
  pinMode(13,OUTPUT);

  // Initialise the timer
   initTimer1();
  // Initialise the Ros node 
  nh.initNode();
  nh.subscribe(sub);

}

void loop()
{
 // Enabling the motor pins
  digitalWrite(24,HIGH);
  digitalWrite(25,HIGH);
  
  // Clearing the the Ultrasonic Trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
// Calculating the distance
  distance= duration*0.034/2;
//Serial.println(distance);

// Refreshing the Ros node
  nh.spinOnce();
  delay(10);
}
  



  
  


