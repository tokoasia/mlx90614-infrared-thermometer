#include <Wire.h>
#include <Adafruit_MLX90614.h>

// Define I2C pins for ESP32 (Change if using non-standard pins)
#define I2C_SDA 21
#define I2C_SCL 22

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  // Use 115200 for ESP32 - make sure your Serial Monitor matches this!
  Serial.begin(115200);
  while (!Serial); 
  
  Serial.println("\n--- ESP32 MLX90614 Diagnostic ---");

  // Manually start I2C on specific pins
  Wire.begin(I2C_SDA, I2C_SCL);

  Serial.println("Initializing sensor...");
  
  // Initialize the sensor
  if (!mlx.begin()) {
    Serial.println("CRITICAL ERROR: MLX90614 not found.");
    Serial.println("1. Check SDA/SCL wiring (Pins 21/22).");
    Serial.println("2. Check power (3.3V vs 5V).");
    Serial.println("3. Ensure pull-up resistors are present.");
    while (1) delay(10); // Halt execution
  }

  Serial.print("Sensor Found! Emissivity: ");
  Serial.println(mlx.readEmissivity());
  Serial.println("------------------------------------------------");
}

void loop() {
  // Read Temperatures
  double ambientC = mlx.readAmbientTempC();
  double objectC  = mlx.readObjectTempC();
  double ambientF = mlx.readAmbientTempF();
  double objectF  = mlx.readObjectTempF();

  // Print Results
  Serial.print("Ambient: "); Serial.print(ambientC); Serial.print("°C | ");
  Serial.print("Object: ");  Serial.print(objectC);  Serial.println("°C");
  
  Serial.print("Ambient: "); Serial.print(ambientF); Serial.print("°F | ");
  Serial.print("Object: ");  Serial.print(objectF);  Serial.println("°F");
  
  Serial.println("------------------------------------------------");

  delay(1000); // Wait 1 second between reads
}
