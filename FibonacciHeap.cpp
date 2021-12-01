#include <bits/stdc++.h>

using namespace std;

struct node
{
    int key;
    int degree;
    node *left;
    node *right;
    node *child;
    node *parent;
    node(int val)
    {
        key = val;
        left = NULL;
        right = NULL;
        child = NULL;
        parent = NULL;
        degree = 0;
    }
};
int LOG;
node *H;
int nodeCnt;
int root_size;
void push(int x)
{
    root_size++;
    node *newNode = new node(x);
    if (!nodeCnt)
    {
        newNode->right = newNode;
        newNode->left = newNode;
        H = newNode;
        nodeCnt++;
        return;
    }
    nodeCnt++;
    LOG = log(nodeCnt) / log(2) + 1;
    newNode->right = H->right;
    newNode->left = H;
    H->right->left = newNode;
    H->right = newNode;
    if (H->key > x)
    {
        H = newNode;
    }
    return;
}

node *G[100];
void consolidate()
{
    for (int i = 0; i < LOG; i++)
    {
        G[i] = NULL;
    }
    node *ini = H;
    node *it = H;
    for (int i = 0; i < root_size; i++)
    {
        int degree = it->degree;
        node *act = it;
        it = it->right;
        node *finalConnect = act;
        while (G[degree] != NULL)
        {
            node *equals = G[degree];
            G[degree] = NULL;
            if (equals->key < act->key)
            {
                finalConnect = equals;
                equals->degree++;
                act->right->left = act->left;
                act->left->right = act->right;
                act->parent = equals;
                if (equals->child == NULL)
                {
                    act->left = act;
                    act->right = act;
                    equals->child = act;
                }
                else
                {
                    node *son = equals->child;
                    act->right = son->right;
                    act->left = son;
                    son->right->left = act;
                    son->right = act;
                }
                act = equals;
            }
            else
            {
                finalConnect = act;
                act->degree++;
                equals->right->left = equals->left;
                equals->left->right = equals->right;
                equals->parent = act;
                if (act->child == NULL)
                {
                    equals->right = equals;
                    equals->left = equals;
                    act->child = equals;
                }
                else
                {
                    node *son = act->child;
                    equals->right = son->right;
                    equals->left = son;
                    son->right->left = equals;
                    son->right = equals;
                }
            }
            degree++;
        }
        G[degree] = finalConnect;
    }
    node *create;
    node *previous;
    H = NULL;
    root_size = 0;
    for (int i = 0; i < LOG; i++)
    {
        if (G[i] != NULL)
        {
            root_size++;
            if (H == NULL)
            {
                H = G[i];
                create = H;
                ini = H;
                create->right = create;
                create->left = create;
                create->parent = NULL;
                previous = create;
            }
            else
            {
                create = G[i];
                previous->right = create;
                create->left = previous;
                create->right = ini;
                ini->left = create;
                if (G[i]->key < H->key)
                {
                    H = G[i];
                }
                previous = create;
            }
            G[i]->degree = i;
        }
    }
}
int topPop()
{
    root_size--;
    nodeCnt--;
    //cout<<H->degree<<"\n";
    int ret = H->key;
    node *it = H->child;
    while (H->degree > 0)
    {
        root_size++;
        node *next = it->right;
        //cout<<"Subi "<<it->key<<"\n";
        it->right->left = it->left;
        it->left->right = it->right;
        it->parent = NULL;
        it->right = H->right;
        it->left = H;
        H->right->left = it;
        H->right = it;
        it = next;
        H->degree--;
    }
    if (!nodeCnt)
    {
        free(H);
        H = NULL;
        return ret;
    }
    H->left->right = H->right;
    H->right->left = H->left;
    it = H;
    H = H->right;
    free(it);
    node *rig = H;
    node *newNode = H;
    //cout<<"Hola";
    /*do{
        cout<<rig->key<<" ";
        rig=rig->right;
    }while(rig!=newNode);
    cout<<"\n";*/
    consolidate();
    return ret;
}

int main()
{
}
