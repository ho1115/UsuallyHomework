#include <stdio.h>
#include <stdlib.h>
typedef struct TreeNode node;

struct TreeNode {
  int ap; int bp; int dif; int leftCnt; int rightCnt; int hei;
  long long oddtotal; long long eventotal;
  node* left;
  node* right;
  node* parent;
};

int max (node* a, node* b) {
  if (a && b) {return a->hei > b->hei ? a->hei : b->hei;}
  else if (a) {return a->hei;}
  else if (b) {return b->hei;}
  else {return 0;}
}

void updatePrice(node* a) {  
    a->eventotal = a->leftCnt % 2 == 1 ? a->ap : a->bp;
    a->oddtotal = a->leftCnt % 2 == 1 ? a->bp : a->ap;
    if (a->left) {
        a->eventotal += a->left->eventotal;
        a->oddtotal += a->left->oddtotal;    
    } 
    if (a->right) {
      a->eventotal += a->leftCnt % 2 == 1 ? a->right->eventotal : a->right->oddtotal;
      a->oddtotal += a->leftCnt % 2 == 1 ? a->right->oddtotal : a->right->eventotal;
    }
  return ;
}

node* nodeMax (node* a, node* b) {
  if (a && b) {return a->hei > b->hei ? a : b;}
  else if (a) {return a;}
  else if (b) {return b;}
  else {return NULL;}
}

node* nodeSuc (node* a) {
  node* next;
  if (a->left == NULL && a->right == NULL) {return a;}
  else if (a->left == NULL) {
    next = a->right;
    while (next->left) {next = next->left;}
  }
  else {
    next = a->left;
    while (next->right) {next = next->right;}
  }
  return next;
}

node* leftRotate(node* nod) {
  node* child = nod->right;
  node* temp = child->left;
  if (nod->parent) {
    if (nod->parent->left == nod) {nod->parent->left = child;}
    else {nod->parent->right = child;}
  }
  child->parent = nod->parent;
  nod->parent = child;
  child->left = nod;
  nod->right = temp;
  if (temp) {temp->parent = nod;}
  nod->hei = max(nod->left, nod->right) + 1;
  child->hei = max(child->left, child->right) + 1;
  child->leftCnt += nod->leftCnt + 1;
  updatePrice(nod);
  updatePrice(child);
  return child;
}

node* rightRotate(node* nod) {
  node* child = nod->left;
  node* temp = child->right;
  if (nod->parent) {
    if (nod->parent->left == nod) {nod->parent->left = child;}
    else {nod->parent->right = child;}
  }
  child->parent = nod->parent;
  nod->parent = child;
  child->right = nod;
  nod->left = temp;
  if (temp) {temp->parent = nod;}
  nod->hei = max(nod->left, nod->right) + 1;
  child->hei = max(child->left, child->right) + 1;
  nod->leftCnt -= child->leftCnt + 1;
  updatePrice(nod);
  updatePrice(child);
  return child;
}

node* insert(node* root, node* nod) {
    node* cur = root;
    node* next;
    node* temp;
    node* nextNext = NULL;
    node* ret;
    int lefH = 0, rigH = 0;
    int dir;
     if (cur->dif < nod->dif) {
        next = cur->right;
        dir = 0;
      } else {
        cur->leftCnt += 1;
        next = cur->left;
        dir = 1;
      }
    while (next) {
      cur = next;
      if (cur->dif < nod->dif) {
        next = cur->right;
        dir = 0;
      } else {
        cur->leftCnt += 1;
        next = cur->left;
        dir = 1;
      }
    }
    if (dir == 1) {cur->left = nod;}
    else {cur->right = nod;}
    nod->parent = cur;
    nod->hei = 1;
    next = nod;
    updatePrice(cur);
    while (cur) { 
      cur->hei = max(cur->left, cur->right) + 1;
      lefH = cur->left ? cur->left->hei : 0;
      rigH = cur->right ? cur->right->hei : 0;
      if (lefH - rigH < -1) {
        if (next->left == nextNext) {
          temp = next;
          next = rightRotate(next);
          nextNext = temp;
          cur->hei = max(cur->left, cur->right) + 1;
          updatePrice(cur);
        }
        leftRotate(cur);
        cur = next->parent;        
      } else if (lefH - rigH > 1) {
        if (next->right == nextNext) {
          temp = next;
          next = leftRotate(next);
          nextNext = temp;
          cur->hei = max(cur->left, cur->right) + 1;
          updatePrice(cur);
        }
        rightRotate(cur);
        cur = next->parent;
      } else {
        nextNext = next;
        next = cur;
        cur = cur->parent; 
      }
      if (cur) {
        cur->hei = max(cur->left, cur->right) + 1;
        updatePrice(cur);
      } else {ret = next;}
      
    }
    return ret;
}

