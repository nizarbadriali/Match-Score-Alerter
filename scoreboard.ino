
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// api and wifi called here on the arduino ide, 

const int redLED = 2;
const int blueLED = 4;

int previousEnglandGoals = 0;
int previousCzechGoals = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);
  
  Serial.println("\n\n=== ENGLAND vs CZECH ===");
  Serial.println("Connecting to WiFi...");
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);  // Uses values from secrets.h
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi Connected!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi Failed!");
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://api-football-v1.p.rapidapi.com/v3/fixtures?team=18&status=LIVE";
    
    http.begin(url);
    http.addHeader("x-rapidapi-key", apiKey);  // Uses value from secrets.h
    http.addHeader("x-rapidapi-host", host);   // Uses value from secrets.h
    
    int httpCode = http.GET();
    
    if (httpCode == 200) {
      String payload = http.getString();
      DynamicJsonDocument doc(4096);
      deserializeJson(doc, payload);
      
      if (doc["response"].size() > 0) {
        int englandGoals = doc["response"][0]["goals"]["home"];
        int czechGoals = doc["response"][0]["goals"]["away"];
        String gameStatus = doc["response"][0]["fixture"]["status"].as<String>();
        String opponent = doc["response"][0]["teams"]["away"]["name"].as<String>();
        
        Serial.println("Status: " + gameStatus);
        Serial.println("England vs " + opponent);
        Serial.println("Score: " + String(englandGoals) + " - " + String(czechGoals));
        
        if (englandGoals > previousEnglandGoals) {
          Serial.println("ENGLAND SCORED! RED LED ON for 10 seconds");
          digitalWrite(redLED, HIGH);
          delay(10000);
          digitalWrite(redLED, LOW);
          previousEnglandGoals = englandGoals;
        }
        
        if (czechGoals > previousCzechGoals) {
          Serial.println("CZECH SCORED! BLUE LED ON for 10 seconds");
          digitalWrite(blueLED, HIGH);
          delay(10000);
          digitalWrite(blueLED, LOW);
          previousCzechGoals = czechGoals;
        }
      } else {
        Serial.println("No live match found");
      }
    } else {
      Serial.println("HTTP Error: " + String(httpCode));
    }
    
    http.end();
  }
  
  delay(30000);
}