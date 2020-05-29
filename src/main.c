#include <stdio.h>
#include <stdlib.h>


int main() {
    int slaveNum = 0, portNum = 0, i = 0;
    char strS[120], strS1[120], strM[120], strM1[120];

    printf("digite o número de escravos:");
    scanf("%d", &slaveNum);

    printf("digite a porta para a conexão:");
    scanf("%d", &portNum);

    // Compile files
    system("gcc ./slave.c -o slave && gcc ./master.c -o master");

    for (i = 0; i < slaveNum; i++) {
        //openPort
        sprintf(strS, "gnome-terminal --bash -c \"./slave %d\"; exec bash", portNum);
        system(strS);
    }
        
    // Execute files in different terminals
    sprintf(strM, "gnome-terminal --bash -c \"./master %d %d\"; exec bash", portNum, slaveNum);
    system(strM);

    // optional
    // sprintf(strS1, "xterm -e bash -c \"./slave %d\"; exec bash", portNum);
    // sprintf(strM1, ""xterm -e bash -c \"./master %d %d\"; exec bash", portNum, slaveNum);
    //
    // system(strS1);
    // system(strM1);

    


    
    
    return 0;
}