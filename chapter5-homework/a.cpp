void a(){
    bool vis[105];
    int n = 100;
    int y = 1;
    for (int i = 0; i < n; i++){
        if (!vis[i]) continue;
        y += i;
    }
}

void b(){
    bool vis[105];
    int n = 100;
    int y = 1;
    for (int i = 0; i < n; i++){
        if (vis[i]){
            y += i;
        }
    }
}