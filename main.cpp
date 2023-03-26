#include <iostream>
#include <iomanip>
using namespace std;
/*
class Monetar
{
    double valoare;
    String currency;
};
*/
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
    void operator = (const Data &copie)
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
        if(copie.pointer==nullptr)
        {
            pointer=nullptr;
            dimensiune = 0;
        }
        else
        {
            dimensiune = copie.dimensiune;
            pointer = new char [dimensiune];
            for(i=0;copie.pointer[i]!=NULL;i++)
                pointer[i]=copie.pointer[i];
            pointer[i]=NULL;
        }
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
        if(copie.pointer==NULL)
        {
            pointer=NULL;
        }
        else
        {
        pointer = new char [dimensiune];
        for(i=0;copie.pointer[i]!=NULL;i++)
            pointer[i]=copie.pointer[i];
        pointer[i]=NULL;
        }
    }
    friend ostream & operator << (ostream &out,const String &str);
};
    ostream & operator << (ostream &out,const String &str)
    {
        if(str.pointer==nullptr)
            out<<"";
        else
            out<<str.pointer;
        return out;
    }
class Produs
{
    // DE CREAT O CLASA REDUCERE
    // valoarea din reducere reprezinta de fapt un procentaj
    double pret,reducere; // monetar pret; eventual
    int nr_bucati_stoc;
    String descriere,tara_provenienta,cod_articol,nume;
    // vector_recenzii recenzii;
public:
    Produs()
    {
        String placeholder("placeholder"),vid,cod_articol_default("#000000");
        reducere=0;
        pret=0;
        descriere=placeholder;
        nr_bucati_stoc=0;
        tara_provenienta=vid;
        nume=placeholder;
        cod_articol=cod_articol_default;
    }
    Produs(String n, double p, int s, String c, String t, String d, double r):
        nume(n),pret(p),nr_bucati_stoc(s),cod_articol(c),tara_provenienta(t),descriere(d),reducere(r){};
    Produs(const Produs &copie)
    {
        reducere = copie.reducere;
        pret = copie.pret;
        descriere = copie.descriere;
        nr_bucati_stoc = copie.nr_bucati_stoc;
        tara_provenienta = copie.tara_provenienta;
        nume = copie.nume;
        cod_articol = copie.cod_articol;
    }
    void set_nume(String nume)
    {
        this -> nume = nume;
    }
    void set_cod_articol(String cod_articol)
    {
        this -> cod_articol = cod_articol;
    }
    void set_tara(String tara)
    {
        tara_provenienta = tara;
    }
    void set_descriere(String descriere)
    {
        this -> descriere = descriere;
    }
    void set_stoc(int nr)
    {
        nr_bucati_stoc = nr;
    }
    void set_pret(double pret)
    {
        this -> pret = pret;
    }
    void set_reducere(double reducere)
    {
        this -> reducere = reducere;
    }
    double get_pret()
    {
        return pret;
    }
    double get_reducere()
    {
        return reducere;
    }
    int get_stoc()
    {
        return nr_bucati_stoc;
    }
    String get_nume()
    {
        return nume;
    }
    String get_cod_articol()
    {
        return cod_articol;
    }
    String get_descriere()
    {
        return descriere;
    }
    String get_tara()
    {
        return tara_provenienta;
    }
    //FUNCTIE BUSINESS
    void aplicare_reducere()
    {
        // Reducere este un procentaj
        double rd;
        rd=reducere/100;
        pret=pret-pret*rd;
    }
    void restaurare_pret()
    {
        pret=(100*pret)/reducere;
    }
    void operator=(const Produs &copie)
    {
        reducere = copie.reducere;
        pret = copie.pret;
        descriere = copie.descriere;
        nr_bucati_stoc = copie.nr_bucati_stoc;
        tara_provenienta = copie.tara_provenienta;
        nume = copie.nume;
        cod_articol = copie.cod_articol;
    }
    //int pret_dupa_reducere(double pret,double reducere)
    friend ostream & operator << (ostream &out,const Produs &prd);
};
    ostream & operator << (ostream &out,const Produs &prd)
    {
        out<<"Fisa produsului \""<<prd.nume<<"\""<<endl;
        out<<"Pretul produsului: "<<prd.pret<<" RON"<<endl;
        out<<"Codul articolului: "<<prd.cod_articol<<endl;
        out<<"Numarul de bucati aflate in stoc: "<<prd.nr_bucati_stoc<<endl;
        out<<"Descrierea produsului:"<<endl<<prd.descriere<<endl;
        out<<"Tara de provenienta a produsului este "<<prd.tara_provenienta<<endl;
        out<<"Reducerea valabila pentru acest produs este "<<prd.reducere<<"%"<<endl;
        return out;
    }
