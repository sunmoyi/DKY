#include<cstdio>
#include<cmath>
#include<cstring>

using namespace std;


double calerfc(char *str){
    int len = strlen(str);
    int ones = 0;
    for(int i = 0; i < len; i++)
        ones += str[i] - '0';//(str[i] != str[i + 1]);
    double ans = abs(ones - (len * 1.0/ 2)) / (sqrt(len*1.0 / 4));
    printf("obs:%lf\n", ans);
    ans = erfc(ans / sqrt(2));


    return ans;
}

int main (void){
    char str[] = "1100100100001111110110101010001000100001011010001100001000110100110001001100011001100010100010111000";
    //char str[] = "1011010101";
    printf("P:%lf", calerfc(str));
}