#include "Mux.h"

int S0,S1,S2,MuxA;
int *MuxVariables[8];
void Mux_init(int _S0, int _S1, int _S2, int _MuxA)
{
  S0 = _S0;
  S1 = _S1;
  S2 = _S2;
  MuxA = _MuxA;
  pinMode(S0,OUTPUT);
  pinMode(S1,OUTPUT);
  pinMode(S2,OUTPUT);
  pinMode(MuxA,INPUT);
}

int Mux_read(int _input)
{
    bool b0 = bitRead(_input,0);
    bool b1 = bitRead(_input,1);
    bool b2 = bitRead(_input,2);
    digitalWrite(S0,b0);
    digitalWrite(S1,b1);
    digitalWrite(S2,b2);
    int analogInputValue = analogRead(MuxA);
    if(*MuxVariables[_input] != NULL)
    {
        *MuxVariables[_input] = analogInputValue;
    }
    return analogInputValue;
}

void Mux_assign(int _input, int *variable)
{
  MuxVariables[_input] = variable;
  DEBUG_PRINT( (int) MuxVariables[_input]);
}

