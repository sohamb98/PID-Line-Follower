
int l1=A4;
int l2=A3;

int r1=A2;
int r2=A1;

int enl=11;
int enr=10;

int a[8];
int last_proportional=0;
int integral=0;



//bool leds=false;


char select_turn(unsigned char found_left,unsigned char found_right,unsigned char found_st); //AI INITIALIZAION

int mod(int v); // MODULUS FUNCTION
int set_motors(int a,int b);
void turn(char dir);
void PID();

 int right=0;
 int left=0;

void setup() {

  pinMode(l1,OUTPUT);   // Left motor output
  pinMode(l2,OUTPUT);
  
  pinMode(r1,OUTPUT);  //Right motor output
  pinMode(r2,OUTPUT);

  pinMode(enl,OUTPUT);   //Enable pins of R and L motors
  pinMode(enr,OUTPUT);

  pinMode(13, INPUT);
  Serial.begin(9600);

 // pinMode(ledg,OUTPUT);
  //pinMode(ledr,OUTPUT);
//  digitalWrite(ledg,leds);
 // digitalWrite(ledr,leds);
}

void loop() {

  int A = digitalRead(13);

  if(A==1){
  stop();
  delay(100);
  }
  else{
  PID();    //Control invoked
 
  unsigned char found_left=0;
  unsigned char found_right=0;   // turn paratmeter.
  unsigned char found_st=0;

readline();
  if(a[0]==LOW)
    found_left=1;
    
  if(a[7]==LOW)
    found_right=1;
 
  if(a[3]==LOW||a[4]==LOW)
  found_st=1;

  unsigned char dir;

  dir=select_turn(found_left, found_right, found_st);
  turn(dir);

  }

}// MAIN body ends



int set_motors(int l,int r) // Motor setup
{
  Serial.println(r);
  Serial.println(l);


if(l>0&&r>0)
{
  analogWrite(enl,mod(l));
analogWrite(enr,mod(r));

    
  digitalWrite(l1,LOW);
  digitalWrite(l2,HIGH);
  
  digitalWrite(r1,LOW);
  digitalWrite(r2,HIGH);
}

else if(l<0&&r>0)
{
  analogWrite(enl,mod(l));
analogWrite(enr,mod(r));

  digitalWrite(l1,HIGH);
  digitalWrite(l2,LOW);
  
  digitalWrite(r1,LOW);
  digitalWrite(r2,HIGH);
}

else if(l>0&&r<0)
{analogWrite(enl,mod(l));
analogWrite(enr,mod(r));

  digitalWrite(l1,LOW);
  digitalWrite(l2,HIGH);
  
  digitalWrite(r1,HIGH);
  digitalWrite(r2,LOW);
}

else if(l==0&&r==0)
{
  analogWrite(enl,0);
analogWrite(enr,0);

  digitalWrite(l1,HIGH);
  digitalWrite(l2,HIGH);
  
  digitalWrite(r1,HIGH);
  digitalWrite(r2,HIGH);
}
}

int readline()
{ 
  int index=0;
  for(int dPin=2; dPin<=9; dPin++,index++) // Read line Function
  {
    a[index]=digitalRead(dPin);
  }
  int v;
 v=(7000*a[0]+6000*a[1]+5000*a[2]+4000*a[3]+3000*a[4]+2000*a[5]+1000*a[6]+0*a[7])/(a[0]+a[1]+a[2]+a[3]+a[4]+a[5]+a[6]+a[7]);
 Serial.println(a[7]);
 return v;
}

int stop()
{
  analogWrite(enl,0);
  analogWrite(enr,0);
   digitalWrite(l1,LOW);
  digitalWrite(l2,LOW);
  
  digitalWrite(r1,LOW);
  digitalWrite(r2,LOW);
  
}

void turn(char dir)   //Turning setup
{
  switch(dir)
  {
    case 'L':
      set_motors(-45,45);
      delay(350);
      break;
    case 'R':
      set_motors(45,-45);
      delay(350);
      break;
    case 'B':
      set_motors(45,-45);
      delay(650);
      break;
    case 'S':
    break;
  }
    
 }


void PID()
{ int i;       // Control function
  int power_difference=0;
  float Kp,Ki,Kd;
  unsigned int position;
  int derivative,proportional;
  while(1)
  { 
  position=readline();
  Serial.println(position);
  proportional=((int)position-3500);
  
   derivative = proportional-last_proportional;
   integral = integral+proportional;

  last_proportional=proportional;
  Kp=0.001;
  Ki=0.0001;
  Kd=6.0;

  power_difference= proportional*Kp + integral*Ki + derivative*Kd;
  const int max=60;
  if(power_difference>max)
   power_difference=max;
  if(power_difference<-max)
   power_difference= (-1*max);
   
  if(power_difference<0)
  {//left
   set_motors(max+power_difference,max);
  }
  else
  {
   set_motors(max,max-power_difference); //right
  }
  readline();
  if(a[0]==HIGH&&a[1]==HIGH&&a[2]==HIGH&&a[3]==HIGH&&a[4]==HIGH&&a[5]==HIGH&&a[6]==HIGH&&a[7]==HIGH)
    return;
  
  else if(a[0]==LOW||a[7]==LOW)
    return;
  

 
  }  
}

char select_turn(unsigned char found_left,unsigned char found_right,unsigned char found_st) // AI Function
{
 if(found_left==1)
 return 'L';
 else if(found_st==1)
 return 'S';
 else if(found_right==1)
 return 'R';
 else
 return 'B';
 
}


int mod(int v)
{
  if(v<0)
  return -1*v;
  else if(v>0)
  return v;
}



