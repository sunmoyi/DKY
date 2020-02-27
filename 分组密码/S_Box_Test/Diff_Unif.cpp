////
//// Created by QL Sun on 2020/2/27.
////
//
//#include <cstdio>
//#include <cstring>
//#include <algorithm>
//#include <vector>
//#include <bitset>
//
//using namespace std;
//
//
//void toBinary(int num, char str[]){
//    str[3] = 0;
//    for(int i = 2; i >=0; i--){
//        str[i] = (num % 2) + '0';
//        num /= 2;
//    }
//}
//
//void calDiffUnif(int ans[][8], const int *sBox, int boxSize){
//    memset(ans, 0, sizeof(int) * boxSize * boxSize);
//
//    for(int i = 0; i < boxSize; i++){
//        for(int j = 0; j < boxSize; j++){
//            int a = i ^ j;
//            int b = sBox[i] ^ sBox[j];
//            ans[a][b] += 1;
//        }
//    }
//}
//
//int main(void){
//    int sBox[] = {2, 7, 5, 0, 3, 1, 4, 6};
//    int ans[8][8];
//    char num[5];
//    calDiffUnif(ans, (int *)sBox, 8);
//    printf("a,b\t");
//    for(int i = 0; i < 8; i++){
//        toBinary(i, num);
//        printf("%s\t", num);
//    }
//    printf("\n");
//    for(int i = 0; i < 8; i++){
//        toBinary(i, num);
//        printf("%s\t", num);
//        for(int j = 0; j < 8; j++)
//            printf("%d\t", ans[i][j]);
//        printf("\n");
//    }
//}