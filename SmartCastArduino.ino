#include <SPI.h>
#include <SD.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

const int CS = 10;
MPU6050 mpu6050(Wire);

void setup()
{
  Serial.begin(9600);
  if (!SD.begin(CS)) {
    while (1);
  }
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

}


void loop() {
   mpu6050.update();
    Serial.print("Angle: ");
  Serial.print(mpu6050.getAngleZ());
  
    float ms = millis();
    float s = (ms/1000);
    unsigned int m = s/60;
    unsigned int h = m/60;
    unsigned int d = h/24;
    

    float FSR1 = analogRead(A0);
    float v1 = (FSR1*5)/1023;
    float vr1 = round(v1*1000);
    float w1 = (vr1 - 450)/5.646;

    float FSR2 = analogRead(A1);
    float v2 = (FSR2*5)/1023;
    float vr2 = round(v2*1000);
    float w2 = (vr2 - 450)/7.492;

    float vf = (v1 + v2);
    float wf = (w1+w2);

 
    Serial.print("\tWeight: ");
    if ((wf < 0) )
    {
    
    Serial.println(0.000);
    }
    else
    {
    Serial.println(wf);
    }
    //{
    if ((wf > 5) )
    {
     File TestBat = SD.open("TESTBAT.TXT", FILE_WRITE);
      TestBat.print(s);
      TestBat.print("\tWeight: ");
      TestBat.print(wf);
      TestBat.close();

    }
    else
    {
          File TestBat = SD.open("TESTBAT.TXT", FILE_WRITE);
        TestBat.print(s);
         TestBat.print("\tAngle: ");
        TestBat.println(mpu6050.getAngleZ());
   }

    delay(1000);
    //}
}
