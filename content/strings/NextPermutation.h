/**
 * Author: Yusuf Sholeh
 * Source: https://github.com/stjepang/snippets/blob/master/min_rotation.cpp
 * Description: Finds the lexicographically smallest next permutation.
 * Intuitively, find largest index i such that a[i] < a[i+1]
 * then, find largest index j such that j >= i and a[j] > a[i]
 * Swap(a[j], a[i-1]). Then reverse suffix start at i.
 * Time: O(N)
 * Status: Fuzz-tested
 * Usage:
 *  return the array x and the permutation
 */
bool nextPermutation(int x[], int n) {
  int k = -1;
  for (int i = n - 2; k == -1 && i >= 0; --i)
    if (x[i] < x[i + 1]) k = i;
  if (k == -1) return false;
  int l = -1;
  for (int i = n - 1; l == -1 && i > k; --i)
    if (x[k] < x[i]) l = i;
  swap(x[k], x[l]);
  reverse(x + k + 1, x + n);
  return true;
}
