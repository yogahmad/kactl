/**
 * Author: Simon Lindholm
 * Date: 2016-08-23
 * License: CC0
 * Source: me
 * Description: Build an implication graph with 2 vertices for each variable (the variable itself and its inverse). 
 * For each clause x V y, add edges (x', y) and (y', x). 
 * The formula is satisfiable iff x and x' are in different SCCs, for all x. 
 * To find a satisfiable assignment, consider the graph's SCCs in topological order from sinks to sources (Kosaraju's last step). 
 * Assign true to all variables of the current SCC (if it hasn't been previously assigned false), and false to all inverses.
 * There is a code above : 2sat.h
 * Status: tested
 */

#include <2sat.h>
