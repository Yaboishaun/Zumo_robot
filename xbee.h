#include <iostream>
#include <unistd.h>
using namespace std;


class Xbee {

public:
Xbee();
~Xbee();
void printInfo();
void converteer();
void leesWaarde();

private:
int data;
int info;
int infoMotorL;
int infoMotorR;
};
