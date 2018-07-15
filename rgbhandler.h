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

#define REDPIN 10  
#define GREENPIN 11
#define BLUEPIN 9
#define VOLUMEPIN A0

#define fade(x,y) if (x>y) x--; else if (x<y) x++;  //Fade x to y, increasing/decreasing x as needed

struct rgb {  //struct for colors (256 values each component r g b)
  byte r;
  byte g;
  byte b;
};

static rgb black = { 0, 0, 0 };
static rgb red = { 255, 0, 0 };
static rgb green = { 0, 255, 0 };
static rgb blue = { 0, 0, 255 };
static rgb white = { 255, 255, 255 };

rgb newrgb(rgb oldrgb=black) {  //choose a new random rgb different than oldrgb (or black if null)
  rgb rndrgb=oldrgb;
  while  (rndrgb.r==oldrgb.r ||
          rndrgb.g==oldrgb.g ||
          rndrgb.b==oldrgb.b ) {
    rndrgb.r=random(0,256);
    rndrgb.g=random(0,256);
    rndrgb.b=random(0,256);
  }
  return rndrgb;
}

void fadergb(rgb fromcolor, rgb tocolor) {  //fade fromcolor to tocolor
    fade(fromcolor.r, tocolor.r);
    fade(fromcolor.g, tocolor.g);
    fade(fromcolor.b, tocolor.b);
}

void writecolor(rgb color)  { //write rgb
  analogWrite(REDPIN, color.r);
  analogWrite(GREENPIN, color.g);
  analogWrite(BLUEPIN, color.b);
}

