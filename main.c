/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include "big_number.h"

int main()
{
    char str[] = "5555555555555555555555555555555";
    BigNumber* bn = CreateBN(str);
    if (bn == NULL)
        printf("bn == NULL!\n");

    char rts[] = "5555555555555555555555555555555";
    BigNumber* bn2 = CreateBN(rts);
    if (bn2 == NULL)
       printf("bn2 == NULL!\n");

        
    PrintBN(bn);

    SumBN(bn, bn2);
    
    DeleteBN(&bn);
    
    PrintBN(bn);

    return 0;
}
