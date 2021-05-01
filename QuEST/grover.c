/**@file grover.c
* @brief Grover搜索算法实现
* @details 该程序模拟了n=1,nout=1的简单情形
*/

#include "QuEST.h"
#include "stdio.h"
#include "mytimer.hpp"

int main (int narg, char *argv[]) {

    QuESTEnv Env = createQuESTEnv();
    double t1 = get_wall_time();

    FILE *fp=fopen("probs.dat", "w");
    if(fp==NULL){
        printf("    open probs.dat failed, Bye!");
        return 0;
    }

    FILE *fvec=fopen("stateVector.dat", "w");
    if(fp==NULL){
        printf("    open stateVector.dat failed, Bye!");
        return 0;
    }

    float q_measure[30];
    int c[30];
    for (int i = 0; i < 30; i++)
        c[i] = 0;
    
    int controls[2] = {0, 1};
    Qureg q = createQureg(3, Env);
    
    pauliX(q,2);

    for (int index=0;index<3;++index)
        hadamard(q,index);
    ///< here we have prepared the initial state |++->    
    ///< toffoli(q,controls,2);
    ComplexMatrix2 u;
    u.r0c0=u.r1c1=(Complex) {.real=.0, .imag=.0};
    u.r0c1=u.r1c0=(Complex) {.real=1.0, .imag=.0};
    multiControlledUnitary(q, controls, 2, 2, u);

    for (int index=0;index<2;++index)
        hadamard(q,index);
    pauliX(q,0);
    pauliX(q,1);
    hadamard(q,1);
    controlledNot(q, 0, 1);
    hadamard(q,1);
    pauliX(q,0);
    pauliX(q,1);
    for (int index=0;index<3;++index)
        hadamard(q,index);
    
    //printf("\n");
    for(long long int i=0; i<3; ++i){
        q_measure[i] = calcProbOfOutcome(q, i, 1);
        //printf("  probability for q[%2lld]==1 : %lf    \n", i, q_measure[i]);
        fprintf(fp, "Probability for q[%2lld]==1 : %lf    \n", i, q_measure[i]);
    }
    fprintf(fp, "\n");
    printf("\n");

    for(int i=0; i<8; ++i){
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