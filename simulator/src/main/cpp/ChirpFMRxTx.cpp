#include "ChirpFMRxTx.h"

void ChirpFMRxTx::send(int, char[], size_t){}
char* ChirpFMRxTx::receive(){return nullptr;}
int ChirpFMRxTx::getNodeId(){return this->nodeId;}
int ChirpFMRxTx::getGroupId(){return this->groupId;}
void ChirpFMRxTx::setNodeId(int nodeId){this->nodeId = nodeId;}
void ChirpFMRxTx::setGroupId(int groupId){this->groupId = groupId;}