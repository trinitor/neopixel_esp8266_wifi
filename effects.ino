// compare string from json input with available effects
// string compare takes a while and should be avoided
void getEffectNumber(String effect) {
  if(effect == "default")       { effectnumber =  1; }
  if(effect == "test")          { effectnumber =  2; }
  if(effect == "rainbow")       { effectnumber =  3; }
  if(effect == "rainbowD")      { effectnumber =  4; }
  if(effect == "rainbowR")      { effectnumber =  5; }
  if(effect == "comet")         { effectnumber =  6; }
  if(effect == "alert")         { effectnumber =  7; }
  if(effect == "alertD")        { effectnumber =  8; }
  if(effect == "color")         { effectnumber =  9; }
  if(effect == "colorL")        { effectnumber = 10; }
  if(effect == "colorR")        { effectnumber = 11; }
  if(effect == "fire")          { effectnumber = 12; }
  if(effect == "sparkle")       { effectnumber = 13; }
  if(effect == "sparklecolor")  { effectnumber = 14; }
  if(effect == "bpm1")          { effectnumber = 15; }
  if(effect == "scroll")        { effectnumber = 16; }
  if(effect == "off")           { effectnumber = 17; }
}

// Run effect number
void runEffectNumber (int number) {
  if(effectnumber ==  1) { showDefaultColor();                              }
  if(effectnumber ==  2) { testBoth();                                      }
  if(effectnumber ==  3) { rainbowSingle(option1);                          }
  if(effectnumber ==  4) { rainbowDouble(option1);                          }
  if(effectnumber ==  5) { rainbowDoubleReverse(option1);                   }
  if(effectnumber ==  6) { comet(option1);                                  }
  if(effectnumber ==  7) { alert(red, green, blue, option1, option2);       }
  if(effectnumber ==  8) { alertDouble(red, green, blue, option1, option2); }
  if(effectnumber ==  9) { ColorBoth(red, green, blue);                     }
  if(effectnumber == 10) { ColorLeft(red, green, blue);                     }
  if(effectnumber == 11) { ColorRight(red, green, blue);                    }
  if(effectnumber == 12) { fire();                                          }
  if(effectnumber == 13) { Sparkle(0xff, 0xff, 0xff, 0);                    }
  if(effectnumber == 14) { SparkleColor(0);                                 }
  if(effectnumber == 15) { bpm1(red, green, blue, option1);                 }
  if(effectnumber == 16) { scroll(red, green, blue);                        }
  if(effectnumber == 17) { off();                                           }
}

// effects
void showDefaultColor() {
  if(lamp == 1) {
    Serial.printf("default = lamp on");
    ColorBoth(255, 210, 0);
  } else {
    Serial.printf("default = lamp off");
    ColorBoth(0, 0, 0);
  }
}

void testBoth() {
  int i;

  for(i=0; i< NUMPIXELS*3; i++) {
    if(i < NUMPIXELS) {
      pixels1.setPixelColor(i, 200, 0, 0);
      pixels2.setPixelColor(i, 200, 0, 0);
    }
    else if(i >= NUMPIXELS && i < NUMPIXELS*2) {
      pixels1.setPixelColor(i-NUMPIXELS, 0, 200, 0);
      pixels2.setPixelColor(i-NUMPIXELS, 0, 200, 0);
    }
    else {
      pixels1.setPixelColor(i-NUMPIXELS*2, 0, 0, 200);
      pixels2.setPixelColor(i-NUMPIXELS*2, 0, 0, 200);
    }
    pixels1.show();
    pixels2.show();
    delay(125);
  }
}

void rainbowSingle(int SpeedDelay) {
  if(SpeedDelay == 0) {SpeedDelay = 20;}
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUMPIXELS; i++) {
      c=Wheel(((i * 256 / NUMPIXELS) + j) & 255);
      pixels1.setPixelColor(i, *c, *(c+1), *(c+2));
    }
    pixels1.show();
    delay(SpeedDelay);
  }
  showDefaultColor();
}

void rainbowDouble(int SpeedDelay) {
  if(SpeedDelay == 0) {SpeedDelay = 20;}
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUMPIXELS; i++) {
      c=Wheel(((i * 256 / NUMPIXELS) + j) & 255);
      pixels1.setPixelColor(i, *c, *(c+1), *(c+2));
      pixels2.setPixelColor(i, *c, *(c+1), *(c+2));
    }
    pixels1.show();
    pixels2.show();
    delay(SpeedDelay);
  }
  showDefaultColor();
}

