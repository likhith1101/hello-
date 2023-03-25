#include <LiquidCrystal.h>
#include <stdio.h>

LiquidCrystal lcd(6, 7, 5, 4, 3, 2);

#include <SoftwareSerial.h>
SoftwareSerial mySerial(8,9);

#include <Wire.h>
#include "dht.h"
#define dht_apin 11
dht DHT;


int tempc=0,humc=0;
int mq2v=0,mq3v=0,ldrv=0;
//#define measurePin = 0; //Connect dust sensor to Arduino A0 pin
//#define ledPower   = 8; //Connect 3 led driver pins of dust sensor to Arduino D2

int ledPower   = A1;
int measurePin = A0;
int buzzer     = 13;
int fan        = 10;


int samplingTime  = 280; // time required to sample signal coming out   of the sensor
int deltaTime     = 40; // 
int sleepTime     = 9680;
float voMeasured  = 0;
float calcVoltage = 0;
float dustDensity = 0;

int ii=0,i=0,lop=0;
int  gps_status=0;
float latitude=0; 
float logitude=0;                       
String Speed="";
String gpsString="";
char *test="$GPRMC";


unsigned char gv=0,msg1[10],msg2[11];
 float lati=0,longi=0;
unsigned int lati1=0,longi1=0;
unsigned char flat[5],flong[5];
char finallat[10],finallong[10];



char res[130];
void serialFlush1()
{
  while(mySerial.available() > 0) 
       {
         char t = mySerial.read();
       }
} 

void myserialFlush()
{
  while(mySerial.available() > 0) 
  {
    char t = mySerial.read();
  }
} 


char check(char* ex,int timeout)
{
  int i=0;
  int j = 0,k=0;
  while (1)
  {
    sl:
    if(mySerial.available() > 0)
    {
      res[i] = mySerial.read();
      if(res[i] == 0x0a || res[i]=='>' || i == 100)
      {
        i++;
        res[i] = 0;break;
      }
      i++;
    }
    j++;
    if(j == 30000)
    {
      k++;
     // Serial.println("kk");
      j = 0;  
    }
    if(k > timeout)
    {
      //Serial.println("timeout");
      return 1;
     }
  }//while 1
  if(!strncmp(ex,res,strlen(ex)))
  {
   // Serial.println("ok..");
    return 0;
   }
  else
  {
   // Serial.print("Wrong  ");
   // Serial.println(res);
    i=0;
    goto sl;
   }
} 

char buff[200],k=0;
void upload(unsigned int s1,unsigned int s2,unsigned int s3);
char readserver(void);
void clearserver(void);

const char* ssid = "iotserver";
const char* password = "iotserver123";


int sti=0;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete


void get_dustvalue()
{
  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(samplingTime);
  voMeasured = analogRead(measurePin); // read the dust value
  delayMicroseconds(deltaTime);

  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);
  
  calcVoltage = (voMeasured * (5.0 / 1024.0));
  dustDensity = 170 * calcVoltage - 0.1;

  //Serial.println(dustDensity); // unit: ug/m3
  //delay(1000);
}

void lcdbasic1()
{  
 lcd.clear(); 
 lcd.setCursor(0,0);lcd.print("D:");   //2,0
 lcd.setCursor(7,0);lcd.print("M2:");  //10,0
 lcd.setCursor(0,1);lcd.print("M3:");  //3,1
 lcd.setCursor(8,1);lcd.print("L:");   //10,1
}
void lcdbasic2()
{
 lcd.clear();
 lcd.setCursor(0,0);lcd.print("Temp:");  //5,0
 lcd.setCursor(0,1);lcd.print("Hum:");   //5,1 
}

