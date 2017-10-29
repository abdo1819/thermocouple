//  author : abdo
//  date   : 10/2017
//  project:thermo couple

#include "max6675.h"

int thermoSO = 4;
int thermoCS = 5;
int thermoCLK = 6;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoSO);

  
void setup() {
  Serial.begin(9600);
 
  
  Serial.println("MAX6675 test");
  
  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  // basic readout test, just print the current temp
   int temp_c = thermocouple.readCelsius();
   /*conver to voltage
    * where  v = 41uV/c 
    */
   int uV = temp_c * 41;

   Serial.print("v = "); 
   Serial.print(uV);
   Serial.print("uV   --- ");
   
   Serial.print("C = "); 
   Serial.println(temp_c);  
  
   delay(1000);
}

