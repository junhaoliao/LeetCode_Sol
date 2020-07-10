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

#define RESULT_ARRAY_SIZE 2
#define HASH_TABLE_SIZE 1024

#define abs(x)  ( ( (x) < 0) ? -(x) : (x) )

// Collision resolved by Separate Chaining with Linked Lists
typedef struct sHashNode{
    int                 iKey;   /* key of the hash table    = pNums[iI]             */
    int                 iIndex; /* data of the hash table   = iI                    */
    struct sHashNode*   pNext;  /* pointer to the next element in the linked list   */
} sHashNode;

int hashFunc(int iNum){
    return abs(iNum % HASH_TABLE_SIZE);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* pNums, int iNumsSize, int iTarget, int* pReturnSize){
    int         iHashIdx    = 0;
    int         iI          = 0;
    int         iKey        = 0;
    sHashNode*  psCurElem   = NULL;
    sHashNode** ppsCurElem  = NULL;
    int*        pResult     = NULL;
    sHashNode*  pHashTable[HASH_TABLE_SIZE] = {NULL};

    *pReturnSize    = 2;
    pResult         = calloc(2,sizeof(int));

    for (iI = 0; iI < iNumsSize; iI++) {
        iKey        = iTarget - pNums[iI];
        iHashIdx    = hashFunc(iKey);
        psCurElem   = pHashTable[iHashIdx];
        while(psCurElem != NULL){
            if(psCurElem -> iKey == iKey){
                pResult[0] = psCurElem -> iIndex;
                pResult[1] = iI;
                return pResult;
            } else{
                psCurElem = psCurElem -> pNext;
            }
        }
        // key not found in the hash table: add the elem
        iKey        = pNums[iI];
        iHashIdx    = hashFunc(iKey);
        ppsCurElem  = &pHashTable[iHashIdx];
        while ((*ppsCurElem) != NULL){
            ppsCurElem = &((*ppsCurElem) -> pNext);
        }
        (*ppsCurElem)           = calloc(1,sizeof(sHashNode));
        (*ppsCurElem) -> iKey   = pNums[iI];
        (*ppsCurElem) -> iIndex = iI;
        (*ppsCurElem) -> pNext  = NULL;
    }

    return NULL;
}

int main(){
    bool    bMatch      = false;
    int     iI          = 0;
    int     iNumsSize   = 4;
    int     iReturnSize = 0;
    int     iTarget     = 0;
    int     pNums[]     = {0,4,3,0};
    int*    pResult     = NULL;
    int     pExpected[] = {0,3};

    pResult = twoSum(pNums,iNumsSize,iTarget,&iReturnSize);
    if(pResult == NULL){
        printf( "twoSum() returned null pointer\n");
        return -1;
    }

    for(iI = 0; iI < RESULT_ARRAY_SIZE; iI++){
        if(pExpected[iI] != pResult[iI]){
            bMatch = false;
            break;
        }
        bMatch = true;
    }

    printf( "The result is [%d, %d]. %s\n",
            pExpected[0],pExpected[1],
            bMatch?"The result matches":"The result doesn't match");

    return 0;
}
