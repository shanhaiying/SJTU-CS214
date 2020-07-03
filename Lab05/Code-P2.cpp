#include <iostream>
#include <string>

using namespace std;


const int COST[5][5] = {
        {0, 1, 2, 1, 3},
        {1, 0, 1, 5, 1},
        {2, 1, 0, 9, 1},
        {1, 5, 9, 0, 1},
        {3, 1, 1, 1, 0}
};

int transform(char a) {
    switch(a) {
        case 'A':
            return 1;
        case 'T':
            return 2;
        case 'G':
            return 3;
        case 'C':
            return 4;
        default:
            return 0;
    }
}

int cost(char a, char b) { return COST[transform(a)][transform(b)]; }

char *str1, *str2;
string s1, s2;
int *pos;
int l1, l2;
char *text1, *text2;

int OPT(int istart, int iend, int jstart, int mi) {
    int ly = iend - istart;
    int lx = mi - jstart;
    int LCS[ly + 1][2];
    for(int i = 0; i <= ly; i++) {
        for(int j = 0; j < 2; j++) {
            LCS[i][j] = -1;
        }
    }
    LCS[0][0] = 0;
    for(int i = 0; i < ly; i++)
        LCS[i + 1][0] = cost(str1[istart + i], '-') + LCS[i][0];

    for(int j = 0; j < lx; j++) {
        LCS[0][(j + 1) % 2] = cost(str2[jstart + j], '-') + LCS[0][j % 2];
        for(int i = 0; i < ly; i++) {
            int a = LCS[i][(j + 1) % 2] + cost(str1[istart + i], '-');
            int b = LCS[i + 1][j % 2] + cost(str2[jstart + j], '-');
            int c = LCS[i][j % 2] + cost(str1[istart + i], str2[jstart + j]);
            LCS[i + 1][(j + 1) % 2] = min(min(a, b), c);
        }
    }
    return LCS[ly][lx % 2];
}

void findmin(int istart, int iend, int jstart, int jend) {
    if(jend == l2 && jstart + 1 == jend) {
        int ly = iend - istart;
        int lx = jend - jstart;
        int LCS1[ly + 1][2];
        for(int i = 0; i <= ly; i++) {
            for(int j = 0; j < 2; j++) {
                LCS1[i][j] = -1;
            }
        }
        LCS1[0][0] = 0;
        for(int i = 0; i < ly; i++)
            LCS1[i + 1][0] = cost(str1[istart + i], '-') + LCS1[i][0];

        for(int j = 0; j < lx; j++) {
            LCS1[0][(j + 1) % 2] = cost(str2[jstart + j], '-') + LCS1[0][j % 2];
            for(int i = 0; i < ly; i++) {
                int a = LCS1[i][(j + 1) % 2] + cost(str1[istart + i], '-');
                int b = LCS1[i + 1][j % 2] + cost(str2[jstart + j], '-');
                int c = LCS1[i][j % 2] + cost(str1[istart + i], str2[jstart + j]);
                LCS1[i + 1][(j + 1) % 2] = min(min(a, b), c);
            }
        }

        int LCS2[ly + 1][2];
        for(int i = 0; i <= ly; i++) {
            for(int j = 0; j < 2; j++) {
                LCS2[i][j] = -1;
            }
        }
        LCS2[ly][lx % 2] = 0;
        for(int i = ly; i > 0; i--)
            LCS2[i - 1][lx % 2] = cost(str1[istart + i - 1], '-') + LCS2[i][lx % 2];

        for(int j = lx; j > 0; j--) {
            LCS2[ly][(j - 1) % 2] = cost(str2[jstart + j - 1], '-') + LCS2[ly][j % 2];
            for(int i = ly; i > 0; i--) {
                int a = LCS2[i][(j - 1) % 2] + cost(str1[istart + i - 1], '-');
                int b = LCS2[i - 1][j % 2] + cost(str2[jstart + j - 1], '-');
                int c = LCS2[i][j % 2] + cost(str1[istart + i - 1], str2[jstart + j - 1]);
                LCS2[i - 1][(j - 1) % 2] = min(min(a, b), c);
            }
        }

        int min_i = 0;
        int min = 0x7FFFFFFF;
        for(int i = istart; i <= iend; i++) {
            int tmp;
            tmp = LCS1[i - istart][lx % 2] + LCS2[i - istart][lx % 2];
            if(tmp < min) {
                min = tmp;
                min_i = i;
            }
        }
        pos[jend] = min_i;

        min = 0x7FFFFFFF;
        for(int i = istart; i <= iend; i++) {
            int tmp;
            tmp = LCS1[i - istart][0] + LCS2[i - istart][0];
            if(tmp <= min) {
                min = tmp;
                min_i = i;
            }
        }

        if(min_i == pos[jend]) {
            pos[jend] += 2 * l1;
        }
        return;
    }

    int mi = (jstart + jend) / 2;

    int ly = iend - istart;
    int lx = mi - jstart;
    int LCS1[ly + 1][2];
    for(int i = 0; i <= ly; i++) {
        for(int j = 0; j < 2; j++) {
            LCS1[i][j] = -1;
        }
    }
    LCS1[0][0] = 0;
    for(int i = 0; i < ly; i++)
        LCS1[i + 1][0] = cost(str1[istart + i], '-') + LCS1[i][0];

    for(int j = 0; j < lx; j++) {
        LCS1[0][(j + 1) % 2] = cost(str2[jstart + j], '-') + LCS1[0][j % 2];
        for(int i = 0; i < ly; i++) {
            int v1 = LCS1[i][(j + 1) % 2] + cost(str1[istart + i], '-');
            int v2 = LCS1[i + 1][j % 2] + cost(str2[jstart + j], '-');
            int v3 = LCS1[i][j % 2] + cost(str1[istart + i], str2[jstart + j]);
            LCS1[i + 1][(j + 1) % 2] = min(min(v1, v2), v3);
        }
    }


    ly = iend - istart;
    lx = jend - mi;
    int LCS2[ly + 1][2];
    for(int i = 0; i <= ly; i++) {
        for(int j = 0; j < 2; j++) {
            LCS2[i][j] = -1;
        }
    }
    LCS2[ly][lx % 2] = 0;
    for(int i = ly; i > 0; i--)
        LCS2[i - 1][lx % 2] = cost(str1[istart + i - 1], '-') + LCS2[i][lx % 2];

    for(int j = lx; j > 0; j--) {
        LCS2[ly][(j - 1) % 2] = cost(str2[mi + j - 1], '-') + LCS2[ly][j % 2];
        for(int i = ly; i > 0; i--) {
            int a = LCS2[i][(j - 1) % 2] + cost(str1[istart + i - 1], '-');
            int b = LCS2[i - 1][j % 2] + cost(str2[mi + j - 1], '-');
            int c = LCS2[i][j % 2] + cost(str1[istart + i - 1], str2[mi + j - 1]);
            LCS2[i - 1][(j - 1) % 2] = min(min(a, b), c);
        }
    }

    if(jstart + 1 == jend) {
        int min_i = 0;
        int min = 0x7FFFFFFF;
        for(int i = istart; i <= iend; i++) {
            int tmp;
            tmp = LCS1[i - istart][lx % 2] + LCS2[i - istart][0];
            if(tmp < min) {
                min = tmp;
                min_i = i;
            }
        }
        if(min_i == iend) {
            pos[jend] = iend + (2 * l1);
        } else {
            pos[jend] = iend;
        }
        return;
    }

    int min_i = 0;
    int min = 0x7FFFFFFF;
    for(int i = istart; i <= iend; i++) {
        int tmp;
        tmp = LCS1[i - istart][lx % 2] + LCS2[i - istart][0];
        if(tmp < min) {
            min = tmp;
            min_i = i;
        }
    }
    if(pos[mi] == -1)
        pos[mi] = min_i;
    findmin(istart, min_i, jstart, mi);
    findmin(min_i, iend, mi, jend);
}

