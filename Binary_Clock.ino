int hours = 0; int minutes = 0; int seconds = 0; //initializes time to zero
int hour1; int minute1; //variables for ones digit of time
int min1[4], min10[4], hr1[4], hr10[4]; //for decimal-binary converter
volatile int state = LOW;//interrupt variable
int sensorPin = A1;
int value = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 3; i <= 10; i++)
    pinMode(i, OUTPUT);
  for (int j = 7; j <= 10; j++)
    digitalWrite(j, HIGH);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, Interrupt, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  seconds++;
  delay(10);

  while (state == HIGH){
    value = analogRead(sensorPin);
    Serial.println(value);
    if (value <= 2)
      minutes--;
    if (value >= 7 && value <= 12)
      minutes++;
    if (value >= 27 && value <= 34 )
      hours--;
    if (value >= 51 && value <= 60 )
      hours++;
    state = !state;
  }
   
  if(seconds >= 60){
    seconds = 0;
    minutes++;
  }if (minutes >= 60){
    minutes = 0;
    hours ++;
  }if (hours >= 24){
    hours = 0;
    minutes = 0;
  }
  
  int minute1 = minutes % 10; //corresponds to pin 5 column
  int minute10 = (minutes - minute1)/10; //corresponds to pin4 column
  int hour1 = hours % 10; //corresponds to pin3 column
  int hour10 = (hours - hour1)/10; //corresponds to pin2 column
  
    
  led_calc(minute1, min1);
  for (int i = 3; i >= 0; i--){
    int groundPin = i + 7;
    if (min1[i] == 1)
      leds(6, groundPin);
  }
  
  led_calc(minute10, min10);
  for (int i = 3; i >= 0; i--){
    int groundPin = i + 7;
    if (min10[i] == 1)
      leds(5, groundPin);
  }
  
  led_calc(hour1, hr1);
  for (int i = 3; i >= 0; i--){
    int groundPin = i + 7;
    if (hr1[i] == 1)
      leds(4, groundPin);
  }
  
  led_calc(hour10, hr10);
  for (int i = 3; i >= 0; i--){
    int groundPin = i + 7;
    if (hr10[i] == 1)
      leds(3, groundPin);
  }
}

void leds(int pwr, int gnd){
  digitalWrite(pwr, HIGH);
  digitalWrite(gnd, LOW);
  delay(1);
  digitalWrite(pwr, LOW);
  digitalWrite(gnd, HIGH);
  delay(1);
}

void led_calc(int x, int s[4]){
  for (int i = 0; i < 4; i++){
    s[i] = x % 2;
    x /= 2;
  }
}

void Interrupt(){
  state =! state;
}











