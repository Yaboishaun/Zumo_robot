

class Xbee {

public:
Xbee();
~Xbee();
int printInfo();
void converteer();
void leesWaarde();

private:
int data;
int info;
int infoMotorL;
int infoMotorR;
bool read = true;
};