class Vector_produse
{
    Produs *lista_produse;
    int dimensiune;
    // stergerea unui produs dupa nume ?
public:
    Vector_produse()
    {
        lista_produse=nullptr;
        dimensiune=0;
    }
    Vector_produse(Produs v[], int d)
    {
        int i;
        lista_produse = new Produs[d];
        dimensiune=d;
        for(i=0;i<d;i++)
            lista_produse[i]=v[i];
    }
    Vector_produse(const Vector_produse &v1)
    {
        int i;
        dimensiune=v1.dimensiune;
        if(v1.lista_produse==nullptr)
        {
            lista_produse=nullptr;
        }
        else
        {
        lista_produse = new Produs[v1.dimensiune];
        for(i=0;i<dimensiune;i++)
            lista_produse[i]=v1.lista_produse[i];
        }
    }
    ~Vector_produse()
    {
        delete [] lista_produse;
    }
    int get_dimensiune()
    {
        return dimensiune;
    }
    Produs * get_lista_produse()
    {
        return lista_produse;
    }
    Produs get_produs(int pozitie)
    {
        pozitie--;
        if(pozitie>=0 && pozitie<dimensiune)
            return lista_produse[pozitie];
        else cout<<"Pozitie invalida";
    }
    void adaugare_produs(Produs &prd)
    {
        Produs *nou_point;
        nou_point= new Produs[dimensiune+1];
        for(int i=0;i<dimensiune;i++)
            nou_point[i]=lista_produse[i];
        nou_point[dimensiune]=prd;
        dimensiune++;
        delete [] lista_produse;
        lista_produse=nou_point;
    }
    void stergere_produs(int poz)
    {
        int i;
        Produs *nou_point;
        nou_point= new Produs[dimensiune-1];
        for(i=0;i<poz-1;i++)
            nou_point[i]=lista_produse[i];
        for(i=poz-1;i<dimensiune-1;i++)
            nou_point[i]=lista_produse[i+1];
        delete [] lista_produse;
        lista_produse=nou_point;
        dimensiune--;
    }
    void operator = (const Vector_produse &v1)
    {
        int i;
        dimensiune=v1.dimensiune;
        if(v1.lista_produse==nullptr)
        {
            lista_produse=nullptr;
        }
        else
        {
        lista_produse = new Produs[v1.dimensiune];
        for(i=0;i<dimensiune;i++)
            lista_produse[i]=v1.lista_produse[i];
        }
    }
    friend ostream & operator << (ostream &out,const Vector_produse &v1);
};
    ostream & operator << (ostream &out,const Vector_produse &v1)
    {
        out<<"Dimensiunea vectorului este "<<v1.dimensiune<<endl;
        out<<"Elementele vectorului sunt:"<<endl;
        if(v1.lista_produse!=nullptr)
        {
            for(int i=0;i<v1.dimensiune-1;i++)
                out<<v1.lista_produse[i].get_nume()<<", ";
            out<<v1.lista_produse[v1.dimensiune-1].get_nume()<<endl;

        }
        else cout<<"";
        return out;
    }
