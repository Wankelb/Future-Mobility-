#include <SoftwareSerial.h>

SoftwareSerial sim808(7,8);

int count=0;
int smsSent = 0;
int start = 0;
int sysStop = 1;
boolean smsReceived;
int safe = 1;
 
char Received_SMS;    
char deneme;          
short yes=-1,no=-1,sStatus=-1;      
String mssg;
unsigned long looptime = 0;
unsigned long serialtime = 0;

//Ultra
int trigPin = 9;    
int echoPin = 10;    
long duration, cm;

//Buttons
const int buttonPin1 = 2;     
const int buttonPin2 = 3;
int buttonState1 = 0;         
int buttonState2 = 0;

//Buzzer 
const int buzzer = 5; 

void setup()
{
  sim808.begin(9600);   
  Serial.begin(9600);     
  Serial.println("Init State ...");
  delay(5000);         
  ReceiveMode();       

  //Ultra
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 // Knopf für neustart und stop
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
// Buzzer für Alarm
  pinMode(buzzer, OUTPUT); 
  
}

void loop()
{

  buttonState1 = digitalRead(buttonPin1);
    
  if (buttonState1 == HIGH) {
    // Start the System
    Serial.println("System started!");
    start = 1;
    sysStop = 0;
    
  }
  
  if(start){
   
    if (!sysStop){
       while(safe && start && !sysStop){
        
        ultra();
        stopSys();
      
        if (cm > 0 && cm < 20){
          safe = 0;
        }     
      }
      
      while(!safe && start){
        if (smsSent != 1){
          Serial.println("SMS sending...");
          sendSMS(); 
          smsSent = 1;
          Serial.println("SMS sent...");
          Serial.println("Alarm ON!");
          Serial.println("Waiting for response...");
        }
        
        readSMS();
        alarm();
        stopSys();
        
      }
    }
  }  
}

void stopSys(){
  //Knopf 2 für stoppen
  buttonState2 = digitalRead(buttonPin2); 
  if (buttonState2 == HIGH) {
    
    sysStop = 1;
    safe = 1;
    smsSent=0;
    Serial.println("Sytem stopped!");
   
  } 
}

void sendSMS()
{
  Serial.println("SOS!");

  sim808.println("AT+CMGS=\"+xxx_XXX\"");
  delay(500);
  sim808.println("Warnung! Bewegung erkannt!!");
  sim808.println("Alarm ist an!");
  sim808.println("Moechten Sie der Polizei einen Hinweis geben und Ihren Wohnort mitteilen ?\n");
  sim808.println("Ja/Nein");
  
  sim808.write(0x1a);

  delay(500);
  
}

void ultra()
{
  //Ultraschall

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  // Umwandlung von Spannung zum Cm 
  cm = (duration/2) / 29.1;     
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);

}

void readSMS(){
  String RSMS;             
                           
  
    while(sim808.available()>0){       
        Received_SMS=sim808.read();  
        Serial.print(Received_SMS);   
        RSMS.concat(Received_SMS);

        if((RSMS.indexOf("Ja")>-1) || (RSMS.indexOf("ja")>1) || (RSMS.indexOf("JA") > -1)){
          yes = 1;
        }

        else if((RSMS.indexOf("Nein")>-1) || (RSMS.indexOf("nein")>1) || (RSMS.indexOf("NEIN") > -1)){
          no = 1;
          
        }                             
    }
    
  if(yes!=-1){                         
       
    delay (500);
    return gps();
                                               
  }


  if(no!=-1){                   
  delay(1000);
  
  ReceiveMode();
  safe = 1;
  
  yes=-1;
  no=-1;
  start = 0;
  sysStop = 1;
  safe = 1;
  smsSent = 0;
  Serial.println("System stopped!");
  delay(1000);
  return;
  }
}

void gps()
{
  String latitude, longitude, date, year, month, day, hour, minute, get_latitude, get_longitude;
  sim808.print("AT+CGNSINF\r\n"); delay(1000);                                           
  readsimPort();  
  if((mssg.indexOf("+CGNSINF: 1,1,") > -1)){
    Serial.println("GPS On, Getting Location..."); delay(10);
    date = getValue(mssg, ',', 2);                 delay(10);
    year = date.substring(0, 4);                   delay(10);
    month = date.substring(4, 6);                  delay(10);
    day = date.substring(6, 8);                    delay(10);
    hour = date.substring(8, 10);                  delay(10);
    minute = date.substring(10, 12);               delay(10);

    get_latitude = getValue(mssg, ',', 3);         delay(10);
    latitude = get_latitude.substring(0, 10);      delay(10);

    get_longitude = getValue(mssg, ',', 4);        delay(10);
    longitude = get_longitude.substring(0, 11);    delay(10);

    mssg = "";                                     delay(10);
    readsimPort();                                 delay(10);

    sim808.println("AT+CMGS=\"+4915774226468\"");                                                       delay(50);
    
    sim808.println("Standort");                                                                   delay(10);
    
    sim808.println("https://www.google.com/maps/search/?api=1&query=" + latitude + "," + longitude);    delay(10);
    
    sim808.println("Datum :" + day + "/" + month + "/" + year);                                          delay(10);
    
    sim808.println("Uhrzeit :" + hour + ":" + minute);                                                     delay(10);

    sim808.println(" Hinweis und Ihrer Wohnort wurde der Polizei mitgeteilt. \n");
    
    sim808.write(0x1a);
    delay(500);
    sim808.flush();

    delay(3000);
    yes=-1;
    no=-1;
    start = 0;
    sysStop = 1;
    safe = 1;
    smsSent = 0;
    
    return;
  }
}

void readsimPort() 
{
  serialtime = looptime;    delay(1);
  while ((looptime - serialtime) < 200)
  {
    looptime = millis();
    while (sim808.available())
    {
      looptime = millis();
      serialtime = looptime;
      char c = sim808.read();  //Ein Byte vom SerialBuffer greifen 
      mssg += c; //Umwandlung von Bytes zu String
    }
  }
  sim808.flush();
}

void Serialcom() // Einlesen für die Befehle von Sim808
{
  delay(500);
  while(Serial.available())                                                                      
  {
    sim808.write(Serial.read());
  }
  while(sim808.available())                                                                      
  {
    Serial.write(sim808.read());
  }
}

void ReceiveMode(){       
  
  sim808.println("AT"); // Überprüfung, ob SIM 808 an ist 
  Serialcom(); // Lesen und Print 
  sim808.println("AT+CMGF=1"); // Umwandlung von der gesendeten Sms von Bit zu Text
  Serialcom();
  sim808.println("AT+CNMI=2,2,0,0,0"); // Einlesen von erhaltenen Nachrichten 
  Serialcom();
  sim808.println("AT+CGPSPWR=1"); // Gps an
  Serialcom();
  sim808.println("AT+CGNSSEQ=RMC"); // Verfahren für Gps Format
  Serialcom();
}

void alarm(){ 
  tone(buzzer, 500); delay(500);        
  noTone(buzzer);    delay(500);       
}

String getValue(String data, char separator, int index)//String Verteiler 
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) 
  {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
