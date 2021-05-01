#include "QuEST.h"
#include "stdio.h"
#include "mytimer.hpp"

int main(int narg, char* argv[]) {

    QuESTEnv Env = createQuESTEnv();
    double t1 = get_wall_time();

    FILE* fp = fopen("probs.dat", "w");
    if (fp == NULL) {
        printf("    open probs.dat failed, Bye!");
        return 0;
    }

    FILE* fvec = fopen("stateVector.dat", "w");
    if (fp == NULL) {
        printf("    open stateVector.dat failed, Bye!");
        return 0;
    }

    int n = 3;
    float q_measure[30];
    Qureg q = createQureg(n, Env);

    pauliX(q, n - 1);



    //Phase Inversion
    //default target qubit : the last one cenvenient to calculate
    for (int index = 0; index < n; ++index)
        hadamard(q, index);

    pauliX(q, n - 1);

    //Inversion about the Mean
    for (int index = 0; index < n; ++index)
        hadamard(q, index);

    //inverse qubit except 0
    for (int index = 1; index < n; ++index)
        pauliX(q, index);

    for (int index = 0; index < n; ++index)
        hadamard(q, index);



    for (long long int i = 0; i < n; ++i) {
        q_measure[i] = calcProbOfOutcome(q, i, 1);
        //printf("  probability for q[%2lld]==1 : %lf    \n", i, q_measure[i]);
        fprintf(fp, "Probability for q[%2lld]==1 : %lf    \n", i, q_measure[i]);
    }
    fprintf(fp, "\n");
    printf("\n");

    for (int i = 0; i < n; ++i) {
        Complex amp = getAmp(q, i);
        //printf("Amplitude of %dth state vector: %f\n", i, prob);
        fprintf(fvec, "Amplitude of %dth state vector: %12.6f,%12.6f\n", i, amp.real, amp.imag);
    }

    double t2 = get_wall_time();
    printf("Complete the simulation takes time %12.6f seconds.", t2 - t1);
    printf("\n");
    destroyQureg(q, Env);
    destroyQuESTEnv(Env);

    return 0;
}