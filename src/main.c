#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {
    int slaveNum = 0, portNum, i = 0;
    char strS[120], strS1[120], strM[120], strM1[120];
    double j;
    srand(time(NULL));
    portNum = (rand()+5000)%60000;

    printf("Digite o número de escravos:");
    scanf("%d", &slaveNum);

    printf("\nInsira o intervalo de discretização:");
    scanf("%lf", &j);

    // Compile files
    system("gcc ./slave.c -lm -o slave && gcc ./master.c -o master");

    for (i = 0; i < slaveNum; i++) {
        // Execute slaves in different terminals
        sprintf(strS, "gnome-terminal -- bash -c \"./slave %d\"", portNum+i);
        system(strS);

        // optional
        // sprintf(strS1, "xterm -e bash -c \"./slave %d\"; exec bash", portNum+i);
        // system(strS1);
    }
        
    // Execute master in current terminal
    sprintf(strM, "./master localhost %d %d %lf", portNum, slaveNum, j);
    system(strM);

    // optional
    // sprintf(strM1, "./master %d %d %lf", portNum, slaveNum, j);
    // system(strM1);


    
    return 0;
}