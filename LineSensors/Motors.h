// Motors.h
#ifndef MOTORS_H
#define MOTORS_H

#include <Zumo32U4.h>

class Motors {
public:
    Motors();

    int speedBlack();
    int speedGreen();
    void printSpeed();
    void handleUserCommands();
    void lineFollow();
    void checkEncoderErrors();
    void readEncoderCounts();
    void turnRight();
    void turnLeft();
    void straight();
    void stop();
    void circleClockwise();
    void circleCounterClockwise();

private:
    int speedLeft;
    int speedRight;
    int userSpeed;
    int maxSpeed;
    float kp;
    float kd;
    float ki;
    int lastError;
    int integral;
    int command;
    bool errorLeft;
    bool errorRight;
    int countsLeft;
    int countsRight;
    char report1[20];
    
    Zumo32U4Motors motors;
    Zumo32U4Encoders encoders;
    Zumo32U4Buzzer buzzer;
    Zumo32U4LineSensors lineSensors;
    uint16_t sensors[3];
};

#endif