#include <fstream>

int main() {
    /*ifstream file1,file2;
    file1.open("Data-P2a.txt");
    file1>>s1;
    file2.open("Data-P2b.txt");
    file2>>s2;
    file1.close();
    file2.close();*/
    cin>> s1;
    cin.get();
    cin >> s2;
    l1 = s1.length();
    l2 = s2.length();
    str1 = new char[l1];
    str2 = new char[l2];
    for(int i = 0; i < l1; i++)
        str1[i] = s1[i];
    for(int i = 0; i < l2; i++)
        str2[i] = s2[i];

    cout << OPT(0, l1, 0, l2) << endl;
    pos = new int[l2 + 1];
    for(int t = 0; t <= l2; t++)
        pos[t] = -1;
    findmin(0, l1, 0, l2);
    pos[0] = 0;


    text1 = new char[l1 + l2];
    text2 = new char[l1 + l2];
    int len = -1;

    for(int k = 1; k <= l2; k++) {
        int flag = pos[k] / (2 * l1);
        if(!flag) {
            for(int t = 0; t < pos[k] % (2 * l1) - pos[k - 1] % (2 * l1) - 1; t++) {
                text1[len + 1] = str1[pos[k - 1] % (2 * l1) + t];
                text2[len + 1] = '-';
                len++;
            }
            text1[len + 1] = str1[pos[k] % (2 * l1) - 1];
            text2[len + 1] = str2[k - 1];
            len++;

        } else {
            for(int t = 0; t < pos[k] % (2 * l1) - pos[k - 1] % (2 * l1) - 1; t++) {
                text1[len + 1] = str1[pos[k - 1] % (2 * l1) + t];
                text2[len + 1] = '-';
                len++;
            }
            text1[len + 1] = '-';
            text2[len + 1] = str2[k - 1];
            len++;
        }
    }

    if(pos[l2] % (2 * l1) < l1) {
        for(int k = 0; k < l1 - pos[l2] % (2 * l1); k++) {
            text1[len + 1] = str1[pos[l2] % (2 * l1) + k];
            text2[len + 1] = '-';
            len++;
        }
    }

    for(int k = 0; k <= len; k++) {
        cout << text1[k];
    }
    cout << endl;
    for(int k = 0; k <= len; k++) {
        cout << text2[k];
    }
    cout << endl;
    delete [] str1;
    delete [] str2;
    delete [] pos;
    delete [] text1;
    delete [] text2;
    return 0;
}
