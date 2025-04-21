/*
  ELEC1100 Your Lab#06 & Project Template

  To program the car tracking the white line on a dark mat

  Group No. (number of your project box):
  Group Member 1 (name & SID):
  Group Member 2 (name & SID):

*/

// assign meaningful names to those pins that will be used

int regular_speed = 140;
const int pinL_Sensor = A5; // pin A5: left sensor
const int pinB_Sensor = A4; // pin A4: bumper sensor
const int pinR_Sensor = A3; // pin A3: right sensor
const int pinOR_Sensor = A1;
const int pinOL_Sensor = A2;

const int pinL_PWM = 9;  // pin D9: left motor speed
const int pinL_DIR = 10; // pin D10: left motor direction

const int pinR_PWM = 11; // pin D11: right motor speed
const int pinR_DIR = 12; // pin D12: right motor direction
int curr_time = 0;
// define variables to be used in script

int bumperSensor = 1; // not sensing white
int leftSensor = 1;   // not sensing white
int rightSensor = 1;  // not sensing white
int OleftSensor = 1;
int OrightSensor = 1;

int countBumper = 0; // bumper sensor not triggered yet

// the setup function runs once when you press reset or power the board

void go_straight(int speed)
{
    analogWrite(pinL_PWM, speed+10);
    analogWrite(pinR_PWM, speed+10);
    digitalWrite(pinL_DIR, HIGH);
    digitalWrite(pinR_DIR, HIGH);
}
void turn_left(int speed)
{
    analogWrite(pinL_PWM, speed);
    analogWrite(pinR_PWM, speed);
    digitalWrite(pinL_DIR, LOW);
    digitalWrite(pinR_DIR, HIGH);
}
void turn_right(int speed)
{
    analogWrite(pinL_PWM, speed);
    analogWrite(pinR_PWM, speed);
    digitalWrite(pinL_DIR, HIGH);
    digitalWrite(pinR_DIR, LOW);
}
void go_back(int speed)
{
    analogWrite(pinL_PWM, speed);
    analogWrite(pinR_PWM, speed);
    digitalWrite(pinL_DIR, LOW);
    digitalWrite(pinR_DIR, LOW);
}
void stop_car()
{
    analogWrite(pinL_PWM, 0);
    analogWrite(pinR_PWM, 0);
}
void turn_right_plus(int speed)
{
    analogWrite(pinL_PWM, speed);
    analogWrite(pinR_PWM, speed * 1.5);
    digitalWrite(pinL_DIR, HIGH);
    digitalWrite(pinR_DIR, LOW);
}
void correct_track(int delaytime)
{
    if (!leftSensor && rightSensor)
    {
        turn_left(regular_speed);
        delay(delaytime);
    }

    if (leftSensor && !rightSensor)
    {
        turn_right(regular_speed);
        delay(delaytime);
    }

    if (leftSensor && rightSensor)
    {
        go_straight(regular_speed);
        delay(delaytime);
    }
}
void older_correct_track()
{
    if (!leftSensor && rightSensor)
    {
        turn_left(regular_speed);
    }

    if (leftSensor && !rightSensor)
    {
        turn_right(regular_speed);
    }

    if (leftSensor && rightSensor)
    {
        go_straight(regular_speed);
    }
}

void setup()
{
    // define pins as input and output
    pinMode(pinB_Sensor, INPUT);
    pinMode(pinL_Sensor, INPUT);
    pinMode(pinR_Sensor, INPUT);
    pinMode(pinOR_Sensor, INPUT);
    pinMode(pinOL_Sensor, INPUT);

    pinMode(pinL_DIR, OUTPUT);
    pinMode(pinR_DIR, OUTPUT);

    pinMode(pinL_PWM, OUTPUT);
    pinMode(pinR_PWM, OUTPUT);

    // initialize output pins
    digitalWrite(pinL_DIR, HIGH); // forward direction
    digitalWrite(pinR_DIR, HIGH); // forward direction
    analogWrite(pinL_PWM, 0);     // stop at the start position
    analogWrite(pinR_PWM, 0);     // stop at the start position
}

// the loop function runs over and over again forever

