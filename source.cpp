#include <iostream>

/*class A {
public:
    void sf() {
        std::cout << "A_sf" << std::endl;
    }
    virtual void vf() {
        std::cout << "A_vf" << std::endl;
    }
    virtual void nov() {
        std::cout << "A_nov" << std::endl;
    }
};*/

struct TI {
    std::string class_name;
};

//A class

struct A {
    void* vptr;
};

struct AVTBL {
    TI* type_info;
    void (*f1)(A*);
    void (*f2)(A*);
};

void A_sf(A* This) {
    std::cout << "A_sf" << std::endl;
}
void A_vf(A* This) {
    std::cout << "A_vf" << std::endl;
}
void A_nov(A* This) {
    std::cout << "A_nov" << std::endl;
}

/*class B : public A {
public:
    virtual void vf() override {
        std::cout << "B_vf" << std::endl;
    }
    virtual void nf() {
        std::cout << "B_nf" << std::endl;
    }
};*/ 

//B class

struct B {
    void* vptr;
};

struct BVTBL {
    TI* type_info;
    void (*f1)(B*);
    void (*f2)(A*);
    void (*f3)(B*);
};

void B_sf(B* This) {
    std::cout << "B_sf" << std::endl;
}

void B_vf(B* This) {
    std::cout << "B_vf" << std::endl;
}
void B_nf(B* This) {
    std::cout << "B_nf" << std::endl;
}

int main() {
    A ob;
    AVTBL avtbl;

    TI ti_a;
    ti_a.class_name = "A";

    avtbl.type_info = &ti_a;
    avtbl.f1 = A_vf;
    avtbl.f2 = A_nov;
    ob.vptr = &avtbl;

//test A
    
    A_sf(&ob); // ob.sf()
    ((AVTBL*)ob.vptr)->f1(&ob); // ob.vf()
    ((AVTBL*)ob.vptr)->f2(&ob); // ob.nov()

    B obj;
    BVTBL bvtbl;

    TI ti_b;
    ti_b.class_name = "B";

    bvtbl.type_info = &ti_b;
    bvtbl.f1 = B_vf;
    bvtbl.f2 = A_nov;
    bvtbl.f3 = B_nf;
    obj.vptr = &bvtbl;

//test B
    
    B_sf(&obj); // obj.sf
    ((BVTBL*)ob.vptr)->f1(&obj); // obj.vf()
    ((BVTBL*)ob.vptr)->f2((A*)&obj); // obj.nov()
    ((BVTBL*)obj.vptr)->f3(&obj); // obj.nf()
                                 
    return 0;
}
