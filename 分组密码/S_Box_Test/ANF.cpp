//
// Created by QL Sun on 2020/2/27.
//

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
#define S_BOX_IN_DIMENSION 3
#define S_BOX_OUT_DIMENSION 3
#define IN_DIMENSION 8
#define OUT_DIMENSION 8

int num = 0;
void printMat(const int ans[][IN_DIMENSION + S_BOX_OUT_DIMENSION]){
    printf("Mat: %d\n", num++);
    for(int i = 0; i < IN_DIMENSION; i++){
        for(int j = 0; j < IN_DIMENSION; j++)
            printf("%d ", ans[i][j]);
        printf("| ");
        for(int j = IN_DIMENSION; j < IN_DIMENSION + S_BOX_OUT_DIMENSION; j++)
            printf("%d ", ans[i][j]);
        printf("\n");
    }
}

void toBinaryNum(int num, int binaryNum[], const int binaryLen){
    memset(binaryNum, 0, sizeof(int) * binaryLen);
    for(int i = 0; i < binaryLen; i++){
        binaryNum[i] = num % 2;
        num /= 2;
    }
}

int findOneLine(int ans[][IN_DIMENSION + S_BOX_OUT_DIMENSION], const int lineNum){
    for(int i = lineNum; i < IN_DIMENSION; i++){
        if(ans[i][lineNum] == 1)
            return i;
    }
    return 0;
}


void swapVec(int a[], int b[]){
    int temp;
    for(int i = 0; i < IN_DIMENSION + S_BOX_OUT_DIMENSION; i++){
        temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}

void initMat(int ans[][IN_DIMENSION + S_BOX_OUT_DIMENSION], const int *sBox){
    memset(ans, 0, sizeof(int) * IN_DIMENSION * (IN_DIMENSION + S_BOX_OUT_DIMENSION));
    int binaryNum[4];
    for(int i = 0; i < IN_DIMENSION; i++){
        toBinaryNum(i, binaryNum, 3);
        //yi = c0 + c1x2 + c2x1 + c3x0 + c4x2x1 + c5x2x0 + c6x1x0 + c7x2x1x0;
        ans[i][0] = 1;
        ans[i][1] = binaryNum[2];
        ans[i][2] = binaryNum[1];
        ans[i][3] = binaryNum[0];
        ans[i][4] = binaryNum[2] & binaryNum[1];
        ans[i][5] = binaryNum[2] & binaryNum[0];
        ans[i][6] = binaryNum[1] & binaryNum[0];
        ans[i][7] = binaryNum[2] & binaryNum[1] & binaryNum[0];
        toBinaryNum(sBox[i], binaryNum, 3);
        ans[i][8] = binaryNum[2];
        ans[i][9] = binaryNum[1];
        ans[i][10] = binaryNum[0];
    }
    printMat(ans);
}

void calculateANF(int ans[][IN_DIMENSION + S_BOX_OUT_DIMENSION], const int *sBox){
    initMat(ans, sBox);

    for(int i = 0; i < IN_DIMENSION; i++){
        if(ans[i][i] != 1){
            int oneLine = findOneLine(ans, i);
            swapVec(ans[i], ans[oneLine]);
            printf("swap %d %d\n", i, oneLine);
            printMat(ans);
        }
        for(int j = i + 1; j < IN_DIMENSION; j++){
            if(ans[j][i] == 1) {
                for(int k = i; k < IN_DIMENSION + S_BOX_OUT_DIMENSION; k++)
                    ans[j][k] = ans[i][k] ^ ans[j][k];
            }
        }
        printMat(ans);
    }

    for(int i = 7; i >= 0; i--){
        for(int j = i - 1; j >= 0; j--){
            if(ans[j][i] == 1){
                for(int k = i; k < IN_DIMENSION + S_BOX_OUT_DIMENSION; k++)
                    ans[j][k] = ans[i][k] ^ ans[j][k];
            }
        }
        printMat(ans);
    }
}

int main(void){
    const int sBox[] = {3, 7, 2, 4, 1, 5, 0, 6};
    int ans[IN_DIMENSION][IN_DIMENSION + S_BOX_OUT_DIMENSION];
    calculateANF(ans, sBox);
    printf("ans: \n");
    for(int i = IN_DIMENSION; i < IN_DIMENSION + S_BOX_OUT_DIMENSION; i++){
        for(int j = 0; j < IN_DIMENSION; j++)
            printf("%d ", ans[j][i]);
        printf("\n");
    }
}