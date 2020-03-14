
template<int n>
struct fibb {
    static const int value = fibb<n - 1>::value + fibb<n - 2>::value; 
};

template<>
struct fibb<0> {
    static const int value = 1;
};

template<>
struct fibb<1> {
    static const int value = 1;
};


static_assert(fibb<0>::value == 1);
static_assert(fibb<1>::value == 1);
static_assert(fibb<2>::value == 2);
static_assert(fibb<3>::value == 3);
static_assert(fibb<4>::value == 5);
static_assert(fibb<5>::value == 8);
static_assert(fibb<6>::value == 13);
static_assert(fibb<7>::value == 21);
static_assert(fibb<8>::value == 34);
static_assert(fibb<9>::value == 55);

int main(){}
