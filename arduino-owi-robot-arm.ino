

const int CONTROL_INPUTS[] = {A0,A1,A2,A3,A4};
const int NUM_CONTROL_INPUTS = 5;

const int NUM_MOTORS = 5;
const int PINS_PER_MOTOR = 2;
const int DRIVE_PINS[NUM_MOTORS][PINS_PER_MOTOR] = {
  {9, 10},
  {11, 12},
  {5, 6},
  {7, 8},
  {3, 4}
};

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    while (!Serial) {
        ; // Wait until Serial is available
    }

    // Set all the drive pins to OUTPUT mode
    for(int i=0; i < NUM_MOTORS; i++) {
        for( int j=0; j < PINS_PER_MOTOR; j++) {
            pinMode(DRIVE_PINS[i][j], OUTPUT);
        }
    }

    // Set all the input control pins to INPUT_PULLUP mode
    for(int i=0; i < NUM_CONTROL_INPUTS; i++) {
        pinMode(CONTROL_INPUTS[i], INPUT_PULLUP);
    }
    
}

void driveMotor(int motor, int direction)
{
    if(direction == -1) {
        digitalWrite(DRIVE_PINS[motor][0], HIGH);
        digitalWrite(DRIVE_PINS[motor][1], LOW);
    } else if(direction == 1) {
        digitalWrite(DRIVE_PINS[motor][0], LOW);
        digitalWrite(DRIVE_PINS[motor][1], HIGH);                
    } else {
        digitalWrite(DRIVE_PINS[motor][0], LOW);
        digitalWrite(DRIVE_PINS[motor][1], LOW); 
    }    
}
  
void loop() {

    //print out the value of the pushbutton
    int val = 0;
    int dir = 0;
    char formatted[3];
    for(int i=0; i < NUM_CONTROL_INPUTS; i++) {
        val = analogRead(CONTROL_INPUTS[i]);
        dir = directionFromAnalogValue(val);
        sprintf(formatted,"%04d ",val);
        Serial.print(formatted);

        driveMotor(i,dir);
        
    }
    Serial.println();
    
    delay(100);
}

/* Based on the controller being wired up with 3.3V for one pole and GND for the other.
 * The Analog inputs are configured INPUT_PULLUP, so normally 5V.
 * If the val is 800 - 900 (around 3.3V) then its been pushed down
 * If the val is   0 - 100 (around 0V) then its been pushed up
 */
int directionFromAnalogValue(long val)
{
    if(val < 100) {
        return -1; // Pushed Down
    } else if(val > 800 && val < 1000) {
        return 1;  // Pushed Up
    } else {
        return 0;  // Idle
    }
}