/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 * 1. Two Sum
 * Given an array of integers, return indices of the two numbers such that they add up to a specific target.
 * You may assume that each input would have exactly one solution, and you may not use the same element twice.
 *
 * Example:
 * Given nums = [2, 7, 11, 15], target = 9,
 * Because nums[0] + nums[1] = 2 + 7 = 9,
 * return [0, 1].
 *
 * Approach:
 * Use a hash table to store (num->idx).
 * Say x + y = z, then y = z - x
 * For each number x, find its counterpart y by subtracting x from z. Now that we have the counterpart y, we can
 * quickly search it in the hash table. If there is such entry, return the index. If not, create a new entry into
 * the hash table.
 *
 * Complexity:
 * Time: O(n)
 * Space: O(n)
 *
 * Test Results:
 * Success
 * Runtime: 4 ms, faster than 98.23% of C online submissions for Two Sum.
 * Memory Usage: 6.5 MB, less than 17.10% of C online submissions for Two Sum.
 *
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
    bool        bCarry  = false;
    int         iSum    = 0;
    sListNode*  psCur   = NULL;
    sListNode*  psHead  = NULL;

    psHead              = calloc(1, sizeof(sListNode));
    psHead -> iVal      = 0;
    psHead -> psNext    = NULL;
    psCur               = psHead;

    if((psL1==NULL) && (psL2==NULL)){
        return psHead;
    }

    while (psL1!=NULL){
        if (psL2 == NULL){
            iSum    = psL1 -> iVal + (int)bCarry;
        } else{
            iSum    = psL1 -> iVal + psL2 -> iVal +(int)bCarry;
            psL2    = psL2 -> psNext;
        }
        psL1                = psL1 -> psNext;
        bCarry              = iSum/10;

        psCur   -> psNext   = calloc(1, sizeof(sListNode));
        psCur               = psCur -> psNext;
        psCur   -> iVal     = iSum % 10;
        psCur   -> psNext   = NULL;
    }

    while (psL2!=NULL){
        iSum                = psL2 -> iVal + (int)bCarry;
        bCarry              = iSum/10;

        psL2                = psL2 -> psNext;

        psCur   -> psNext   = calloc(1, sizeof(sListNode));
        psCur               = psCur -> psNext;
        psCur   -> iVal     = iSum % 10;
        psCur   -> psNext   = NULL;
    }

    if(bCarry){
        psCur   -> psNext   = calloc(1, sizeof(sListNode));
        psCur               = psCur -> psNext;
        psCur   -> iVal     = 1;
        psCur   -> psNext   = NULL;
    }

    psCur = psHead -> psNext;
    free(psHead);
    return psCur;
}

int main(){
    bool        bMatch              = false;
    int         pExpectedArr[]      = {0,1};
    int         pExpectedArrSize    = 2;
    int         pL1Nums[]           = {5};
    int         pL1NumsSize         = 1;
    int         pL2Nums[]           = {5};
    int         pL2NumsSize         = 1;
    sListNode*  psL1                = NULL;
    sListNode*  psL2                = NULL;
    sListNode*  psExpected          = NULL;
    sListNode*  psResult            = NULL;

    psL1        = creatList(pL1Nums     ,pL1NumsSize);
    psL2        = creatList(pL2Nums     ,pL2NumsSize);
    psExpected  = creatList(pExpectedArr,pExpectedArrSize);

    psResult    = addTwoNumbers(psL1,psL2);
    if(psResult == NULL){
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
    bMatch = true;

    printf( "%s\n",
            bMatch?"The result matches":"The result doesn't match");

    return 0;
}
