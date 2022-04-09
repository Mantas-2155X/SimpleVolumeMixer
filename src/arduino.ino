#define DeviceCount 4

#define Device0 A2
#define Device1 A3
#define Device2 A4
#define Device3 A5

int currentVol[DeviceCount];
int previousVol[DeviceCount];

bool dirty;

void setup() 
{
  pinMode(Device0, INPUT);
  pinMode(Device1, INPUT);
  pinMode(Device2, INPUT);
  pinMode(Device3, INPUT);

  Serial.begin(9600);
}

void loop() 
{
  currentVol[0] = analogRead(Device0);
  delay(15);
  currentVol[1] = analogRead(Device1);
  delay(15);
  currentVol[2] = analogRead(Device2);
  delay(15);
  currentVol[3] = analogRead(Device3);
  delay(15);

  for (int i = 0; i < DeviceCount; i++)
  {
    if (currentVol[i] > previousVol[i] + 1 || currentVol[i] < previousVol[i] - 1)
    {
      dirty = true;
      previousVol[i] = currentVol[i];
    }
  }

  if (dirty)
  {
    dirty = false;
    Serial.println(
      String(map(currentVol[0], 0, 1023, 0, 65536)) + ' ' + 
      String(map(currentVol[1], 0, 1023, 0, 65536)) + ' ' + 
      String(map(currentVol[2], 0, 1023, 0, 65536)) + ' ' + 
      String(map(currentVol[3], 0, 1023, 0, 65536)));

    delay(25);
  }
}
