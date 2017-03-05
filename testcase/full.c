struct TestType {
    int a, b;
    double c, d[10];
};
int main(void) {
    int m = 3, n = m+3;
    int k = foo(m, n, 2);
    struct TestType s[10];
    int l = foo(foo(m,n,k+(-2)), -2, s[1].d.foo.bar);
    k = m+5;
    m = m/-4;
    if(m>n) {
        return !m+4;
    }else while(k>l)
        k = k-1;
    return 0;
}

int foo(int  bar,    int bar, int bar3) {
    return bar/bar2*bar3;
}
