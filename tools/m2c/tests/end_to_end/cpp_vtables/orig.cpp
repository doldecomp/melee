// This disables inlining, similar to the `-inline off` flag
#pragma inline_depth(0)

class Base {
public:
    int member;
    virtual int virtual_method(int x);
    static int static_method(int x) {
        return x * 2;
    }
    int method(int x) {
        return x * 3;
    }
};

class Derived : public Base {
public:
    Derived(int x) {
        member = x;
    }
    int virtual_method(int x) {
        return x * 4;
    }
};

int compute(Derived &d, int x) {
    d.member = x;
    x = d.virtual_method(x);
    x = d.static_method(x);
    x = d.method(x);
    return x;
}

extern "C" {
    int test(int x) {
        Derived d(x);
        return compute(d, x);
    }
}
