#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

string index[14]={"tGate","sGate","pauliX","pauliY","pauliZ","hadamard","controlledNot","controlledPauliY","rotateX","rotateY","rotateZ","controlledRotateX","controlledRotateY","controlledRotateZ"};
int main ()
{
    srand(time(NULL));

    int n,m,i,j;//n: 模拟量子比特数，m: 门的索引
    double angle;
    const double double_pi=6.28318530717958647;
   ofstream outfile;
   outfile.open("new.c");

   cout << "Writing to the file" << endl;
   cout << "Enter the number of qubits: ";
   cin>>n;
   outfile<<"#include \"QuEST.h\"\n#include \"stdio.h\"\n#include \"mytimer.hpp\"\n\n";
   outfile<<"int main(int narg, char* argv[]) {\n\n";
   outfile<<'\t'<<"QuESTEnv Env = createQuESTEnv();\n\tdouble t1 = get_wall_time();\n\n";
   outfile<<'\t'<<"FILE* fp = fopen(\"probs.dat\", \"w\");\n";
   outfile<<'\t'<<"if (fp == NULL) {\n\t\tprintf(\"    open probs.dat failed, Bye!\");\n\t\treturn 0;\n\t}\n\n";
   outfile<<'\t'<<"FILE* fvec = fopen(\"stateVector.dat\", \"w\");\n";
   outfile<<'\t'<<"if (fp == NULL) {\n\t\tprintf(\"    open stateVector.dat failed, Bye!\");\n\t\treturn 0;\n\t}\n\n";
   outfile<<'\t'<<"Qureg q = createQureg("<<n<<", Env);\n\n";
   outfile<<'\t'<<"float q_measure["<<n<<"];\n\n";
    for(int it=0;it<n*16;++it){
        m=rand()%14;
        i=rand()%n;//i: 控制比特，j：目标比特

        if(m<6){
            outfile<<'\t'<<index[m]<<"(q, "<<i<<");"<<endl;
        }
        else if(m<8){
            do{
                j=rand()%n;
            }while(j==i);
            outfile<<'\t'<<index[m]<<"(q, "<<i<<", "<<j<<");"<<endl;
        }
        else{
            angle=rand()*double_pi/double(RAND_MAX+1);
            if(m<11){
                outfile<<'\t'<<index[m]<<"(q, "<<i<<", "<<angle<<");"<<endl;
            }
            else{
                do{
                    j=rand()%n;
                }while(j==i);
                outfile<<'\t'<<index[m]<<"(q, "<<i<<", "<<j<<", "<<angle<<");"<<endl;
            }
        }
    }

    outfile<<"\nprintf(\"\\n\");\nfor (long long int i = 0; i < "<<n<<"; ++i) {\n    q_measure[i] = calcProbOfOutcome(q, i, 1);\n    //printf(\"  probability for q[%2lld]==1 : %lf    \\n\", i, q_measure[i]);\n    fprintf(fp, \"Probability for q[%2lld]==1 : %lf    \\n\", i, q_measure[i]);\n}\nfprintf(fp, \"\\n\");\nprintf(\"\\n\");\n\n\n";
    outfile<<"for (int i = 0; i < 10; ++i) {\n    Complex amp = getAmp(q, i);\n    //printf(\"Amplitude of %dth state vector: %f\\n\", i, prob);\n    fprintf(fvec, \"Amplitude of %dth state vector: %12.6f,%12.6f\\n\", i, amp.real, amp.imag);\n}";
    outfile<<"\n\ndouble t2 = get_wall_time();\nprintf(\"Complete the simulation takes time %12.6f seconds.\", t2 - t1);\nprintf(\"\\n\");\ndestroyQureg(q, Env);\ndestroyQuESTEnv(Env);\n\nreturn 0;\n}";
   // 关闭打开的文件
   outfile.close();

   return 0;
}
