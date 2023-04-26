
#include <stdio.h>

 
 unsigned char rcv,count,gchr,gchr1,robos='s';
 //char pastnumber[11]="";
 

int sti=0;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete


int ir1   = 2;
int ir2   = 3;
int ir3   = 4;
int ir4   = 5;


int led1_green  = 10;
int led1_yellow = 9;
int led1_red    = 8;


int led2_green  = 13;
int led2_yellow = 12;
int led2_red    = 11;


int led3_green  = A0;
int led3_yellow = A1;
int led3_red    = A2;


int led4_green  = A5;
int led4_yellow = A4;
int led4_red    = A3;


float tempc=0;
float vout=0;


void delay_c(unsigned int itime)
{
  unsigned int x=0,y=0;
  for(x=0;x<itime;x++)
    {
      for(y=0;y<20000;y++);
    }
}

void t_delay(unsigned int tvalue)
{
unsigned int k,l;
for(k=0;k<tvalue;k++)
{  delay(100);
 if(digitalRead(ir1) == HIGH)
   {    
   digitalWrite(led1_green, LOW);digitalWrite(led1_yellow, HIGH);digitalWrite(led1_red, HIGH);
   digitalWrite(led2_green, HIGH);digitalWrite(led2_yellow, HIGH);digitalWrite(led2_red, LOW);
   digitalWrite(led3_green, HIGH);digitalWrite(led3_yellow, HIGH);digitalWrite(led3_red, LOW);
   digitalWrite(led4_green, HIGH);digitalWrite(led4_yellow, HIGH);digitalWrite(led4_red, LOW);
  
    Serial.write("AT+CIPSEND=0,12\r\n");delay(2000);
    Serial.write("Rd-1 Dens\r\n");delay(3000);
   }
   
  if(digitalRead(ir2) == HIGH)
   {        
    digitalWrite(led1_green, HIGH);digitalWrite(led1_yellow, HIGH);digitalWrite(led1_red, LOW);
    digitalWrite(led2_green, LOW);digitalWrite(led2_yellow, HIGH);digitalWrite(led2_red, HIGH);
    digitalWrite(led3_green, HIGH);digitalWrite(led3_yellow, HIGH);digitalWrite(led3_red, LOW);
    digitalWrite(led4_green, HIGH);digitalWrite(led4_yellow, HIGH);digitalWrite(led4_red, LOW);
     
    Serial.write("AT+CIPSEND=0,12\r\n");delay(2000);
    Serial.write("Rd-2 Dens\r\n");delay(3000);
   }
  if(digitalRead(ir3) == HIGH)
   {    
    digitalWrite(led1_green, HIGH);digitalWrite(led1_yellow, HIGH);digitalWrite(led1_red, LOW);
    digitalWrite(led2_green, HIGH);digitalWrite(led2_yellow, HIGH);digitalWrite(led2_red, LOW);
    digitalWrite(led3_green, LOW);digitalWrite(led3_yellow, HIGH);digitalWrite(led3_red, HIGH);
    digitalWrite(led4_green, HIGH);digitalWrite(led4_yellow, HIGH);digitalWrite(led4_red, LOW);
    
    Serial.write("AT+CIPSEND=0,12\r\n");delay(2000);
    Serial.write("Rd-3 Dens\r\n");delay(3000);                           
   }
  if(digitalRead(ir4) == HIGH)
   {  
  digitalWrite(led1_green, HIGH);digitalWrite(led1_yellow, HIGH);digitalWrite(led1_red, LOW);
  digitalWrite(led2_green, HIGH);digitalWrite(led2_yellow, HIGH);digitalWrite(led2_red, LOW);
  digitalWrite(led3_green, HIGH);digitalWrite(led3_yellow, HIGH);digitalWrite(led3_red, LOW);
  digitalWrite(led4_green, LOW);digitalWrite(led4_yellow, HIGH);digitalWrite(led4_red, HIGH);
        
    Serial.write("AT+CIPSEND=0,12\r\n");delay(2000);
    Serial.write("Rd-4 Dens\r\n");delay(3000);                  
   }   
}
}



