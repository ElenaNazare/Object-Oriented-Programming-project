#include <iostream>
using namespace std;

class Data
{
    int zi,luna,an;
public:
    Data()
    {
        zi=1;
        luna=1;
        an=2000;
    }
    Data(int zi, int luna, int an)
    {
        this -> zi = zi;
        this -> luna = luna;
        this -> an = an;
    }
    Data(const Data &copie)
    {
        zi = copie.zi;
        luna = copie.luna;
        an = copie.an;
    }
    void set_zi(int zi)
    {
        this -> zi = zi;
    }
    void set_luna(int luna)
    {
        this -> luna = luna;
    }
    void set_an(int an)
    {
        this -> an = an;
    }
    int get_zi()
    {
        return zi;
    }
    int get_luna()
    {
        return luna;
    }
    int get_an()
    {
        return an;
    }
    void operator=(const Data &copie)
    {
        zi = copie.zi;
        luna = copie.luna;
        an = copie.an;
    }
    friend ostream & operator << (ostream &out,const Data &d1);
};
    ostream & operator << (ostream &out,const Data &d1)
    {
        out<<d1.zi;
        out<<"/"<<d1.luna<<"/"<<d1.an;
        return out;
    }

class String
{
    char *pointer;
    int dimensiune;
    // vid si "guest" declarate static
public:
    // concat + adaugare caract
    String()
    {
        pointer=nullptr;
        dimensiune=0;
    }
    String(char a[])
    {
        int n=0,i;
        for(i=0;a[i]!=NULL;i++)
            n++;
        dimensiune=n+1;
        pointer = new char [dimensiune];
        for(i=0;a[i]!=NULL;i++)
            pointer[i]=a[i];
        pointer[i]=NULL;
    }
    String(const String &copie)
    {
        int i;
        dimensiune = copie.dimensiune;
        pointer = new char [dimensiune];
        for(i=0;copie.pointer[i]!=NULL;i++)
            pointer[i]=copie.pointer[i];
        pointer[i]=NULL;
    }
    ~String()
    {
        delete [] pointer;
    }
    int get_dim()
    {
        return dimensiune;
    }
    void operator=(const String &copie)
    {
        delete [] pointer;
        int i;
        dimensiune = copie.dimensiune;
        pointer = new char [dimensiune];
        for(i=0;copie.pointer[i]!=NULL;i++)
            pointer[i]=copie.pointer[i];
        pointer[i]=NULL;
    }
    friend ostream & operator << (ostream &out,const String &d1);
};
    ostream & operator << (ostream &out,const String &d1)
    {
        out<<d1.pointer;
        return out;
    }

class Client
{
    String nume,prenume,email,adresa;
    Data data_inregistrare_cont;
    double balanta;
    //clasa conversie balanta -> pt Alex
    //istoric comenzi
public:
    Client()
    {
        String def("guest"),vid;
        nume=def;
        prenume=def;
        email=vid;
        adresa=vid;
        Data d_vid;
        data_inregistrare_cont=d_vid;
        balanta=0;
    }
    Client(String n, String p, String e, String a, Data d, double b):
        nume(n),prenume(p),email(e),adresa(a),data_inregistrare_cont(d),balanta(b){};
    // constructorul de copiere este redundant pentru conturile clientilor
    void set_nume(String nume)
    {
        this -> nume = nume;
    }
    void set_prenume(String prenume)
    {
        this -> prenume = prenume;
    }
    void set_email(String email)
    {
        this -> email = email;
    }
    void set_adresa(String adresa)
    {
        this -> adresa = adresa;
    }
    void set_data_inr_cont(Data data_inregistrare_cont)
    {
        this -> data_inregistrare_cont = data_inregistrare_cont;
    }
    void set_balanta(double balanta)
    {
        this -> balanta = balanta;
    }
    String get_nume()
    {
        return nume;
    }
    String get_prenume()
    {
        return prenume;
    }
    String get_email()
    {
        return email;
    }
    String get_adresa()
    {
        return adresa;
    }
    Data get_data_inr_cont()
    {
        return data_inregistrare_cont;
    }
    double get_balanta()
    {
        return balanta;
    }
    // clasa comanda sa poata schimba balanta unui cont
    friend ostream & operator << (ostream &out,const Client &cl);
};
    ostream & operator << (ostream &out,const Client &cl)
    {
        out<<"Nume: "<<cl.nume<<" "<<endl<<"Prenume: "<<cl.prenume<<endl;
        out<<"Email: "<<cl.email<<endl;
        out<<"Adresa: "<<cl.adresa<<endl;
        out<<"Data inregistrarii contului: "<<cl.data_inregistrare_cont<<endl;
        out<<"Balanta contului: "<<cl.balanta<<" RON";
        return out;
    }
int main()
{
    cout<<"Testare clasa Data"<<endl;
    Data d1(20,3,2023),d2;
    cout<<d1;
    d2=d1;
    cout<<d2;
    cout<<endl<<endl;

    cout<<"Testare clasa String"<<endl;
    String m("mama"),t;
    cout<<m<<" ";
    t="taran";
    cout<<t<<" ";
    t=m;
    cout<<m<<" "<<m.get_dim();
    cout<<endl<<endl;

    cout<<"Testare clasa Client"<<endl;
    Client client0("Ionescu","Robert","irobert@yahoo.com","Str.Florilor nr.7, Sect.5, bl. Z7",d2,10);
    cout<<client0;
    return 0;
}
