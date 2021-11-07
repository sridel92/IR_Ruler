

#include <SharpIR.h>
//https://github.com/guillaume-rico/SharpIR

#include "U8glib.h"
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);  // I2C / TWI 

void u8g_prepare(void) {
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}

#define ir A2
#define model 1080
// ir: the pin where your sensor is attached
// model: an int that determines your sensor:  1080 for GP2Y0A21Y    ( 10 to 80 cm )
//                                            20150 for GP2Y0A02Y    ( 20 to 150 cm )
//                                            (working distance range according to the datasheets)
SharpIR SharpIR(ir, model);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  delay(50);   

  unsigned long time1=millis();  // takes the time before the loop on the library begins
  int dis=SharpIR.distance();  // this returns the distance to the object you're measuring

  Serial.print("Distance: ");  // returns it to the serial monitor
  Serial.print(dis);
  String Distance = String(dis);
  unsigned long time2=millis()-time1;  // the following gives you the time taken to get the measurement
  Serial.print(" - - -     Time taken (ms): ");
  Serial.println(time2);

  u8g.firstPage();  
  do {  
      u8g.setFont(u8g_font_unifont);
      u8g.drawStr( 0, 22, "IR Ruler (cm)");
      u8g.setPrintPos(0, 40); 
      u8g.print(dis);
     } while( u8g.nextPage() );

}
