#include <Pixy2.h>
#define X_CENTER         (pixy.frameWidth/2)

Pixy2 pixy;

void setup()
{
  Serial.begin(115200);
  pixy.init();
  pixy.setLamp(1, 1);
  pixy.changeProg("line");
}


void loop()
{
  int8_t res;
  int32_t error;
  float x,y,theta;
  int deg;

  // Get latest data from Pixy, including main vector, new intersections and new barcodes.
  res = pixy.line.getMainFeatures();

  // If error or nothing detected, stop motors
  if (res <= 0)
  {
    Serial.print("stop ");
    Serial.println(res);
    return;
  }

  // We found the vector...
  if (res & LINE_VECTOR)
  {
    error = (int32_t)pixy.line.vectors->m_x0 - (int32_t)X_CENTER;
    x = pixy.line.vectors->m_y0 - pixy.line.vectors->m_y1;
    y = pixy.line.vectors->m_x0 - pixy.line.vectors->m_x1;
    theta = atan2(y, x);
    deg = theta * 180 / PI;
    Serial.print(deg);
    Serial.print(" ");
    Serial.println(error);
  }
}
