//FCPC S.2 2024 F
#include <bits/stdc++.h>
using namespace std;

int main() {
   	int m, n, k;
   	cin >> m >> n >> k;
   	string sh1[m];
   	for(int i = 0; i < m; i++) {
       cin >> sh1[i];
   	}
   	string sh2[m*k];
   	for(int i = 0; i < m; i++) {
       	string one_line = "";
       	for(int j = 0; j < n; j++) {
           	for(int l = 0; l < k; l++) {
               	one_line += sh1[i][j];
           }
       	}
       	for(int l = 0; l < k; l++) {
           	sh2[i*k+l] = one_line;
       	}
   	}
   	for(int i = 0; i < m*k; i++) {
       	cout << sh2[i] << "\n";
   }
	return 0;
}