void rainbowDoubleReverse(int SpeedDelay) {
  if(SpeedDelay == 0) {SpeedDelay = 20;}
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUMPIXELS; i++) {
      c=Wheel(((i * 256 / NUMPIXELS) + j) & 255);
      pixels1.setPixelColor(i, *c, *(c+1), *(c+2));
      pixels2.setPixelColor(NUMPIXELS - i, *c, *(c+1), *(c+2));
    }
    pixels1.show();
    pixels2.show();
    delay(SpeedDelay);
  }
  showDefaultColor();
}

void comet(int wait) {
  if(wait == 0) {wait = 20;}
  //green
  for (int i=32; i>=0; i--) {
    for(int j=NUMPIXELS; j>=0; j--) {
      uint32_t color = pixels1.getPixelColor(j);
      pixels1.setPixelColor(j+1, color);
    }
    int light = 0;

    if (i == 32) {
      light = 128;
    }
    else if (i > 16) {
      light = i-17;
    }

    pixels1.setPixelColor(0, pixels1.Color(0,light,0));
    pixels1.show();
    delay(wait);
  }

  // red
  for (int i=32; i>=0; i--) {
    for(int j=NUMPIXELS; j>=0; j--) {
      uint32_t color = pixels1.getPixelColor(j);
      pixels1.setPixelColor(j+1, color);
    }
    int light = 0;

    if (i == 32) {
      light = 128;
    }
    else if (i > 16) {
      light = i-17;
    }

    pixels1.setPixelColor(0, pixels1.Color(light,0,0));
    pixels1.show();
    delay(wait);
  }

  //gold (rgb = 255,215,0)
  for (int i=32; i>=0; i--) {
    for(int j=NUMPIXELS; j>=0; j--) {
      uint32_t color = pixels1.getPixelColor(j);
      pixels1.setPixelColor(j+1, color);
    }
    int light = 0;

    if (i == 32) {
      light = 128;
    }
    else if (i > 16) {
      light = i-17;
    }

    int red = light;
    int green = light * 215 / 255;
    int blue = 0;
    pixels1.setPixelColor(0, pixels1.Color(red,green,blue));
    pixels1.show();
    delay(wait);
  }
}

void alert(int red, int green, int blue, int speed, int steps) {
  if (red    == 0) { red    = 255; }
  if (green  == 0) { green  = 0; }
  if (blue   == 0) { blue   = 0; }
  if (option1 == 0) { option1 = 10; }
  if (option2 == 0) { option2 = 100; }
  for(int i=1; i<steps; i++) {
    int percent  = i *  100/ steps;
    int newred   = red * percent /100;
    int newgreen = green * percent /100;
    int newblue  = blue * percent /100;

    for(int j=0; j<NUMPIXELS; j++) {
      pixels1.setPixelColor(j, pixels1.Color(newred,newgreen,newblue));
    }
    pixels1.show();
    delay(speed);
  }
  delay(20);
  for(int i=steps; i>=0; i--) {
    int percent  = i *  100/ steps;
    int newred   = red * percent /100;
    int newgreen = green * percent /100;
    int newblue  = blue * percent /100;

    for(int j=0; j<NUMPIXELS; j++) {
      pixels1.setPixelColor(j, pixels1.Color(newred,newgreen,newblue));
    }
    pixels1.show();
    delay(speed);
  }
  showDefaultColor();
}

void alertDouble(int red, int green, int blue, int speed, int steps) {
  if (red    == 0) { red    = 255; }
  if (green  == 0) { green  = 0; }
  if (blue   == 0) { blue   = 0; }
  if (option1 == 0) { option1 = 10; }
  if (option2 == 0) { option2 = 100; }
  for(int i=1; i<steps; i++) {
    int percent  = i *  100/ steps;
    int newred   = red * percent /100;
    int newgreen = green * percent /100;
    int newblue  = blue * percent /100;

    for(int j=0; j<NUMPIXELS; j++) {
      pixels1.setPixelColor(j, pixels1.Color(newred,newgreen,newblue));
      pixels2.setPixelColor(j, pixels1.Color(newred,newgreen,newblue));
    }
    pixels1.show();
    pixels2.show();
    delay(speed);
  }
  delay(20);
  for(int i=steps; i>=0; i--) {
    int percent  = i *  100/ steps;
    int newred   = red * percent /100;
    int newgreen = green * percent /100;
    int newblue  = blue * percent /100;

    for(int j=0; j<NUMPIXELS; j++) {
      pixels1.setPixelColor(j, pixels1.Color(newred,newgreen,newblue));
      pixels2.setPixelColor(j, pixels1.Color(newred,newgreen,newblue));
    }
    pixels1.show();
    pixels2.show();
    delay(speed);
  }
  showDefaultColor();
}

void ColorLeft(int red, int green, int blue) {
  for(int j=0; j<NUMPIXELS; j++) {
      pixels1.setPixelColor(j, pixels1.Color(red,green,blue));
  }
  pixels1.show();
}

