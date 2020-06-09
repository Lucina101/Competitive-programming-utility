#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7, maxn=100;
int a[maxn][maxn],ans[maxn],n;
int add(int a, int b) {
  a += b;
  if (a >= mod) a -= mod;
  return a;
}

int sub(int a, int b) {
  a -= b;
  if (a < 0) a += mod;
  return a;
}

int mul(int a, int b) {
  return (int) ((long long) a * b % mod);
}

int power(int a,long long b) {
  int res = 1;
  while (b > 0) {
    if (b & 1) {
      res = mul(res, a);
    }
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int main(){
    scanf("%d",&n);
    int ma,tmp;
    for(int i=1;i<=n;i++){
		if(!a[i][i]){
			ma=0;
			for(int j=i+1;j<=n&&!ma;j++)
				if(a[j][i]) ma=j;
			if(!ma) continue;
			for(int j=i;j<=n+1;j++)
				swap(a[ma][j],a[i][j]);
		}
		for(int j=i+1;j<=n;j++){
			tmp=a[j][i];
			if(!tmp) continue;
			for(int k=i;k<=n+1;k++)
                a[j][k]=sub(mul(a[j][k],a[i][i]),mul(a[i][k],tmp));
		}
	}
	for(int i=n;i;i--){
		for(int j=i+1;j<=n;j++)
            a[i][n+1]=sub(a[i][n+1],mul(ans[j],a[i][j]));
			ans[i]=(mul(a[i][n+1],power(a[i][i],mod-2)));
			/*if normal version(no modulo)
			ans[i]=a[i][n+1]/a[i][i];
            */
	}
}
