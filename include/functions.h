void sendData(float, float);

void printData(float humidity, float temperature) {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(DEGREE_SYMBOL);
}