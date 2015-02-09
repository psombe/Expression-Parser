//
//  main.cpp
//  Expression Parser
//
//  Created by Srinivas Eswar on 08/02/15.
//  Copyright (c) 2015 Srinivas Eswar. All rights reserved.
//
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

class Node
{
public:
    char op;
    string var;
    int data;
    bool isdata;
    Node* left;
    Node* right;
    Node(int d, char o, bool i, string x)
    {
        op = o;
        data = d;
        isdata = i;
        var = x;
        left = NULL;
        right = NULL;
    }
};

map<string,int> varmap;

int evaluate(Node* root)
{
    if(root == NULL) return 0;
    else if(root->left == NULL && root->right == NULL)
    {
        if(root->isdata)
        {
            // Data node
            return root->data;
        }
        else
        {
            // Var node
            return varmap[root->var];
        }
    }
    else
    {
        // Op node
        if(root->op == '+')
        {
            return evaluate(root->left) + evaluate(root->right);
        }
        if(root->op == '*')
        {
            return evaluate(root->left) * evaluate(root->right);
        }
    }
    
    return 0;
}

Node* create_expr_tree(vector<string> tokens)
{
    stack<Node*> parse;
    vector<string>::iterator i;
    
    for(i = tokens.end()-1; i >= tokens.begin(); i--)
    {
        if(*i == "add")
        {
            if(parse.size() < 2)
            {
                cout << "Erroroneous expression" << endl;
                return NULL;
            }
            else
            {
                Node* l = parse.top();
                parse.pop();
                
                Node* r = parse.top();
                parse.pop();
                
                Node* n = new Node(-1,'+',0,"");
                n->left = l;
                n->right = r;
                parse.push(n);
            }
            
        }
        else if(*i == "mul")
        {
            if(parse.size() < 2)
            {
                cout << "Erroroneous expression" << endl;
                return NULL;
            }
            else
            {
                Node* l = parse.top();
                parse.pop();
                
                Node* r = parse.top();
                parse.pop();
                
                Node* n = new Node(-1,'*',0,"");
                n->left = l;
                n->right = r;
                parse.push(n);
            }
            
        }
        else if(varmap.count(*i) == 1)
        {
            Node* n = new Node(-1,'X',0,*i);
            parse.push(n);
        }
        else
        {
            int data = stoi(*i);
            Node* n = new Node(data,'.',1,"");
            parse.push(n);
        }
    }
    
    return parse.top();
}

vector<string> tokenizer(string line)
{
    vector<string> tokens;
    string str;
    istringstream ss(line);
    char braces[] = "()";
    
    while(ss >> str)
    {
        for(int i=0; i < strlen(braces); i++)
        {
            str.erase(remove(str.begin(),str.end(),braces[i]),str.end());
        }
        tokens.push_back(str);
    }
    return tokens;
}

vector<string> let_tokenizer(string line)
{
    vector<string> tokens;

    // Coding this function in C style
    bool flag = 1;
    int i;
    
    // Locate the beginning of let assignments
    for( i = 4; i < line.length() && flag; i++)
    {
        if(line[i] == '(') flag = 0;
    }
    
    int balance = 0;
    int j = i;
    
    while(balance >= 0)
    {
        if(balance == 0 && j != i)
        {
            string substring = line.substr(j,i-j);
            
            vector<string> expr = tokenizer(substring);
            vector<string> expr2;
            
            for(int l=1; l < expr.size(); l++)
            {
                expr2.push_back(expr[l]);
            }
            varmap[*expr.begin()] = evaluate(create_expr_tree(expr2));
            
            
            j=i+1;
        }
        if(line[i] == '(') balance++;
        if(line[i] == ')') balance--;
        
        i++;
    }
    
    tokens = tokenizer(line.substr(i,line.length()-i));
    
    return tokens;
}

void eval_line(string line)
{
    vector<string> tokens;
    
    if(line.substr(0,4) == "(let") tokens = let_tokenizer(line);
    else tokens = tokenizer(line);
    
    Node* parsetree = NULL;
    parsetree = create_expr_tree(tokens);
    
    cout << evaluate(parsetree) << endl;
}

int main(int argc, const char * argv[])
{
    string line = "(let ((X 5) (Z 3) (Y (add X Z))) (add Y (add (mul (add X (add 2 10)) (add 1 1)) Z)))";
    
    eval_line(line);
    
    return 0;
}
