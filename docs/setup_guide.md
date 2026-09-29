# Live Soccer LED Scoreboard - Setup Guide

Complete step-by-step instructions to build and run the project from scratch.

## Prerequisites

- Computer (Windows, Mac, or Linux)
- USB-C cable for ESP32
- Internet connection for downloading software and API key
- Basic soldering skills optional (breadboard requires no soldering)

---

## Phase 1: Gather Hardware

### Shopping List

Order these parts before starting. Total cost: ~$20

| Part | Quantity | Where to Buy | Cost |
|------|----------|--------------|------|
| ESP32 Dev Board | 1 | Amazon, AliExpress, eBay | ~$10 |
| Red LED 5mm | 1 | Amazon, eBay, local electronics | ~$0.25 |
| Blue LED 5mm | 1 | Amazon, eBay, local electronics | ~$0.25 |
| 220 Ohm Resistor 1/4W | 2 | Amazon, eBay, electronics store | ~$0.10 |
| Breadboard (half-size) | 1 | Amazon, eBay, electronics store | ~$3 |
| Jumper Wire Pack | 1 | Amazon, eBay, electronics store | ~$3 |
| USB-C Cable | 1 | Amazon, eBay (or use existing) | ~$2 |
| 100uF Capacitor (optional) | 1 | Amazon, eBay, electronics store | ~$0.20 |

**Estimated arrival:** 3-7 days for Amazon, 2-3 weeks for AliExpress

### What You Should Have

After ordering, confirm you have all 8 items before proceeding.

```
[] ESP32 board (check for USB-C port)
[] Red LED
[] Blue LED
[] 220Ω resistor (should say "220" on brown/red/brown bands)
[] Breadboard (30 rows x 2 power rails minimum)
[] Jumper wires (assorted pack)
[] USB-C cable
[] 100uF capacitor (optional for stability)
```

---

## Phase 2: Software Installation

### Step 1: Download Arduino IDE

1. Go to https://arduino.cc
2. Click "Download" (top right)
3. Select your operating system:
   - Windows
   - Mac
   - Linux
4. Follow the installer instructions
5. Launch Arduino IDE after installation completes

### Step 2: Add ESP32 Board Support

1. Open Arduino IDE
2. Go to **File** → **Preferences** (Arduino → Preferences on Mac)
3. Find the field labeled "Additional Board Manager URLs"
4. Click the icon on the right (looks like a square with dotted border)
5. Paste this URL in the text box:
   ```
   https://dl.espressif.com/dl/package_esp32_index.json
   ```
6. Click OK
7. Go to **Tools** → **Board** → **Board Manager**
8. Search for "ESP32"
9. Click the result by "Espressif Systems"
10. Click **Install** button
11. Wait 2-3 minutes for installation to complete

### Step 3: Install Required Libraries

1. Go to **Tools** → **Manage Libraries** (or Sketch → Include Library → Manage Libraries)
2. In the search box, type: `ArduinoJson`
3. Find the result by "Benoit Blanchon"
4. Click **Install**
5. Wait for installation to complete

**That's it!** You now have all the software needed.

---

## Phase 3: Get Your API Key

### Create RapidAPI Account

1. Go to https://api-football.com
2. Click "Sign Up" (top right)
3. Enter your email address
4. Create a password
5. Check your email inbox for verification link
6. Click the verification link
7. Log in to your account

### Get Your API Key

