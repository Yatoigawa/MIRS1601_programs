double val = 0;
byte  PinA = 2;
byte PinB = 3;
int ASet;
int BSet;

void setup()
{
  Serial.begin(9600);
  pinMode(PinA, INPUT);
  pinMode(PinB, INPUT);


  ASet = digitalRead(PinA);
  BSet = digitalRead(PinB);   // read the input pin

  attachInterrupt(0, INCRE, CHANGE);
  attachInterrupt(1, DECRE, CHANGE);

  analogWrite(8, 100);        // for Motor Driving purpose only
}

void loop()
{
  int time = millis() / 1000;
  if (time % 10 == 0)
  {
    Serial.print(time);
    Serial.print("  \t  ");
    Serial.print(val * 6 / 200);
    Serial.println(" rpm");
    val = 0;
    delay(1000);
  }
}

void INCRE()
{
  ASet = digitalRead(PinA) == HIGH;
  val += (ASet != BSet) ? +1 : -1;
}

void DECRE()
{
  BSet = digitalRead(PinB) == HIGH;
  val += (ASet == BSet) ? +1 : -1;
}

