#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

struct punto
{
    lli x, y;
    bool operator<(punto aux) const
    {
        if (x < aux.x)
        {
            return true;
        }
        if (x == aux.x && y < aux.y)
        {
            return true;
        }
        return false;
    }
};
lli orientation(punto p, punto q, punto r)
{
    lli k = (r.x - q.x) * (q.y - p.y) - (r.y - q.y) * (q.x - p.x);
    return k;
}
lli por(punto p, punto q, punto r)
{
    lli k = (r.x - q.x) * (q.y - p.y) - (r.y - q.y) * (q.x - p.x);
    if (k == 0)
        return 0;
    if (k > 0)
        return 1;
    return -1;
}
punto rojo[50002];
punto azul[50002];
punto CHR[50002];
punto CHA[50002];
punto pila[50002];
lli tope = 2;
lli n;
bool dentrorojo(punto act)
{
    punto inf = act;
    int cuts = 0;
    for (int i = 1; i < tope; i++)
    {
        //cout<<orientation(CHR[i],CHR[i+1],act)<<"\n";
        if (orientation(CHR[i], CHR[i + 1], act) < 0)
        {
            return false;
        }
        if (orientation(CHR[i], CHR[i + 1], act) == 0)
        {
            lli lx = min(CHR[i].x, CHR[i + 1].x);
            lli hx = max(CHR[i].x, CHR[i + 1].x);
            lli ly = min(CHR[i].y, CHR[i + 1].y);
            lli hy = max(CHR[i].y, CHR[i + 1].y);
            return (act.x >= lx && act.x <= hx && act.y >= ly && act.y <= hy);
        }
    }
    //cout<<cuts<<"\n";
    return true;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> rojo[i].x >> rojo[i].y;
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> azul[i].x >> azul[i].y;
    }
    sort(rojo + 1, rojo + n + 1);
    sort(azul + 1, azul + n + 1);
    pila[1] = rojo[1];
    pila[2] = rojo[2];
    for (int i = 3; i <= n; i++)
    {
        if (tope >= 2)
        {
            lli ori = orientation(pila[tope - 1], pila[tope], rojo[i]);
            while (tope >= 2 && ori <= 0)
            {
                //cout<<"Saque "<<pila[tope].x<<" "<<pila[tope].y<<"\n";
                tope--;
                ori = orientation(pila[tope - 1], pila[tope], rojo[i]);
            }
            tope++;
            pila[tope] = rojo[i];
            //cout<<"Meti "<<pila[tope].x<<" "<<pila[tope].y<<"\n";
        }
    }

    for (int i = 1; i <= tope; i++)
    {
        CHR[i] = pila[i];
        //cout<<CHR[i].x<<" "<<CHR[i].y<<"\n";
    }
    lli fin = 2;
    pila[1] = rojo[1];
    pila[2] = rojo[2];
    for (int i = 3; i <= n; i++)
    {
        if (fin >= 2)
        {
            lli ori = orientation(pila[fin - 1], pila[fin], rojo[i]);
            while (fin >= 2 && ori >= 0)
            {
                fin--;
                ori = orientation(pila[fin - 1], pila[fin], rojo[i]);
            }
            fin++;
            pila[fin] = rojo[i];
        }
    } //cout<<"Hola\n";
    for (int i = fin - 1; i > 1; i--)
    {
        CHR[++tope] = pila[i];
    }
    CHR[++tope] = CHR[1];
    /*for(int i=1;i<=tope;i++){
        cout<<CHR[i].x<<" "<<CHR[i].y<<"\n";
    }*/
    // cout<<"\n";
    lli red = 0;
    for (int i = 1; i <= n; i++)
    {
        red += dentrorojo(azul[i]);
    }
    cout << red << " ";
    pila[1] = azul[1];
    pila[2] = azul[2];
    tope = 2;
    for (int i = 3; i <= n; i++)
    {
        if (tope >= 2)
        {
            lli ori = orientation(pila[tope - 1], pila[tope], azul[i]);
            while (tope >= 2 && ori <= 0)
            {
                //cout<<"Saque "<<pila[tope].x<<" "<<pila[tope].y<<"\n";
                tope--;
                ori = orientation(pila[tope - 1], pila[tope], azul[i]);
            }
            tope++;
            pila[tope] = azul[i];
            //cout<<"Meti "<<pila[tope].x<<" "<<pila[tope].y<<"\n";
        }
    }
    for (int i = 1; i <= tope; i++)
    {
        CHR[i] = pila[i];
        //cout<<CHR[i].x<<" "<<CHR[i].y<<"\n";
    }
    fin = 2;
    pila[1] = azul[1];
    pila[2] = azul[2];
    for (int i = 3; i <= n; i++)
    {
        if (fin >= 2)
        {
            lli ori = orientation(pila[fin - 1], pila[fin], azul[i]);
            while (fin >= 2 && ori >= 0)
            {
                fin--;
                ori = orientation(pila[fin - 1], pila[fin], azul[i]);
            }
            fin++;
            pila[fin] = azul[i];
        }
    } //cout<<"Hola\n";
    for (int i = fin - 1; i > 1; i--)
    {
        CHR[++tope] = pila[i];
    }
    CHR[++tope] = CHR[1];
    /* for(int i=1;i<=tope;i++){
        cout<<CHR[i].x<<" "<<CHR[i].y<<"\n";
    }
    cout<<"\n";*/
    red = 0;
    for (int i = 1; i <= n; i++)
    {
        red += dentrorojo(rojo[i]);
    }
    cout << red;
    return 0;
}