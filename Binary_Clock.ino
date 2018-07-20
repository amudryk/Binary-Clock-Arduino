unsigned long milliseconds;
int hours = 0; int minutes = 0; int seconds = 0; //initializes time to zero
int hour1; int minute1; //variables for ones digit of time
int min1[4], min10[4], hr1[4], hr10[4]; //for decimal-binary converter
volatile int state = LOW;//interrupt variable
int sensorPin = A1;
int value = 0;

void setup() {
  // put your setup code here, to run once:
  cli();    //disable interrupts
  Serial.begin(9600);
  TCNT1 = 1536;     //sets initial value of timer so that one turnover is exactly 4 milliseconds
  TCCR1A = 0x0;     //resets TCCR1A to zero
  TCCR1B = 0x1;     //Selects timer 1 so no prescaler is needed
  TIMSK1 = 0x1;     //Enables interrupts overflow bit
  for (int i = 3; i <= 10; i++) //initalize all pins as output
    pinMode(i, OUTPUT);
  for (int j = 7; j <= 10; j++)
    digitalWrite(j, HIGH); //initially writes all ground pins to HIGH
  pinMode(2, INPUT_PULLUP); //interrupt pin pull up
  attachInterrupt(0, Interrupt, LOW);//attach interrupt to pin 2
  sei(); // enable interupts
}

void loop() {
  // put your main code here, to run repeatedly:
  static unsigned long x = 0; //stores previous state of milliseconds
  if (milliseconds - x >= 100){ //increment seconds every 1000 milliseconds
    x = milliseconds;
    seconds++;
  }

  while (state == HIGH){  //interrupt flag
    value = analogRead(sensorPin);
    Serial.println(value);  //for testing
    if (value >= 6 && value <= 10) //conditions for each button being pressed tested value = 8
      minutes--;
      seconds = 0;
      delay(150);
    if (value >= 17 && value <= 21) //tested value = 19
      minutes++;
      seconds = 0;
      delay(150);
    if (value >= 28 && value <= 32 ) // tested value = 30
      hours--;
      seconds = 0;
      delay(150);
    if (value >= 38 && value <= 52) // tested value = 40
      hours++;
      seconds = 0;
      delay(150);
    state = !state; //resets interrupt flag
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
  
    
  led_calc(minute1, min1);  //decimal to binary converter, edits array to be binary representation of decimal number
  for (int i = 3; i >= 0; i--){
    int groundPin = i + 7;
    if (min1[i] == 1) //if index of array is high, turn LED on
      leds(6, groundPin); //6 is constant because we are turning LEDs on column by column
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

void leds(int pwr, int gnd){  //function to pulse an LED
  digitalWrite(pwr, HIGH);
  digitalWrite(gnd, LOW);
  delay(1);
  digitalWrite(pwr, LOW);
  digitalWrite(gnd, HIGH);
  delay(1);
}

void led_calc(int x, int s[4]){   //decimal to binary converter
  for (int i = 0; i < 4; i++){  //x is decimal number, s[4] is 4 digit integer array to store binary number (will store in reverse order)
    s[i] = x % 2;
    x /= 2;
  }
}

void Interrupt(){   //interrupt triggers flag in loop
  state =! state;
}

ISR(TIMER1_OVF_vect){   //non pin-based interrupt (timer1) (will trigger on an overflow)
  TCNT1 = 1536;   //initial value of timer1
  milliseconds += 4;  //increment milleseconds by 4 every time overflow occurs
}










