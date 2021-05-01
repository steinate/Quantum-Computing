/** @file 
 * Implements the Bernstein--Vazirani circuit
 * 30 qubits
 */

# include <stdio.h>
# include <math.h>

# include "QuEST.h" 


int main (int narg, char** varg) {


    /* 	
     * PREPARE QuEST
     */
    double t1 = get_wall_time();

    // model parameters
    int numQubits = 30;
    int secretNum = pow(2,30) + 1;

    // prepare QuEST
    QuESTEnv env = createQuESTEnv();

    // create qureg; let zeroth qubit be ancilla
    Qureg qureg = createQureg(numQubits, env);
    initZeroState(qureg);


    /* 	
     * APPLY ALGORITHM
     */

    // NOT the ancilla
    pauliX(qureg, 0);

    // CNOT secretNum bits with ancilla
    int bits = secretNum;
    int bit;
    for (int qb=1; qb < numQubits; qb++) {
        bit = bits % 2;
        bits /= 2;
        if (bit)
            controlledNot(qureg, 0, qb);
    }


    /* 	
     * VERIFY FINAL STATE
     */

    // calculate prob of solution state
    double successProb = 1.0;
    bits = secretNum;
    for (int qb=1; qb < numQubits; qb++) {
        bit = bits % 2;
        bits /= 2;
        successProb *= calcProbOfOutcome(qureg, qb, bit);
    }

    printf("solution reached with probability ");
    printf("%f", successProb);
    printf("\n");
    double t2 = get_wall_time();
    printf("Complete the simulation takes time %12.6f seconds.", t2 - t1);
    printf("\n");

    /*
    * 
     * FREE MEMORY
     */

    destroyQureg(qureg, env); 
    destroyQuESTEnv(env);
    return 0;
}
