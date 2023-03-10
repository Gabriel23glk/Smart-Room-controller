/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/gabea/Documents/IoT/Smart-Room-controller/Project_Light_Lantern/src/Project_Light_Lantern.ino"
/*
 * Project Project_Light_Lantern
 * Description:
 * Author:
 * Date:
 */
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"
#include "IoTClassroom_CNM.h"
#include <Encoder.h>
#include "colors.h"
#include "neopixel.h"
#include "Light_Bulb.h"
void setup();
void loop();
void pixelFill(int startPixel,int endPixel,int color1,int color2);
#line 14 "c:/Users/gabea/Documents/IoT/Smart-Room-controller/Project_Light_Lantern/src/Project_Light_Lantern.ino"
int PINA=D11;
int PINB=D12;
const int PIXELPIN=D5;
const int PIXELNUMBER=16;
int pixelBrightness;
int maxPos=15;
int startPixel=0;
int endPixel=15;
int color1=green;
int color2=blue;
int positionA;
int pixelCount;
const int OLED_RESET=4;
bool buttonState;
int buttonPin=A3;
const int MYWEMO1=1;
const int MYWEMO2=2;

Adafruit_SSD1306 display(OLED_RESET);
Adafruit_NeoPixel pixel(PIXELNUMBER,PIXELPIN,WS2812B);
Encoder myEnc(PINA, PINB);
SYSTEM_MODE(MANUAL);
int BULB;
int colorHue;
int brightness;
int val;
const int Tswitch=A3;
// setup() runs once, when the device is first turned on.
void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected,15000);
  display.begin (SSD1306_SWITCHCAPVCC, 0x3c);
  display.display();
  delay(200);
  display.clearDisplay();
  display.drawBitmap(16,20, myBitmap,112, 44, 1);
  display.display();
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.setTextSize(1);
  display.setTextColor(BLACK,WHITE);
  display.printf("Light It Up%c",33);
  display.display();

  pinMode(Tswitch, INPUT);
  pixel.begin();
  pixel.show();


  WiFi.on();
  WiFi.setCredentials("IoTNetwork");
   WiFi.connect();
  while(WiFi.connecting()) {
    Serial.printf(".");
  }
  Serial.printf("\n\n");

}
  // Put initialization like pinMode and begin functions here.



// loop() runs over and over again, as quickly as it can execute.
void loop() {
   buttonState=digitalRead(buttonPin);
 positionA=myEnc.read();
if(positionA>95){
  positionA=95;
  myEnc.write(95);
}
if(positionA<0){
  positionA=0;
  myEnc.write(0);
}

 pixelBrightness=map(positionA,0,95,0,229);
 pixel.setBrightness(pixelBrightness);
 pixelFill(startPixel,endPixel,color1,color2);
// Serial.printf("val of my encoder/n");
 Serial.printf("%i %i\n",positionA,pixelBrightness);
  
    Serial.printf("%i,%i\n",positionA,pixelBrightness);
    val=analogRead(Tswitch);
    brightness=255;
    // Serial.printf("val=%i\n",val);
    if (val<200){
     for (BULB=1; BULB<=3; BULB++){
      setHue(BULB,false,HueGreen,0,255);
      switchOFF(MYWEMO1);

     } 
    //  Serial.printf("bulb off");
     for (BULB=4; BULB<=6; BULB++){
      setHue(BULB, false, HueBlue,0,255);
      switchOFF(MYWEMO2);
     }
    }
    
    else{
      for (BULB=1; BULB<=3; BULB++){
        setHue(BULB,true,HueGreen,brightness,255);
        Serial.printf("bulb on");
        switchON(MYWEMO1);
      }
        for (BULB=4; BULB<=6; BULB++){
          setHue(BULB, true, HueBlue,brightness,255);
          switchON(MYWEMO2);
 
}
}
}
void pixelFill(int startPixel,int endPixel,int color1,int color2){
    for (pixelCount=startPixel; pixelCount<=endPixel; pixelCount=pixelCount+2){
      pixel.setPixelColor(pixelCount,color1);
      pixel.setPixelColor(pixelCount+1,color2);
      pixel.show();  
    }
}

     

