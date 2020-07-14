/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 * 4. Median of Two Sorted Arrays
 * There are two sorted arrays nums1 and nums2 of size m and n respectively.
 * Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
 * You may assume nums1 and nums2 cannot be both empty.
 *
 * Example 1:
 *
 * nums1 = [1, 3]
 * nums2 = [2]
 *
 * The median is 2.0
 *
 * Example 2:
 *
 * nums1 = [1, 2]
 * nums2 = [3, 4]
 * The median is (2 + 3)/2 = 2.5
 *
 * Approach:
 * A median in a group of numbers partitions the numbers into 2 groups, where the left partition is always smaller than
 * the median, and the right partition is always greater than the median. Say we have 2 sorted arrays X and Y, we
 * partition the arrays like this:
 *
 * left parts | right parts
 * X:  a b c [d] e f g
 * Y:  h i j [k] l m n
 *
 * where [d] is the partition pivot of array X, and [k] is the partition pivot of array Y.
 *
 * Since both arrays are sorted, we can be certain that c<=e and j<=l.
 * We only need to move the pivots so that c<=l and j<=e (the numbers in the left parts are always smaller than the
 * numbers in the right parts).
 *
 * Complexity:
 * Time: O(log(min(m,n))), where m is the size of nums1 and n is the size of nums2
 * Space: O(1)
 *
 * Test Results:
 * Success
 * Runtime: 12 ms, faster than 84.59% of C online submissions for Median of Two Sorted Arrays.
 * Memory Usage: 6 MB, less than 89.55% of C online submissions for Median of Two Sorted Arrays.
 *
 */////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <stdio.h>
#include <limits.h>

#define abs(x)      ( ((x) <  0 ) ?-(x) : (x) )
#define max(a,b)    ( ((a) > (b)) ? (a) : (b) )
#define min(a,b)    ( ((a) < (b)) ? (a) : (b) )

double findMedianSortedArrays(int* pNums1, int iNums1Size, int* pNums2, int iNums2Size){
    // In each round, we want to partition the array with smaller size
    if(iNums1Size>iNums2Size){
        return findMedianSortedArrays(pNums2, iNums2Size, pNums1, iNums1Size);
    }

    // left boundary. Everything on the left of this boundary will be smaller than the median
    int iHigh       = iNums1Size;
    // right boundary. Everything on the right of this boundary will be greater than the median
    int iLow        = 0;
    int iMaxLeftX   = 0;
    int iMaxLeftY   = 0;
    int iMinRightX  = 0;
    int iMinRightY  = 0;
    int iPartitionX = 0; // partitioning pivot in array X
    int iPartitionY = 0; // partitioning pivot in array Y

    while (iLow <= iHigh){
        // we always start partitioning the array by setting the pivot in the middle of te boundaries
        iPartitionX = (iLow + iHigh)/2;
        // to ensure we have equal counts of numbers on both left and right partitions
        iPartitionY = (iNums1Size + iNums2Size + 1)/2 - iPartitionX;

        // assume negative infinity for X[-1] and Y[-1]
        iMaxLeftX   = (iPartitionX == 0)            ? INT_MIN : pNums1[iPartitionX - 1];
        iMaxLeftY   = (iPartitionY == 0)            ? INT_MIN : pNums2[iPartitionY - 1];

        // assume positive infinity for X[m] and Y[n]
        iMinRightX  = (iPartitionX == iNums1Size)   ? INT_MAX : pNums1[iPartitionX];
        iMinRightY  = (iPartitionY == iNums2Size)   ? INT_MAX : pNums2[iPartitionY];

        if (iMaxLeftX > iMinRightY){
            // we have too many numbers in the right partitions. shift the right boundary to left by 1
            iHigh = iPartitionX - 1;
        } else if (iMaxLeftY > iMinRightX){
            // we have too many numbers in the left partitions. shift the left boundary to right by 1
            iLow = iPartitionX + 1;
        } else{
            // iMaxLeftX <= iMinRightY && iMaxLeftY <= iMinRightX
            // now everything in the left partitions are smaller than the ones in the right partitions
            if((iNums1Size + iNums2Size) % 2 == 0){
                // the total count is an even number. calculate the average of the middle 2 numbers
                return (double)(max(iMaxLeftX,iMaxLeftY) + min(iMinRightX,iMinRightY))/2;
            } else{
                // return the number closer to the pivots, from the left partitions
                return max(iMaxLeftX,iMaxLeftY);
            }
        }
    }
    return -1;
}

int main(){
    bool    bMatch          = false;
    int     iNums1Size   = 2;
    int     iNums2Size   = 2;
    int     pNums1[]     = {1,2};
    int     pNums2[]     = {3,4};
    double     dExpected       = 2.5;
    double     dResult         = 0;

    dResult = findMedianSortedArrays(pNums1,iNums1Size,pNums2,iNums2Size);

    // check if the floating-point results match
    bMatch  = (abs(dExpected - dResult) < 0.001);

    printf( "The result is %.1lf. %s\n",
            dResult,
            bMatch?"The result matches":"The result doesn't match");

    return 0;
}
