
// to the pins used:
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 12; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

int LED = 13;
int flame_sensor = 7;
int flame_detected;


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
    lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0, 0);
  lcd.print("R-NF");

    lcd.setCursor(6, 0);
  lcd.print("Y-NF");

    lcd.setCursor(12, 0);
  lcd.print("B-NF");

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);


  pinMode(LED, OUTPUT);
  pinMode(flame_sensor, INPUT);
}

void loop() {


  //Flame control
flame_detected = digitalRead(flame_sensor);
  if (flame_detected == 1)
  {
    Serial.println("Flame detected...! take action immediately.");
    //digitalWrite(buzzer, HIGH);
    digitalWrite(LED, HIGH);
    //delay(200);
   // digitalWrite(LED, LOW);
    //delay(200);
  }
  else
  {
    Serial.println("No flame detected. stay cool");
    //digitalWrite(buzzer, LOW);
    digitalWrite(LED, LOW);
  }
  delay(1000);



  //Flame control end


  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);

  lcd.setCursor(10, 1);
  lcd.print(sensorValue);

//FAULT 1 R-12KM
  if (sensorValue==446)
  {
    lcd.setCursor(0, 0);
    lcd.print("R-F");
    lcd.setCursor(0, 1);
    lcd.print("12-KM");

      digitalWrite(8, HIGH);   // turn the R-relay on (HIGH is the voltage level)
      delay(5000);
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
  }
  else{
           if (sensorValue>=452 && sensorValue<=454) //FAULT 1 Y-12KM
        {
          lcd.setCursor(6, 0);
          lcd.print("Y-F");
          lcd.setCursor(0, 1);
          lcd.print("12-KM");
        }
        else 
        {
            if (sensorValue>=467 && sensorValue<=469)  //FAULT 1 Y-12KM
          {
            lcd.setCursor(12, 0);
            lcd.print("B-F");
            lcd.setCursor(0, 1);
            lcd.print("12-KM");
          }
          else
          {
            if (sensorValue>=544 && sensorValue<=545)  //FAULT 2 R-8KM
            {
              lcd.setCursor(0, 0);
              lcd.print("R-F");
              lcd.setCursor(0, 1);
              lcd.print("8-KM");
            }
            else
            {
              if (sensorValue>=584 && sensorValue<=585)  //FAULT 2 y-8KM
              {
                lcd.setCursor(6, 0);
                lcd.print("Y-F");
                lcd.setCursor(0, 1);
                lcd.print("8-KM");
              }
              else
              {
                if (sensorValue>=664 && sensorValue<=666)  //FAULT 2 B-8KM
                {
                  lcd.setCursor(12, 0);
                  lcd.print("B-F");
                  lcd.setCursor(0, 1);
                  lcd.print("8-KM");
                }
                else
                {
                  if (sensorValue>=791 && sensorValue<=793)  //FAULT 3 r-4KM
                  {
                    lcd.setCursor(0, 0);
                    lcd.print("R-F");
                    lcd.setCursor(0, 1);
                    lcd.print("4-KM");
                  }
                  else
                  {
                     if (sensorValue>=930 && sensorValue<=935)  //FAULT 3 Y-4KM
                    {
                      lcd.setCursor(6, 0);
                      lcd.print("Y-F");
                      lcd.setCursor(0, 1);
                      lcd.print("4-KM");
                    }
                    else
                    {
                       if (sensorValue>=1000)  //FAULT 3 B-4KM
                      {
                        lcd.setCursor(12, 0);
                        lcd.print("B-F");
                        lcd.setCursor(0, 1);
                        lcd.print("4-KM");
                      }
                    }
                  } 
                }
              }
            }
          }
        }
      }
 





  // print the results to the serial monitor:
  Serial.print("sensor = " );
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);
}
