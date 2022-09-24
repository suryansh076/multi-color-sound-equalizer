int led_pin1 = 3 ;
int led_pin2 = 5;
int led_pin3 = 6;
int select = 2;
bool music = false;
int blutooth = 9;
int sound = 7;
int ang = A0;
int feq = 0;
int mapped = 0;
int a[3];
void setup() {
  Serial.begin(9600);
  pinMode(led_pin1, OUTPUT);
  pinMode(led_pin2, OUTPUT);
  pinMode(led_pin3, OUTPUT);
  pinMode(led_pin3, OUTPUT);
  pinMode(select, INPUT);
  pinMode(sound, OUTPUT);
  pinMode(blutooth, OUTPUT);
  pinMode(ang, INPUT);
  digitalWrite(led_pin1, 1);
  delay(1000);
  digitalWrite(led_pin2, 0);
  digitalWrite(led_pin3, 0);
  digitalWrite(select, 0);
}
void loop() {
  if (digitalRead(select) == HIGH)
  {
    Serial.println("hii");
    music = !music;
    delay(1000);
  }
  if (music == true)
  {
    a[0] = 0;
    a[1] = 0;
    a[2] = 0;
    digitalWrite(sound, 1);
    digitalWrite(blutooth, 0);
    //    Serial.println("byee");
    feq = (analogRead(A0));
    Serial.println(feq);
    if ((feq > 0) && (feq < 540))
    {
      if ((feq > 500) && (feq < 540))
      {
        int value = fliker(feq);
        analogWrite(led_pin1, (255 - value));
      }
      else if ((feq > 450) && (feq < 500))
      {
        int value = fliker(feq);
        analogWrite(led_pin2, (255 - value));
      }
      else if ((feq < 450 ))
      {
        int value = fliker(feq);
        analogWrite(led_pin3, (255 - value));
      }
    }
    else
    {
      analogWrite(led_pin1, 0);
      analogWrite(led_pin2, 0);
      analogWrite(led_pin3, 0);
    }
  }
  else {
    Serial.println("hiii");
    digitalWrite(blutooth, 1);
    digitalWrite(sound, 0);
    if (Serial.available() > 0)
    {
      String s = Serial.readStringUntil(')');

      for (int i = 0; i < 3; i++)
      {
        a[i] = s.toInt();
        for (int j = 0; j < s.length(); j++)
        {
          if (s[j] == '.')
          {
            s.remove(0, (j + 1));//bcz 0 is starting and including but j is excludeing(j-1) so include j we need to perform (j+1)
            break;
          }
        }
      }
    }
    Serial.print("r: ");
    Serial.print(a[0]);
    Serial.print("g: ");
    Serial.print(a[1]);
    Serial.print("b: ");
    Serial.println(a[2]);
    analogWrite(led_pin3, a[0]);
    analogWrite(led_pin2, a[1]);
    analogWrite(led_pin1 , a[2]);


  }
}
int fliker(int feq)
{
  mapped = map(feq, 0, 540 , 0, 255);
  //  Serial.print(mapped);
  //  Serial.print("    ");
  //Serial.println(feq);
  return mapped;
}
