# Disjoint Ingridient Subarray Matching(Design and Analysis of Algorithms Course Project)

The objective of this problem was to determine whether all dishes can be prepared using available ingredients by finding disjoint subarrays that match each dish’s required ingredients (regardless of order).
Moreover this was an Algorithms course so had to implement a solution with least time and space complexity. Following is the analysis of time and space complexity of my implemented solution:

## TIME COMPLEXITY ANALYSIS: 
The time complexity of re assign function is O (n^2) because it uses a nested for loop to assign the
values of group and group copy arrays again to themselves.
The time complexity of the file reading function is O (x * y * z)
where,
x = length of the file provided
y = length of one test case
z = length of one element
The time complexity of quicksort is O (m * log m).
Time complexity of array invert function is O (n) because it uses a simple loop to invert nums array.
The time complexity of mymain function is also O (m) because it uses for loop to call the string-
matching function.
Finally, the analysis of time complexity of string-matching function.
The time complexity of my string-matching function is O (n * m).

It is because I have used the naïve-string matching algorithm which has a time complexity of
O (n * m). After this algorithm, my code uses quicksort algorithm with a time complexity of
O (m * log m), after that a single for loop is used to check if the elements found in the nums array
occur together in the nums string or not with the time complexity of O (n * m). if the groups are found,
replacements in the nums array are done with a single for loop with time complexity of O (m) and true
is returned. If groups are not found, array is inverted and the string function is called to check again.
In all this process, the dominant time complexity is of the naïve-string matching algorithm having time
complexity of O (n * m), hence, the string-matching function has a time complexity of O (n * m).
In last, dividing my complete program in 2 parts i.e., one part consists of file handling which has a
time complexity of O (x * y * z), and the second part which comprises of the all-other parts having a
combined time complexity of O (a * b * n * m)

where,
a = number of test cases given
b = number of groups
n = length of nums array
m = length of group array
The dominant part of both these parts is the file handling part hence, my complete code has a time
complexity of O (x * y * z). However, the time complexity of my specific algorithm that I made and
which is of our concern is O (n * m).


## SPACE COMPLEXITY ANALYSIS:
The space complexity of re assign function is O (1) as there is no new space being allocated, the
arrays and their sizes are being passed as references so no new memory is being allocated. Same is
the case with the array invert function. Space complexity of quick sort algorithm is O (log m).
The file reading function allocates memory for groups and nums array; these both are 2D array, and
also allocates space for num cols and group cols which are 1D arrays, hence the overall space
complexity of the function is O (n * m). There are also other temporary variables created by the
function to assist the creation of these arrays, but these variables don’t have a significant effect on
the memory and have a space complexity of O (1).
Space complexity of string-matching function is O (m) because it creates one temporary array of the
size of the pattern (group cols), there are other temporary variables too with the space complexity
of O (1). The mymain function also has the space complexity of O (m) due to the same reasons. The
main function has a time complexity of O (1) because it only creates some temporary variables.
Hence, the overall space complexity of the complete code is O (n * m) because it is the dominant in
all other terms.
