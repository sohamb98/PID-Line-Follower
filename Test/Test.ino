//motor Driver 
#define enA 10
#define in1 A1
#define in2 A2
#define enB 11
#define in3 A3
#define in4 A4

#define s2 A5
#define s3 A6
#define s4 A7

int pwmOutput = 0;
int dPin = 0;
int val[8];
double color[3];

void setup() {
  // put your setup code here, to run once:
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(2, INPUT);
  Serial.begin(9600);
}

void loop() {
  // line Sensor

 

  
  int index = 0;
   for(dPin=2; dPin<=9; dPin++,index++){
    val[index]=digitalRead(dPin);
  }
  //Serial.print(digitalRead(2));  

  for(int i=0; i<8; i++){
    Serial.print(val[i]);
  }
  Serial.print('\n');
  

  
  pwmOutput=225;
  //forward left
  //for(pwmOutput=0; pwmOutput<225; pwmOutput++){
    analogWrite(enA, pwmOutput);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  //forward right
   // analogWrite(enB, pwmOutput);
   // digitalWrite(in3, HIGH);
   // digitalWrite(in4, LOW);
    
    delay(200);
  //}

   color[1]=analogRead(s2);
   //color[2]=analogRead(s3);
   color[3]=analogRead(s4);
   Serial.print(color[1]);
   Serial.print("  ");
   Serial.print(color[2]);
   Serial.print("  ");
   Serial.print(color[3]);
   Serial.print("  ");
   Serial.print('\n');

}
