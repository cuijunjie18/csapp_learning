struct ELE{
    long v;
    struct ELE *p;
};

long fun(struct ELE *ptr){
    long result = 0;
    while (ptr){
        result += ptr->v;
        ptr = ptr->p;
    }
    return result;
}