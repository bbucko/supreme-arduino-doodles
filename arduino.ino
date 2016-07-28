#include <Arduino.h>

//Grove LCD
#include <rgb_lcd.h>

//NFC
#include <Wire.h>
#include <Adafruit_PN532.h>

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetClient.h>

#define PN532_SCK  (2)
#define PN532_MOSI (3)
#define PN532_SS   (4)
#define PN532_MISO (5)

Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);

rgb_lcd lcd;

const char *server = "google.com";                      // server's address
const char *resource = "/users/1";                      // http resource
const unsigned long HTTP_TIMEOUT = 10000;               // max respone time from server
const size_t MAX_CONTENT_SIZE = 512;                    // max size of the HTTP response

const unsigned long BAUD_RATE = 9600;                   // serial connection speed

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
EthernetClient client;

int trig = 4;
int echo = 3;

void setup() {
    Serial.begin(1);
    while (!Serial) { ;  // wait for serial port to initialize
    }
    Serial.println("Serial ready");

    Ethernet.begin(mac);

    pinMode(13, OUTPUT);

    nfc.begin();
    nfc.SAMConfig();

    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("Distance: ");
}

void loop() {
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);

    pinMode(trig, OUTPUT);
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(5);
    digitalWrite(trig, LOW);

    // The same pin is used to read the signal from the PING))): a HIGH
    // pulse whose duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(echo, INPUT);
    long duration = pulseIn(echo, HIGH);
    Serial.println(duration);

    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(duration);

    client.print("GET ");
    client.print(resource);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();

    delay(200);
}