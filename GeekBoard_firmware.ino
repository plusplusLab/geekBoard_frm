
uint8_t bytes_read; //incomming bytes
uint8_t bytes_left; //
uint16_t tmpAnalogVal, tmpDigitalValue;

char cmd[3]; // store cmd bytes : 3 bytes


void setup() {
    Serial.begin(115200);

    // initialize internal pullUps
    pinMode(3, INPUT_PULLUP);
    //digitalWrite(3, HIGH);

    pinMode(5, INPUT_PULLUP);
    //digitalWrite(5, HIGH);

    pinMode(6, INPUT_PULLUP);
    //digitalWrite(6, HIGH);

    pinMode(9, INPUT_PULLUP);
    //digitalWrite(9, HIGH);
    pinMode(LED_BUILTIN, OUTPUT);
    //digitalWrite(13, HIGH );

}

 void loop() {

   if(Serial.available()>0){
     //reads 3 bytes from serial
      cmd[bytes_read] = Serial.read();
      bytes_read ++;

       if(bytes_read == 3){

         //we have a full cmd check it
         // check if get digital
         if(strstr(cmd, "GD")!= NULL){
            //digitalWrite(13, HIGH);
            switch(cmd[2]){

              case 3:

                sendDigitalValue(3);
                break;
              case 5:
                sendDigitalValue(5);
                break;
              case 6:
                sendDigitalValue(6);
                break;
              case 9:
                sendDigitalValue(9);
                break;
              }
              //check if get analog
         } else if(strstr(cmd, "GA")!=NULL){

            switch(cmd[2]){

              case 0:
                  sendAnalogValue(0);
                  break;
              case 1:
                  sendAnalogValue(1);
                  break;
              case 2:
                  sendAnalogValue(2);
                  break;
              case 3:
                  sendAnalogValue(3);
                  break;
            }


       }
       //reset bytes_read
       bytes_read = 0;
     }
  }
}

void sendAnalogValue(uint16_t pin){

  tmpAnalogVal = analogRead(pin);
  Serial.write('A');
  Serial.write(pin);
  // send analog value as 2 bytes
  Serial.write(highByte(tmpAnalogVal));
  Serial.write(lowByte(tmpAnalogVal));

}

void sendDigitalValue(uint16_t pin){

  tmpDigitalValue = digitalRead(pin);
  Serial.write('D');
  
  Serial.write(pin);
  //send digital value as 1 byte value is going to be 1 for LOW since pullUps are activated , invert it
  Serial.write(tmpDigitalValue);
  
}




/*
/// check pinMode for digital pins
uint8_t bit = digitalPinToBitMask(pin);
uint8_t port = digitalPinToPort(pin);
volatile uint8_t *reg = portModeRegister(port);

if (*reg & bit) {
    // It's an output
} else {
    // It's an input
}
*/