void setup() 
{
 Serial.begin(9600);//serialEvent();
 mySerial.begin(9600);

 pinMode(ledPower, OUTPUT);
 pinMode(buzzer, OUTPUT);
 pinMode(fan, OUTPUT);
 
 digitalWrite(buzzer, HIGH);
 digitalWrite(fan, LOW);
  
 lcd.begin(16, 2);lcd.cursor();  
 lcd.print("    Air Quality");
 lcd.setCursor(0,1); 
 lcd.print("     Monitoring");
  delay(2000);

  get_gps();

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.write("Lat:");
     for(ii=0;ii<=6;ii++) lcd.write(finallat[ii]);
     
    lcd.setCursor(0,1);
    lcd.write("Long:");
     for(ii=0;ii<=7;ii++) lcd.write(finallong[ii]);    
  delay(1500); 
  
 wifiinit();
  delay(1000);
   
 lcd.clear(); 
 lcd.setCursor(0,0);lcd.print("D:");   //2,0
 lcd.setCursor(7,0);lcd.print("M2:");  //10,0
 lcd.setCursor(0,1);lcd.print("M3:");  //3,1
 lcd.setCursor(8,1);lcd.print("L:");   //10,1
}

char modes='x';
int cntlmk=0;
void loop() 
{
  lcdbasic1();
 for(int tp=0;tp<20;tp++)
    {
      get_dustvalue();
      lcd.setCursor(2,0);convertl(dustDensity);  delay(100);

      mq2v = analogRead(A2);
      lcd.setCursor(10,0);convertl(mq2v);   delay(100);
      
      mq3v = analogRead(A3);
      lcd.setCursor(3,1);convertl(mq3v);   delay(100);

      ldrv = analogRead(A4);
      lcd.setCursor(10,1);convertl(ldrv);   delay(100);

      if(mq2v > 200 || mq3v > 120)
        {
          digitalWrite(buzzer, LOW);
          digitalWrite(fan, HIGH);
        }
      else
        {
          digitalWrite(buzzer, HIGH);
          digitalWrite(fan, LOW);  
        }
    }
 
 lcdbasic2();
 for(int tp=0;tp<30;tp++)
    {
          DHT.read11(dht_apin);

      tempc = DHT.temperature;
      humc  = DHT.humidity;

    lcd.setCursor(5,0);convertl(tempc);
    lcd.setCursor(5,1);convertl(humc);
    delay(100);    
    }
    
 cntlmk++;
 if(cntlmk >= 10)
   {
   
    upload(finallat,finallong,tempc,humc,dustDensity,mq2v,mq3v,ldrv);
   
   }
 delay(1000);  
}


void serialEvent() 
{
   while(Serial.available()) 
        {         
         char inChar = (char)Serial.read();
          if(inChar == '*')
            {
               sti=1;
            }
          if(sti == 1)
            {
               inputString += inChar;
            }
          if(inChar == '#')
            {sti=0;
              stringComplete = true;      
            }
        }
}


char bf2[50];
void upload(const char *s1,const char *s2,int s3,int s4,int s5,int s6,int s7,int s8)
{
  delay(2000);
  lcd.setCursor(15, 1);lcd.print("U");
  myserialFlush();
  mySerial.println("AT+CIPSTART=4,\"TCP\",\"projectsfactoryserver.in\",80");
    
  //http://projectsfactoryserver.in/storedata.php?name=pf5&s1=25&s2=35
  //sprintf(buff,"GET http://embeddedspot.top/iot/storedata.php?name=iot139&s1=%u&s2=%u&s3=%u\r\n\r\n",s1,s2);
  
      delay(8000);
  //https://projectsfactoryserver.in/storedata.php?name=iotgps&lat=17.167898&lan=79.785643   
      memset(buff,0,strlen(buff));
      sprintf(buff,"GET http://projectsfactoryserver.in/storedata.php?name=iot224&lat=%s&lan=%s&s1=%u&s2=%u&s3=%u&s4=%u&s5=%u&s6=%u\r\n\r\n",s1,s2,s3,s4,s5,s6,s7,s8);
         
              delay(2000);
              
              mySerial.println("AT+CIPCLOSE");
       lcd.setCursor(15, 1);lcd.print(" ");  
}

