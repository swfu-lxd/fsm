
/*
 * fsm.cpp
 *
 *  Created on: Sep 7, 2012
 *      Author: Sailor Lee
 */

#include "fsm.hpp"

/**
 * FsmState
 */
FsmState::FsmState()
{
    this->stateName = "";
    this->nextState = NULL;
    this->function = NULL;
}

FsmState::~FsmState()
{

}

string FsmState::GetStateName()
{
    return stateName;
}

FsmState *FsmState::GetNextState()
{
    return nextState;
}

void FsmState::SetStateName(string statename)
{
    stateName = statename;
}

void FsmState::SetNextState(FsmState *nextstate)
{
    nextState = nextstate;
}

bool FsmState::isEqualNull()
{
    bool b;
    b=(this == NULL);
    return b;
}

/**
 * FSM
 */

FSM::FSM()
{
    this->fsmBase = NULL;
    this->fsmCurState = NULL;
    this->fsmCurStateName = "";
    this->fsmArgNum = 0;
    this->fsmArgValue = NULL;
}

FSM::~FSM()
{

}

FsmState  *FSM::GetFsmBase()
{
    return fsmBase;
}

FsmState *FSM::GetFsmCurState()
{
    return fsmCurState;
}

string FSM::GetFsmCurStateName()
{
    return fsmCurStateName;
}

int FSM::GetFsmArgNum()
{
    return fsmArgNum;
}

void **FSM::GetFsmArgValue()
{
    return fsmArgValue;
}

void FSM::SetFsmCurState(FsmState *state)
{
    fsmCurState = state;
}

void FSM::SetFsmCurStateName(string stateName)
{
    fsmCurStateName = stateName;
}

void FSM::SetFsmArgNum(int num)
{
    fsmArgNum = num;
}

void **FSM::SetFsmArgValue(void **arg)
{
    fsmArgValue = arg;
    return fsmArgValue;
}

void FSM::SetFsmBase(FsmState *fsmbase)
{
    fsmBase = fsmbase;
}

int FSM::FsmNextState()
{
    FsmState *tmp = GetFsmBase();
    if((tmp == NULL)||(GetFsmCurState() == NULL))
    {
        return -1;
    }

    while ((tmp->GetStateName() != GetFsmCurStateName()) && (tmp!=NULL))
            tmp = tmp->GetNextState();
        if (tmp == NULL)
            return -1;
        tmp->function(this,GetFsmArgNum(),GetFsmArgValue());

    return 0;
}

int FSM::FsmMain()
{
    while(!FsmNextState())
    {

    }

    return 0;
}

int FSM::FsmAdd( string state, void (*fun)(FSM *, int, void **) )
{
    FsmState *tmp = GetFsmBase();
    FsmState *newState = new FsmState();
    while(tmp->GetNextState())
            tmp = tmp->GetNextState();

    newState->SetStateName(state);
    newState->function = fun;
    newState->SetNextState(NULL);
    tmp->SetNextState(newState);

   // delete(newState);
    return 0;
}

int FSM::FsmRemove(string state)
{
   // if (!strcmp(state,"default"))
    if(state == "default")
        return -1;

    FsmState *to_del;
    FsmState *tmp= GetFsmBase();

    while((tmp->GetNextState()!=NULL)&&(tmp->GetNextState()->GetStateName() == state))
        tmp=tmp->GetNextState();
    if (tmp == NULL)
        return -1;
    to_del = tmp->GetNextState();
    tmp->SetNextState(tmp->GetNextState()->GetNextState());
    delete(to_del);
    return 0;
}

int FSM::FsmDefault( void (*fun)(FSM *, int, void **) )
{
    this->fsmBase = new FsmState;
    this->GetFsmBase()->SetStateName("default");
    this->GetFsmBase()->function = fun;
    this->GetFsmBase()->SetNextState( NULL);
    // set current state to default
    this->SetFsmCurState(this->GetFsmBase());
    this->SetFsmCurStateName(this->GetFsmBase()->GetStateName());
    return 0;
}

int FSM::FsmToState( string state, int num, void** arg)
{
    FsmState *tmp=this->GetFsmBase();
    bool isTempNull, isStringEqual;
    while(!(tmp->isEqualNull())&&((tmp->GetStateName() != state)))
        tmp=tmp->GetNextState();
    if (tmp == NULL)
        return -1;
    this->SetFsmCurState( tmp);
    this->SetFsmCurStateName( tmp->GetStateName());
    this->SetFsmArgNum(num);
    this->SetFsmArgValue(arg);
    return 0;
}

void FSM::FsmTerminate()
{
    FsmState *tmp = this->GetFsmBase();
    FsmState *to_del=tmp;
    while(tmp)
    {
        to_del = tmp;
        tmp=tmp->GetNextState();
        delete(to_del);
    }
    // reset FSM base to NULL causes while loop in fsm_main to quit
    // terminating the program
    this->SetFsmCurState(NULL);
    this->SetFsmCurStateName( NULL);
    this->SetFsmBase( NULL);
}
