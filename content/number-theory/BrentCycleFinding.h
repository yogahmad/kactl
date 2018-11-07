/**
 * Author: Lukas Polacek
 * Date: 2010-01-26
 * License: CC0
 * Source: TopCoder tutorial
 * Description: Cycle finding on modulo.
 * Lambda is the length of the loop to be found, and miu is the index of the first element.
 * Time: 15 times the complexity of $a^b \mod c$.
 */

int f(int x) { 
  // state transition from x 
  return // something; 
} 

pair<int,int> brent(int x0) { 
  int lambda = 0, mu = 0, power; 
	int tortoise = x0; 
	int hare = f(x0);
	// finding succesive power of two 
	// find lambda 
	lambda = power = 1; 
	while (tortoise != hare){ 
		if (power == lambda) { 
			power <<= 1; 
			tortoise = hare; 
			lambda = 0; 
		} 
		hare = f(hare); 
		++lambda; 
	} 
	// find mu 
	tortoise = hare = x0; 
	for (int i = 0; i < lambda; ++i) 
		hare = f(hare); 
	while (tortoise != hare) 
	{ 
		tortoise = f(tortoise); 
		hare = f(hare); 
		++mu; 
	} 
	return make_pair(lambda, mu); 
}
