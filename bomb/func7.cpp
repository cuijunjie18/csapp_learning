int fun7(int cmp, Node* addr){
    if(addr == 0){
      return -1;
    }
    int v = addr->value;
    if (v == cmp){
      return 0;
    }else if( v < cmp){
          return 1 + 2*fun7(cmp, addr->right);
    }else{
      return 2*func7(cmp, addr->left);
    }
  }