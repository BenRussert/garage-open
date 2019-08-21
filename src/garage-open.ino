unsigned long duration;
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
    // Particle.publish("GARAGE_IS_OPEN", boolToString(isOpen), 60, PRIVATE);
    Particle.publish("GARAGE_IS_OPEN", String(duration), 60, PRIVATE);
  };
  // reset after publish, but before new measurement
  wasOpen = isOpen;
}

bool checkIfOpen(unsigned long threshold = THRESHOLD)
{
  digitalWrite(D2, HIGH); // activate trigger
  delayMicroseconds(10);
  digitalWrite(D2, LOW); // de-activate trigger

  duration = pulseIn(D6, HIGH); // how long until a reply?
  // open if duration < THRESHOLD, else closed
  return duration < threshold;
}

void setup()
{

  // ultrasonic range finder Robotshop RB-lte-54

  // GND pin goes to ground
  pinMode(D6, INPUT);  // echo / yellow
  pinMode(D2, OUTPUT); // Trig / orange
  // VCC pin goes to VIN on the photon
  pinMode(D7, OUTPUT);
  // For LED
  // pinMode(D4, OUTPUT);
  duration = pulseIn(D6, HIGH); // how long until a reply?
  Particle.variable("isOpen", isOpen);
  Particle.variable("duration", duration);
  THRESHOLD = 2000;
  isOpen = checkIfOpen();
  publishStatus(true);
}

void loop()
{
  delay(1000); // even cicuits need a break

  if (checkIfOpen())
  {
    isOpen = true;
    // digitalWrite(D2, HIGH); // activate trigger
  }
  else
  {
    isOpen = false;
    // digitalWrite(D2, LOW); // activate trigger
  }
  publishStatus(wasOpen != isOpen);
}