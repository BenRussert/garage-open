unsigned long duration;
unsigned long THRESHOLD;
bool isOpen;
bool wasOpen;

inline const char *const boolToString(bool b)
{
  return b ? "true" : "false";
}

void publishStatus(bool shouldPublish)
{
  if (shouldPublish)
  {
    Particle.publish("GARAGE_IS_OPEN", boolToString(isOpen), 60, PRIVATE);
    Particle.publish("GARAGE_DISTANCE", String(duration), 60, PRIVATE);
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

  // GND pin goes to ground
  // VCC pin goes to VIN on the photon

  pinMode(D6, INPUT);  // echo / yellow
  pinMode(D2, OUTPUT); // Trig / orange
  Particle.variable("isOpen", isOpen);
  Particle.variable("duration", duration);
  THRESHOLD = 1000;
  isOpen = checkIfOpen();
  publishStatus(true);
}

void loop()
{
  delay(1000); // even cicuits need a break

  if (checkIfOpen())
  {
    isOpen = true;
  }
  else
  {
    isOpen = false;
  }
  publishStatus(wasOpen != isOpen);
}