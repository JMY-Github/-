#define PIN_LED 13
unsigned int count, toggle;


void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200); // Initialize serial port
  while (!Serial) {
    ; // wait for serial port to connect.
  }
  digitalWrite(PIN_LED, 0); // turn off LED.
  digitalWrite(PIN_LED, 1);
  delay(1000);
  count = 0;
}


void loop() {
  toggle = 0; //toggle LED value.
  count++;
  digitalWrite(PIN_LED, toggle); // update LED status.
  delay(100);
  toggle = 1;
  digitalWrite(PIN_LED, toggle);
  delay(100); // wait for 100 milliseconds
  if (count == 5) {
    toggle = 0;
    digitalWrite(PIN_LED, toggle);
    while(1){

    }

  }
}