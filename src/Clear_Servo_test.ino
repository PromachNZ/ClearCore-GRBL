#include "ClearCore.h"
#define motor ConnectorM0
#define baudRate 9600
int velocityLimit = 10000; // pulses per sec
int accelerationLimit = 100000; // pulses per sec^2
// 
void Moved(int distance);

void setup() {
    // Put your setup code here, it will only run once:

    // Sets the input clocking rate.
    MotorMgr.MotorInputClocking(MotorManager::CLOCK_RATE_NORMAL);

    // Sets all motor connectors into step and direction mode.
    MotorMgr.MotorModeSet(MotorManager::MOTOR_ALL,
                          Connector::CPM_MODE_STEP_AND_DIR);

    // These lines may be uncommented to invert the output signals of the 
    // Enable, Direction, and HLFB lines. Some motors may have input polarities 
    // that are inverted from the ClearCore's polarity.
    //motor.PolarityInvertSDEnable(true);
    //motor.PolarityInvertSDDirection(true);
    //motor.PolarityInvertSDHlfb(true);

    // Sets the maximum velocity for each move
    motor.VelMax(velocityLimit);

    // Set the maximum acceleration for each move
    motor.AccelMax(accelerationLimit);

    // Sets up serial communication and waits up to 5 seconds for a port to open.
    // Serial communication is not required for this example to run.
    Serial.begin(baudRate);
    uint32_t timeout = 5000;
    uint32_t startTime = millis();
    while (!Serial && millis() - startTime < timeout) {
        continue;
    }

    motor.EnableRequest(true);
    Serial.println("Motor Ready");
}

void loop() {
    // Put your main code here, it will run repeatedly:
    Moved(6400);
    delay(2000);
    
    Moved(19200);
    delay(2000);
    
    Moved(-12800);
    delay(2000);

    Moved(-6400);
    delay(2000);

    Moved(-6400);
    delay(2000);
}

// Function used to move the motor to number of steps. +ve Values depicts the one side while -ve values depicts the opposite side.
void Moved(int distance) {
    Serial.print("Moving distance: ");
    Serial.println(distance);

    // Command the move of incremental distance
    motor.Move(distance);

    // Waits for all step pulses to output
    Serial.println("Moving... Waiting for the step output to finish...");
    while (!motor.StepsComplete()) {
        continue;
    }

    Serial.println("Steps Complete");
}
//------------------------------------------------------------------------------
