#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull maxr = 1000;
const ull maxc = 1000;

ull get_max_main(ull r,ull row,ull col,double **mat){
    ull res = r;
    double val = abs(mat[r][r]);
    for(ull i=r+1;i<row;i++){
        if(val < abs(mat[i][r])){
            val = abs(mat[i][r]),res = i;
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
            val = abs(mat[i][r]),res = i;
            continue;
        }
        if(val > abs(mat[i][r])){
            val = abs(mat[i][r]),res = i;
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
bool solve(ull row,ull col,double **mat,ull mode){
    for(ull i=0;i<row;i++){
        ull main_item = 0;
        if(mode == 0)main_item = i;
        else if(mode == 1)main_item = get_max_main(i,row,col,mat);
        else if(mode == 2)main_item = get_min_main(i,row,col,mat);
        else {
            for(ull j=i;j<row;j++)
                cout<<j<<":"<<(mat[j][i])<<(j==row-1?"\n":" ");
            cin>>main_item;
        }
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
double norm_1(ull row,double**mat){
    double res = 0;
    for(ull j=0;j<row;j++){
        double sum = 0;
        for(ull i=0;i<row;i++){
            sum += abs(mat[i][j]);
        }
        res = max(res,sum);
    }
    return res;
}
double **new_matrix(){
    double **res = (double**)malloc(maxr*sizeof(double*));
    for(ull i=0;i<maxr;i++)res[i] = new double[maxc];
    return res;
}
int main(){
    freopen("in.txt","r",stdin);
    /*
    ull mr = 50;
    for(ull i=0;i<mr;i++){
        for(ull j=0;j<mr;j++){
            if(i == j)cout<<6;
            else if(i == j+1)cout<<8;
            else if(i == j-1)cout<<1;
            else cout<<0;
            cout<<" ";
        }
        if(i == 0)cout<<7<<endl;
        else if(i == mr-1)cout<<14<<endl;
        else cout<<15<<endl;
    }
    */
    double **mato=new_matrix(),**matt=new_matrix(),**mati=new_matrix();
    ull row,mode;
    while(cin>>row>>mode){
        for(ull i=0;i<row;i++)for(ull j=0;j<row+1;j++){
            cin>>mato[i][j];
        }

        for(ull i=0;i<row;i++)for(ull j=0;j<2*row;j++){
            if(j<row)matt[i][j] = mato[i][j];
            else matt[i][j] = (i==j-row?1:0);
        }
        if(!solve(row,row*2,matt,1)){
            cout<<"error"<<endl;
            return 0;
        }
        for(ull i=0;i<row;i++)for(ull j=0;j<row;j++){
            mati[i][j] = matt[i][j+row];
        }
        double condition = norm_1(row,mato)*norm_1(row,mati);
        cout<<condition<<endl;

        if(!solve(row,row+1,mato,mode)){
            cout<<"error"<<endl;
            return 0;
        }
        for(ull i=0;i<row;i++){
            cout<<mato[i][row]<<(i==row-1?"\n":",");
        }
        /*
        for(ull i=0;i<row;i++)for(ull j=0;j<row+1;j++){
            cout<<mato[i][j]<<(j==row?"\n":" ");
        }
        */
    }
    return 0;
}
