
// CODE TO CONTROL THE ROBOT USING TWIST  KEYBOARD ALONG WITH THE ULTRASONIC INTERRUPT


// DECLARATION ON THE HEADER FILES
#include <ros.h>
#include <std_msgs/Empty.h>
#include<geometry_msgs/Twist.h>
#include <math.h>

// DECLARATION OF THE HANDLE FOR THE ROS TELEOP MESSAGES
ros::NodeHandle  nh;




//DECLARATION of the Ultrasonic pins
const int trigPin = 23;
const int echoPin = 22;
long duration;
int distance;
bool flag=false;

//Declaration of Ultrasonic functions

void initTimer1()
{
  // Using timer1 for ultrasonic sensor
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
flag = false;
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
 
  if(distance < 10)
  {
    flag = true;
    digitalWrite(13, HIGH);   // Set LED high when obsticle detected
    istop();
  }
//  else
    flag =false;
    digitalWrite(13, LOW);   // Set LED low when no object is there
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
  digitalWrite(7,LOW);
  digitalWrite(6,LOW);
  digitalWrite(3,LOW);
  digitalWrite(2,LOW);
}

// Declaration of CallBack for cmd_vel
void messageCb( const geometry_msgs::Twist& msg){
  if(msg.linear.x>0&&msg.angular.z==0)
  {
            int y=msg.linear.x;
            forward(y);
            //digitalWrite(3,LOW); //forward
            //digitalWrite(7,LOW);
            //analogWrite(2,((int)msg.linear.x < 255) ? (int)msg.linear.x : 255);
            //analogWrite(6,((int)msg.linear.x < 255) ? (int)msg.linear.x : 255);

}
else  if(msg.linear.x<0&&msg.angular.z==0)
{
            int y=msg.linear.x;
            reverse(y);
            //digitalWrite(2,LOW); //reverse
            //digitalWrite(6,LOW);
            //analogWrite(3,(-(int)msg.linear.x < 255) ? -(int)msg.linear.x : 255);
            //analogWrite(7,(-(int)msg.linear.x < 255) ? -(int)msg.linear.x : 255);
  
}
else if(msg.linear.x==0 &&msg.angular.z>1.0)
{ 
  int y=msg.angular.z;
  left(y);
 //digitalWrite(3,LOW);//left
 //analogWrite(2,((int)msg.angular.z < 255) ? (int)msg.angular.z : 255);
 
}
else if(msg.linear.x==0 &&msg.angular.z<-1.0)
{
  int y=msg.angular.z;
  right(y);
 //digitalWrite(7,LOW);//right
 //analogWrite(6,(-(int)msg.angular.z < 255) ? -(int)msg.angular.z : 255);
 
}
else
{
  digitalWrite(7,LOW);
  digitalWrite(6,LOW);
  digitalWrite(3,LOW);
  digitalWrite(2,LOW);
}
}

// Subscription to topic
ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &messageCb );


void setup() {
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(24,OUTPUT);

  pinMode(3,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(25,OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(13,OUTPUT);

 
  nh.initNode();
  nh.subscribe(sub);

}

void loop() {
  digitalWrite(24,HIGH);
  digitalWrite(25,HIGH);
  nh.spinOnce();
  delay(10);


  
  


  }
  



  
  


