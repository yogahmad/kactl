/**
 * Author: Ignore this
 * Date: 2004-02-08
 * Description: Invert matrix $A$. Returns rank; result is stored in $A$ unless singular (rank < n).
 * Can easily be extended to prime moduli; for prime powers, repeatedly
 * set $A^{-1} = A^{-1} (2I - AA^{-1})\  (\text{mod }p^k)$ where $A^{-1}$ starts as
 * the inverse of A mod p, and k is doubled in each step.
 * Time: O(n^3)
 * Status: Slightly tested
 */
#pragma once

void printCircuit(vector<vector<int>> adj)
{
    unordered_map<int, int> edge_count;

    for (int i = 0; i < adj.size(); i++)
    {
        edge_count[i] = adj[i].size();
    }
    stack<int> curr_path;
    vector<int> circuit;

    curr_path.push(0);
    int curr_v = 0; // Start vertex

    while (!curr_path.empty())
    {
        if (edge_count[curr_v])
        {
            curr_path.push(curr_v);
            int next_v = adj[curr_v].back();
            edge_count[curr_v]--;
            adj[curr_v].pop_back();
            curr_v = next_v;
        }
        else
        {
            circuit.push_back(curr_v);
            curr_v = curr_path.top();
            curr_path.pop();
        }
    }
    for (int i = circuit.size() - 1; i >= 0; i--)
    {
        cout << circuit[i];
        if (i)
            cout << " -> ";
    }
}
