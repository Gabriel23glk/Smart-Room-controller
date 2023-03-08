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
int PINA=A5;
int PINB=A4;
const int PIXELPIN=D5;
const int PIXELNUMBER=15;
int pixelBrightness;
// int maxPos=15;
int startPixel=0;
int endPixel=15;
int color=0x008000;
int positionA;
int pixelCount;
const int OLED_RESET=4;

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
  display.clearDisplay();
  display.drawBitmap(16,20, myBitmap,231, 105, 1);
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
 positionA=myEnc.read();
 pixelBrightness=map(positionA,0,95,0,15);
 pixel.setBrightness(pixelBrightness);
 pixelFill(startPixel,endPixel,color);
//  Serial.printf("%i %i",positionA,pixelBrightness);
 myEnc.write(maxPos);  
    // Serial.printf("%i,%i\n",positionA,pixelBrightness);
    val=analogRead(Tswitch);
    brightness=255;
    Serial.printf("val=%i\n",val);
    if (val<200){
     for (BULB=1; BULB<=3; BULB++){
      setHue(BULB,false,HueGreen,0,255); 
     Serial.printf("bulb off");
     for (BULB=4; BULB<=6; BULB++);{
      setHue(BULB, false, HueBlue,0,255);
     }
     }
    }
    
    else{
      for (BULB=1; BULB<=3; BULB++){
        setHue(BULB,true,HueGreen,brightness,255);
        Serial.printf("bulb on");
        for (BULB=4; BULB<=6; BULB++);{
          setHue(BULB, true, HueBlue,brightness,255);
 }
}
}
}
void pixelFill(int startPixel,int endPixel,int color){
    for (pixelCount=startPixel; pixelCount<=endPixel; pixelCount++)
      pixel.setPixelColor(pixelCount,color);
      pixel.show();
      pixel.clear();
      // Serial.printf("encoder value%i\r",positionA);

}