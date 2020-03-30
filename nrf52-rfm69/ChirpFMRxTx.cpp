#include <SPI.h>                // Included with Arduino IDE, should also add https://github.com/LowPowerLab/SPIFlash
#include "ChirpFMRxTx.h"

int ChirpFMRxTx::getNodeId(){return this->nodeId;}
int ChirpFMRxTx::getGroupId(){return this->groupId;}
void ChirpFMRxTx::setNodeId(int nodeId){this->nodeId = nodeId;}
void ChirpFMRxTx::setGroupId(int groupId){this->groupId = groupId;}
