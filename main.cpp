/*
 * main.cpp
 *
 *  Created on: Sep 7, 2012
 *      Author:  Sailor Lee
 */
#include "fsm.hpp"
#include <stdio.h>
#include <iostream>
int i;
using namespace std;
void f0(FSM *obj, int val,void **arg)
{
    // state -> default
    printf("value = %d\n",val);
    printf("at f0\n");
    i++;

    obj->FsmToState("st1",i,NULL);
}

void f1(FSM *obj, int val,void **arg)
{
    printf("value = %d\n",val);
    printf("at f1\n");

    if(i == 50)
        obj->FsmTerminate();

    obj->FsmToState("st2",i,NULL);
}


void f2(FSM *obj, int val,void **arg)
{
    printf("value = %d\n",val);
    printf("at f2\n");
    i++;
    if(i % 2 == 0)
        obj->FsmToState("st4",i,NULL);
    else
        obj->FsmToState("st3",i,NULL);;
}

void f3(FSM *obj, int val,void **arg)
{
    printf("value = %d\n",val);
    printf("at f3\n");
    obj->FsmToState("st1",i,NULL);;
}

void f4(FSM *obj, int val,void **arg)
{
    printf("value = %d\n",val);
    printf("at f4\n");
    obj->FsmToState("st1",i,NULL);;
}
int main()
{
    i = 1;
    FSM fsmObject;
    printf("value = %d\n",i);
    fsmObject.FsmDefault(f0);
    fsmObject.FsmAdd("st1",f1);
    fsmObject.FsmAdd("st2",f2);
    fsmObject.FsmAdd("st3",f3);
    fsmObject.FsmAdd("st4",f4);
    printf("value = %d\n",i);
    fsmObject.FsmMain();
    return 0;
}
