# Notes

## A
Easy peasy.

If array contains equal elements, it will always be perfect.

## B
Quite easy.

The answer is **YES** if and only if array contains duplicate elements.
Otherwise sum of any subarray is a binary representatiton of a number and
since all elements unique, distinct subarrays can't correspond to same numbers.

## C
Very easy.

Just use the checkboard principle.

## D
Interesting.

a ^ a ^ b = b.

If array length is odd, it's always possible (create consequent pairs).

If array length is even, calculate X = xor of all elements in array.
If X = 0 then use the trick for odd array on (n-1) elements.
If X > 0, it's impossible.
