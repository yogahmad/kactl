/**
 * Author: Simon Lindholm
 * Date: 2015-02-18
 * License: CC0
 * Source: marian's (TC) code
 * Description: Aho-Corasick tree is used for dictionary matching.
 * Initialize the tree like the example at main below.
 * Time: Function create is $O(26N)$ where $N$ is the sum of length of patterns.
 * Becareful if the pattern allow duplicate. If not, the worst case is $N \sqrt N$.
 * Status: lightly tested
 */
#pragma once

#include<bits/stdc++.h> 
const int NALPHABET = 26;
struct Node {
  Node** children, go;
  bool leaf;
  char charToParent;
  Node* parent, suffLink, dictSuffLink;
  int count, value;
 
  Node(){
    children = new Node*[NALPHABET];
    go = new Node*[NALPHABET];
    for(int i = 0; i < NALPHABET;++i){
      children[i] = go[i] = NULL;
    }
    parent = suffLink = dictSuffLink = NULL;
    leaf = false;
    count = 0;
  }
};
 
Node* createRoot() {
  Node* node = new Node();
  node->suffLink = node;
  return node;
}
 
void addString(Node* node, const string& s, int value =-1) {
  for(int i = 0; i < s.length(); ++i){
    int c = s[i] - 'a';
    if(node->children[c] == NULL){
      Node* n = new Node();
      n->parent = node;
      n->charToParent = s[i];
      node->children[c] = n;
    }
    node = node->children[c];
  }
  node->leaf = true;
  node->count++;
  node->value = value;
}
 
Node* suffLink(Node* node);
Node* dictSuffLink(Node* node);
Node* go(Node* node, char ch);
int calc(Node* node);
 
Node* suffLink(Node* node) {
  if (node->suffLink == NULL){
    if (node->parent->parent == NULL){
      node->suffLink = node->parent;
    } else {
      node->suffLink = go(suffLink(node->parent),node->charToParent);
    }
  }
  return node->suffLink;
}
 
Node* dictSuffLink(Node* node) {
  if(node->dictSuffLink == NULL){
    Node* n = suffLink(node);
    if (node == n){
      node->dictSuffLink = node;
    } else {
      while (!n->leaf && n->parent != NULL){
        n = dictSuffLink(n);
      }
      node->dictSuffLink = n;
    }
  }
  return node->dictSuffLink;
}
 
Node* go(Node* node, char ch) {
  int c = ch -'a';
  if (node->go[c] == NULL){
    if (node->children[c] != NULL) {
      node->go[c]= node->children[c];
    } else {
      node->go[c]= node->parent == NULL? node : go(suffLink(node), ch);
    }
  }
  return node->go[c];
}

int calc(Node* node) {
  if (node->parent == NULL) {
    return 0;
  } else {
    return node->count + calc(dictSuffLink(node));
  }
}
 
int main() {
  Node* root = createRoot();
  addString(root,"a",0);
  addString(root,"aa",1);
  addString(root,"abc",2);
 
  string s("abcaadc");
  Node* node = root;
  for (int i = 0; i < s.length(); ++i){
    node = go(node, s[i]);
    Node* temp = node;
    while (temp != root) {
      if (temp->leaf) {
        printf("string (%d) occurs at position %d\n", temp->value, i);
      }
      temp = dictSuffLink(temp);
    }
  }
  return 0;
}
