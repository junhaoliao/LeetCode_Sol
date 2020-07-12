/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 * 2. Add Two Numbers
 * You are given two non-empty linked lists representing two non-negative integers. The digits
 * are stored in reverse order and each of their nodes contain a single digit. Add the two numbers
 * and return it as a linked list.
 * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
 *
 * Example:
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 0 -> 8
 * Explanation: 342 + 465 = 807.
 *
 * Approach:
 * Say x + y = z
 * If z>=10, there is a carry digit (1). The carry digit should be accounted for the next digit.
 * Starting from the heads of the linked lists(least-significant digit), do addition for each
 * digit in the linked lists in order. If there is a carry digit, account for it in the addition
 * for the next digit.
 *
 * Complexity:
 * Time: O(max(m+n))
 * Space: O(max(m+n))
 *
 * Test Results:
 * Success
 * Runtime: 12 ms, faster than 82.78% of C online submissions for Add Two Numbers.
 * Memory Usage: 7.3 MB, less than 68.43% of C online submissions for Add Two Numbers.
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

    // do addition as long as either list is not NULL
    while (psL1!=NULL || psL2!=NULL){
        // if the list node is null, the number should be seen as 0
        iSum    = (psL1?(psL1 -> iVal):0) + (psL2?(psL2 -> iVal):0) +(int)bCarry;
        if(psL1){
            psL1    = psL1 -> psNext;
        }
        if(psL2){
            psL2    = psL2 -> psNext;
        }
        bCarry              = iSum/10;

        psCur   -> psNext   = calloc(1, sizeof(sListNode));
        psCur               = psCur -> psNext;
        psCur   -> iVal     = iSum % 10;
        psCur   -> psNext   = NULL;
    }

    // account for the carry digit if any
    if(bCarry){
        psCur   -> psNext   = calloc(1, sizeof(sListNode));
        psCur               = psCur -> psNext;
        psCur   -> iVal     = 1;
        psCur   -> psNext   = NULL;
    }

    // free the dummy head and return the actual head
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

    if(psResult == NULL){
        bMatch = true;
    }

    printf( "%s\n",
            bMatch?"The result matches":"The result doesn't match");

    return 0;
}
