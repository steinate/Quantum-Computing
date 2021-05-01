**The QuEST Challenge**   

Because of the huge cost of computational resources and the processing time needed, numerous
problems such as cryptology, many body quantum mechanics, and quantum machine learning still
can't be solved effectively even utilizing the most powerful supercomputers today. However,
quantum computers, which are based on the quantum mechanics, have demonstrated huge
advantages in these fields by benefiting from the advanced quantum algorithms. Among those
quantum algorithms, the Shor large number decomposition algorithm as well as the Grover quantum
search algorithm are the two most renowned. They have raised interest from the scientists and is
inspiring further development of quantum computing and quantum information. Unfortunately, the
development curve of the quantum computer hardware is still not very step, and there is no actual
quantum computer which can be used for solving practical science or cryptology issues. Thus, the
quantum systems are still simulated by using the classical computers.  

QuEST is the first open source, hybrid multithreaded and distributed, GPU accelerated simulator of
universal quantum circuits. QuEST is capable of simulating generic quantum circuits of general
one-qubit and two-qubits and multi-qubit controlled gates, on pure and mixed states, represented as
state-vectors and density matrices under the presence of decoherence.  

Describing the state of an n-bit classical register requires just n bits while describing the state of an
n-qubit quantum register requires $2^n$ complex numbers. As a result, simulating a quantum computer
using a classical machine is believed to be exponentially expensive with respect to the number of
qubits. But despite this, classical simulation of quantum computation is crucial for the study of new
algorithms and architectures  

In the preliminary round of ASC20-21, all teams are encouraged to complete the simulation of
quantum circuits of 30 qubits by using the provided quantum random circuit (random.c) and the
quantum Fourier transform circuits (GHZ_QFT.c). The memory requirement is at least 16GB. Such
circuits are actually intended for cracking the RSA encryption algorithm. In this challenge, you
should strive for the best results by reducing the computational needs in time and resources. The
proposal document should include descriptions of the software environment (operating system,
complier, math library, MPI software, and QuEST version, etc.), testing methods, performance
optimization methods, performance estimation, problem and solution analysis, etc. In-depth analysis
into QuEST's algorithm and source code is highly encouraged. The detailed tasks and requirements
for this challenge are listed below.  

Please compile, install the QuEST and run the program against the given data according to the
instructions below:

First, should compile and install QuEST, referring to the following steps:

1. Download the source code of QuEST
   ➢ The QuEST is most easily downloaded by using apt, git and GNU make, which can be
   obtained with “sudo apt install git make (Ubuntu) or yum install git make (Redhat)”.
   ➢ Downloaded it to the current directory (path/ to/QuEST) with “git clone
   https://github.com/QuEST-Kit/QuEST.git”.
   ➢ Or you can directly download the compressed file of QuEST (.tar.gz) at
   https://github.com/QuEST-Kit/QuEST/releases.  
2. Download the necessary QuEST associated files
   Three necessary files, including the mytimer.hpp, random.c and GHZ_QFT.c, are provided
   and can be downloaded through Baidu SkyDrive or Microsoft OneDrive, similar with the
   Language exam (LE) challenge listed above. In this challenge, two workloads should be
   completed: for the first workload named random circuit, mytimer.hpp, random.c and the
   source code of QuEST will be used, and for the other workload named GHZ_QFT, the
   mytimer.hpp, GHZ_QFT.c and the source code of QuEST will be used. Due to the independence of the two workloads, QuEST should be installed separately for each workload.  
3. Install QuEST and run the challenge tests
   For the workload named random circuit:
   “cp random.c tutorial_example.c”
   “cd build”
   “cmake ..”
   “make –j4”
   “./demo”
   Note that this is just an example to show how to install and run the tests. The participants
   can compile the code by using their optimizing strategies or run the test with MPI or
   OpenMP.
   The second workload (GHZ_QFT.c) can be installed in the same way mentioned above,
   except for “cp GHC_QHF.c tutorial_example.c” (instead of “cp random.c
   tutorial_example.c”).  

<img src="C:\Users\pjq\AppData\Roaming\Typora\typora-user-images\image-20210501104118471.png" alt="image-20210501104118471" style="zoom:80%;" />