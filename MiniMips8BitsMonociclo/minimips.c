#include "minimips.h"
#include <string.h>
#include <math.h>
#include <stdio.h>


int conversorBinParaDecimal (int compDeDois, char * palavra){
    int decimal = 0;
    int len = strlen(palavra);
    int i = len - 1, posicao = 0;

    //ASCII//
    // 0 = 48
    // 1 = 49
    // ... //

    if (compDeDois == 1)
    {
        /* complemento de 2 */
        //...
        if ((palavra[0] - '0') == 0)
        {
            /* numero positivo */
           //...
        }else
        {
            /* numero negativo */
            //...
        }
        
        



    }else
    {
        /* não é complemento de 2 */
        for (i; i>=0; i--)
        {
            int num = palavra[i] - '0';
            decimal += num * pow(2 , posicao);
            posicao++;
        }
        printf("Decimal: %d", decimal);
    }

    return decimal;
    
}
