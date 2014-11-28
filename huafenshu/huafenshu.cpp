 #include <iostream>
 #include <cstdio>
 #include <algorithm>
 using namespace std;
 #define N 100005
 int a[N], as[N];//ԭ���飬���������
 int n, m;
 int sum[20][N];//��¼��i���1~j���ֵ���������Ԫ�ظ���(����j)
 int tree[20][N];//��¼��i��Ԫ������
 void build(int c, int l, int r){
     int i, mid = (l + r) >> 1, lm = mid - l + 1, lp = l, rp = mid + 1;
     for (i = l; i <= mid; i++){
         if (as[i] < as[mid]){
             lm--;//�ȼ�����ߵ�(mid - l + 1)����������as[mid],Ȼ���ʵ����С��as[mid]�ļ�ȥ
         }
     }
     for (i = l; i <= r; i++){
         if (i == l){
             sum[c][i] = 0;//sum[i]��ʾ[l, i]���ж��ٸ����ֵ���ߣ���DP��ά��
         }else{
             sum[c][i] = sum[c][i - 1];
         }
         if (tree[c][i] == as[mid]){
             if (lm){
                 lm--;
                 sum[c][i]++;
                 tree[c + 1][lp++] = tree[c][i];
             }else
                 tree[c + 1][rp++] = tree[c][i];
         } else if (tree[c][i] < as[mid]){
             sum[c][i]++;
             tree[c + 1][lp++] = tree[c][i];
         } else{
             tree[c + 1][rp++] = tree[c][i];
         }
     }
     if (l == r)return;
     build(c + 1, l, mid);
     build(c + 1, mid + 1, r);
 }
 int query(int c, int l, int r, int ql, int qr, int k){
     int s;//[l, ql)�ڽ������ֵ���������Ԫ����Ŀ
     int ss;//[ql, qr]�ڽ������ֵ���������Ԫ����Ŀ
     int mid = (l + r) >> 1;
     if (l == r){
         return tree[c][l];
     }
     if (l == ql){//����Ҫ���⴦��
     s = 0;
     ss = sum[c][qr];
     }else{
         s = sum[c][ql - 1];
         ss = sum[c][qr] - s;
     }//����Ҫ������[l,r]�в��ҵ�k��Ԫ�أ�tΪ��ǰ�ڵ㣬lch��rchΪ���Һ��ӣ�left��midΪ�ڵ�t��߽���м�㡣
     if (k <= ss){//sum[r]-sum[l-1]>=k������lch[t],�����ӦΪ[ left+sum[l-1], left+sum[r]-1 ]
         return query(c + 1, l, mid, l + s, l + s + ss - 1, k);
     }else{//sum[r]-sum[l-1]<k,����rch[t]�������ӦΪ[ mid+1+l-left-sum[l-1], mid+1+r-left-sum[r] ]
         return query(c + 1, mid + 1, r, mid - l + 1 + ql - s, mid - l + 1 + qr - s - ss,k - ss);
     }
 }
 int main(){
     int i, j, k;
     while(~scanf("%d%d", &n, &m)){
         for (i = 1; i <= n; i++){
             scanf("%d", &a[i]);
             tree[0][i] = as[i] = a[i];
         }
         sort(as + 1, as + 1 + n);
         build(0, 1, n);
         while(m--){
             scanf("%d%d%d",&i,&j,&k);// i,j�ֱ�Ϊ������ʼ�㣬kΪ�������k�������
             printf("%d\n", query(0, 1, n, i, j, k));
         }
     }
     return 0;
 }
