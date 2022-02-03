#include <M5EPD.h>
#include <SD.h>
#include <CrcXModem128.h>

CrcXModem128 xmodem;

M5EPD_Canvas canvas(&M5.EPD);

void setup() {
  // put your setup code here, to run once:
  //M5paper display settings
  M5.begin();
  M5.EPD.SetRotation(90);
  M5.EPD.Clear(true);
  M5.RTC.begin();
  canvas.createCanvas(540, 960);
  canvas.setTextSize(3);
  canvas.drawString("Hello World", 45, 350);
  canvas.pushCanvas(0,0,UPDATE_MODE_DU4);

  //xomdem setup
  Serial.begin(115200);
  while (!Serial) continue;
  xmodem.begin(&Serial);

  Serial.println("ready to receive");

  /* M5Paper -> PC */
  File sndFile;
  sndFile = SD.open("/helloworld.txt", FILE_READ);
  Serial.println("ready to send");

  if (sndFile) {
    Serial.println("XModem ready!");
    xmodem.sendFile(sndFile);
  } else {
    Serial.println("file doesnot exists");
  }
  sndFile.close();

}

void loop() {
  // put your main code here, to run repeatedly:
}
