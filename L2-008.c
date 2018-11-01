#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1002
int main()
{
    char str[MAX_N];
    int i, len, j, curLen, bSymmetric;
    fgets(str, MAX_N, stdin);
    len = strlen(str);
    str[len-1] = '\0';
    for(curLen=len; curLen>=1; --curLen)
    {
        for(i=0; i<=len-curLen; ++i)
        {
            //[i, j]  is symmetric
            j = i+curLen-1;
            bSymmetric = 1;
            while(i<j)
            {
                if(str[i]!=str[j])
                {
                    bSymmetric = 0;
                    break;
                }
                ++i;
                --j;
            }
            if(bSymmetric)
                break;
        }
        if(bSymmetric)
        {
            printf("%d", curLen);
            break;
        }
    }
    return 0;
}
