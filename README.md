# web-app-controlled-LED-strip
PWM LED strips controlled by a nodeMCU that gets its data from a web app that is hosted on a raspberry pi.

Communication works over wifi.

<h2>Requirements:</h2>
<ul>
  <li>Raspberry Pi (pi zero works fine)</li>
  <li>NodeMCU or other ESP8266 board</li>
  <li>3 MOSFET transistors</li>
  <li>12V to 5V converter</li>
  <li>12V powersupply</li>
  <li>LED strip</li>
  <li>cables and some blank circuit board to solder everything onto</li>
</ul>

<h2>How to use:</h2>
<p>For desktop use: go to "IP OF YOUR RASPBERRY":80
For mobile use: go to "IP OF YOUR RASPBERRY":80/mobile</p>

<h3>How it works:</h3>
<p>The flask based web app handles user input and stores the values for each volor in a list. The nodeMUC gets these values as a string via a http get request. Then the passed string is split uo into the three original values and the nodeMCU sets the PWM values accordingly. The transistors are needed to controll the higher powerded LEDs </p>
<p>In my case a 12V powersupply powers the nodeMCU and the LEDS. If you power the nodeMCU via a standart USB charger you dont need a 12V to 5V converter</>
