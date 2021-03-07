#include <WiFi.h>
#include "time.h"

const char *ssid="itHertzwhenIP";
const char *password="11@35*13";

const char *ntpServer = "pool.ntp.org";
const long  gmtOffset_sec =  -18000;
const int   daylightOffset_sec = 3600;

int diffPin1 = 19;
int diffPin2 = 18;

int diffP[] = {1,0};
int diffM[] = {0,1};
int diffOff[]={0,0};
int diffOn[]= {1,1};

int minPin1 = 0;
int minPin2 = 2;
int minPin3 = 15;

int minOff[]={1,0,1};
int min0[] = {1,0,0}; 
int min1[] = {0,1,0};
int min2[] = {1,1,0};
int min3[] = {0,1,1};
int min4[] = {1,1,1};
int min5[] = {0,0,0};

int hrPin1 = 33;
int hrPin2 = 25;
int hrPin3 = 26;
int hrPin4 = 27;
int hrPin5 = 14;
int hrPin6 = 12;

int hrOff[]={1,1,1,1,0,0};
int hr0[] = {1,1,0,1,1,0};
int hr1[] = {1,0,1,1,0,0};
int hr2[] = {0,0,1,1,0,0};
int hr3[] = {1,1,1,0,0,1};
int hr4[] = {1,1,0,0,0,1};
int hr5[] = {1,1,1,0,0,0};
int hr6[] = {1,1,0,0,0,0};
int hr7[] = {1,1,1,1,1,1};
int hr8[] = {1,1,0,1,1,1};
int hr9[] = {1,1,1,1,1,0};

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  setTime(timeinfo.tm_hour, timeinfo.tm_min);
//  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}
 
void setup() {
  Serial.begin(115200);
    
  pinMode(diffPin1, OUTPUT);
  pinMode(diffPin2, OUTPUT);
  
  pinMode(minPin1, OUTPUT);
  pinMode(minPin2, OUTPUT);
  pinMode(minPin3, OUTPUT);
  
  pinMode(hrPin1, OUTPUT);
  pinMode(hrPin2, OUTPUT);
  pinMode(hrPin3, OUTPUT);
  pinMode(hrPin4, OUTPUT);
  pinMode(hrPin5, OUTPUT);
  pinMode(hrPin6, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to "); Serial.println(ssid);
 
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(500);
 
    if ((++i % 16) == 0)
    {
      Serial.println(F(" still trying to connect"));
    }
  }
 
  Serial.print(F("Connected. My IP address is: "));
  Serial.println(WiFi.localIP());

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
}

void loop() {
  printLocalTime();
  delay(10000);
}

void setHour(int hr[]){
  digitalWrite(hrPin1,hr[0]);
  digitalWrite(hrPin2,hr[1]);
  digitalWrite(hrPin3,hr[2]);
  digitalWrite(hrPin4,hr[3]);
  digitalWrite(hrPin5,hr[4]);
  digitalWrite(hrPin6,hr[5]);
} 
void setDiff(int d[]){
  digitalWrite(diffPin1,d[0]);
  digitalWrite(diffPin2,d[1]);
}
void setMin(int minu[]){
  digitalWrite(minPin1,minu[0]);
  digitalWrite(minPin2,minu[1]);
  digitalWrite(minPin3,minu[2]);
}

void setTime(int hr, int mn){
    switch(hr%10){
    case(0):
      setHour(hr0);
    break;
    case(1):
      setHour(hr1);
    break;
    case(2):
      setHour(hr2);
    break;
    case(3):
      setHour(hr3);
    break;
    case(4):
      setHour(hr4);
    break;
    case(5):
      setHour(hr5);
    break;
    case(6):
      setHour(hr6);
    break;
    case(7):
      setHour(hr7);
    break;
    case(8):
      setHour(hr8);
    break;
    case(9):
      setHour(hr9);
    break;
    default:
      setHour(hr0);
    break;  
    }
  
    if(floor(hr/10)==1){
      setDiff(diffM);  
    }else if(floor(hr/10)==2){
      setDiff(diffP);
    }else{
      setDiff(diffOff);
    }

    switch(int(floor(mn/10))){
    case(0):
      setMin(min0);
    break;
    case(1):
      setMin(min1);
    break;
    case(2):
      setMin(min2);
    break;
    case(3):
      setMin(min3);
    break;
    case(4):
      setMin(min4);
    break;
    case(5):
      setMin(min5);
    break;
    default:
      setMin(min0);
    break;  
    }
}
