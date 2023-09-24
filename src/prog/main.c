#include "../betterC/betterC.h"

#define nb_display 50
//typedef u64 rng_val;
#define get_bit(v, idx) ((v >> idx) & 1)

// keep 4 digits
int rng_middle_square_4(int v)
{
    v = v*v;
    v = (v / 100) % 10000;
    return v;
}

void print_coin_distribution(char* title, int nb_pile, int nb_face)
{
    printf_title(title);
    int total = nb_pile+nb_face;
    printf("%i (%s%7.4f%s %%) pile, %i (%s%7.4f%s %%) face, total = %i\n\n", nb_pile, COLOR_FOREGROUND_GREEN, nb_pile/(float)total*100, COLOR_RESET, nb_face, COLOR_FOREGROUND_GREEN, nb_face/(float)total*100, COLOR_RESET, total);
}

int sum_array(int* tab, int tab_size)
{
    int sum = 0;
    repeat(i, tab_size)
    {
        sum += tab[i];
    }
    return sum;
}

void print_distribution(char* title, int* tab, int tab_size)
{
    printf_title(title);

    int sum = sum_array(tab, tab_size);
    repeat(i, tab_size)
    {
        printf("[%i] : %i (%s%7.4f %%%s)\n", (int)i, tab[i], COLOR_FOREGROUND_GREEN, tab[i]/(float)sum*100, COLOR_RESET);
    }
    printf("total = %i\n\n", sum);
}

void distribution_std(int nb_lance, int mod)
{
    int* a = make_array(int, mod);
    repeat(i, mod){ a[i] = 0; }

    repeat(i, nb_lance)
    {
        a[rand()%mod]++;
    }

    print_distribution("rand", a, mod);
    free(a);
}

void coin_distribution_std(int nb_lance)
{
    int nb_pile = 0;
    repeat(i, nb_lance)
    {
        if(rand()%2){ nb_pile++; }
    }
    print_coin_distribution("rand", nb_pile, nb_lance-nb_pile);
}

void print_rng_middle_square_4(int seed, int nb_loop)
{
    printf_title("rng_middle_square");
    printf("%s", COLOR_FOREGROUND_YELLOW);

    int val = seed;
    repeat(i, nb_loop)
    {
        printf("%08i ", val);
        val = rng_middle_square_4(val);
    }
    printf("%s\n\n", COLOR_RESET);
}

void partie_a()
{
    print_rng_middle_square_4(1234, nb_display);
    print_rng_middle_square_4(4100, nb_display);
    print_rng_middle_square_4(1234, nb_display);
    print_rng_middle_square_4(3141, nb_display);
}

void partie_b()
{
    coin_distribution_std(10);
    coin_distribution_std(100);
    coin_distribution_std(1000);
    coin_distribution_std(10000000);

    distribution_std(10, 6);
    distribution_std(100, 6);
    distribution_std(1000, 6);
    distribution_std(1000000, 6);
}

typedef struct
{
    int seed;
    int val;
    int coef;
    int offset;
    int mod;
}rng_lcg;

rng_lcg rng_lcg_make(int seed, int coef, int offset, int mod)
{
    rng_lcg r;
    r.seed = seed;
    r.val = seed;
    r.coef = coef;
    r.offset = offset;
    r.mod = mod;
    return r;
}

rng_lcg rng_lcg_next(rng_lcg r)
{
    r.val = (r.coef * r.val + r.offset) % r.mod;
    return r;
}

void rng_lcg_printf(rng_lcg r)
{
    printf("rng_lcg with x0 = %i : (%i*x + %i) %% %i\n", r.seed, r.coef, r.offset, r.mod);
}

void print_rng_lcg(rng_lcg r, int nb_lance)
{
    printf_title("rng_lcg");
    rng_lcg_printf(r);

    repeat(i, nb_lance)
    {
        printf("%4i (%s%7.4f%s )\n", r.val, COLOR_FOREGROUND_GREEN, r.val/(float)r.mod, COLOR_RESET);
        r = rng_lcg_next(r);
    }
    printf("%s\n\n", COLOR_RESET);
}

void partie_c()
{
    print_rng_lcg(rng_lcg_make(5, 5, 1, 16) , nb_display);
    print_rng_lcg(rng_lcg_make(125, 25, 16, 256) , nb_display);
}

// – Shift register generators
typedef struct
{
    u32 val;
    u32 seed;
    // 1 : take the input
    u32 polynom;
    u32 size;
}rgn_srg;

rgn_srg rgn_srg_make(u32 seed, u32 polynom, u32 size)
{
    rgn_srg r;
    r.seed = seed;
    r.val = seed;
    r.polynom = polynom;
    r.size = size;
    return r;
}

rgn_srg rgn_srg_next(rgn_srg r)
{
    unsigned int xor_val = 0;
    repeat(i, r.size)
    {
        unsigned int bit = (r.polynom >> i) & 1;
        if(bit){ xor_val = (xor_val ^ (r.val >> i)) & 1; }
    }
    r.val = r.val >> 1;

    r.val = xor_val ? (r.val | (1 << (r.size-1))) : (r.val & (~(1 << (r.size-1))));
    return r;
}

void print_u32_bin(u32 v, int nbBit)
{
    printf("0b");
    repeat_reverse(i, nbBit)
    {
        printf("%i", (v >> i)&1);
    }
}

void rgn_srg_printf(rgn_srg r)
{
    printf("rgn_srg of size %u, polynom ", r.size);
    print_u32_bin(r.polynom, r.size);
    printf(", seed %u\n", r.seed);
}


void print_rgn_srg(rgn_srg r, int nb_lance)
{
    printf_title("shift register generators");
    rgn_srg_printf(r);

    repeat(i, nb_lance)
    {
        printf("%8u ", r.val);
        printf("%s", COLOR_FOREGROUND_GREEN);
        print_u32_bin(r.val, r.size);
        printf("%s\n", COLOR_RESET);
        r = rgn_srg_next(r);
    }
    printf("%s\n\n", COLOR_RESET);
}

void partie_d()
{
    /*
    https://www.gnu.org/software/gsl/
    https://www.gnu.org/software/gsl/doc/html/rng.html

    http://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/SFMT/index.html#SFMT

    https://www.example-code.com/c/prng_generate_random.asp
    */
}

void partie_e()
{
    print_rgn_srg(rgn_srg_make(0b110, 0b11, 4), nb_display);
    print_rgn_srg(rgn_srg_make(0b110, 0b11011, 16), nb_display);
}

int main(int argc, char const* argv[])
{
    unused(argc);
    unused(argv);
    printf("%sCompilation%s de %s \n", COLOR_DEBUG_CATEGORY, COLOR_RESET, current_time);
    
    partie_a();
    partie_b();
    partie_c();
    partie_e();
    partie_d();

    memory_printf_final();
    return EXIT_SUCCESS;
}