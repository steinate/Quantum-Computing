# Bernstein-Vazirani算法

主要原理图：<img src="https://sjtueducn-my.sharepoint.com/personal/keymorrislane_sjtu_edu_cn/Documents/%E9%AB%98%E6%80%A7%E8%83%BD%E8%AE%A1%E7%AE%97%E7%AB%9E%E8%B5%9B/ASC21/QuEST/%E6%9B%B4%E5%A4%9A%E7%AE%97%E4%BE%8B/Bernstein-Vazirani/Bernstein-Vazirani.png" style="zoom:50%;" />

```c
// model parameters
int numQubits = 30;
int secretNum = pow(2,30) + 1;

// prepare QuEST
QuESTEnv env = createQuESTEnv();

// create qureg; let zeroth qubit be ancilla
Qureg qureg = createQureg(numQubits, env);
initZeroState(qureg);

// NOT the ancilla
pauliX(qureg, 0)
```

构造30量子比特，单节点上最多33量子比特，并全初始化为$\vert0\rangle$，再将第0个比特翻转为$\vert1\rangle$，即ancilla ，初始化完毕。

```c
// CNOT secretNum bits with ancilla
    int bits = secretNum;
    int bit;
    for (int qb=1; qb < numQubits; qb++) {
        bit = bits % 2;
        bits /= 2;
        if (bit)
            controlledNot(qureg, 0, qb);
    }
```

注意，此处采用了一种简化的方式，称为Mermins‘explanation，由于两个 Hadamard门在controlledNot门前后作用相当于没有操作，只需要在secretNum二进制位上为1的位上作用controlledNot门就可以实现，而此处的循环为寻找二进制位上为1的位并与ancilla相互作用即controlledNot门。

```c
 // calculate prob of solution state
    double successProb = 1.0;
    bits = secretNum;
    for (int qb=1; qb < numQubits; qb++) {
        bit = bits % 2;
        bits /= 2;
        successProb *= calcProbOfOutcome(qureg, qb, bit);
    }
```

将每个量子位为secretNum上对应的位的概率计算后相乘得到总的概率。

```c

```