void okcheck()
{
  unsigned char rcr;
  do{
      rcr = Serial.read();
    }while(rcr != 'K');
}
void link()
{
  unsigned char rcr;
  do{
      rcr = Serial.read();
    }while(rcr != 'L');
}
void setup() 
{
  // initialize serial:
  Serial.begin(9600);serialEvent();
//    serialEvent();

  pinMode(ir1, INPUT);pinMode(ir2, INPUT);pinMode(ir3, INPUT);pinMode(ir4, INPUT);
  
  pinMode(led1_green, OUTPUT);pinMode(led1_yellow, OUTPUT);pinMode(led1_red, OUTPUT);
  pinMode(led2_green, OUTPUT);pinMode(led2_yellow, OUTPUT);pinMode(led2_red, OUTPUT);
  pinMode(led3_green, OUTPUT);pinMode(led3_yellow, OUTPUT);pinMode(led3_red, OUTPUT);
  pinMode(led4_green, OUTPUT);pinMode(led4_yellow, OUTPUT);pinMode(led4_red, OUTPUT);
  

  
  digitalWrite(led1_green, HIGH);digitalWrite(led1_yellow, HIGH);digitalWrite(led1_red, HIGH);
  digitalWrite(led2_green, HIGH);digitalWrite(led2_yellow, HIGH);digitalWrite(led2_red, HIGH);
  digitalWrite(led3_green, HIGH);digitalWrite(led3_yellow, HIGH);digitalWrite(led3_red, HIGH);
  digitalWrite(led4_green, HIGH);digitalWrite(led4_yellow, HIGH);digitalWrite(led4_red, HIGH);

  
  //cli();
  //serialEvent();
  
   


  Serial.write("AT\r\n");         delay(3000);//okcheck();
  Serial.write("ATE0\r\n");         okcheck();
  Serial.write("AT+CIPMUX=1\r\n");delay(3000);//         okcheck();
  Serial.write("AT+CIPSERVER=1,23\r\n"); //        okcheck();

  
  digitalWrite(led1_green, LOW);digitalWrite(led1_yellow, LOW);digitalWrite(led1_red, LOW);
  digitalWrite(led2_green, LOW);digitalWrite(led2_yellow, LOW);digitalWrite(led2_red, LOW);
  digitalWrite(led3_green, LOW);digitalWrite(led3_yellow, LOW);digitalWrite(led3_red, LOW);
  digitalWrite(led4_green, LOW);digitalWrite(led4_yellow, LOW);digitalWrite(led4_red, LOW);

  link();

    
  digitalWrite(led1_green, HIGH);digitalWrite(led1_yellow, HIGH);digitalWrite(led1_red, HIGH);
  digitalWrite(led2_green, HIGH);digitalWrite(led2_yellow, HIGH);digitalWrite(led2_red, HIGH);
  digitalWrite(led3_green, HIGH);digitalWrite(led3_yellow, HIGH);digitalWrite(led3_red, HIGH);
  digitalWrite(led4_green, HIGH);digitalWrite(led4_yellow, HIGH);digitalWrite(led4_red, HIGH);

 serialEvent();
}

void loop() 
{

     t_delay(10);
  digitalWrite(led1_green, HIGH);digitalWrite(led1_yellow, LOW);digitalWrite(led1_red, HIGH);
     t_delay(10);
  digitalWrite(led1_green, LOW);digitalWrite(led1_yellow, HIGH);digitalWrite(led1_red, HIGH);
  digitalWrite(led2_green, HIGH);digitalWrite(led2_yellow, HIGH);digitalWrite(led2_red, LOW);
  digitalWrite(led3_green, HIGH);digitalWrite(led3_yellow, HIGH);digitalWrite(led3_red, LOW);
  digitalWrite(led4_green, HIGH);digitalWrite(led4_yellow, HIGH);digitalWrite(led4_red, LOW);



   t_delay(10); 
  digitalWrite(led2_green, HIGH);digitalWrite(led2_yellow, LOW);digitalWrite(led2_red, HIGH);
    t_delay(10);
  digitalWrite(led1_green, HIGH);digitalWrite(led1_yellow, HIGH);digitalWrite(led1_red, LOW);
  digitalWrite(led2_green, LOW);digitalWrite(led2_yellow, HIGH);digitalWrite(led2_red, HIGH);
  digitalWrite(led3_green, HIGH);digitalWrite(led3_yellow, HIGH);digitalWrite(led3_red, LOW);
  digitalWrite(led4_green, HIGH);digitalWrite(led4_yellow, HIGH);digitalWrite(led4_red, LOW);


 
 t_delay(10);
  digitalWrite(led3_green, HIGH);digitalWrite(led3_yellow, LOW);digitalWrite(led3_red, HIGH);
 t_delay(10);
  digitalWrite(led1_green, HIGH);digitalWrite(led1_yellow, HIGH);digitalWrite(led1_red, LOW);
  digitalWrite(led2_green, HIGH);digitalWrite(led2_yellow, HIGH);digitalWrite(led2_red, LOW);
  digitalWrite(led3_green, LOW);digitalWrite(led3_yellow, HIGH);digitalWrite(led3_red, HIGH);
  digitalWrite(led4_green, HIGH);digitalWrite(led4_yellow, HIGH);digitalWrite(led4_red, LOW);



  t_delay(10);
  digitalWrite(led4_green, HIGH);digitalWrite(led4_yellow, LOW);digitalWrite(led4_red, HIGH);
  t_delay(10);
  digitalWrite(led1_green, HIGH);digitalWrite(led1_yellow, HIGH);digitalWrite(led1_red, LOW);
  digitalWrite(led2_green, HIGH);digitalWrite(led2_yellow, HIGH);digitalWrite(led2_red, LOW);
  digitalWrite(led3_green, HIGH);digitalWrite(led3_yellow, HIGH);digitalWrite(led3_red, LOW);
  digitalWrite(led4_green, LOW);digitalWrite(led4_yellow, HIGH);digitalWrite(led4_red, HIGH);

}



