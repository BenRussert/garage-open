unsigned long THRESHOLD;
bool isOpen;
bool wasOpen;
// String status;
// String previousStatus;
inline const char *const boolToString(bool b)
{
  return b ? "true" : "false";
}

void publishStatus(bool shouldPublish)
{
  if (shouldPublish)
  {
    Particle.publish("isOpen", boolToString(isOpen), 60, PRIVATE);
  };
  // reset after publish, but before new measurement
  wasOpen = isOpen;
}

bool checkIfOpen(unsigned long threshold = THRESHOLD)
{
  digitalWrite(D2, HIGH); // activate trigger
  delayMicroseconds(10);
  digitalWrite(D2, LOW); // de-activate trigger

  unsigned long duration = pulseIn(D6, HIGH); // how long until a reply?
  // open if duration < THRESHOLD, else closed
  return duration < threshold;
}

void setup()
{

  // ultrasonic range finder Robotshop RB-lte-54

  // GND pin goes to ground
  pinMode(D6, INPUT);  // echo
  pinMode(D2, OUTPUT); // Trig
  // VCC pin goes to VIN on the photon

  // For LED
  pinMode(D4, OUTPUT);

  THRESHOLD = 2000;
  isOpen = checkIfOpen();
  publishStatus(true);
  Particle.variable("isOpen", isOpen);
}

void loop()
{
  delay(1000); // even cicuits need a break

  if (checkIfOpen())
  {
    isOpen = true;
    digitalWrite(D4, HIGH); // activate trigger
  }
  else
  {
    isOpen = false;
    digitalWrite(D4, LOW); // activate trigger
  }
  publishStatus(wasOpen != isOpen);
}