class Cos_cumparaturi
{
    Vector_produse produse_cos;
    double total_cos;
public:
    Cos_cumparaturi()
    {
        Vector_produse nul;
        total_cos=0;
        produse_cos=nul;
    }
    Cos_cumparaturi(Vector_produse &v1)
    {
        double suma=0;
        for(int i=0;i<v1.get_dimensiune();i++)
            suma+=v1.get_lista_produse()[i].get_pret();
        total_cos=suma;
        produse_cos=v1;
    }
    Cos_cumparaturi(const Cos_cumparaturi &cos)
    {
        produse_cos = cos.produse_cos;
        total_cos = cos.total_cos;
    }
    Vector_produse get_produse_cos()
    {
        return produse_cos;
    }
    double get_total_cos()
    {
        return total_cos;
    }
    void adaugare_produs_cos(Produs &prd)
    {
        total_cos=total_cos+prd.get_pret();
        produse_cos.adaugare_produs(prd);
    }
    void stergere_produs_cos(int poz)//pozitia produsului in vectorul produse_cos
    {
        total_cos = total_cos - produse_cos.get_produs(poz).get_pret();
        produse_cos.stergere_produs(poz);
    }
    void operator = (const Cos_cumparaturi &cos)
    {
        produse_cos = cos.produse_cos;
        total_cos = cos.total_cos;
    }
    friend ostream & operator << (ostream &out, Cos_cumparaturi &cos1);
};
    ostream & operator << (ostream &out, Cos_cumparaturi &cos1)
    {
        out<<"Cos:"<<endl;
        out<<"Numarul de produse din cos este: "<<cos1.produse_cos.get_dimensiune()<<endl;
        out<<"Produsele din cos sunt: ";
        if(cos1.produse_cos.get_lista_produse()!=nullptr)
        {
            for(int i=0;i<cos1.produse_cos.get_dimensiune()-1;i++)
                out<<cos1.produse_cos.get_lista_produse()[i].get_nume()<<", ";
            cout<<cos1.produse_cos.get_lista_produse()[cos1.produse_cos.get_dimensiune()-1].get_nume();
        }
        else out<<"";
        out<<endl;
        out<<"Pretul total al produselor din cos este "<<cos1.total_cos<<" RON"<<endl;
        return out;
    }
