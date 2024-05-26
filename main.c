#include <stdio.h>
#include "big_number.h"

int main()
{
    char str[] = "-1";
    BigNumber* bn = CreateBN(str);
    if (bn == NULL)
        printf("bn == NULL!\n");

    char rts[] = "-1";
    BigNumber* bn2 = CreateBN(rts);
    if (bn2 == NULL)
       printf("bn2 == NULL!\n");

    PrintBN(bn);

    SumBN(bn, bn2);

    DiffBN(bn, bn2);

    ProdBN(bn, bn2);

    DivBN(bn, bn2);

    PrintBN(bn);

    PrintBN(bn2);
    
    DeleteBN(&bn);
    
    PrintBN(bn);

    return 0;
}