void ColorRight(int red, int green, int blue) {
  for(int j=0; j<NUMPIXELS; j++) {
      pixels2.setPixelColor(j, pixels2.Color(red,green,blue));
  }
  pixels2.show();
}

void ColorBoth(int red, int green, int blue) {
  for(int j=0; j<NUMPIXELS; j++) {
      pixels1.setPixelColor(j, pixels1.Color(red,green,blue));
      pixels2.setPixelColor(j, pixels1.Color(red,green,blue));
  }
  pixels1.show();
  pixels2.show();
}

void fire() {
  Serial.printf("fire \n");
  int red = 200;
  int green = 90;
  int blue = 10;
  int diff = 50;
  int mindelay = 50;
  int maxdelay = 150;

  for(int x = 0; x <NUMPIXELS; x++) {
    int red_new = random(red-diff,red);
    int green_new =  random(green-diff,green);
    //int blue_new = random(blue-diff,blue+diff);
    int blue_new = 10;
    if(red_new < 0)   {red_new = 0; }
    if(green_new < 0) {green_new = 0; }
    if(blue_new < 0)  {blue_new = 0; }
    pixels1.setPixelColor(x, red_new, green_new, blue_new);
  }
  pixels1.show();
  delay(random(mindelay,maxdelay));
}

void Sparkle(byte red, byte green, byte blue, int SpeedDelay) {
  int Pixel = random(NUMPIXELS);
  pixels1.setPixelColor(Pixel,red,green,blue);
  pixels1.show();
  delay(SpeedDelay);
  pixels1.setPixelColor(Pixel,0,0,0);
}

void SparkleColor(int SpeedDelay) {
  int Pixel = random(NUMPIXELS);
  int red   = random(100);
  int green = random(100);
  int blue  = random(100);
  pixels1.setPixelColor(Pixel,red,green,blue);
  pixels1.show();
  delay(SpeedDelay);
  pixels1.setPixelColor(Pixel,0,0,0);
}

void bpm1(byte red, byte green, byte blue, int bpm) {
  if (red       == 0) { red    = 10; }
  if (green     == 0) { green  = 10; }
  if (blue      == 0) { blue   = 100; }
  if (bpm       == 0) { bpm = 100; }
  int beatlength = 30;

  //draw beat
  for (int i=1; i<=beatlength/2; i++) {
    for(int j=NUMPIXELS; j>=0; j--) {
      uint32_t color = pixels1.getPixelColor(j);
      pixels1.setPixelColor(j+1, color);
    }

    int percent  = beatlength * 100 / i / 2;
    int newred   = red   * percent / 100;
    int newgreen = green * percent / 100;
    int newblue  = blue  * percent / 100;
    if(debugMode == 1)
    {
      Serial.printf("percent = %i \n", percent);
    }

    pixels1.setPixelColor(0, pixels1.Color(newred,0,10));
    pixels1.show();
    delay(60 * 1000 / bpm / beatlength);
  }

  //blank
  for (int i=beatlength/2; i>=0; i--) {
    for(int j=NUMPIXELS; j>=0; j--) {
      uint32_t color = pixels1.getPixelColor(j);
      pixels1.setPixelColor(j+1, color);
    }

    pixels1.setPixelColor(0, pixels1.Color(0,0,0));
    pixels1.show();
  }
}

void scroll(byte red, byte green, byte blue) {
  for(int j=NUMPIXELS; j>=0; j--) {
    uint32_t color = pixels1.getPixelColor(j);
    pixels1.setPixelColor(j+1, color);
  }

  if (red >0 || green >0 || blue >0) {
    //read current color
    uint32_t CurrentColor = pixels1.getPixelColor(1);
    uint8_t  CurrentRed   = CurrentColor >> 16;
    uint8_t  CurrentGreen = CurrentColor >> 8;
    uint8_t  CurrentBlue  = CurrentColor;

    // if no new color was set -> reuse the old color
    if (red   == 0) {red  = CurrentRed;}
    if (green == 0) {green = CurrentGreen;}
    if (blue  == 0) {blue  = CurrentBlue;}

      pixels1.setPixelColor(0, pixels1.Color(red,green,blue));
  } else {
//    Serial.printf("no new color");
      uint32_t color = pixels1.getPixelColor(1);
      pixels1.setPixelColor(0, color);
  }

  pixels1.show();
  delay(10);

}

void off() {
  ColorBoth(0, 0, 0);
}


//functions
void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUMPIXELS; i++ ) {
    pixels1.setPixelColor(i, pixels1.Color(red, green, blue));
  }
  pixels1.show();
}

byte * Wheel(byte WheelPos) {
  static byte c[3];

  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}

