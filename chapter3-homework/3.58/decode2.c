long decode2(long x,long y,long z){
    return (x * (y - z)) ^ ((y - z) << 63 >> 63);
}