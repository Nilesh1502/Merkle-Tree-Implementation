#include <bits/stdc++.h>
#include "sha256.h"
using namespace std;

class TreeNode
{
    string Hashval;
    TreeNode *left;
    TreeNode *right;

    TreeNode(string Hashval)
    {
        this->Hashval = Hashval;
        left = nullptr;
        right = nullptr;
    }
};

int main()
{
    int i, j, n = 5;
    SHA256 sha256;
    vector<string> v;
    string s;
    string input;
    cout << "No. of strings" << endl;
    cin >> n;

    cout << "Enter strings..." << endl;
    for (i = 0; i < n; i++)
    {
        cin >> input;
        v.push_back(input);
    }
    // v.push_back("abc");
    // v.push_back("ijk");
    // v.push_back("xyz");
    // v.push_back("lmn");
    // v.push_back("uvw");

    vector<vector<string>> hashes;
    vector<string> temp;
    hashes.push_back(temp);
    for (int i = 0; i < v.size(); i++)
    {
        hashes[0].push_back(sha256(v[i]));
    }
    int prev_nodes = v.size();
    int flag = 1;
    int level = 1;

    while (flag)
    {
        int count = 0;
        temp.clear();
        hashes.push_back(temp);
        for (i = 0; i < prev_nodes; i = i + 2)
        {
            string s = hashes[level - 1][i];
            if (i + 1 == prev_nodes)
            {
                s += s;
            }
            else
            {
                s += hashes[level - 1][i + 1];
            }
            int t = i / 2;
            SHA256 hashfunc;
            hashes[level].push_back(hashfunc(s));
            count++;
        }
        prev_nodes = count;
        level++;
        if (prev_nodes == 1)
        {
            flag = 0;
        }
    }

    for (i = 0; i < hashes.size(); i++)
    {
        for (j = 0; j < hashes[i].size(); j++)
        {
            cout << hashes[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
