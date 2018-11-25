/**
 * Author: Johan Sannemo
 * License: CC0
 * Description: pi[x] computes the length of the longest prefix of t that ends at x (abacaba -> 0010123).
 * Can be used to find all occurrences of a string.
 * Time: O(n)
 * Status: Tested on Kattis, stringmatching
 */
#pragma once

int kmp(const string &T, const string &P) {
  if (P.empty()) return 0;
  vector<int> pi(P.size(), 0);
  for (int i = 1, k = 0; i < P.size(); ++i) {
    while (k && P[k] != P[i]) k = pi[k - 1];
    if (P[k] == P[i]) ++k;
    pi[i] = k;
  }
  for (int i = 0, k = 0; i < T.size(); ++i) {
    while (k && P[k] != T[i]) k = pi[k - 1];
    if (P[k] == T[i]) ++k;
    if (k == P.size()) return i - k + 1;
  }
  return -1;
}