void loop()
{

    // Arduino is reading the sensor measurements
    bumperSensor = digitalRead(pinB_Sensor);
    leftSensor = digitalRead(pinL_Sensor);
    rightSensor = digitalRead(pinR_Sensor);
    OrightSensor = digitalRead(pinOR_Sensor);
    OleftSensor = digitalRead(pinOL_Sensor);

    // car stops at the start position when bumper sensor no trigger
    if (bumperSensor && countBumper == 0)
    {
        analogWrite(pinL_PWM, 0); // stop at the start position
        analogWrite(pinR_PWM, 0);
    }

    // bumper sensor is triggered at the start position for the 1st time
    if (!bumperSensor && countBumper == 0)
    {
        go_straight(regular_speed+10);
        countBumper = countBumper + 1;
        delay(600); // to let the car leave the start position with no miscount
    }
    if (bumperSensor && countBumper == 1)
    {
        if (!OleftSensor && !OrightSensor)
        {
            // stop_car();
            go_straight(regular_speed);
            delay(100);
            turn_left(regular_speed);
            delay(350);
            go_straight(regular_speed);
            delay(150);
            countBumper = countBumper + 1;
        }
        older_correct_track();
    }

    if (bumperSensor && countBumper == 2)
    {

        if (!OleftSensor && OrightSensor)
        {
            //stop_car();
            turn_left(regular_speed);
            countBumper++;
            delay(350);
            go_straight(regular_speed);
            delay(100);
        }
        older_correct_track();
    }

    if (bumperSensor && countBumper == 3)
    {

        correct_track(10);
        if (!leftSensor && !rightSensor)
        {
            turn_left(regular_speed);
            countBumper++;
            delay(800);
        }
    }
    if (bumperSensor && countBumper == 4)
    {
        /*go_straight(regular_speed);
        delay(700);*/
        correct_track(10);
        if (!leftSensor && !rightSensor && !OleftSensor && !OrightSensor)
        {
            go_straight(regular_spped);
            delay(100);
            turn_left(regular_speed);
            delay(350);
            countBumper = countBumper + 1;
            
        }
    }
    if (bumperSensor && countBumper == 5)
    {
        go_straight(regular_speed);
        delay(300);
        correct_track(10);
        if (!OrightSensor && !rightSensor)
        {
            go_straight(regular_speed);
            delay(100);
            turn_right(regular_speed);

            delay(500);
            go_straight(regular_speed);
            delay(100);
            curr_time = millis();
            countBumper = countBumper + 1;
        }
    }

    if (bumperSensor && countBumper == 6)
    {

        // correct_track(1000);
        older_correct_track();
        if (!leftSensor && !rightSensor && !OleftSensor && !OrightSensor && millis() > curr_time + 1000)
        {

            go_straight(regular_speed);
            delay(100);
            turn_left(regular_speed);
            delay(360);
            go_straight(regular_speed);
            delay(150);
            countBumper = countBumper + 1;
        }
    } // C curve and left_turn after C curve
    if (bumperSensor && countBumper == 7)
    {
        /*go_straight(regular_speed);
        delay(500);*/
        correct_track(10);
        if (!leftSensor && !OleftSensor && rightSensor)
        {
            go_straight(regular_speed);
            delay(400);
            countBumper++;
        }

        /*older_correct_track();
           countBumper = countBumper + 1;
           delay(360);*/
    }
    if (bumperSensor && countBumper == 8)
    {

        correct_track(10);
        if (!leftSensor && !OleftSensor && rightSensor)
        {
            turn_left(regular_speed);
            delay(360);
            // stop_car();
            go_straight(regular_speed);
            delay(200);
            turn_right(regular_speed);
            delay(360);
            go_straight(regular_speed);
            delay(300);
            // older_correct_track();
            countBumper = countBumper + 1;
        }
    }
    if (bumperSensor && countBumper == 9)
    {
        older_correct_track();
        if (!rightSensor && !OrightSensor && leftSensor)
        {
            turn_right(regular_speed);
            delay(360);
            go_straight(regular_speed);
            delay(150);
            older_correct_track();
            if (!rightSensor && !OrightSensor && leftSensor)
            {
                turn_right(regular_speed);
                delay(360);
                go_straight(regular_speed);
                delay(150);
                countBumper++;
            }
        }
    }

    if (bumperSensor && countBumper == 10)
    {
        older_correct_track();
        if (!leftSensor && !OleftSensor && rightSensor)
        {
            turn_left(regular_speed);
            countBumper = countBumper + 1;
            delay(360);
            go_straight(regular_speed);
            delay(150);
            countBumper++;
        }
    }
    if (bumperSensor && countBumper == 11)
    {
        older_correct_track();
        if (!leftSensor && !OleftSensor && rightSensor)
        {
            turn_left(regular_speed);
            countBumper = countBumper + 1;
            delay(360);
            go_straight(regular_speed);
            delay(150);
            countBumper++;
        }
    }
    if (bumperSensor && countBumper == 12)
    {
        older_correct_track();
        if (!leftSensor && !OleftSensor && !rightSensor && !OrightSensor)
        {
            //stop_car();
            turn_left(regular_speed);
            delay(1500);
            go_straight(regular_speed);
            delay(200);
            countBumper++;
        }
    }
    if(bumperSensor && countBumper == 13)
    {
        older_correct_track();
        if(!bumperSensor)
        {
            stop_car();
            go_back(regular_speed);
            delay(300);
            return;
        }
    }
     // second turn left
    /*if (bumperSensor && countBumper == 12)
    {
        if (!leftSensor && rightSensor)
        {
            turn_left(regular_speed);
        }

        if (leftSensor && !rightSensor)
        {
            turn_right(regular_speed);
        }

        if (leftSensor && rightSensor)
        {
            go_straight(regular_speed);
        }
        if (!rightSensor && !OrightSensor)
        {
            turn_right_plus(regular_speed);
            countBumper = countBumper + 1;
            delay(360);
        }
    }
    if (bumperSensor && countBumper == 13)
    {
        if (!leftSensor && rightSensor)
        {
            turn_left(regular_speed);
        }

        if (leftSensor && !rightSensor)
        {
            turn_right(regular_speed);
        }

        if (leftSensor && rightSensor)
        {
            go_straight(regular_speed);
        }
    }
    */
}