class Client
{
    String nume,prenume,email,adresa;
    Data data_inregistrare_cont;
    double balanta;
    //clasa conversie balanta
    //ISTORIC COMENZI
    Cos_cumparaturi cos_de_cumparaturi;
public:
    Client()
    {
        String def("guest"),vid;
        Cos_cumparaturi cos_gol;
        nume=def;
        prenume=def;
        email=vid;
        adresa=vid;
        Data d_vid;
        data_inregistrare_cont=d_vid;
        balanta=0;
        cos_de_cumparaturi=cos_gol;
    }
    Client(String n, String p, String e, String a, Data d, double b,Cos_cumparaturi cos):
        nume(n),prenume(p),email(e),adresa(a),data_inregistrare_cont(d),balanta(b),cos_de_cumparaturi(cos){};
    Client(const Client &copie)
    {
        nume = copie.nume;
        prenume = copie.prenume;
        email = copie.email;
        adresa = copie.adresa;
        data_inregistrare_cont = copie.data_inregistrare_cont;
        balanta = copie.balanta;
        cos_de_cumparaturi = copie.cos_de_cumparaturi;
    }
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
    void set_cos_cumparaturi(Cos_cumparaturi cos)
    {
        cos_de_cumparaturi = cos;
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
    Cos_cumparaturi get_cos()
    {
        return cos_de_cumparaturi;
    }
    double get_balanta()
    {
        return balanta;
    }
    void operator = (const Client &copie)
    {
        nume = copie.nume;
        prenume = copie.prenume;
        email = copie.email;
        adresa = copie.adresa;
        data_inregistrare_cont = copie.data_inregistrare_cont;
        balanta = copie.balanta;
        cos_de_cumparaturi = copie.cos_de_cumparaturi;
    }
    // clasa comanda sa poata schimba balanta unui cont
    friend ostream & operator << (ostream &out, Client &cl);
};
    ostream & operator << (ostream &out, Client &cl)
    {
        out<<"Nume: "<<cl.nume<<" "<<endl<<"Prenume: "<<cl.prenume<<endl;
        out<<"Email: "<<cl.email<<endl;
        out<<"Adresa: "<<cl.adresa<<endl;
        out<<"Data inregistrarii contului: "<<cl.data_inregistrare_cont<<endl;
        out<<"Balanta contului: "<<cl.balanta<<" RON"<<endl;
        out<<"Afisarea cosului de cumparaturi al clientului: "<<cl.cos_de_cumparaturi;
        return out;
    }
class Comanda
{
    Client cont_client;
    Vector_produse produse;// cos_de_cumparaturi -> cos_de_cumparaturi ar trebui sa provina din cosul curent al clientului;
    String id_comanda,status,detalii_livrare;
    Data data_plasare_comanda;
    // DE FACUT CLASA VOUHER CU EXPIRARE ETC.
    bool voucher;
    double valoare_voucher;//procentaj
    double pret_total;
    //metoda  : adaugare voucher;
public:
    Comanda()
    {
        Client client0;
        String placeholder("placeholder"),status_initial("?"),id("#00000000"),vid;
        Data data_standard(1,1,2000);
        Vector_produse vector_vid;

        cont_client=client0;
        id_comanda=id;
        status=status_initial;
        voucher=false;
        detalii_livrare=vid;
        data_plasare_comanda=data_standard;
        valoare_voucher=0;

        produse=vector_vid;
        pret_total=0;
    }
    // vectorul produse si pretul sunt luate din cosul curent al cumparatorului
    Comanda(Client c, String id, String s, String d, Data data, bool v, double val_v)
    {
        cont_client = c;
        id_comanda = id;
        status = s;
        detalii_livrare = d;
        voucher = v;
        valoare_voucher = val_v;
        //
        produse = cont_client.get_cos().get_produse_cos();
        pret_total = cont_client.get_cos().get_total_cos();
    }
    Comanda(const Comanda &cmd)
    {
        cont_client = cmd.cont_client;
        produse = cmd.produse;
        id_comanda = cmd.id_comanda;
        status = cmd.status;
        detalii_livrare = cmd.detalii_livrare;
        data_plasare_comanda = cmd.data_plasare_comanda;
        voucher = cmd.voucher;
        valoare_voucher = cmd.valoare_voucher;
        pret_total = cmd.pret_total;
    }
    void set_client(Client client1)
    {
        cont_client = client1;
        produse = client1.get_cos().get_produse_cos();
        pret_total = client1.get_cos().get_total_cos();
    }
    void set_produse(Vector_produse vect_prod)
    {
        //nu ar trebui folosit pe cont propriu, e setat in cont client
        produse = vect_prod;
    }
    void set_id_comanda(String id)
    {
        id_comanda = id;
    }
    void set_status(String status)
    {
        this -> status = status;
    }
    void set_detalii_livrare(String detalii_livrare)
    {
        this -> detalii_livrare = detalii_livrare;
    }
    void set_data_plasare_comanda(Data data)
    {
        data_plasare_comanda = data;
    }
    void set_voucher(bool val)
    {
        voucher = val;
    }
    void set_valoare_voucher(double val)
    {
        valoare_voucher = val;
    }
    void set_pret_total(double pret_total)
    {
        //nu ar trebui folosit pe cont propriu, e setat in cont client
        this -> pret_total = pret_total;
    }
    Client get_client()
    {
        return cont_client;
    }
    Vector_produse get_produse()
    {
        return produse;
    }
    String get_id_comanda()
    {
        return id_comanda;
    }
    String get_status()
    {
        return status;
    }
    String get_detalii_livrare()
    {
        return detalii_livrare;
    }
    Data get_data_plasare_comanda()
    {
        return data_plasare_comanda;
    }
    bool get_voucher()
    {
        return voucher;
    }
    double get_valoare_voucher()
    {
        return valoare_voucher;
    }
    double get_pret_total()
    {
        return pret_total;
    }
    //FUNCTIE BUSINESS
    void aplicare_voucher()
    {
        if(voucher==true)
        {
            // Voucher-ul reprezinta un procentaj
            double vch;
            vch=valoare_voucher/100;
            pret_total=pret_total-pret_total*vch;
        }
        else cout<<"Nu exista niciun voucher disponibil."<<endl;
    }
    void operator = (const Comanda &cmd)
    {
        cont_client = cmd.cont_client;
        produse = cmd.produse;
        id_comanda = cmd.id_comanda;
        status = cmd.status;
        detalii_livrare = cmd.detalii_livrare;
        data_plasare_comanda = cmd.data_plasare_comanda;
        voucher = cmd.voucher;
        valoare_voucher = cmd.valoare_voucher;
        pret_total = cmd.pret_total;
    }
    friend ostream & operator << (ostream &out, Comanda &cmd);
};
    ostream & operator << (ostream &out, Comanda &cmd)
    {
        out<<"Comanda cu id-ul "<<cmd.id_comanda<<" a clientului "<<cmd.cont_client.get_nume()<<" "<<cmd.cont_client.get_prenume()<<":"<<endl;
        out<<"Produse: ";
        if(cmd.produse.get_lista_produse()!=nullptr)
        {
            for(int i=0;i<cmd.produse.get_dimensiune()-1;i++)
                out<<cmd.produse.get_lista_produse()[i].get_nume()<<", ";
            out<<cmd.produse.get_lista_produse()[cmd.produse.get_dimensiune()-1].get_nume();
        }
        else out<<"";
        out<<endl;
        out<<"Data plasarii comenzii: "<<cmd.data_plasare_comanda<<endl;
        out<<"Statusul comenzii este: "<<cmd.status<<endl;
        out<<"Detaliile de livrare ale comenzii: "<<cmd.detalii_livrare<<endl;
        out<<"Total comanda: "<<cmd.pret_total<<" RON";
        if(cmd.voucher==true)
        {
            out<<endl<<"Voucher disponibil: reducere "<<cmd.valoare_voucher<<"% din totalul comenzii."<<endl;
        }
        else out<<endl;
        return out;
    }
void testare();
int main()
{
    testare();
    return 0;
}
void testare()
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

