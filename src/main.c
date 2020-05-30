#include <stdio.h>
#include <stdlib.h>


int main() {
    int slaveNum = 0, portNum = 0, i = 0;
    char strS[120], strS1[120], strM[120], strM1[120];
    double j;

    printf("digite o número de escravos:");
    scanf("%d", &slaveNum);

    printf("digite a porta para a conexão:");
    scanf("%d", &portNum);

    printf("digite o valor de discretização:");
    scanf("%lf", &j);

    // Compile files
    system("gcc ./slave.c -lm -o slave && gcc ./master.c -o master");
    printf("chegou aqui feiao");
    for (i = 0; i < slaveNum; i++) {
        // Execute slaves in different terminals
        sprintf(strS, "gnome-terminal -- bash -c \"./slave %d\"; exec bash", portNum+i);
        system(strS);

        // Optional
        // sprintf(strS1, "xterm -e bash -c \"./slave %d\"; exec bash", portNum+i);
        // system(strS1);
    }
    // Execute master in current terminal 
    sprintf(strM, "./master localhost %d %d %lf", portNum, slaveNum, j);
    system(strM);
    
    // Optional
    // sprintf(strM1,"./master localhost %d %d %lf", portNum, slaveNum, j);
    // system(strM1);



    


    
    
    return 0;
}
