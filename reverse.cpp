

template <int index, int number>
struct get_digit {
    static const int value = get_digit<index - 1, number / 10>::value;
};

template<int number>
struct get_digit<0, number> {
    static const int value = number % 10;
};

template<int n>
struct len {
    static const int value = len<n / 10>::value + 1;
};

template<>
struct len<0> {
    static const int value = 0;
};

template<int n, int a>
struct concat {
    static const int value = n * 10 + a;
};

template<int i, int n, int m>
struct reverse_impl : reverse_impl<i - 1, n,
    concat<m, get_digit<len<n>::value - i - 1, n>::value>::value> { 
};

template<int n, int m>
struct reverse_impl<-1, n, m> {
    static const int value = m;
};

template<int n>
using reverse = reverse_impl<len<n>::value - 1, n, 0>;

static_assert(reverse<9473712>::value == 2173749);
static_assert(reverse<2757632>::value == 2367572);
static_assert(reverse<2792231>::value == 1322972);
static_assert(reverse<8299713>::value == 3179928);
static_assert(reverse<1084693>::value == 3964801);
static_assert(reverse<6515857>::value == 7585156);
static_assert(reverse<9547663>::value == 3667459);
static_assert(reverse<9911315>::value == 5131199);
static_assert(reverse<1391480>::value == 841931);
static_assert(reverse<4914194>::value == 4914194);
static_assert(reverse<8435202>::value == 2025348);
static_assert(reverse<6822116>::value == 6112286);
static_assert(reverse<1837395>::value == 5937381);
static_assert(reverse<146607>::value == 706641);
static_assert(reverse<8357120>::value == 217538);

int main(){}
