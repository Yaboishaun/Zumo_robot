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
    int lineFollow(int, int, bool);
     int lineFollow(int, int, bool, String);
    void checkEncoderErrors();
    void readEncoderCounts();
    void turnRight();
    void turnLeft();
    void straight();
    void stop();
    void circleClockwise();
    void circleCounterClockwise();
    void Left();
    void Right();
    void HardLeft();
    void HardRight();
    void HardStraight();
    void Back();
    void HardBack();

private:
    int speedLeft;
    int speedRight;
    int userSpeed;
    int maxSnelh;
    float kp = 0.2;
    float kd = 1;
    float ki = 0;
    int error= 0;
    int lastError;
    int integral;
    int command;
    bool errorLeft;
    bool errorRight;
    int countsLeft;
    int countsRight;
    int position = 0;
    char report1[20];
    
    Zumo32U4Motors motors;
    Zumo32U4Encoders encoders;
    Zumo32U4Buzzer buzzer;
    Zumo32U4LineSensors lineSensors;
    uint16_t sensors[3];
};

#endif
