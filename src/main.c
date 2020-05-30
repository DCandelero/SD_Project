#include <stdio.h>
#include <stdlib.h>


int main() {
    int slaveNum = 0, portNum = 50000, j_size = 0, i = 0, k = 0;
    char strS[120], strS1[120], strM[120], strM1[120];
    double j[] = {0.01, 0.001, 0.0001};
    
    // Getting array size
    j_size = sizeof(j)/sizeof(j[0]);

    printf("digite o número de escravos:");
    scanf("%d", &slaveNum);

    for (k = 0; k<j_size; k++) {
        printf("Using %lf as discretization interval:\n-----------------------------------------\n", j[k]);

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
        sprintf(strM, "./master localhost %d %d %lf", portNum, slaveNum, j[k]);
        system(strM);

        // optional
        // sprintf(strM1, "./master localhost %d %d %lf", portNum, slaveNum, j[k]);
        // system(strM1);
    }

    return 0;
}