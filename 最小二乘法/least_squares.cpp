#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull maxr = 100;
const ull maxc = 100;
ull get_max_main(ull r,ull row,ull col,double **mat){
    ull res = r;
    double val = mat[r][r];
    for(ull i=r+1;i<row;i++){
        if(val < mat[i][r]){
            val = mat[i][r],res = i;
        }
    }
    return res;
}
ull get_min_main(ull r,ull row,ull col,double **mat){
    ull res = -1;
    double val = 0;
    for(ull i=r;i<row;i++){
        if(mat[i][r] == 0)continue;
        else if(val == 0){
            val = mat[i][r],res = i;
            continue;
        }
        if(val > mat[i][r]){
            val = mat[i][r],res = i;
        }
    }
    return res;
}
void clear_item_lower(ull r,ull row,ull col,double **mat){
    for(ull i=r+1;i<row;i++){
        double bl = mat[i][r]/mat[r][r];
        mat[i][r] = 0;
        for(ull j=r+1;j<col;j++){
            mat[i][j] -= bl*mat[r][j];
        }
    }
}
void clear_item_upper(ull r,ull row,ull col,double **mat){
    for(ull i=r-1;i<r;i--){//attention
        double bl = mat[i][r]/mat[r][r];
        mat[i][r] = 0;
        for(ull j=i+1;j<col;j++){
            if(j!=r)mat[i][j] -= bl*mat[r][j];
        }
    }
}
bool solve(ull row,ull col,double **mat){
    for(ull i=0;i<row;i++){
        ull main_item = 0;
        main_item = get_max_main(i,row,col,mat);
        if(main_item==ull(-1) || mat[main_item][i]==0){
            return 0;
        }
        swap(mat[main_item],mat[i]);
        clear_item_lower(i,row,col,mat);
    }
    for(ull i=row-1;i<row;i--){//attention
        clear_item_upper(i,row,col,mat);
    }
    for(ull i=0;i<row;i++){
        double dv = mat[i][i];
        for(ull j=col-1;j<col;j--){//attention
            mat[i][j] /= dv;
        }
    }
    return 1;
}
double **new_matrix(){
    double **res = (double**)malloc(maxr*sizeof(double*));
    for(ull i=0;i<maxr;i++)res[i] = new double[maxc];
    return res;
}
double x[maxr],y[maxr],p[maxr],f[maxr],mat[maxr][maxc];
double xx[maxr],yy[maxr],xp[maxr][maxr*2],yp[maxr][2];
ull m,n;
double sum_xyp(ull xu,ull yu){
    double sum = 0;
    for(ull i=0;i<m;i++)
        sum += xp[i][xu]*yp[i][yu]*p[i];
    return sum;
}
double fai_0(double **resmat,double xin){
    double a1 = resmat[0][3];
    double a2 = resmat[1][3];
    double a3 = resmat[2][3];
    return a1*xin+a2*xin*xin+a3*xin*xin*xin;
}
double fai_1(double **resmat,double xin){
    double a0 = resmat[0][2];
    double a1 = resmat[1][2];
    return a0+a1*xin;
}
void print_exp_str_0(double **resmat){
    double a1 = resmat[0][3];
    double a2 = resmat[1][3];
    double a3 = resmat[2][3];
    printf("f(t)=%f*t+%f*t^2+%f*t^3\n",a1,a2,a3);
}
void print_exp_str_1(double **resmat){
    double a0 = resmat[0][2];
    double a1 = resmat[1][2];
    printf("f(t)=%f+%f*t\n",a0,a1);
}
int main(){
    freopen("in.txt","r",stdin);
    double **mat = new_matrix();
    ull mode;
    while(cin>>m>>mode){
        for(ull i=0;i<m;i++)cin>>x[i];
        for(ull i=0;i<m;i++)cin>>y[i];
        for(ull i=0;i<m;i++)cin>>p[i];
        if(mode == 0){
            for(ull i=0;i<m;i++)
                xx[i] = x[i],yy[i] = y[i];
            n = 3;
        }else if(mode == 1){
            for(ull i=0;i<m;i++)
                xx[i] = x[i],yy[i] = y[i];
            n = 1;
        }else return 0;

        for(ull i=0;i<m;i++){
            xp[i][0] = 1;
            for(ull j=1;j<=2*n;j++)
                xp[i][j] = xx[i]*xp[i][j-1];
        }
        for(ull i=0;i<m;i++){
            yp[i][0] = 1,yp[i][1] = yy[i];
        }
        for(ull i=0;i<=n;i++){
            mat[0][i] = sum_xyp(i,0);
            mat[n][i] = sum_xyp(i+n,0);
            mat[i][n+1] = sum_xyp(i,1);
        }
        for(ull i=1;i<n;i++){
            for(ull j=0;j<=n;j++){
                if(j<n)mat[i][j] = mat[i-1][j+1];
                else mat[i][j] = mat[j][i];
            }
        }

        if(mode == 0){
            n--;
            for(ull i=0;i<=n;i++)for(ull j=0;j<=n+1;j++){
                mat[i][j] = mat[i+1][j+1];
            }
        }
/*
        for(ull i=0;i<=n;i++)for(ull j=0;j<=n+1;j++){
            cout<<mat[i][j]<<(j==n+1?"\n":" ");
        }
*/
        solve(n+1,n+2,mat);

        if(mode == 0){
            print_exp_str_0(mat);
            for(ull i=0;i<m;i++)
                f[i] = fai_0(mat,x[i]);
        }else if(mode == 1){
            print_exp_str_1(mat);
            for(ull i=0;i<m;i++)
                f[i] = fai_1(mat,x[i]);
        }

        double norm2 = 0;
        for(ull i=0;i<m;i++){
            norm2 += (y[i]-f[i])*(y[i]-f[i]);
        }
        norm2 = sqrt(norm2);
        //for(ull i=0;i<m;i++)cout<<f[i]<<(i==m-1?"\n":" ");
        cout<<norm2<<endl;
    }
    return 0;
}
