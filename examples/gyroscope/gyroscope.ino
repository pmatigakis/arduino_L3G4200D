#include <L3G4200D.h>
#include <Wire.h>

L3G4200D g(L3G4200D_ADDRESS_1);

void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  //the begin method must be called after the Wire library has been initialized
  g.begin(DR_100HZ, BW_00, X_EN | X_EN | Z_EN);

  //wait for some time until the gyroscope has initialized
  delay(2000);
}

void loop() {
  short xacc = g.x_rotation();
  short yacc = g.y_rotation();
  short zacc = g.z_rotation();

  Serial.print(xacc);
  Serial.print('\t');
  Serial.print(yacc);
  Serial.print('\t');
  Serial.print(zacc);
  Serial.print('\n');
}