void serialEvent() 
{
  while (Serial.available()) 
        {
         
         char inChar = (char)Serial.read();
           //sti++;
           //inputString += inChar;
          if(inChar == '*')
            {sti=1;
              inputString += inChar;
             //  stringComplete = true;
             // gchr = inputString[sti-1] 
            }
          if(inChar == '#')
            {sti=0;
              stringComplete = true;      



              if(inputString[2] == '1')
                {inputString="";
                  digitalWrite(led1_green, LOW);digitalWrite(led1_yellow, HIGH);digitalWrite(led1_red, HIGH);
                  digitalWrite(led2_green, HIGH);digitalWrite(led2_yellow, HIGH);digitalWrite(led2_red, LOW);
                  digitalWrite(led3_green, HIGH);digitalWrite(led3_yellow, HIGH);digitalWrite(led3_red, LOW);
                  digitalWrite(led4_green, HIGH);digitalWrite(led4_yellow, HIGH);digitalWrite(led4_red, LOW);

    Serial.write("AT+CIPSEND=0,9\r\n");delay(2000);
    Serial.write("Amb Rd1\r\n");delay(3000);
                }              
              if(inputString[2] == '2')
                {inputString="";
                  digitalWrite(led1_green, HIGH);digitalWrite(led1_yellow, HIGH);digitalWrite(led1_red, LOW);
                  digitalWrite(led2_green, LOW);digitalWrite(led2_yellow, HIGH);digitalWrite(led2_red, HIGH);
                  digitalWrite(led3_green, HIGH);digitalWrite(led3_yellow, HIGH);digitalWrite(led3_red, LOW);
                  digitalWrite(led4_green, HIGH);digitalWrite(led4_yellow, HIGH);digitalWrite(led4_red, LOW);
                  
    Serial.write("AT+CIPSEND=0,9\r\n");delay(2000);
    Serial.write("Amb Rd2\r\n");delay(3000);
                }              
              if(inputString[2] == '3')
                { inputString="";
  digitalWrite(led1_green, HIGH);digitalWrite(led1_yellow, HIGH);digitalWrite(led1_red, LOW);
  digitalWrite(led2_green, HIGH);digitalWrite(led2_yellow, HIGH);digitalWrite(led2_red, LOW);
  digitalWrite(led3_green, LOW);digitalWrite(led3_yellow, HIGH);digitalWrite(led3_red, HIGH);
  digitalWrite(led4_green, HIGH);digitalWrite(led4_yellow, HIGH);digitalWrite(led4_red, LOW);
                  
    Serial.write("AT+CIPSEND=0,9\r\n");delay(2000);
    Serial.write("Amb Rd3\r\n");delay(3000);
                }              
              if(inputString[2] == '4')
                {inputString="";
                    digitalWrite(led1_green, HIGH);digitalWrite(led1_yellow, HIGH);digitalWrite(led1_red, LOW);
  digitalWrite(led2_green, HIGH);digitalWrite(led2_yellow, HIGH);digitalWrite(led2_red, LOW);
  digitalWrite(led3_green, HIGH);digitalWrite(led3_yellow, HIGH);digitalWrite(led3_red, LOW);
  digitalWrite(led4_green, LOW);digitalWrite(led4_yellow, HIGH);digitalWrite(led4_red, HIGH);
                 
    Serial.write("AT+CIPSEND=0,9\r\n");delay(2000);
    Serial.write("Amb Rd4\r\n");delay(3000);
                }      
            }
        }
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


/*
   sensorValue = analogRead(analogInPin);
   sensorValue = (sensorValue/9.31);
   lcd.setCursor(1,1); //rc
   lcd.print(sensorValue);
   Serial.print(sensorValue);
