int b;
struct Test{
    int a, Test;
    double b;
};
struct a {
    struct Test ttt;
    int Test;
};
int foo(int bar) {
    return -bar;
}
int main() {
    struct a var;
    int mm, n[10];
    foo(var);
    var.ttt.Test = 10.0;
    mm = var.ttt.a + 10;
    n[2] = 11 + mm + n;
    n[mm+2] = var.Test;
    return 0;
}
