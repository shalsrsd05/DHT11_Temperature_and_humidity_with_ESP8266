#include <DHT.h>

#define DHTPIN D4       // GPIO2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius

  if (isnan(humidity) || isnan(temperature)) {
    return; // skip invalid readings
  }

  // ---- Serial Plotter Format ----
  // Temperature Humidity
  Serial.print(temperature);
  Serial.print(" ");
  Serial.println(humidity);

  delay(2000);
}
