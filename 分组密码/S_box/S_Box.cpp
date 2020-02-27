#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

int sBox4By4[16];
int sBox3By3[9];
default_random_engine random_engine(time(NULL));

void sBoxInit(int a[], int n){
    for(int i = 0; i < n; i++){
        a[i] = i + 1;
    }
}

void random(int a[], int n){
    int index, tmp, i;

//    srand(time(NULL));
    for (i = 0; i < n; i++){
        index = (int)random_engine() % (n - i) + i;
        if (index != i){
            tmp = a[i];
            a[i] = a[index];
            a[index] = tmp;
        }
    }
}
int main()
{
    for(int j = 1; j <= 10; j++) {
        sBoxInit(sBox4By4, 16);
        random(sBox4By4, 16);
        for (int i = 0; i < 16; i++)
            printf("%d ", sBox4By4[i]);
        printf("\n");
    }
    return 0;
}