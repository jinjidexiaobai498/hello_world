#include <iostream>
#include <string>

using namespace std;

void ByteToBit(bool *Out, long long int in, int & k)//???????????
{
    k=0;
    for(int i=0; i<64&&in; i++)
    {
        Out[i]=in&1;
        //cout<<Out[i];
        in=in>>1;
        k++;
    }
    //cout<<"\n"<<endl;
}
void BitToByte(char *Out,const bool *In,int bits)//???????????
{
    int i;
    //memset(Out,0,(bits+7)/8);
    for(i=0; i<bits; i++)
    {
        Out[i/8]|=In[i]<<(i%8);

    }
}

long long int a_b_mod_n(long long int a,long long int b,long long int n)
{
    long long int d=1;
    bool out[32];
    int k=0;
   //cout<<"//"<<a<<" "<<b<<" "<<n;
    ByteToBit(out,b,k);
    for(int i=k-1; i>=0; i--)
    {
        d=d*d%n;
        if(out[i])
        {
            d=(d*a)%n;
            //cout<<"?";
        }
    }
    return d;
}

const long long int p=167;
    const long long int q=173;//p,q???????????
    const long long int f=28552;
    const long long int n=28891;
class RSA
{
private:
    long long int e;//e,n??????e??f????
    long long int d;//????d,d=(e^-1)mod f
public:
    RSA() {}
    RSA(long long int e)
    {
        this->e=e;
        SetKey(e);
    }
    long long int  SetKey(long long int e)
    {
        this->e=e;
        e=e%f;
        int i;
       for(i=0;i<f;i++)
       {
           int t=i*f+1;
           //cout<<t<<endl;
           if(t%e==0)
           {
               d=(i*f+1)/e;
               return d;
           }
       }
       //cout<<"设置"<<endl;
       return -1;
    }
    long long int Encryption(long long int m)
    {
        return a_b_mod_n(m,e,n);
    }

   long long  int Decrypton(long long int c,long long int pd)
    {
        if(pd==d)
        return a_b_mod_n(c,d,n);
        else cout<<"密钥错误"<<endl;
        return 0;
    }

};

int main()
{
     RSA a;
     cout<<"lvxvdong 吕旭东";
     cout<<"p: "<<p<<"  q:"<<q<<endl;
    long long int m,e,d,c;
    int f=1,n;

    cout<<"初始化公钥e"<<endl;
    cin>>e;
    cout<<"你的私钥为: "<<a.SetKey(e)<<endl;
    while(f)
    {
        cout<<"选择1 加密；2 解密；3 重置e； 0 exit"<<endl;
        cin>>n;
        switch(n)
        {
            case 1 :
                cout<<"输入你的明文"<<endl;
                   cin>>m;
                   cout<<"密文为："<<a.Encryption(m)<<endl;
                   break;
            case 2 :
                cout<<"输入 密文和密钥 ";
                cin>>c>>d;cout<<"明文为："<<a.Decrypton(c,d)<<endl;
                break;
            case 3 :
                cout<<"重新输入e"<<endl;
                cin>>e;
                cout<<"你的私钥为： "<<a.SetKey(e)<<endl;
                break;
            case 0 :
                f=0;
                break;
        }
    }
    return 0;
}
