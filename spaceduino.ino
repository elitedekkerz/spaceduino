static uint8_t buttons[] = {
    2,4,6,8,10,12,14,16,18,20,24,26,28,30,48,44,42,40,38,36,34,32};
static uint8_t lights[] = {
    3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,47,45,43,41,39,37,35,33};
static uint8_t analogs[] = {
    A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A12,A14,A15};
const uint8_t buttonsLen = sizeof(buttons)/sizeof(buttons[0]);
const uint8_t lightsLen = sizeof(lights)/sizeof(lights[0]);
const uint8_t analogsLen = sizeof(analogs)/sizeof(analogs[0]);
uint8_t lightStates[lightsLen];

void setup(){
    //setup buttons
    if (buttonsLen != 0)
        for(uint8_t i = 0; i<buttonsLen; i ++){
            pinMode(buttons[i], INPUT);
            digitalWrite(buttons[i], HIGH);
        }

    //setup lights
    if (lightsLen != 0)
        for(uint8_t i = 0; i<lightsLen; i ++){
            pinMode(lights[i], OUTPUT);
            digitalWrite(lights[i], HIGH);
        }

    //setup analog inputs
    if (analogsLen != 0)
        for(uint8_t i = 0; i<analogsLen; i ++){
            pinMode(analogs[i], INPUT);
            digitalWrite(analogs[i], LOW);
        }

    Serial.begin(115200);
    Serial.print("ready\n");
}

void loop(){
    //read inputs and output them to serial as JSON string

    static uint8_t currentLight=0;
    while (Serial.available()){
        char value = Serial.read();
        switch (value){ 
            case '\r':
            case '\n':
            case ';':
                //reset light counter on newline
                currentLight = 0;
                //return io status
                Serial.print("{\"analogs\":[");
                for (uint8_t i=0; i<analogsLen; i++){
                    Serial.print(analogRead(analogs[i]));
                    if (i != analogsLen -1)
                        Serial.print(",");
                }
                Serial.print("],\"digitals\":[");
                for (uint8_t i=0; i<buttonsLen; i++){
                    Serial.print(digitalRead(buttons[i]));
                    if (i != buttonsLen -1)
                        Serial.print(",");
                }
                Serial.print("],\"outputs\":[");
                for (uint8_t i=0; i<lightsLen; i++){
                    Serial.print(digitalRead(lights[i]));
                    if (i != lightsLen -1)
                        Serial.print(",");
                }
                Serial.print("]}\n");
                break;
            case ',':
                //change light
                if (currentLight<lightsLen)
                    currentLight ++;
                break;
            case '1':
                //set current light high
                digitalWrite(lights[currentLight],HIGH);
                break;
            case '0':
                //set current light low
                digitalWrite(lights[currentLight],LOW);
                break;
            case '?':
                //give basic info
                Serial.print("http://github.com/eliteDekkerz/spaceduino\n");
                break;
        }
    }
}
