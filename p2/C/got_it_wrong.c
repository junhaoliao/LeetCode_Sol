/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 */////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <malloc.h>
#include <stdio.h>

typedef struct sListNode {
    int iVal;
    struct sListNode *psNext;
} sListNode;

sListNode* creatList(int* iNums, int iNumsSize){
    int         iI      = 0;
    sListNode*  psCur   = NULL;
    sListNode*  psHead  = NULL;

    if(iNumsSize == 0){
        return  psHead;
    }
    psHead              = calloc(1, sizeof(sListNode));
    psHead -> iVal      = iNums[0];
    psHead -> psNext    = NULL;
    psCur               = psHead;

    for(iI = 1; iI < iNumsSize; iI++){
        psCur -> psNext = calloc(1, sizeof(sListNode));
        psCur           = psCur -> psNext;
        psCur -> iVal   = iNums[iI];
        psCur -> psNext = NULL;
    }

    return psHead;
}

struct sListNode* addTwoNumbers(struct sListNode* psL1, struct sListNode* psL2){
    sListNode*  psCur   = NULL;
    sListNode*  psHead  = NULL;

    if((psL1 == NULL) && (psL2 == NULL)){
        return psHead;
    }

    psHead              = calloc(1, sizeof(sListNode));
    psHead -> psNext    = NULL;
    psCur               = psHead;
    while (psL1!=NULL){
        psCur -> psNext     = calloc(1, sizeof(sListNode));
        psCur               = psCur -> psNext;
        psCur -> psNext     = NULL;

        if(psL2 == NULL){
            psCur -> iVal   = psL1 -> iVal;
        } else {
            psCur -> iVal   = psL1 -> iVal + psL2 -> iVal;
            psL2            = psL2 -> psNext;
        }
        psL1                = psL1 -> psNext;
    }
    while (psL2!=NULL){
        psCur -> psNext     = calloc(1, sizeof(sListNode));
        psCur               = psCur -> psNext;
        psCur -> psNext     = NULL;

        psCur -> iVal       = psL2 -> iVal;
        psL2                = psL2 -> psNext;
    }

    psCur = psHead -> psNext;
    free(psHead);
    return psCur;
}

int main(){
    bool        bMatch              = false;
    int         pExpectedArr[]      = {7,10,7};
    int         pExpectedArrSize    = 3;
    int         pL1Nums[]           = {2,4,3};
    int         pL1NumsSize         = 3;
    int         pL2Nums[]           = {5,6,4};
    int         pL2NumsSize         = 3;
    sListNode*  psL1                = NULL;
    sListNode*  psL2                = NULL;
    sListNode*  psExpected          = NULL;
    sListNode*  psResult            = NULL;

    psL1        = creatList(pL1Nums     ,pL1NumsSize);
    psL2        = creatList(pL2Nums     ,pL2NumsSize);
    psExpected  = creatList(pExpectedArr,pExpectedArrSize);

    psResult    = addTwoNumbers(psL1,psL2);
    if(psResult == NULL && !(psL1 == NULL && psL2 == NULL)){
        printf( "addTwoNumbers() returned null pointer\n");
        return -1;
    }

    while (psExpected != NULL){
        if(psResult == NULL){
            printf( "The result list is shorter than expected. %s\n",
                    bMatch?"The result matches":"The result doesn't match");
            return  -1;
        }
        if(psResult -> iVal != psExpected -> iVal){
            printf( "psResult -> iVal = %d, psExpected -> iVal = %d, "
                    "The result list doesn't match the expected list. %s\n",
                    psResult -> iVal,
                    psExpected -> iVal,
                    bMatch?"The result matches":"The result doesn't match");
            return  -1;
        }
        psExpected  = psExpected    -> psNext;
        psResult    = psResult      -> psNext;
    }

    if(psResult == NULL){
        bMatch = true;
    }

    printf( "%s\n",
            bMatch?"The result matches":"The result doesn't match");

    return 0;
}
