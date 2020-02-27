////
//// Created by QL Sun on 2020/2/27.
////
//
//#include <cstdio>
//#include <cstring>
//#include <bitset>
//#include <algorithm>
//
//using namespace std;
//
//
//
//void toBinaryNum(int num, int binaryNum[], int binaryLen){
//    memset(binaryNum, 0, sizeof(int) * binaryLen);
//    for(int i = 0; i < binaryLen; i++){
//        binaryNum[i] = num % 2;
//        num /= 2;
//    }
//}
//
//int calculateAX(int a, int x){
//    int binaryA[4];
//    int binaryX[4];
//    toBinaryNum(a, binaryA, 3);
//    toBinaryNum(x, binaryX, 3);
//    int ans = 0;
//    for(int i = 0; i < 3; i++){
//        ans ^= (binaryA[i] * binaryX[i]);
//    }
//    return ans;
//}
//
//int calculateBSx(int b, int sBox[], int x){
//    int binaryB[4];
//    int binarySx[4];
//    toBinaryNum(b, binaryB, 3);
//    toBinaryNum(sBox[x], binarySx, 3);
//    int ans = 0;
//    for(int i = 0; i < 3; i++){
//        ans ^= (binaryB[i] * binarySx[i]);
//    }
//    return ans;
//}
//
//void calculateLinearProbability(int ans[][8], int sBox[], int boxSize){
//    memset(ans, 0, sizeof(int) * boxSize * boxSize);
//    for(int i = 0; i < boxSize; i++){
//        for(int j = 0; j < boxSize; j++){
//            for(int x = 0; x < boxSize; x++){
//                int AX = calculateAX(i, x);
//                int BSx = calculateBSx(j, sBox, x);
//                if(AX == BSx)
//                    ans[i][j] += 1;
//            }
//        }
//    }
//}
//
//int main(void){
//    int sBox[] = {3, 7, 2, 4, 1, 5, 0, 6};
//    int binaryNum[4];
//    int ans[8][8];
//    for(int i = 0; i < 8; i++){
//        toBinaryNum(i, binaryNum, 3);
//        for(int j = 2; j >= 0; j--)
//            printf("%d", binaryNum[j]);
//        printf("\t");
//    }
//    printf("\n");
//    calculateLinearProbability(ans, sBox, 8);
//    for(int i = 0; i < 8; i++){
//        toBinaryNum(i, binaryNum, 3);
//        for(int j = 2; j >= 0; j--)
//            printf("%d", binaryNum[j]);
//        printf("\t");
//        for(int j = 0; j < 8; j++)
//            printf("%d\t", ans[i][j]);
//        printf("\n");
//    }
//}
