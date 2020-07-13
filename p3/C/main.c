/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 * 3. Longest Substring Without Repeating Characters
 * Given a string, find the length of the longest substring without repeating characters.
 *
 * Example 1:
 * Input: "abcabcbb"
 * Output: 3
 * Explanation: The answer is "abc", with the length of 3.
 *
 * Example 2:
 * Input: "bbbbb"
 * Output: 1
 * Explanation: The answer is "b", with the length of 1.
 *
 * Example 3:
 * Input: "pwwkew"
 * Output: 3
 * Explanation: The answer is "wke", with the length of 3.
 * Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
 *
 * Approach:
 * Now that we are working with a string that only consists of ASCII characters, we are certain
 * that there will be only 128 characters.
 * If I store some character's last unseen index into an
 * array, I can quickly reference the index by casting the char into an int. Subtracting the
 * current index by the current character's last unseen index, I can know the length of the current
 * "Substring Without Repeating Characters".
 * By utilizing a max() function, I can know the length of the longest
 * "Substring Without Repeating Characters".
 *
 * Complexity:
 * Time: O(n)
 * Space: O(128) = O(1)
 *
 * Test Results:
 * Success
 * Runtime: 4 ms, faster than 82.24% of C online submissions for Longest Substring Without Repeating Characters.
 * Memory Usage: 5.2 MB, less than 100.00% of C online submissions for Longest Substring Without Repeating Characters.
 *
 */////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <stdio.h>

#define max(a,b) ( ((a) > (b)) ? (a):(b) )

int lengthOfLongestSubstring(char * pcS){
    int iSubStringStartIdx  = 0;
    int iI                  = 0;
    int iResult             = 0;
    int pLastUnseenInx[128] = {0}; // maximum 128 characters in ASCII

    for(iI = 0; pcS[iI] != '\0'; iI++){
        // This acts as a shifting window. The current substring's starting index shifts to the current
        //  character's last unseen index (if it has been seen).
        iSubStringStartIdx              = max(iSubStringStartIdx,pLastUnseenInx[ (int)pcS[iI] ]);

        // Update the current charter's last unseen index: iI is the current index, it has been seen.
        //  Therefore, the next unseen index should be iI + 1
        pLastUnseenInx[(int)pcS[iI]]    = iI + 1;

        // Only update iResult if the current substring's length is larger than any previous ones.
        // The substring's length is calculated by ((current index) - (starting index) + 1), where 1
        // accounts for the character at the current index.
        iResult                         = max(iResult, (iI - iSubStringStartIdx + 1));
    }

    return iResult;
}

int main(){
    bool    bMatch          = false;
    int     iExpected       = 3;
    int     iResult         = 0;
    char    pcInputString[] = "pwwkew";

    iResult = lengthOfLongestSubstring(pcInputString);

    bMatch  = (iExpected == iResult);

    printf( "The result is %d. %s\n",
            iResult,
            bMatch?"The result matches":"The result doesn't match");

    return 0;
}
