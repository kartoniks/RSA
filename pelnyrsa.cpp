#include<iostream>
#include<vector>
#include<time.h>
#include <stdlib.h>
using namespace std;
long long nwd(long long a, long long b)
{
    if(b==0)
        return a;
    else
        return nwd(b,a%b);
}
long long gete(long long a)
{
    long long e=3;
    while(nwd(a,e)!=1)
        e+=2;
    return e;
}
long long inverse(long long a, long long n)
{
	long long a0, n0, p0, p1, q, r, t;

	p0 = 0; p1 = 1; a0 = a; n0 = n;
	q = n0 / a0;
	r = n0 % a0;
	while (r > 0)
	{
		t = p0 - q * p1;
		if (t >= 0)
			t = t % n;
		else
			t = n - ((-t) % n);
		p0 = p1; p1 = t;
		n0 = a0; a0 = r;
		q = n0 / a0;
		r = n0 % a0;
	}
	return p1;
}
long long power (long long b, long long n, long long limit)
{
    if(n==0)
        return 1;
    long long h=power(b,n/2,limit);
    if(n%2==0)
        return (h*h)%limit;
    else
        return (h*h)%limit*b%limit;
}
vector<long long> encrypt (string m, long long e, long long limit, long long indian)
{
    vector<long long> c;
    long long temp=m.size();
    if(temp%indian!=0)
        temp+=indian-temp%indian;
    m.resize(temp);
    c.resize(temp/indian);
    for(int i=0; i<temp/indian; i++)
    {
        for(int j=0; j<indian; j++)
        {
            c[i]*=256;
            c[i]+=m[i*indian+j];
            cout<<m[i*indian+j];
        }
        c[i]=power(c[i],e,limit);
    }
    return c;

}
string decrypt (vector<long long> c, long long d, long long limit, long long indian)
{
    string m;
    m.resize(c.size()*indian);
    for(int i=0; i<c.size(); i++)
    {
        long long t=power(c[i], d, limit);
        for(int j=indian; j>0; j--)
        {
            m[i*indian+j-1]=t%256;
            t/=256;
        }
    }
    return m;
}
bool isprime(long long a)
{
    for(int i=2; i*i<a; i++)
        if(a%i==0)
            return false;
    return true;
}
long long generaterandom(long long l, long long r)
{
    long long n;
    n=l+rand()/(RAND_MAX/(r-l+1)+1);
    return n;
}

int main()
{
    srand(time(NULL));
    string message;
    cout<<"Podaj wiadomosc do zakodowania:\n";
    cin>>message;
    vector<long long> code;
    long long p,q,e,indian;
    cout<<"Po ile bajtow chcesz kodowac?\n";
    cin>>indian;

    p=generaterandom(256,256*256);
    while(!isprime(p))
        p=generaterandom(256,256*256);
    q=generaterandom(256,256*256);
    while(!isprime(q))
        q=generaterandom(256,256*256);


    long long n=p*q;
    long long capn=(p-1)*(q-1);
    e=gete(capn);
    long long d=inverse(e,capn);
    cout<<"To jest e: "<<e<<" To odwrotnosc e: "<<d<<" To jest p: "<<p<<" To jest q "<<q<<" To jest n: "<<n<<"\n";
    code=encrypt(message,e,n,indian);
    cout<<"To jest zakodowana wiadomosc: ";
    for(int i=0; i<code.size(); i++)
        cout<<code[i]<<" ";
    cout<<"\n";
    string newmessage;
    newmessage=decrypt(code,d,n,indian);
    cout<<newmessage<<"\n";
    return 0;
}
