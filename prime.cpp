

template<int a, int b>
struct is_divisible {
    static const bool value = (a % b == 0);
};

template<bool, int p, int q>
struct if_for_prime;

template<int p, int q>
struct is_prime_impl {
    static const bool value = if_for_prime<!is_divisible<p, q>::value, p, q>::value; 
};

template<int p, int q>
struct if_for_prime<false, p, q>{
    static const bool value = false;
};

template<int p, int q>
struct if_for_prime<true, p, q>{
    static const bool value = is_prime_impl<p, q-1>::value;
};

template<int p>
struct is_prime_impl<p, 1> {
    static const bool value = true; 
};


template<int p>
using is_prime = is_prime_impl<p, p - 1>;


static_assert(is_prime<17>::value == true);
static_assert(is_prime<2>::value == true);
static_assert(is_prime<3>::value == true);
static_assert(is_prime<4>::value == false);
static_assert(is_prime<5>::value == true);
static_assert(is_prime<6>::value == false);
static_assert(is_prime<7>::value == true);
static_assert(is_prime<8>::value == false);
static_assert(is_prime<9>::value == false);
static_assert(is_prime<10>::value == false);

int main(){}
