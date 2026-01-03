
# DHT11 Temperature and Humidity Monitoring using ESP8266, MQTT, and MySQL

This project demonstrates a complete IoT-based temperature and humidity monitoring system using a DHT11 sensor and ESP8266. Sensor data is published to an MQTT broker and received by a Python application, which stores the data in a MySQL database for further analysis and visualization.



## 1. Project Overview

The system consists of two main components:

1. Sender Unit (ESP8266 + DHT11)  
   - Reads temperature and humidity values
   - Connects to WiFi
   - Publishes data to an MQTT broker in JSON format

2. Receiver Unit (Python + MQTT + MySQL)  
   - Subscribes to MQTT topic
   - Displays real-time sensor data
   - Stores readings in a MySQL database

This project is suitable for IoT learning, academic mini projects, and real-time monitoring applications.


## 2. Hardware Requirements

- ESP8266 NodeMCU
- DHT11 Temperature and Humidity Sensor
- USB Cable
- Jumper Wires
- PC or Laptop with Internet Access



## 3. Software Requirements

- Arduino IDE
- Python 3.8 or higher
- MySQL Server (XAMPP / WAMP / Standalone)
- Internet connection


## 4. Circuit Connections

| DHT11 Pin | ESP8266 Pin |
|----------|-------------|
| VCC | 3.3V |
| DATA | D4 (GPIO2) |
| GND | GND |

Note: Do not power the DHT11 sensor using 5V when connected to ESP8266 GPIO pins.



## 5. Sender Side (ESP8266) Setup

### 5.1 ESP8266 Board Installation

1. Open Arduino IDE  
2. Go to File → Preferences  
3. Add the following URL in Additional Board Manager URLs:



[https://arduino.esp8266.com/stable/package_esp8266com_index.json](https://arduino.esp8266.com/stable/package_esp8266com_index.json)


4. Go to Tools → Board → Boards Manager  
5. Install "ESP8266 by ESP8266 Community"



### 5.2 Required Arduino Libraries

Install the following libraries using Arduino Library Manager:

- ESP8266WiFi (installed automatically with ESP8266 board)
- PubSubClient (by Nick O'Leary)
- DHT sensor library (by Adafruit)
- Adafruit Unified Sensor



### 5.3 WiFi Configuration

Update WiFi credentials in the sender code:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
````



### 5.4 MQTT Configuration (Sender)

```cpp
const char* mqtt_broker = "broker.emqx.io";
const int mqtt_port = 1883;
const char* mqtt_topic = "esp8266/dht11";
```


### 5.5 Uploading Sender Code

1. Open the ESP8266 sender `.ino` file in Arduino IDE
2. Select Board: NodeMCU 1.0 (ESP-12E Module)
3. Select correct COM Port
4. Set baud rate to 115200
5. Upload the code
6. Open Serial Monitor to verify WiFi and MQTT connection


### 5.6 MQTT Data Format

The ESP8266 publishes data in JSON format:

```json
{
  "temperature": 28.5,
  "humidity": 63.0
}
```

---

## 6. Receiver Side (Python + MQTT + MySQL) Setup

### 6.1 Python Dependencies

Install required Python libraries:

```bash
pip install paho-mqtt mysql-connector-python
```

Verify installation:

```bash
python -c "import paho.mqtt, mysql.connector"
```



### 6.2 MySQL Configuration

Ensure MySQL Server is running. The default configuration assumes:

```python
MYSQL_HOST = "localhost"
MYSQL_USER = "root"
MYSQL_PASSWORD = ""
MYSQL_DATABASE = "dht11_monitoring"
MYSQL_TABLE = "sensor_data"
```

Modify these values if your MySQL credentials are different.



### 6.3 Database Initialization

The receiver program automatically:

* Creates the database `dht11_monitoring` if it does not exist
* Creates the table `sensor_data` on first run

No manual SQL commands are required.



### 6.4 MQTT Configuration (Receiver)

```python
MQTT_BROKER = "broker.emqx.io"
MQTT_PORT = 1883
MQTT_TOPIC = "esp8266/dht11"
```

Ensure the MQTT topic matches the sender configuration.



### 6.5 Running the Receiver Program

Navigate to the project directory and run:


python receiver.py


Expected output:

```
Connected to MQTT Broker
Temperature: 28.4 °C | Humidity: 65 %
```



## 7. Database Schema

Database Name: `dht11_monitoring`
Table Name: `sensor_data`

| Column      | Type                              |
| ----------- | --------------------------------- |
| id          | INT (Primary Key, Auto Increment) |
| temperature | FLOAT                             |
| humidity    | FLOAT                             |
| timestamp   | DATETIME                          |



## 8. Project Files

| File Name                     | Description                             |
| ----------------------------- | --------------------------------------- |
| dht11_sender_code.ino         | ESP8266 MQTT sender code                |
| dht11_serial_plotter_code.ino | Serial plotter compatible ESP8266 code  |
| dht11_receiver_python_code.py | Python MQTT receiver with MySQL storage |



## 9. Common Issues and Troubleshooting

| Issue               | Solution                       |
| ------------------- | ------------------------------ |
| MQTT not connecting | Verify WiFi and broker address |
| No data in receiver | Check topic name and internet  |
| MySQL access denied | Verify username and password   |
| NaN sensor values   | Check DHT11 wiring and power   |



## 10. Applications

* Smart Home Monitoring
* Weather Monitoring Systems
* IoT Academic Projects
* Environmental Monitoring
* Industrial Data Logging



## 11. Future Enhancements

* Web dashboard using Flask or Node-RED
* Data visualization using Grafana
* Email or SMS alerts
* Cloud storage integration
* Mobile application support


## 12. Author

SHALINI DEVI R
GitHub: [https://github.com/shalsrsd05](https://github.com/shalsrsd05)



## 13. License

This project is intended for educational and academic use.