    cout<<"Testare clasa Produs"<<endl;
    Produs produs0,produs2;
    produs0.set_nume("Hrana pentru perusi");
    produs0.set_pret(18.99);
    produs0.set_stoc(120);
    produs0.set_cod_articol("#972538");
    cout<<produs0<<endl;
    Produs produs1("Os de sepie",15,70,"#268432","Africa","Asigura necesarul de minerale si ajuta la intretinerea ciocului.",0);
    cout<<produs1<<endl;
    cout<<"Pretul combinat al produselor este: "<<produs0.get_pret()+produs1.get_pret()<<endl;
    cout<<"Produs0 devine produs1"<<endl;cout<<"Testare clasa Produs"<<endl;
    produs2=produs0;
    produs0=produs1;
    cout<<produs0<<endl;

    cout<<"Testare clasa Vector_produse"<<endl;
    Produs p[]={produs0,produs1},p2[]={produs0};
    Vector_produse v1(p,2),v2(p2,1),v0;
    cout<<v1;
    v1.adaugare_produs(produs2);
    cout<<v1;
    v1.stergere_produs(2);
    cout<<v1;
    cout<<v2;
    v0=v2;
    v2=v1;
    cout<<v2<<endl;

    cout<<"Testare clasa Cos_cumparaturi"<<endl;
    Cos_cumparaturi cos2(v2),cos(v0);
    cout<<cos2;
    cout<<cos;
    cos=cos2;
    cout<<cos;
    Produs produs3("Minge plastic",3.44,160,"#743294","Olanda","O jucarie standard pentru catei.",0);
    cos.adaugare_produs_cos(produs3);
    cout<<cos;
    cos.stergere_produs_cos(1);
    cout<<cos;
    cout<<endl;

    cout<<"Testare clasa Client"<<endl;
    Client client0("Ionescu","Robert","irobert@yahoo.com","Str.Florilor nr.7, Sect.5, bl. Z7",d2,10,cos),client1;
    cout<<client0;
    cout<<client1;
    client1=client0;
    client1.set_prenume("Marius");
    cout<<client1<<endl;

    cout<<"Testare clasa Comanda"<<endl;
    Comanda comanda_test;
    Comanda comanda1(client1,"#28632430","in curs de procesare","",d1,false,0);
    cout<<comanda1<<endl<<comanda_test;
    comanda_test=comanda1;
    cout<<comanda1<<endl;

    cout<<"Testare Functie Business#1"<<endl;
    cout<<produs3.get_nume()<<" are pretul: "<<produs3.get_pret()<<", reducere posibila: "<<produs3.get_reducere()<<endl;
    cout<<"Aplicam o reducere de 50%"<<endl;
    produs3.set_reducere(50);
    produs3.aplicare_reducere();
    cout<<produs3.get_nume()<<" are pretul: "<<produs3.get_pret()<<endl;
    cout<<"Restabilim pretul initial al produsului"<<endl;
    produs3.restaurare_pret();
    cout<<produs3.get_nume()<<" are pretul: "<<produs3.get_pret()<<endl<<endl;

    cout<<"Testare Functie Business#2"<<endl;
    comanda1.set_voucher(true);
    comanda1.set_valoare_voucher(25);
    cout<<comanda1;
    comanda1.aplicare_voucher();
    cout<<"Pretul comenzii precedente a devenit(dupa aplicarea voucher-ului): "<<setprecision(2)<<comanda1.get_pret_total()<<" RON"<<endl;
}
