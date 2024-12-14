#include <LiquidCrystal_I2C.h>

const int pwmPin = 9; // PWM output pin connected to the fan or motor
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows
int C1  = 2;
int C2 = 3;
int CO1 = 4;
int CO2 = 5;
int D1 = 7; // Assign a pin number to D1
//declaring the counter and initialising it at 0:
int count = 0;
int previous_read = LOW;


void setup()
{
  lcd.init(); // initialize the lcd
  lcd.backlight();
  pinMode(C1, INPUT);
  pinMode(C2, INPUT);
  pinMode(CO1, OUTPUT);
  pinMode(CO2, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  Serial.begin(9600); // For debugging purposes
  pinMode(D1, INPUT);

}

void loop()
{ int State1 = digitalRead(C1); // State of first Op Amp
  int State2 = digitalRead(C2); // State of Second Op Amp 
  int currentState = digitalRead(D1);

  if (State1 == LOW && State2 == HIGH){
  lcd.clear();                 // clear display
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("BELOW 20C");        // print message at (0, 0)
  delay(2000); 
  
  }

  else if (State1 == HIGH && State2 == HIGH){
  lcd.clear();                 // clear display
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("WITHIN 20/30C");        // print message at (0, 0)
  delay(2000); 
  }

  else if (State1 == HIGH && State2 == LOW){
  lcd.clear();                 // clear display
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("ABOVE 30C");        // print message at (0, 0)
  delay(2000); 
  analogWrite(pwmPin, 255); // 100% duty cycle
  Serial.println("Fan ON at full speed");
  delay(5000); // Keep the fan ON for 5 seconds
  analogWrite(pwmPin, 255); // 100% duty cycle
  Serial.println("Fan ON at full speed");
  delay(5000); // Keep the fan ON for 5 seconds
  analogWrite(pwmPin, 125); // 100% duty cycle
  Serial.println("Fan ON at half speed");
  delay(5000); // Keep the fan ON for 5 seconds
  analogWrite(pwmPin, 0); // 100% duty cycle
  Serial.println("Fan OFF");
  delay(5000); // Keep the fan ON for 5 seconds

    if (currentState == HIGH && previous_read == LOW) {
    //increment the count if there is a LOW-HIGH transition:
    count = count + 1;
  }
   previous_read = currentState;
   delay(100); 
  }


}