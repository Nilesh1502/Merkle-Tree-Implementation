#include <bits/stdc++.h>
#include "sha256.h"
using namespace std;

class TreeNode
{
public:
    string hashval;
    TreeNode *left;
    TreeNode *right;

    TreeNode(string hashval)
    {
        this->hashval = hashval;
        left = nullptr;
        right = nullptr;
    }

    string gethashval()
    {
        return hashval;
    }
};

void TraverseTree(TreeNode *root);

int main()
{
    int i, j, n = 5;
    SHA256 sha256;
    vector<string> v;
    string s;
    string input;
    cout << "No. of strings" << endl;
    cin >> n;
    if (n <= 0)
    {
        cout << "Type positive number only" << endl;
        exit(0);
    }
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

    // Generation of hashes
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

    while (flag && v.size() != 1)
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

    cout << "Generated Hashes:" << endl;
    for (i = 0; i < hashes.size(); i++)
    {
        for (j = 0; j < hashes[i].size(); j++)
        {
            cout << hashes[i][j] << " ";
        }
        cout << endl;
    }

    // Creating the Merkle Tree
    TreeNode *Merkle_Root;
    queue<TreeNode *> q;
    for (i = 0; i < hashes.size(); i++)
    {
        for (j = 0; j < hashes[i].size(); j++)
        {
            TreeNode *ptr = new TreeNode(hashes[i][j]);
            if (hashes[i].size() == 1)
            {
                Merkle_Root = ptr;
            }
            if (i == 0)
            {
                q.push(ptr);
            }
            else
            {
                TreeNode *p = q.front();
                ptr->left = p;
                q.pop();
                p = q.front();
                if (p == nullptr)
                {
                    TreeNode *ptr1 = new TreeNode(ptr->left->hashval);
                    ptr->right = ptr1;
                }
                else
                {
                    ptr->right = p;
                }
                q.pop();
                q.push(ptr);
            }
        }
        if (q.front() == nullptr)
        {
            q.pop();
        }
        q.push(nullptr);
    }

    // Printing the final root hash
    cout << "\n#Final Root Hash" << endl;
    cout << Merkle_Root->hashval << endl;
    cout << "\n";

    // Printing the tree
    cout << "Tree Pre-Order Traversal" << endl;
    TraverseTree(Merkle_Root);

    return 0;
}

void TraverseTree(TreeNode *root)
{
    if (!root)
    {
        return;
    }
    else
    {
        cout << root->hashval << endl;
        TraverseTree(root->left);
        TraverseTree(root->right);
    }
}
