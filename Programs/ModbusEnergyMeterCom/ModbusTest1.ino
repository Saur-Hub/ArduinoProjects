  #include<ModbusMaster.h>
  #define MAX485_DE      3
  #define MAX485_RE_NEG  2
  ModbusMaster node;

  void preTransmission()
  {
    digitalWrite(MAX485_RE_NEG, 1);
    digitalWrite(MAX485_DE, 1);
  }

  void postTransmission()
  {
    digitalWrite(MAX485_RE_NEG, 0);
    digitalWrite(MAX485_DE, 0);
  }

  void setup() {
    pinMode(MAX485_RE_NEG, OUTPUT);
    pinMode(MAX485_DE, OUTPUT);
    // Init in receive mode 
    digitalWrite(MAX485_RE_NEG, 0);  
    digitalWrite(MAX485_DE, 0);  
  
    Serial.begin(19200,SERIAL_8E1);  
    //slave ID 1  
    node.begin(1, Serial);  

    Serial.println("Starting Modbus Transaction:");  
    node.preTransmission(preTransmission);  
    node.postTransmission(postTransmission);  
  }
  
  uint16_t newData = 0;
  float R, Y, B;
 
  void loop() {                           // loop starts from here.
    static uint32_t i;
    uint8_t j, result;
    uint16_t data[10];
    uint32_t lw;
    float fval;

    i++;
    result = node.readHoldingRegisters(3026,2);
    Serial.println(" ");
    if (result == node.ku8MBSuccess) {
      
      Serial.print("\nSuccess, Received data R: ");
      
      for (j = 0; j < 2; j++) {
        data[j] = node.getResponseBuffer(j);
 //       floatData = node.getResponseBuffer(j);
      }
       unsigned long temp = (unsigned long)data[0] + (unsigned long)data[1]*65536;
       R = *((float*)&temp);
       Serial.print("\nVoltage R:");
       Serial.print(R);
    } else {
      Serial.print("Failed, Response Code: ");
      Serial.print(result, HEX);
      Serial.println(" ");
      delay(5000); 
    }
    delay(1000);

    result = node.readHoldingRegisters(3028,2);
    Serial.println(" ");
    if (result == node.ku8MBSuccess) {
      
      Serial.print("\nSuccess, Received data Y: ");
      
      for (j = 0; j < 2; j++) {
        data[j] = node.getResponseBuffer(j);
 //       floatData = node.getResponseBuffer(j);
        }
       unsigned long temp = (unsigned long)data[0] + (unsigned long)data[1]*65536;
       Y = *((float*)&temp);
       Serial.print("\nVoltage Y:");
       Serial.print(Y);
    } else {
      Serial.print("Failed, Response Code: ");
      Serial.print(result, HEX);
      Serial.println(" ");
      delay(5000); 
    }
    delay(1000);

    result = node.readHoldingRegisters(3030,2);
    Serial.println(" ");
    if (result == node.ku8MBSuccess) {
      
      Serial.print("\nSuccess, Received data C: ");
      for (j = 0; j < 2; j++) {
        data[j] = node.getResponseBuffer(j);
 //       floatData = node.getResponseBuffer(j);
      }
        
       unsigned long temp = (unsigned long)data[0] + (unsigned long)data[1]*65536;
       B = *((float*)&temp);
       Serial.print("\nVoltage B:");
       Serial.print(B);
    } else {
      Serial.print("Failed, Response Code: ");
      Serial.print(result, HEX);
      Serial.println(" ");
      delay(5000); 
    }
    delay(1000);
  }
