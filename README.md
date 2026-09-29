# Live Soccer LED Scoreboard

An embedded systems project that displays live soccer match scores using hardware LEDs controlled by API data.

## Overview

This project fetches **live soccer scores** from a football API and uses an **ESP32 microcontroller** to control LEDs based on match results:
- **Red LED** lights up for **10 seconds** when your team scores
- **Blue LED** lights up for **10 seconds** when the opposition scores

The system polls the API every 30 seconds to check for goal updates during live matches.

## How It Works

```
API (RapidAPI Football) 
    ↓
Fetches live score data
    ↓
ESP32 compares: Your Team Goals vs Opposition Goals
    ↓
GPIO pins trigger LEDs based on who scored
    ↓
Serial Monitor displays live updates
```

## Hardware Requirements

| Component | Quantity | Cost | Purpose |
|-----------|----------|------|---------|
| ESP32 Dev Board | 1 | ~$10 | Microcontroller with WiFi |
| Red LED (5mm) | 1 | ~$0.25 | Your team's score indicator |
| Blue LED (5mm) | 1 | ~$0.25 | Opposition's score indicator |
| 220Ω Resistor | 2 | ~$0.10 | LED current limiting |
| Breadboard | 1 | ~$3 | Prototyping board |
| Jumper Wires | Pack | ~$3 | Connections |
| USB-C Cable | 1 | ~$2 | Power & Programming |
| **Total** | | **~$20** | |

## Wiring Diagram

```
ESP32 GPIO 2 ──→ 220Ω Resistor ──→ Red LED (positive leg)
                                    Red LED (negative leg) ──→ GND

ESP32 GPIO 4 ──→ 220Ω Resistor ──→ Blue LED (positive leg)
                                    Blue LED (negative leg) ──→ GND

ESP32 5V ──→ Breadboard Power Rail
ESP32 GND ──→ Breadboard GND Rail
```

## Software Requirements

- **Arduino IDE** (v2.x or later)
- **ESP32 Board Package** (via Arduino Board Manager)
- **Libraries:**
  - `ArduinoJson` (by Benoit Blanchon)
  - `HTTPClient` (included with ESP32)
  - `WiFi` (included with ESP32)

## Setup Instructions

### 1. Install Arduino IDE & ESP32 Support

```bash
# Download Arduino IDE from: https://arduino.cc
# In Arduino IDE:
# Tools → Board Manager → Search "ESP32" → Install by Espressif Systems
```

### 2. Install Required Libraries

```
Tools → Manage Libraries
Search for "ArduinoJson" → Install (v6.x or later)
```

### 3. Get API Credentials

1. Go to **[api-football.com](https://api-football.com)**
2. Sign up for free account
3. Go to Dashboard → Get your **x-rapidapi-key**
4. Note: Free tier = 100 requests/day (plenty for one match)

### 4. Configure & Upload Code

Edit the code with your credentials:

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* apiKey = "YOUR_RAPIDAPI_KEY";
```

Then:
- Connect ESP32 via USB
- Tools → Board → ESP32
- Tools → Port → Select your COM port
- Click Upload

### 5. Monitor Output

```
Tools → Serial Monitor (Ctrl+Shift+M)
Set Baud Rate: 115200
```

Expected output:
```
=== ENGLAND vs CZECH ===
Connecting to WiFi...
WiFi Connected!
IP: 192.168.1.100

Status: LIVE
England vs Czech Republic
Score: 1 - 0
ENGLAND SCORED! RED LED ON for 10 seconds
```

## Features

* **Real-time score updates** - Checks every 30 seconds  
* **Live API data** - Uses RapidAPI football data  
* **Hardware feedback** - LEDs light up based on goals  
* **Serial debugging** - See live score updates in monitor  
* **WiFi enabled** - Works over any WiFi network  
* **Low cost** - ~$20 total BOM  

## Supported Teams

The code currently tracks **England national team** (`team=18`). To track other teams:

| Team | Team ID |
|------|---------|
| Arsenal Men | 42 |
| England National | 18 |
| Manchester United | 33 |
| Liverpool | 40 |
| Chelsea | 49 |
| [Full team list](https://www.api-football.com/docs-v3#tag/Teams) | - |

Change the code to:
```cpp
String url = "https://api-football-v1.p.rapidapi.com/v3/fixtures?team=YOUR_TEAM_ID&status=LIVE";
```

## Future Enhancements

**Phase 2: Audio Module**
- Add DFPlayer Mini for goal celebration sounds
- "North London Forever" plays when team scores
- Sad trombone when opposition scores

**Phase 3: Display Module**
- Add OLED screen to show live scoreline
- Display possession, shots on target, next match

**Phase 4: PCB Manufacturing**
- Design custom PCB in KiCad
- Manufacture via JLCPCB
- Compact & professional finish

## Troubleshooting

| Issue | Solution |
|-------|----------|
| LEDs don't light up | Check LED polarity (long leg = positive) |
| WiFi won't connect | Double-check SSID/password (2.4GHz only) |
| "API Key invalid" | Verify API key from RapidAPI, copy exactly |
| "No live matches found" | Team might not be playing right now |
| Board won't upload | Install CH340 USB driver for ESP32 |

## API Rate Limits

- **Free tier:** 100 requests/day
- **Project usage:** ~180 requests per 90-min match (every 30 sec)
- **Verdict:** One match per day stays well within limits

## Code Structure

```
arsenal_led_scoreboard/
├── arsenal_scoreboard.ino      # Main sketch
├── README.md                   # This file
├── .gitignore                  # Git ignore rules
└── docs/
    ├── wiring_diagram.md
    ├── api_reference.md
    └── troubleshooting.md
```

## License

MIT License - Feel free to use, modify, and distribute!

## Contributing

Found a bug? Have an idea? Open an issue or submit a pull request!

## Author

Built for tracking live soccer scores with hardware feedback.

---

**Next Goal:** Get it working on breadboard → Convert to custom PCB → Add audio alerts