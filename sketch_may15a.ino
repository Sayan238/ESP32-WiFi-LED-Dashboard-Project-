#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ENTER_YOUR_WIFI_NAME";
const char* password = "ENTER_YOUR_PASSWARD";

WebServer server(80);

// ================= LED PINS =================

#define RED_LED 25
#define GREEN_LED 26
#define BLUE_LED 27
#define YELLOW_LED 14

// ================= MODES =================

bool partyMode = false;
bool breatheMode = false;

// ================= BRIGHTNESS VALUES =================

int redValue = 0;
int greenValue = 0;
int blueValue = 0;
int yellowValue = 0;

// ================= HTML =================

String webpage = R"rawliteral(

<!DOCTYPE html>
<html>

<head>

<meta name="viewport" content="width=device-width, initial-scale=1.0">

<title>Smart Light Control</title>

<style>

*{
margin:0;
padding:0;
box-sizing:border-box;
font-family:Arial,sans-serif;
}

body{

background:
linear-gradient(135deg,#020617,#0f172a);

min-height:100vh;

padding:20px;

display:flex;
justify-content:center;
align-items:center;

color:white;
}

.container{

width:100%;
max-width:500px;

}

.title{

text-align:center;

font-size:34px;
font-weight:bold;

margin-bottom:25px;

}

.card{

background:rgba(255,255,255,0.08);

backdrop-filter:blur(14px);

padding:25px;

border-radius:28px;

margin-bottom:25px;

box-shadow:
0 0 25px rgba(0,255,255,0.08);

}

.light-name{

font-size:24px;
font-weight:bold;

margin-bottom:20px;

text-align:center;
}

.buttons{

display:flex;
justify-content:center;
gap:18px;

margin-bottom:20px;
}

button{

width:110px;
height:50px;

border:none;

border-radius:16px;

font-size:18px;
font-weight:bold;

cursor:pointer;

transition:0.25s;

color:white;
}

button:hover{

transform:scale(1.05);

}

.red-on{background:#ef4444;}
.red-off{background:#7f1d1d;}

.green-on{background:#22c55e;}
.green-off{background:#14532d;}

.blue-on{background:#3b82f6;}
.blue-off{background:#1e3a8a;}

.yellow-on{
background:#facc15;
color:black;
}

.yellow-off{
background:#854d0e;
}

.slider{

width:100%;
height:14px;

border-radius:10px;

outline:none;

appearance:none;
}

.slider::-webkit-slider-thumb{

appearance:none;

width:24px;
height:24px;

background:white;

border-radius:50%;

cursor:pointer;
}

.red-slider{
background:linear-gradient(to right,#220000,#ff0000);
}

.green-slider{
background:linear-gradient(to right,#002200,#00ff66);
}

.blue-slider{
background:linear-gradient(to right,#000022,#0066ff);
}

.yellow-slider{
background:linear-gradient(to right,#332200,#ffcc00);
}

.value{

text-align:center;

margin-top:10px;

font-size:18px;
opacity:0.8;
}

.effect-btn{

background:#8b5cf6;

width:180px;

}

.breathe-btn{

background:#06b6d4;

width:180px;

}

.footer{

text-align:center;

margin-top:20px;

opacity:0.5;

font-size:14px;
}

</style>

</head>

<body>

<div class="container">

<div class="title">
SMART LIGHT CONTROL
</div>

<!-- RED -->

<div class="card">

<div class="light-name">
Red Light
</div>

<div class="buttons">

<button class="red-on"
onclick="fetch('/redon')">
ON
</button>

<button class="red-off"
onclick="fetch('/redoff')">
OFF
</button>

</div>

<input type="range"
min="0"
max="255"
value="0"
class="slider red-slider"
oninput="setBrightness('red',this.value,'redValue')">

<div class="value" id="redValue">
Brightness: 0
</div>

</div>

<!-- GREEN -->

<div class="card">

<div class="light-name">
Green Light
</div>

<div class="buttons">

<button class="green-on"
onclick="fetch('/greenon')">
ON
</button>

<button class="green-off"
onclick="fetch('/greenoff')">
OFF
</button>

</div>

<input type="range"
min="0"
max="255"
value="0"
class="slider green-slider"
oninput="setBrightness('green',this.value,'greenValue')">

<div class="value" id="greenValue">
Brightness: 0
</div>

</div>

<!-- BLUE -->

<div class="card">

<div class="light-name">
Blue Light
</div>

<div class="buttons">

<button class="blue-on"
onclick="fetch('/blueon')">
ON
</button>

<button class="blue-off"
onclick="fetch('/blueoff')">
OFF
</button>

</div>

<input type="range"
min="0"
max="255"
value="0"
class="slider blue-slider"
oninput="setBrightness('blue',this.value,'blueValue')">

<div class="value" id="blueValue">
Brightness: 0
</div>

</div>

<!-- YELLOW -->

<div class="card">

<div class="light-name">
Yellow Light
</div>

<div class="buttons">

<button class="yellow-on"
onclick="fetch('/yellowon')">
ON
</button>

<button class="yellow-off"
onclick="fetch('/yellowoff')">
OFF
</button>

</div>

<input type="range"
min="0"
max="255"
value="0"
class="slider yellow-slider"
oninput="setBrightness('yellow',this.value,'yellowValue')">

<div class="value" id="yellowValue">
Brightness: 0
</div>

</div>

<!-- EFFECTS -->

<div class="card">

<div class="light-name">
Effects
</div>

<div class="buttons">

<button class="effect-btn"
onclick="fetch('/party')">
PARTY
</button>

<button class="breathe-btn"
onclick="fetch('/breathe')">
BREATHE
</button>

</div>

</div>

<div class="footer">
ESP32 WiFi Home Automation
</div>

</div>

<script>

function setBrightness(color,value,id){

document.getElementById(id).innerHTML =
"Brightness: " + value;

fetch("/" + color + "?value=" + value);

}

</script>

</body>
</html>

)rawliteral";

// ================= EFFECTS =================

void breathingEffect(){

  static int brightness = 0;
  static int fadeAmount = 3;

  brightness += fadeAmount;

  if(brightness <= 0 || brightness >= 255){

    fadeAmount = -fadeAmount;
  }

  ledcWrite(RED_LED, brightness);
  ledcWrite(GREEN_LED, brightness);
  ledcWrite(BLUE_LED, brightness);
  ledcWrite(YELLOW_LED, brightness);

  delay(15);
}

void partyLights(){

  static int state = 0;
  static unsigned long lastChange = 0;

  if(millis() - lastChange > 500){

    lastChange = millis();

    state++;

    if(state > 3) state = 0;
  }

  ledcWrite(RED_LED, state == 0 ? 255 : 0);
  ledcWrite(GREEN_LED, state == 1 ? 255 : 0);
  ledcWrite(BLUE_LED, state == 2 ? 255 : 0);
  ledcWrite(YELLOW_LED, state == 3 ? 255 : 0);
}

// ================= SETUP =================

void setup() {

Serial.begin(115200);

// PWM Attach
ledcAttach(RED_LED, 5000, 8);
ledcAttach(GREEN_LED, 5000, 8);
ledcAttach(BLUE_LED, 5000, 8);
ledcAttach(YELLOW_LED, 5000, 8);

// WiFi
WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {

delay(500);
Serial.print(".");

}

Serial.println("");
Serial.println(WiFi.localIP());

// MAIN PAGE

server.on("/", []() {

server.send(200, "text/html", webpage);

});

// ================= RED =================

server.on("/redon", []() {

partyMode = false;
breatheMode = false;

redValue = 255;

ledcWrite(RED_LED,255);

server.send(200,"text/plain","ON");

});

server.on("/redoff", []() {

partyMode = false;
breatheMode = false;

redValue = 0;

ledcWrite(RED_LED,0);

server.send(200,"text/plain","OFF");

});

// ================= GREEN =================

server.on("/greenon", []() {

partyMode = false;
breatheMode = false;

greenValue = 255;

ledcWrite(GREEN_LED,255);

server.send(200,"text/plain","ON");

});

server.on("/greenoff", []() {

partyMode = false;
breatheMode = false;

greenValue = 0;

ledcWrite(GREEN_LED,0);

server.send(200,"text/plain","OFF");

});

// ================= BLUE =================

server.on("/blueon", []() {

partyMode = false;
breatheMode = false;

blueValue = 255;

ledcWrite(BLUE_LED,255);

server.send(200,"text/plain","ON");

});

server.on("/blueoff", []() {

partyMode = false;
breatheMode = false;

blueValue = 0;

ledcWrite(BLUE_LED,0);

server.send(200,"text/plain","OFF");

});

// ================= YELLOW =================

server.on("/yellowon", []() {

partyMode = false;
breatheMode = false;

yellowValue = 255;

ledcWrite(YELLOW_LED,255);

server.send(200,"text/plain","ON");

});

server.on("/yellowoff", []() {

partyMode = false;
breatheMode = false;

yellowValue = 0;

ledcWrite(YELLOW_LED,0);

server.send(200,"text/plain","OFF");

});

// ================= SLIDERS =================

server.on("/red", [](){

partyMode = false;
breatheMode = false;

redValue = server.arg("value").toInt();

ledcWrite(RED_LED, redValue);

server.send(200,"text/plain","OK");

});

server.on("/green", [](){

partyMode = false;
breatheMode = false;

greenValue = server.arg("value").toInt();

ledcWrite(GREEN_LED, greenValue);

server.send(200,"text/plain","OK");

});

server.on("/blue", [](){

partyMode = false;
breatheMode = false;

blueValue = server.arg("value").toInt();

ledcWrite(BLUE_LED, blueValue);

server.send(200,"text/plain","OK");

});

server.on("/yellow", [](){

partyMode = false;
breatheMode = false;

yellowValue = server.arg("value").toInt();

ledcWrite(YELLOW_LED, yellowValue);

server.send(200,"text/plain","OK");

});

// ================= EFFECTS =================

server.on("/party", [](){

partyMode = true;
breatheMode = false;

server.send(200,"text/plain","PARTY");

});

server.on("/breathe", [](){

breatheMode = true;
partyMode = false;

server.send(200,"text/plain","BREATHE");

});

server.begin();

}

// ================= LOOP =================

void loop() {

server.handleClient();

if(partyMode){

partyLights();

}

else if(breatheMode){

breathingEffect();

}

}