char readserver(void)
{
  char t;
  delay(2000);
  lcd.setCursor(15, 1);lcd.print("R");
  myserialFlush();
  mySerial.println("AT+CIPSTART=4,\"TCP\",\"projectsfactoryserver.in\",80");

  //http://projectsfactoryserver.in/last.php?name=amvi001L

      delay(8000);
      memset(buff,0,strlen(buff));
      sprintf(buff,"GET http://projectsfactoryserver.in/last.php?name=iot4L\r\n\r\n");
      myserialFlush();
      sprintf(bf2,"AT+CIPSEND=4,%u",strlen(buff));
      mySerial.println(bf2);
      
         delay(5000);
          
          
          myserialFlush();
          mySerial.print(buff);
          
       //read status
        while(1)
        {
           while(!mySerial.available());
            t = mySerial.read();
           // Serial.print(t);
            if(t == '*' || t == '#')
            {
              if(t == '#')return 0;
              while(!mySerial.available());
               t = mySerial.read();
             //  Serial.print(t);
               delay(1000);
                myserialFlush();
               return t;
            }
        }
              delay(2000);
              
       mySerial.println("AT+CIPCLOSE");
       lcd.setCursor(15, 1);lcd.print(" "); 
       delay(2000);  
return t;
}

void clearserver(void)
{
  delay(2000);
  lcd.setCursor(15, 1);lcd.print("C");
  myserialFlush();
  mySerial.println("AT+CIPSTART=4,\"TCP\",\"projectsfactoryserver.in\",80");

       delay(5000);
          
          
          myserialFlush();
          mySerial.print(buff);
          
          delay(2000);
          myserialFlush();
      
              
              
       mySerial.println("AT+CIPCLOSE");
       lcd.setCursor(15, 1);lcd.print(" "); 
       delay(2000);  
}


void wifiinit()
{
 char ret;  
  st:
  mySerial.println("ATE0");
  ret  = check((char*)"OK",50);
  mySerial.println("AT");
  ret  = check((char*)"OK",50);
  if(ret != 0)
  {
    delay(1000);
   goto st; 
  }
  
     lcd.clear();lcd.setCursor(0, 0);lcd.print("CONNECTING");  
  mySerial.println("AT+CWMODE=1");
   ret  = check((char*)"OK",50);
 cagain:
    
  myserialFlush();
  mySerial.print("AT+CWJAP=\"");
  mySerial.print(ssid);
  mySerial.print("\",\"");
  mySerial.print(password);
  mySerial.println("\"");
  if(check((char*)"OK",300))goto cagain;    
  mySerial.println("AT+CIPMUX=1");
  delay(1000);
 

  lcd.clear();lcd.setCursor(0, 0);lcd.print("WIFI READY"); 
}

void converts(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
   Serial.write(a);
   Serial.write(c);
   Serial.write(e); 
   Serial.write(g);
   Serial.write(h);
}

void convertl(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
   //lcd.write(a);
   //lcd.write(c);
   lcd.write(e); 
   lcd.write(g);
   lcd.write(h);
}

void convertk(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
  // lcd.write(a);
  // lcd.write(c);
  // lcd.write(e); 
  // lcd.write(g);
   lcd.write(h);
}




void gpsEvent()
{
  gpsString="";
  while(1)
  {
   //while (gps.available()>0)            //Serial incoming data from GPS
    while (Serial.available() > 0)
   {
    //char inChar = (char)gps.read();
    char inChar = (char)Serial.read();
     gpsString+= inChar;                    //store incoming data from GPS to temparary string str[]
     i++;
    // Serial.print(inChar);
     if (i < 7)                      
     {
      if(gpsString[i-1] != test[i-1])         //check for right string
      {
        i=0;
        gpsString="";
      }
     }
    if(inChar=='\r')
    {
     if(i>60)
     {
       gps_status=1;
       break;
     }
     else
     {
       i=0;
     }
    }
  }
   if(gps_status)
    break;
  }
}

