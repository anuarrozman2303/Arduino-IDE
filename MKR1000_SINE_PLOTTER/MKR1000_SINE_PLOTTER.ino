void setup(){
  Serial.begin(96000);
  pinMode(35,INPUT);
}

void loop(){
  Serial.println(analogRead(35));
}

