//#include <ros.h>
//#include <std_msgs/Float32.h>
//#include <std_msgs/Int32.h>
//#include <ros/time.h>

#define ERR_THR 100
#define DELAY_MILI 2

//ros::NodeHandle nh;  
//std_msgs::Int32 SICK_debug; 
//std_msgs::Float32 SICK_rdistance; 
//ros::Publisher SICK_distance("SICK_distance", &SICK_debug); 
//ros::Publisher SICK_realdistance("SICK_realdistance", &SICK_rdistance);

int buttonPin = 2;    // select the input pin for the potentiometer
int sensorValue = 0;   
char outputValue; 
int lastValues[20]; 
int counter = 0; 
long t0 = 0; 
long t1 = 0;
long tm; 
bool countingFlag = false; 
bool endFlag = true; 

void setup() {
  
  pinMode(buttonPin, INPUT);
  Serial.begin(19200);
}

void loop() {
  
  sensorValue = digitalRead(buttonPin);
  
  tm = millis() - t1; 
  // letterEnd? wordEnd?
  if(endFlag == false && tm > 500){
   
    Serial.print(' ');
    
    endFlag = true;  
  }
  
  // start counting
  if(countingFlag == false && sensorValue == 1){
    t0 = millis();
    if(t0 - t1 > 900){
       Serial.print('/');
    }
    tm = 0; 
    countingFlag = true; 
  }

  // examine pressing time
  if( sensorValue == 0 && countingFlag == true ){
    countingFlag = false;
    t1 = millis();
    if( t1 - t0 > 200 ){
      outputValue = '-'; 
    }else{
      outputValue = '.';
    }
    Serial.print(outputValue);
    endFlag = false; 
    
  }
  delay(DELAY_MILI); 
   
}
