#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>

#define typename(x) _Generic((x), _Bool: "_Bool", \
    char: "char", \
    signed char: "signed char", \
    unsigned char: "unsigned char", \
    short int: "short int", \
    unsigned short int: "unsigned short int", \
    int: "int", \
    unsigned int: "unsigned int", \
    long int: "long int", \
    unsigned long int: "unsigned long int", \
    long long int: "long long int", \
    unsigned long long int: "unsigned long long int", \
    float: "float", \
    double: "double", \
    long double: "long double", \
    char *: "char *", \
    void *: "void *", \
    int *: "int *", \
    default: "other")

#define printf_dec_format(x) _Generic((x), \
    char: "%c", \
    signed char: "%hhd", \
    unsigned char: "%hhu", \
    signed short: "%hd", \
    unsigned short: "%hu", \
    signed int: "%d", \
    unsigned int: "%u", \
    long int: "%ld", \
    unsigned long int: "%lu", \
    long long int: "%lld", \
    unsigned long long int: "%llu", \
    float: "%f", \
    double: "%f", \
    long double: "%Lf", \
    char *: "%s", \
    int *: "%d", \
    void *: "%p")

int n=0,min_index=-1,max_index=-1,low,high,mid;
#define vector(type) type *

#define newVector(type) (vector(type))malloc(n * sizeof(type))

#define push_back(a,x) n++, a=realloc(a, n *sizeof(a)), a[n-1]=x

#define pop_back(a) n--, a=realloc(a,n*sizeof(a))

#define printV(a) for(int i=0;i<n;i++){ printf(printf_dec_format(a[i]),a[i]), printf("\t"); }

#define Vsize(a) n;

#define min_element(a,minn) for(int i=0;i<n;i++){ if(minn>a[i]){ minn=a[i], min_index=i; } } minn=min_index;

#define max_element(a,maxx) for(int i=0;i<n;i++){ if(maxx<a[i]){ maxx=a[i], max_index=i; } } maxx=max_index;

#define clear(a) free(a); n=0;

#define first_element(a) a[0]

#define last_element(a) a[n-1]

#define lower_bound(a,lb,X) \
    low=0;\
    high=n;\
    while (low < high) { \
        mid = low + (high - low) / 2; \
        if (X <= a[mid]) { \
            high = mid; \
        } \
        else { \
            low = mid + 1; \
        } \
    } \
    lb=low

#define upper_bound(a,ub,X)\
    low=0;\
    high=n;\
    while (low < high) { \
        mid = low + (high - low) / 2; \
        if (X >= a[mid]) { \
            low=mid+1; \
        } \
        else { \
            high=mid; \
        } \
    } \
    ub=low;

void test() {

    vector(int) a=newVector(int); // create
    push_back(a,4);
    push_back(a,6);
    push_back(a,10);
    push_back(a,12);
    push_back(a,20);
    push_back(a,18);

    int s=Vsize(a);
    int minn=10;
    int maxx=0;
    min_element(a,minn);
    max_element(a,maxx);
    printV(a);
    printf("\nmin: %d, max: %d\n", minn, maxx);
    int f=first_element(a);
    int l=last_element(a);
    printf("\nf: %d, l: %d\n", f, l);
    int lb=lower_bound(a,lb,6);
    int ub=upper_bound(a,ub,18);
    printf("%d ",lb);
    printf("%d\n",ub);
    pop_back(a);
    printV(a);
    clear(a);
}
int main()
{
    // test();
    putchar('\n');

    vector(char) b = newVector(char);
    vector(int) a = newVector(int);
    push_back(b, 'x');
    push_back(a, 19);

    push_back(b, 'e');
    int szb = Vsize(b); int sza = Vsize(a);
    printf("\n%d %d\n", szb, sza);

    printV(a);
    printV(b);



    // getchar();
}