1. After logging in, click your profile icon (top right)
2. Go to **Dashboard**
3. Look for "My Access" or "API Keys" section
4. Find the field labeled **x-rapidapi-key**
5. Click the copy icon next to your key
6. Paste it somewhere safe (you'll need it later)

**Important:** Your API key = Password to the football data. Keep it private!

### Check Your Limits

- Free tier gives you: 100 API requests per day
- This project uses: ~2 requests per 30 seconds
- During a 90-minute match: ~180 requests total
- Verdict: You can run 1 live match per day comfortably

---

## Phase 4: Hardware Assembly

### Prepare Your Workspace

1. Clear a flat surface for your breadboard
2. Organize your components by type
3. Use good lighting (you'll be working with small parts)

### Step 1: Place the Breadboard

1. Put the breadboard on your flat surface
2. Note the **power rails** (usually marked + and - or red/blue lines)
3. Note the **main rows** (numbered 1-30 or higher)

### Step 2: Connect Power and Ground

1. Take a **red jumper wire**
2. Connect one end to **ESP32 5V pin**
3. Connect other end to the **breadboard + (positive) rail**

4. Take a **black jumper wire**
5. Connect one end to **ESP32 GND pin**
6. Connect other end to the **breadboard - (negative/GND) rail**

Verify: 5V rail should have red line, GND rail should have black line

### Step 3: Wire Red LED Circuit

1. Insert the **red LED** into the breadboard at positions:
   - Positive leg (long leg): Row 5, Column A
   - Negative leg (short leg): Row 5, Column B

2. Take a **220Ω resistor** and insert it:
   - One end: Row 4, Column A (above positive LED leg)
   - Other end: Row 4, Column C

3. Connect **ESP32 GPIO 2** to the resistor:
   - Take a jumper wire from **GPIO 2** (on ESP32)
   - Insert into breadboard at **Row 4, Column C** (where resistor ends)

4. Connect **LED negative leg to GND**:
   - Take a jumper wire from the LED negative leg location
   - Insert into breadboard at **GND rail**

### Step 4: Wire Blue LED Circuit

1. Insert the **blue LED** into the breadboard at positions:
   - Positive leg (long leg): Row 15, Column A
   - Negative leg (short leg): Row 15, Column B

2. Take a **220Ω resistor** and insert it:
   - One end: Row 14, Column A (above positive LED leg)
   - Other end: Row 14, Column C

3. Connect **ESP32 GPIO 4** to the resistor:
   - Take a jumper wire from **GPIO 4** (on ESP32)
   - Insert into breadboard at **Row 14, Column C** (where resistor ends)

4. Connect **LED negative leg to GND**:
   - Take a jumper wire from the LED negative leg location
   - Insert into breadboard at **GND rail**

### Step 5: Verify Your Wiring

Check these connections:

```
ESP32 5V       ──→ Breadboard + (red) rail
ESP32 GND      ──→ Breadboard - (black) rail

GPIO 2         ──→ 220Ω Resistor ──→ Red LED positive leg
Red LED negative leg ──→ GND rail

GPIO 4         ──→ 220Ω Resistor ──→ Blue LED positive leg
Blue LED negative leg ──→ GND rail
```

**Double check LED polarity:**
- Long leg = positive (toward resistor)
- Short leg = negative (toward GND)

If reversed, LEDs won't work (but won't break).

---

## Phase 5: Test Hardware

### Upload Test Code

1. Connect ESP32 to computer via **USB-C cable**
2. Open Arduino IDE
3. Go to **Tools** → **Board** → **ESP32** → **ESP32 Dev Module**
4. Go to **Tools** → **Port** → Select the port (should show /dev/cu.usbserial or COM3, etc)

**If you don't see a port:**
- You may need to install USB driver
- Search "CH340 driver" and install for your OS
- Restart Arduino IDE and try again

5. Paste this code into Arduino IDE:

```cpp
const int redLED = 2;
const int blueLED = 4;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  
  Serial.println("\n=== LED TEST ===\n");
  
  Serial.println("Red LED ON");
  digitalWrite(redLED, HIGH);
  delay(10000);
  digitalWrite(redLED, LOW);
  
  Serial.println("Blue LED ON");
  digitalWrite(blueLED, HIGH);
  delay(10000);
  digitalWrite(blueLED, LOW);
  
  Serial.println("Both LEDs ON");
  digitalWrite(redLED, HIGH);
  digitalWrite(blueLED, HIGH);
  delay(10000);
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);
  
  Serial.println("Test complete");
}

void loop() {
  delay(1000);
}
```

6. Click **Upload** (arrow icon)
7. Wait for "Done uploading" message

### Verify LEDs Work

1. Watch your breadboard for LED blinks
2. Red LED should light for 10 seconds
3. Blue LED should light for 10 seconds
4. Both LEDs should light for 10 seconds
5. Then all turn off

If you see all 3 sequences: Hardware works! Go to Phase 6.

If LEDs don't light up:
- Check LED polarity (swap them around)
- Check jumper wire connections are firm
- Try different GPIO pins
- See Troubleshooting section

---

## Phase 6: Configure Live Match Code

### Create Your Sketch

1. Open Arduino IDE
2. Go to **File** → **New**
3. Copy and paste this complete code:

```cpp
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// ===== EDIT THESE THREE LINES =====
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* apiKey = "YOUR_RAPIDAPI_KEY";
// ==================================

const int redLED = 2;
const int blueLED = 4;
const char* host = "api-football-v1.p.rapidapi.com";

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
  WiFi.begin(ssid, password);
  
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
    http.addHeader("x-rapidapi-key", apiKey);
    http.addHeader("x-rapidapi-host", host);
    
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
        
        // Check if England just scored
        if (englandGoals > previousEnglandGoals) {
          Serial.println("ENGLAND SCORED! RED LED ON for 10 seconds");
          digitalWrite(redLED, HIGH);
          delay(10000);
          digitalWrite(redLED, LOW);
          previousEnglandGoals = englandGoals;
        }
        
        // Check if Czech just scored
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
  
  delay(30000);  // Check every 30 seconds
}
```

### Edit Your Credentials

Find these three lines at the top and edit them:

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* apiKey = "YOUR_RAPIDAPI_KEY";
```

Replace with:
- Your WiFi network name
- Your WiFi password
- Your API key from RapidAPI (paste the exact value you copied earlier)

Example:
```cpp
const char* ssid = "MyHomeNetwork";
const char* password = "SuperSecret123!";
const char* apiKey = "a1b2c3d4e5f6g7h8i9j0k1l2m3n4o5p6";
```

**Important:** Keep the quotes around each value!

### Upload the Code

1. Click **Upload** button
2. Wait for "Done uploading"
3. Leave USB cable connected

---

## Phase 7: Monitor Live Results

### Open Serial Monitor

1. Go to **Tools** → **Serial Monitor** (or Ctrl+Shift+M)
2. In bottom right, set Baud Rate to **115200**
3. Press Enter or wait 2 seconds

You should see:

```
=== ENGLAND vs CZECH ===
Connecting to WiFi...
.................
WiFi Connected!
IP: 192.168.1.105

Status: LIVE
England vs Czech Republic
Score: 1 - 0
ENGLAND SCORED! RED LED ON for 10 seconds
```

### What the Code Does

Every 30 seconds:
1. Connects to football API
2. Fetches latest England vs Czech score
3. Compares with previous score
4. If England scored: RED LED turns on for 10 seconds
5. If Czech scored: BLUE LED turns on for 10 seconds
6. Prints everything to Serial Monitor

### Troubleshooting Live Code

| Issue | Solution |
|-------|----------|
| WiFi won't connect | Check SSID/password spelling (case-sensitive). Must be 2.4GHz WiFi. |
| "API Key invalid" | Copy API key again from RapidAPI. Don't include quotes or spaces. |
| "No live match found" | England might not be playing right now. Check if match has started. |
| Serial Monitor shows garbage | Wrong baud rate. Set to 115200 in bottom right. |
| Can't find COM port | Install CH340 USB driver for your operating system. |

---

## Phase 8: Switch to Your Team

Want to track Arsenal, Manchester United, or another team instead?

### Find Team ID

Go to https://www.api-football.com/docs-v3 and search for your team in the Teams section.

Common IDs:
- Arsenal Men: 42
- Manchester United: 33
- Liverpool: 40
- Chelsea: 49
- Manchester City: 50

### Update Code

Change this line:

```cpp
String url = "https://api-football-v1.p.rapidapi.com/v3/fixtures?team=18&status=LIVE";
```

To your team (replace 18 with your team ID):

```cpp
String url = "https://api-football-v1.p.rapidapi.com/v3/fixtures?team=42&status=LIVE";
```

Upload and it will now track your team!

---

## Phase 9: Next Steps

Once the breadboard version is working perfectly:

1. **Test during a live match** - Watch your LEDs light up when goals happen
2. **Document what you built** - Take photos, write notes
3. **Push to GitHub** - Share your code with others
4. **Plan PCB version** - Design in KiCad, order from JLCPCB
5. **Add audio** - DFPlayer module plays celebration sounds
6. **Add display** - OLED screen shows live score

---

## Troubleshooting

### LEDs Don't Light Up at All

1. Check LED polarity (long leg = positive)
2. Check all jumper wires are firmly inserted
3. Try different GPIO pins
4. Use multimeter to test voltage at GPIO pins
5. Test LEDs individually with 5V from breadboard power rail

### WiFi Connection Fails

1. Check SSID spelling (case-sensitive)
2. Check password is correct
3. Verify WiFi is 2.4GHz (not 5GHz - ESP32 doesn't support 5GHz)
4. Move ESP32 closer to router
5. Restart WiFi router

### API Returns Error

1. Verify API key is correct (copy again from RapidAPI)
2. Check internet connection
3. Verify you haven't exceeded 100 requests/day limit
4. Wait a minute and try again (rate limiting)

### Serial Monitor Shows Garbage

1. Set baud rate to 115200 (bottom right of monitor)
2. Click reset button on ESP32
3. Reopen Serial Monitor

### Code Won't Upload

1. Check USB cable (some cables are charging only)
2. Install CH340 driver for your OS
3. Verify correct board: Tools → Board → ESP32 Dev Module
4. Verify correct port is selected

### Still Stuck?

1. Check Serial Monitor for error messages
2. Search the exact error message online
3. Post your issue on Arduino forums with error message and code

---

## Success Checklist

Before considering this phase complete:

```
[] Parts arrived and all present
[] Arduino IDE installed
[] ESP32 board support installed
[] ArduinoJson library installed
[] API key obtained and tested
[] Hardware wired correctly
[] Test code runs and LEDs blink
[] WiFi connects successfully
[] API fetches live match data
[] Red LED lights on England goals
[] Blue LED lights on Czech goals
[] Serial Monitor shows live updates
[] Code runs for entire match without errors
```

Once all boxes are checked, you have a working embedded system!

Next: Design a custom PCB and manufacture it.