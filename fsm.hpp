
/*
 * fsm.hpp
 *
 *  Created on: Sep 7, 2012
 *      Author:  Sailor Lee
 */

#ifndef FSM_HPP_
#define FSM_HPP_

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <string>


using namespace std ;

class FSM;

/*
 * ----------------------------------FsmState--Start--------------------------------------------
 */
/**
 * @Class FsmState fsm.hpp "fsm.hpp"
 * @brief Stores state information
 */
class FsmState
{
public:
    /**
     * constructor
     */
    FsmState();
    /**
     * deconstructor
     */
    ~FsmState();

    /**
     * Get state Name
     */
    string GetStateName();

    /**
     * Get next State
     */
    FsmState *GetNextState();

    /**
     * Set state Name
     */
    void SetStateName(string stateName);

    /**
     * Get function
     */
    //void *GetFunciton();
    /**
     * Set next State
     */
    void SetNextState(FsmState *nextstate);

    bool isEqualNull();

public:
    /**
     * stores the function pointer for the state
     */
    void (*function)( FSM* ,int,void**);


private:
    /**
     * Stores the name of the state
     */
   string stateName;
    /**
     * pointer to the next state
     */
    FsmState *nextState;

};


/*
 * ----------------------------------FsmState-End---------------------------------------------
 */
/**
 * -------------------------------------FSM--Start-----------------------------------------------------------
 */
/**
 * @struct FSM fsm.hpp "fsm.hpp"
 * @brief stores info regarding state machine
 */
class FSM{
public:

    /*
     * constructor
     */
    FSM();

    /**
     * deconstructor
     */
    ~FSM();

    /**
     * Get the fsmBase
     */
    FsmState *GetFsmBase();

    /**
     * Get the fsmCurState
     */
    FsmState *GetFsmCurState();

    /**
     * Get the fsmCurStateName
     */
    string GetFsmCurStateName();

    /**
     * Get the fsmArgNum
     */
    int GetFsmArgNum();

    /**
     * Get the fsmArgValue
     */

    void **GetFsmArgValue();

    //---------------------------------------------------------------------------------
    /**
         * Set the fsmBase
         */
        void SetFsmBase(FsmState *fsmbase);

        /**
         * Set the fsmCurState
         */
        void SetFsmCurState(FsmState *state);

        /**
         * Set the fsmCurStateName
         */
        void SetFsmCurStateName(string stateName);

        /**
         * Set the fsmArgNum
         */
        void SetFsmArgNum(int num);

        /**
         * Set the fsmArgValue
         */

        void **SetFsmArgValue(void **arg);
    //---------------------------------------------------------------------------------

    /**
     * The FSM entry point, this is where execution of code begins in FSM.
     */
    int FsmMain();

    /**
     * Execution of next state takes place here
     * @details function fsm_next can be used without FsmMain when we want to handle
     * state execution and not rely on FsmMain 's loop
     * @param obj: pointer to structure of type FSM, which defines the FSM
     */
    int FsmNextState();

    /**
     * Function to add a new state to the FSM.
     * @param state: name of the state to be added.
     * @param fun: name of the function to be executed for this state
     */
    int FsmAdd( string state, void (*fun)(FSM *, int, void **) );

    /**
     * Function to add a default state to FSM.
     * @details Adds a default state to FSM, this is the function called at the start of the FSM
     * or in case of error, with the appropriate error code
     * @param fun name of the function to be executed for this state
     */
    int FsmDefault( void (*fun)(FSM *, int, void **) );

    /**
     * Function to remove a state from the FSM.
     * @param state :name of state to be removed
     */
    int FsmRemove(string state);
    /**
     * Function to change state.
     * @details changes state to the new specified state, if the state does not exist returns error,
     * state change is not triggered till function calling FsmToState returns
     * @param state: name of state to change to
     * @param num: number of arguments
     * @param arg: arguments
     */
    int FsmToState( string state, int num, void** arg);

    /**
     * Function for FSM termination
     */
    void FsmTerminate();

private:
    /**
     * pointer to the linked list of FsmState structures
     */
     FsmState * fsmBase;

    /**
        * pointer to current FSM state
        */
     FsmState * fsmCurState;

    /**
     * name of current FSM state
     */
    string fsmCurStateName;
    /**
     * number of argument passed to the nest state
     */

    int fsmArgNum;
    /**
     * values of arguments passed to the next state
     */
    void ** fsmArgValue;
};
/**
 * -------------------------------------FSM--End-----------------------------------------------------------
 */

#endif /* FSM_HPP_ */
