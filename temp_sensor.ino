
#include <DHT.h>

#define DHTPIN 2      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22 (AM2302) sensor type

DHT dht(DHTPIN, DHTTYPE);
void printbin(int temperature,int humidity ,uint8_t checksum) {
    byte data[5];
    data[0] = humidity >> 8;
    data[1] = humidity & 0xFF;
    data[2] = temperature >> 8;
    data[3] = temperature & 0xFF;
    data[4] = checksum;

    for (int i = 0; i < 5; i++) {
      for (int j = 7; j >= 0; j--) {
        Serial.print(bitRead(data[i], j)? "1" : "0");
      }
      Serial.print(" ");
    }
    Serial.println();
  }
void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(1000);  // Delay between sensor readings

  // Read temperature as Celsius
  float temperature = dht.readTemperature();
  // Read humidity (%)
  float humidity = dht.readHumidity();

  // Check if any reads failed and exit early (to try again).
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Calculate checksum
  uint8_t checksum = temperature + temperature / 256 + humidity + humidity / 256;

  // Print the values to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\t");
  float farenheit = dht.convertCtoF(temperature);
  Serial.print("Temperature in F = ");
  Serial.print(farenheit);
   Serial.print(" °F\t");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Print checksum to Serial Monitor
  Serial.print("DHT22 output Binary: ");
    printbin(temperature,humidity,checksum);
}