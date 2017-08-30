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

int realcolor[3];   //Actual color
int newrealcolor[3];    //Next color
float colors[6][5][3];  //Store all RGB values wanted [6x5]x[3] = [Value]x[applied to this RGB component]

void flash();

void choosenewrealcolor(int pnewrealcolor[]);
void colorWrite(int color2write[]);

void setup() {

  pinMode(4,INPUT); //SIG of the Parallax Sound Impact Sensor connected to Digital Pin 7
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  
  //define colors;
  float f=0;
  for(int j=0; j<5;j++) {
            //Matrix [6x5]x3 = [Select color value]x[applied to this RGB component]
            colors[0][j][0]=1;  //Red
            colors[0][j][1]=0;  //Blue
            colors[0][j][2]=f;  //Green
            f+=0.25;
  }
  f=1;
  for(int j=0; j<5;j++) {
            colors[1][j][0]=f;
            colors[1][j][1]=0;
            colors[1][j][2]=1;
            f-=0.25;
  }
  f=0;
  for(int j=0; j<5;j++) {
            colors[2][j][0]=0;
            colors[2][j][1]=f;
            colors[2][j][2]=1;
            f+=0.25;
  }
  f=1;
  for(int j=0; j<5;j++) {
            colors[3][j][0]=0;
            colors[3][j][1]=1;
            colors[3][j][2]=f;
            f-=0.25;
  }
  f=0;
  for(int j=0; j<5;j++) {
            colors[4][j][0]=f;
            colors[4][j][1]=1;
            colors[4][j][2]=0;
            f+=0.25;
  }
  f=1;
  for(int j=0; j<5;j++) {
            colors[5][j][0]=1;
            colors[5][j][1]=f;
            colors[5][j][2]=0;
            f-=0.25;
  }
  
  choosenewrealcolor(realcolor);

  flash();

  Serial.begin(9600);
}
 
#define fade(x,y) if (x>y) x--; else if (x<y) x++;  //Fade x to y, increasing/decreasing x as needed

void loop() {
  
  boolean soundstate = digitalRead(4);  //Mic's pin
  
  if (soundstate == 1) {  //Is there sound above the level trigger? yes;
    choosenewrealcolor(newrealcolor);   //Choose the next color and fade to it from the old color, in case they are not the same
    while (realcolor[0] != newrealcolor[0] ||
           realcolor[1] != newrealcolor[1] ||
           realcolor[2] != newrealcolor[2] ){
              for(int i=0; i<3;i++) {
                  fade(realcolor[i],newrealcolor[i]);
              }
              colorWrite(realcolor);  //Write the new (now actual) color
           } 
  }
  
  else {    //Is there sound above the level trigger? nope; turn off lights
    analogWrite(BLUEPIN, 0);
    analogWrite(REDPIN, 0);
    analogWrite(GREENPIN, 0);
  }
  
}


void choosenewrealcolor(int pnewrealcolor[]) { //Pick a new color
    for(int i=0;i<3;i++){
      pnewrealcolor[i]=colors[ random(0,7) ] [ random(0,6) ] [ i ];   //Choose randomly a new value for each RGB component
      pnewrealcolor[i]*=random(0,256);      //And randomly assign a bright to the choosed color
    }
}

void colorWrite(int color2write[]) {  //Write "color2write" values to the pins where them belongs
    analogWrite(BLUEPIN, color2write[0]);
    analogWrite(REDPIN, color2write[1]);
    analogWrite(GREENPIN, color2write[2]);
}

void flash() {    //Display all colors with max bright
  for (int i=0; i<6; i++) {
    for(int j=0; j<5;j++) {
      
          analogWrite(BLUEPIN, colors[i][j][0]*255);
          analogWrite(REDPIN, colors[i][j][1]*255);
          analogWrite(GREENPIN, colors[i][j][2]*255);
          delay(250);
    }
  }
}