void get_gps()
{
  
  lcd.clear();
  lcd.print("Getting GPS Data");
  lcd.setCursor(0,1);
  lcd.print("Please Wait.....");
 
   gps_status=0;
   int x=0;
   while(gps_status==0)
   {
    gpsEvent();
    int str_lenth=i;
    coordinate2dec();
    i=0;x=0;
    str_lenth=0;
   }
}
void coordinate2dec()
{
  String lat_degree="";
    for(i=19;i<=20;i++)         
      lat_degree+=gpsString[i];
      
  String lat_minut="";
     for(i=20;i<=21;i++)         
      lat_minut+=gpsString[i];
     for(i=23;i<=24;i++)         
      lat_minut+=gpsString[i];


       
  String log_degree="";
    for(i=31;i<=33;i++)
      log_degree+=gpsString[i];
  String log_minut="";
    for(i=34;i<=35;i++)
      log_minut+=gpsString[i];
    for(i=37;i<=38;i++)
      log_minut+=gpsString[i];


    Speed="";
    for(i=42;i<45;i++)          //extract longitude from string
      Speed+=gpsString[i];
      
     float minut= lat_minut.toFloat();
     minut=minut/60;
     float degree=lat_degree.toFloat();
     latitude=degree+minut;
     
     minut= log_minut.toFloat();
     minut=minut/60;
     degree=log_degree.toFloat();
     logitude=degree+minut;
}

void gps_convert()
{
  if(gps_status)
  {
 // Serial.println(gpsString);

  if(gpsString[0] == '$' && gpsString[1] == 'G' && gpsString[2] == 'P' && gpsString[3] == 'R' && gpsString[4] == 'M' && gpsString[5] == 'C')
    {
     // Serial.println("Don11111111111111111111111111111111111111111111111111111\r\n");      
    //  Serial.write(gpsString[18]);Serial.write(gpsString[19]);Serial.write(gpsString[20]);Serial.write(gpsString[21]);Serial.write(gpsString[22]);
     //lcd.setCursor(0,0);
     for(ii=0;ii<9;ii++)
       {
        //lcd.write(gpsString[19+ii]);    
        msg1[ii] = gpsString[19+ii];
        //Serial.write(msg1[ii]);
       }
       //Serial.println("\r\n");
     //lcd.setCursor(0,1);
      for(ii=0;ii<10;ii++)
       {
        //lcd.write(gpsString[32+ii]);
        msg2[ii] = gpsString[32+ii];    
       // Serial.write(msg2[ii]);
       }


              convlat(lati); convlong(longi);
        finallat[0] = msg1[0];
        finallat[1] = msg1[1];
        finallat[2] = '.';
        finallat[3] = flat[0]; finallat[4] = flat[1];finallat[5] = flat[2];finallat[6] = flat[3];finallat[7] = '\0';


        finallong[0] = msg2[0];
        finallong[1] = msg2[1];
        finallong[2] = msg2[2];
        finallong[3] = '.';
        finallong[4] = flong[0];finallong[5] = flong[1];finallong[6] = flong[2];finallong[7] = flong[3];finallong[8] = '\0'; 

   
    }
  }  
}

void convlat(unsigned int value)  
{
             unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;              
      c=c|0x30;
      e=e|0x30; 
    g=g|0x30;              
      h=h|0x30;
   
  // dlcd(a);
//   dlcd(c);dlcd(e); dlcd(g);dlcd(h);//lcddata('A');//lcddata(' ');lcddata(' ');
    
         
               flat[0] = c;
               flat[1] = e;
               flat[2] = g;
             flat[3] = h;
}

void convlong(unsigned int value)  
{
            unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;              
      c=c|0x30;
      e=e|0x30; 
    g=g|0x30;              
      h=h|0x30;
   
  // dlcd(a);
//   dlcd(c);dlcd(e); dlcd(g);dlcd(h);//lcddata('A');//lcddata(' ');lcddata(' ');
    
         
               flong[0] = c;
               flong[1] = e;
               flong[2] = g;
             flong[3] = h;


}
