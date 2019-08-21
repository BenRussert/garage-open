unsigned long duration;
unsigned long THRESHOLD;
bool isOpen;
String status;

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
  isOpen = false;
  status = "Loading";
  Particle.variable("duration", duration);
  Particle.variable("garageDoor", status);
  Particle.variable("isOpen", isOpen);
}

void loop()
{

  delay(1000);            // even cicuits need a break
  digitalWrite(D2, HIGH); // activate trigger
  delayMicroseconds(10);
  digitalWrite(D2, LOW); // de-activate trigger

  duration = pulseIn(D6, HIGH); // how long until a reply?
                                // a blocking call so may wait a few seconds

  if (duration < THRESHOLD)
  {
    // I'll fix this api later, but isOpen means something is "CLOSE" to the sensor
    status = "Open";
    isOpen = true;
    digitalWrite(D4, HIGH); // activate trigger
  }
  else
  {
    status = "Closed";
    isOpen = false;
    digitalWrite(D4, LOW); // activate trigger
  }
}