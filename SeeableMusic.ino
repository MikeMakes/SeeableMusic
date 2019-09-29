/*  The thing you need to rock at nerds (and not so nerd if you manage it well) parties
 *   
    SeeableMusic Copyright (C) 2017 Miguel López Gil @MikeMakes
            
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "rgbhandler.h"

rgb nextcolor, actualcolor;
rgb fadetest;

void setup() {
  pinMode(4,INPUT); //SIG of the Parallax Sound Impact Sensor connected to Digital Pin 7
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  Serial.begin(57600);
  actualcolor=newrgb();
  Serial.println("start");
  writecolor(red);
  delay(1000);
  writecolor(green);
  delay(1000);
  writecolor(blue);
  delay(1000);
  Serial.println("start fade");
  fadenwrite(blue,green,1);
  delay(1000);
  fadenwrite(green,red,1);
  delay(1000);
  Serial.println("exit setup");
}

void loop() {
  Serial.println("loop");
  boolean soundstate = digitalRead(4);  //Mic's pin
  if (soundstate == 1) {  //Is there sound above the level trigger? yes;
    Serial.println("trigger");
    nextcolor = newrgb(actualcolor);   //Choose the next color
    //fadenwrite(nextcolor,actualcolor,1);
    do {
      writecolor(actualcolor);
      fadergb(actualcolor, nextcolor,1);  //fade the actual color to the next color
    } while  (actualcolor.r!=nextcolor.r || //while actual != next color
              actualcolor.g!=nextcolor.g ||
              actualcolor.b!=nextcolor.b );
  } else {
    writecolor(black);
  }
}
