#include <LiquidCrystal.h>
#define v A0
LiquidCrystal lcd(1,2,3,4,5,6);
float adc_voltage = 0.0;
float in_voltage = 0.0;
 
// Floats for resistor values in divider (in ohms)
float R1 = 30000.0;
float R2 = 7500.0; 
 
// Float for Reference Voltage
float ref_voltage = 5.0;
 
// Integer for ADC value
int adc_value = 0;

void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
  
  // put your setup code here, to run once:
   lcd.print("voltage:");
   
}

void loop() {
  // put your main code here, to run repeatedly:
    
  adc_value = analogRead(v);
  adc_voltage  = (adc_value * ref_voltage) / 1024.0; 
   
   // Calculate voltage at divider input
   in_voltage = adc_voltage / (R2/(R1+R2)) ;
  //lcd.setCursor(0,14);
  //lcd.print(in_voltage);
   lcd.clear();
   Serial.print("Voltage:");
   Serial.println(in_voltage);
   delay(1000);

}
