#include "Mux.h"
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Initialize:
//assign 3 select ports and set the common
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
void multiplexer::init(int _S0, int _S1, int _S2, int _common)
{
  S0 = _S0;
  S1 = _S1;
  S2 = _S2;
  common = _common;
  pinMode(S0,OUTPUT);
  pinMode(S1,OUTPUT);
  pinMode(S2,OUTPUT);
  pinMode(common,INPUT);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//read:
//write the requested port number to the select bits
//then do an analogRead.
//if a variable is assigned, write the result to this variable.
//also return the read value
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
int multiplexer::read(int port)
{
    digitalWriteFast(S0,bitRead(port,0));
    digitalWriteFast(S1,bitRead(port,1));
    digitalWriteFast(S2,bitRead(port,2));
    delayMicroseconds(50);//experiment with value
    int analogInputValue = analogRead(common);
    if(assignedVar[port] != nullptr && abs(analogInputValue-oldInputValue[port]) > 10)
    {
        *assignedVar[port] = analogInputValue;
        oldInputValue[port] = analogInputValue;
    }
    return analogInputValue;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//auto read
//automatically increments the read port every call
//useful for keeping code clean when doing volume sliders
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
int multiplexer::read()
{
    int analogInputValue = read(autoreadPort);
    autoreadPort++;
    autoreadPort%=8;
    return analogInputValue;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//assign variables
//save the pointer to a variable to an internal database.
//when doing autoreads this variable is then automatically updated.
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
void multiplexer::assign(int port, int16_t *variable)
{
  assignedVar[port] = variable;
  int16_t i = *assignedVar[port];
  DEBUG_PRINT(i);
}

