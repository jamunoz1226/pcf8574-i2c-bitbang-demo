#define SDA_PIN 8
#define SCL_PIN 9
#define PCF8574_ADDR 0x20

void i2c_delay() {
  delayMicroseconds(5);
}

void sda_high() { pinMode(SDA_PIN, INPUT_PULLUP); }
void sda_low() { pinMode(SDA_PIN, OUTPUT); digitalWrite(SDA_PIN, LOW); }

void scl_high() { pinMode(SCL_PIN, INPUT_PULLUP); }
void scl_low() { pinMode(SCL_PIN, OUTPUT); digitalWrite(SCL_PIN, LOW); }

// I2C START condition:
// SDA transitions from HIGH to LOW while SCL is HIGH
void i2c_start() {
  sda_high();
  scl_high();
  i2c_delay();
  sda_low();
  i2c_delay();
  scl_low();
}

// I2C STOP condition:
// SDA transitions from LOW to HIGH while SCL is HIGH
void i2c_stop() {
  sda_low();
  i2c_delay();
  scl_high();
  i2c_delay();
  sda_high();
}

// Send one bit on SDA while toggling SCL to clock it into the slave
void i2c_write_bit(bool b) {
  if (b) sda_high();
  else sda_low();

  i2c_delay();
  scl_high();
  i2c_delay();
  scl_low();
}


bool i2c_read_bit() {
  sda_high();
  i2c_delay();

  scl_high();
  i2c_delay();

  bool bit = digitalRead(SDA_PIN);

  scl_low();
  return bit;
}

// After sending a byte the slave pulls SDA LOW to acknowledge (ACK)
bool i2c_read_ack() {
  sda_high();
  i2c_delay();

  scl_high();
  i2c_delay();

  bool ack = digitalRead(SDA_PIN) == LOW;

  scl_low();
  return ack;
}

bool i2c_write_byte(byte data) {
  for (int i = 7; i >= 0; i--) {
    i2c_write_bit((data >> i) & 1);
  }

  return i2c_read_ack();
}

byte i2c_read_byte(bool sendAck) {
  byte data = 0;

  for (int i = 7; i >= 0; i--) {
    if (i2c_read_bit()) data |= (1 << i);
  }

  if (sendAck) sda_low();
  else sda_high();

  i2c_delay();
  scl_high();
  i2c_delay();
  scl_low();

  sda_high();

  return data;
}

bool pcf_write(byte data) {
  i2c_start();

  bool ack1 = i2c_write_byte((PCF8574_ADDR << 1) | 0);
  bool ack2 = i2c_write_byte(data);

  i2c_stop();

  return ack1 && ack2;
}

byte pcf_read() {
  byte data;

  i2c_start();
  i2c_write_byte((PCF8574_ADDR << 1) | 1);
  data = i2c_read_byte(false);
  i2c_stop();

  return data;
}

void setup() {
  Serial.begin(9600);

  sda_high();
  scl_high();

  delay(200);

  pcf_write(0xFF);
}

void loop() {

  byte input = pcf_read();

  byte output = 0xFF;

  if ((input & (1 << 4)) == 0) output &= ~(1 << 0);
  if ((input & (1 << 5)) == 0) output &= ~(1 << 1);
  if ((input & (1 << 6)) == 0) output &= ~(1 << 2);
  if ((input & (1 << 7)) == 0) output &= ~(1 << 3);

  pcf_write(output);

  Serial.print("Inputs: ");
  Serial.print(input, BIN);

  Serial.print("  Outputs: ");
  Serial.println(output, BIN);

  delay(100);
}
