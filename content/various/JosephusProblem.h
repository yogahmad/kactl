/**
 * Author: Simon Lindholm
 * Date: 2016-07-23
 * License: CC0
 * Source: me
 * Description: There are n person in a table waiting to be executed. 
 * Person 1 hold a knife. Each step whoever has the knife, kill the person next to him.
 * Who's alive at the end?
 * Status: tested
 */

int x = 0;
for (int i = 2; i <= n; ++i)
	x = (x + i) % i;