node* delete(node* nod) {
    node* suc = nodeSuc(nod);
    node* cur = suc->parent;
    suc->parent = NULL;
    if (cur == NULL) {return NULL;}
    node* next;
    node* nextNext = NULL;
    node* ret;
    int lefH = 0, rigH = 0;
    if (cur->left == suc) {
      cur->left = NULL;
      if (suc->left) {cur->left = suc->left;}    
      if (suc->right) {cur->left = suc->right;}
      cur->leftCnt -= 1;
      next = cur->right;
      if (next) {nextNext = nodeMax(next->left, next->right);}
    } 
    else if (cur->right == suc) {
      cur->right = NULL;
      if (suc->left) {cur->right = suc->left;}    
      if (suc->right) {cur->right = suc->right;}
      next = cur->left;
      if (next) {nextNext = nodeMax(next->left, next->right);}
    }
    updatePrice(cur);
    while (cur) {
      cur->hei = max(cur->left, cur->right) + 1;
      lefH = cur->left ? cur->left->hei : 0;
      rigH = cur->right ? cur->right->hei : 0;
      if (lefH - rigH < -1) {
        if (next->left == nextNext) {          
          next = rightRotate(next);
          cur->hei = max(cur->left, cur->right) + 1;
          updatePrice(cur);
        }
        leftRotate(cur);
        cur = next->parent;
        if (cur && cur->left == next) {cur->leftCnt -= 1;}
      } else if (lefH - rigH > 1) { 
        if (next->right == nextNext) {       
          next = leftRotate(next);
          cur->hei = max(cur->left, cur->right) + 1;
          updatePrice(cur);
        }
        rightRotate(cur);
        cur = next->parent;
        if (cur && cur->left == next) {cur->leftCnt -= 1;}
        
      } else {
        if (next == NULL) {next = nod == suc ? cur : suc;}
        if (cur->parent && cur->parent->left == cur) {cur->parent->leftCnt -= 1;}
        cur = cur->parent;
      }
      if (cur) {
        cur->hei = max(cur->left, cur->right) + 1;
        updatePrice(cur);
        next = nodeMax(cur->left, cur->right);
        nextNext = nodeMax(next->left, next->right);
      } else {ret = next;}
    }
    if (suc != nod) {
      if (nod->parent) {
        if (nod->parent->left == nod) {nod->parent->left = suc;}
        else {nod->parent->right = suc;}
      } 
      suc->parent = nod->parent;
      suc->left = nod->left == suc ? NULL : nod->left;
      suc->right = nod->right == suc ? NULL : nod->right;
      suc->hei = nod->hei;
      suc->leftCnt = nod->leftCnt;
      updatePrice(suc);
      if (nod->left) {nod->left->parent = suc;}
      if (nod->right) {nod->right->parent = suc;}
    }
    while (ret->parent) {ret = ret->parent;}
    nod->parent = NULL;
    nod->left = NULL;
    nod->right = NULL;    
    return ret;//????
}



int main () {
  int N, M, apri, bpri, t, c, d, e, f, temp, factor;
  long long P = 0;
  node** allNodes = (node**) malloc(sizeof(node*) * N);
  node* trueNodes = (node*) malloc(sizeof(node) * N);
  node* root = NULL;
  scanf("%d%d", &N, &M);
  for (int i = 0; i < N; i++) {
    scanf("%d%d", &apri, &bpri);
    if (apri > bpri) {
      temp = apri;
      apri = bpri;
      bpri = temp; 
    }
    allNodes[i] = &trueNodes[i];
    allNodes[i]->ap = apri;
    allNodes[i]->bp = bpri;
    allNodes[i]->hei = 1;
    allNodes[i]->leftCnt = 0;
    allNodes[i]->dif = bpri - apri;
    allNodes[i]->oddtotal = apri;
    allNodes[i]->eventotal = bpri;
    if (root) {root = insert(root, allNodes[i]);}
    else {root = allNodes[i];}
  }
  factor = N % 2;
  if (factor == 1) {printf("%lld\n", root->oddtotal);} 
  else {printf("%lld\n", root->eventotal);}
  for (int i = 0; i < M-1; i++) {
    scanf("%d%d%d%d%d", &t, &c, &d, &e, &f);    
    apri = factor == 1 ? (c*root->oddtotal % 1000000007 + d) % 1000000007 : (c*root->eventotal % 1000000007 + d) % 1000000007;
    bpri = factor == 1 ? (e*root->oddtotal % 1000000007 + f) % 1000000007 : (e*root->eventotal % 1000000007 + f) % 1000000007;
    root = delete(allNodes[t-1]); 
    if (apri > bpri) {
      temp = apri;
      apri = bpri;
      bpri = temp; 
    } 
    allNodes[t-1]->ap = apri;
    allNodes[t-1]->bp = bpri;
    allNodes[t-1]->hei = 1;
    allNodes[t-1]->leftCnt = 0;
    allNodes[t-1]->dif = bpri - apri;
    allNodes[t-1]->oddtotal = apri;
    allNodes[t-1]->eventotal = bpri;
    if (root) {root = insert(root, allNodes[t-1]);}
    else {root = allNodes[t-1];}
    if (factor == 1) {printf("%lld\n", root->oddtotal);} 
    else {printf("%lld\n", root->eventotal);}
  }
  return 0;
}
