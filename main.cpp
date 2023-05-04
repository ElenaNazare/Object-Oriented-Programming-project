#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <functional>
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

        if(pointer==nullptr)
            throw bad_alloc();

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
        if(pointer!=nullptr)
            delete [] pointer;
    }
    int get_dim()
    {
        return dimensiune;
    }
    void operator=(const String &copie)
    {
        if(pointer!=nullptr)
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
class Vector_produse;
///EXCEPTIE CUSTOM (4)
class Bad_delete : public exception
{
    string mesaj;
public:
    Bad_delete()
    {
        mesaj="";
    }
    Bad_delete(string mesaj)
    {
        this->mesaj = mesaj;
    }
    const char* what()
    {
        return mesaj.c_str();
    }
};
class Bad_init : public exception
{
    string mesaj;
public:
    Bad_init()
    {
        mesaj="";
    }
    Bad_init(string mesaj)
    {
        this->mesaj = mesaj;
    }
    const char* what()
    {
        return mesaj.c_str();
    }
};
class Bad_length : public exception
{
    string mesaj;
public:
    Bad_length()
    {
        mesaj="";
    }
    Bad_length(string mesaj)
    {
        this->mesaj = mesaj;
    }
    const char* what()
    {
        return mesaj.c_str();
    }
};
class Mesaj : public exception
{
    string mesaj;
public:
    Mesaj()
    {
        mesaj="";
    }
    Mesaj(string mesaj)
    {
        this->mesaj = mesaj;
    }
    const char* what()
    {
        return mesaj.c_str();
    }
};
class Interfata
{
public:
    ///MET. VIRT.1 + 2
    virtual double average_pret(Vector_produse *v)=0;
    virtual bool verificare_valabilitate(Data d)=0;
};
///PRIMA IERARHIE || MODIFICATOR 1
///INTERFATA
///CLASA ABSTRACTA || BUNIC DIAMANT
class Produs : public Interfata
{
    // DE CREAT O CLASA REDUCERE
    // valoarea din reducere reprezinta de fapt un procentaj
    string cod_articol;
    // vector_recenzii recenzii;
    ///PROTECTED_DATE
protected:
    double pret,reducere; // monetar pret; eventual
    int nr_bucati_stoc;
    String descriere,tara_provenienta,nume;
    ///PROTECTED_METODA
    ///PRIMUL THROW
    void set_cod_articol(string cod_articol)
    {
        char c;
        c=cod_articol[0];
        if(c!='#')
            throw Bad_init("Codul de articol nu incepe corespunzator.");
        else if(cod_articol.size()!=7)
                throw Bad_length("Codul de articol nu este corespunzator standardului: nu are lungimea = 7 caractere (incluzand #).");
        this -> cod_articol = cod_articol;
    }
public:
    Produs()
    {
        String placeholder("placeholder"),vid;
        string cod_articol_default("#000000");
        reducere=0;
        pret=0;
        descriere=placeholder;
        nr_bucati_stoc=0;
        tara_provenienta=placeholder;
        nume=placeholder;
        cod_articol=cod_articol_default;
    }
    Produs(String nume, double pret, int bucati_stoc, string cod_articol, String tara_provenienta, String descriere, double reducere)
        //nume(n),pret(p),nr_bucati_stoc(s),cod_articol(c),tara_provenienta(t),descriere(d),reducere(r)
    {
        this->nume = nume;
        this->pret = pret;
        nr_bucati_stoc=bucati_stoc;
        if(cod_articol.size()!=7)
            throw Bad_length("Codul de articol nu este corespunzator standardului: nu are destule caractere.");
        this->cod_articol = cod_articol;
        this->tara_provenienta = tara_provenienta;
        this->descriere = descriere;
        this->reducere = reducere;
    };
    ///DESTR. VIRTUAL
    virtual ~Produs()=default;
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
    //am sters setterul pt cod articol
    void set_nume(String nume)
    {
        this -> nume = nume;
    }
    ///CLASA ABSTRACTA
    virtual string categorie_produs()=0;
    ///MET. VIRT.3
    virtual string tip_asistenta()
    {
        return "Intrebari frecvente pe pagina magazinului";
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
    virtual double get_pret()// GET PRET IN FUNCTIE DE REDUCERE< DE SETAT UN PRET DE BAZA
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
    string get_cod_articol()
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
    ///TRATAREA ERORILOR
    ///AL DOILEA THROW
    void schimbare_cod_articol(string str)
    {
        try{
            this->set_cod_articol(str);
        }
        ///CATCH PRIMUL THROW
        catch(Bad_init bi){
            string aux;
            aux.push_back('#');
            for(int i=0;i<str.size();i++)
                aux.push_back(str[i]);
            cerr<<"EROARE: "<<bi.what();
            throw Mesaj(aux);
        }
        catch(Bad_length bl)
        {
            cerr<<"EROARE: "<<bl.what();
            if(str.size()<7)
                throw Mesaj(" sa mai adaugati cifre.");
            else
                throw Mesaj(" sa mai eliminati cifre.");
        }
    }
    ///FUNCTIE BUSINESS
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
    ///MET. VIRT.4
    virtual void afisare()
    {
        cout<<"Fisa produsului \""<<nume<<"\""<<endl;
        cout<<"Pretul produsului: "<<pret<<" RON"<<endl;
        cout<<"Codul articolului: "<<cod_articol<<endl;
        cout<<"Numarul de bucati aflate in stoc: "<<nr_bucati_stoc<<endl;
        cout<<"Descrierea produsului:"<<endl<<descriere<<endl;
        cout<<"Tara de provenienta a produsului este "<<tara_provenienta<<endl;
        cout<<"Reducerea valabila pentru acest produs este "<<reducere<<"%"<<endl;
    }
    //int pret_dupa_reducere(double pret,double reducere)
    friend ostream & operator << (ostream &out,const Produs &prd);
    double average_pret(Vector_produse* q){cout<<"YAY";}
    bool verificare_valabilitate(Data d)=0;
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
class Vector_produse : private vector<Produs*>
{
public:
    using vector<Produs*>::size;
    using vector<Produs*>::operator[];
    using vector<Produs*>::clear;
    using vector<Produs*>::erase;
    using vector<Produs*>::begin;
    using vector<Produs*>::empty;
    ~Vector_produse()
    {
        for(int i=0;i<size();i++)
            delete (*this)[i];
        (*this).clear();
    }
    void adaugare(Produs *p)
    {
        push_back(p);
    }
    ///DESTR. VIRTUAL
    void stergere(Produs *p)
    {
        if((*this).empty())
            throw Bad_delete("Nu se poate sterge din vectorul gol.");
        bool gasit=false;
        for(int i=0;i<size();i++)
            if((*this)[i]->get_cod_articol()==p->get_cod_articol()){
                (*this).erase((*this).begin()+i);
                gasit=true;
            }
        if(!gasit)
            throw Bad_delete("Nu se poate sterge un element ce nu se afla in vector.");
    }
    //nu cred ca folosesc, dar nu sterg acum:
    int dimensiune()
    {
        return (*this).size();
    }
    friend ostream & operator << (ostream &out, Vector_produse &vect);
};
    ostream & operator << (ostream &out, Vector_produse &vect)
    {
        for(int i=0;i<vect.size();i++)
        {
             vect[i]->afisare();
             out<<endl;
        }
        return out;
    }
class Cos_cumparaturi
{
    Vector_produse produse_cos;
    double total_cos;
public:
    ~Cos_cumparaturi()
    {
        //produse_cos.clear();
    }
    Cos_cumparaturi()
    {
        Vector_produse nul;
        total_cos=0;
        produse_cos=nul;
    }
    Cos_cumparaturi(Vector_produse &v1)
    {
        double suma=0;
        for(int i=0;i<v1.size();i++)
            suma+=v1[i]->get_pret();
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
        produse_cos.adaugare(&prd);
    }
    void stergere_produs_cos(int poz)//pozitia produsului in vectorul produse_cos
    {
        total_cos = total_cos - produse_cos[poz]->get_pret();
        produse_cos.erase(produse_cos.begin()+poz);
        //(*this).erase((*this).begin()+i)
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
        out<<"Numarul de produse din cos este: "<<cos1.produse_cos.size()<<endl;
        out<<"Produsele din cos sunt: ";
        if(!cos1.produse_cos.empty())
        {
            for(int i=0;i<cos1.produse_cos.size()-1;i++)
                out<<cos1.produse_cos[i]->get_nume()<<", ";
            cout<<cos1.produse_cos[cos1.produse_cos.size()-1]->get_nume();
        }
        else out<<"";
        out<<endl;
        out<<"Pretul total al produselor din cos este "<<cos1.total_cos<<" RON"<<endl;
        return out;
    }
class Client
{
    ///VAR. STATICA
    static int nr_clienti;
    string id;
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
        nr_clienti++;
        id.push_back('#');
        if(nr_clienti<10)
        {
            id.push_back(48+nr_clienti);
            id.push_back('0');id.push_back('0');
        }
        else if(nr_clienti<100)
        {
            id.push_back(48+(nr_clienti%10));
            id.push_back(48+((nr_clienti/10)%10));id.push_back('0');
        }
        else{id.push_back(48+(nr_clienti%10));id.push_back(48+((nr_clienti/10)%10));id.push_back(48+((nr_clienti/100)%10));}
    }
    Client(String n, String p, String e, String a, Data d, double b,Cos_cumparaturi cos)
    {
        nume=n;
        prenume=p;
        email=e;
        adresa=a;
        data_inregistrare_cont=d;
        balanta=b;
        cos_de_cumparaturi=cos;
        nr_clienti++;
        id.push_back('#');
        if(nr_clienti<10)
        {
            id.push_back(48+nr_clienti);
            id.push_back('0');id.push_back('0');
        }
        else if(nr_clienti<100)
        {
            id.push_back(48+(nr_clienti%10));
            id.push_back(48+((nr_clienti/10)%10));id.push_back('0');
        }
        else{id.push_back(48+(nr_clienti%10));id.push_back(48+((nr_clienti/10)%10));id.push_back(48+((nr_clienti/100)%10));}
    }
    ///METODA STATICA 1
    static Client create_guest(String alias_tmp,Data data_curenta)
    {
        Cos_cumparaturi cos;
        Client g(alias_tmp,"","","",data_curenta,0,cos);
        return g;
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
    ///METODA STATICA 2
    static int get_nr_clienti()
    {
        return nr_clienti;
    }
    string get_id()
    {
        return id;
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
    // clasa comanda sa poata schimba balanta unui cont
    friend ostream & operator << (ostream &out, Client &cl);
};
    ostream & operator << (ostream &out, Client &cl)
    {
        out<<"Nume: "<<cl.nume<<" "<<endl<<"Prenume: "<<cl.prenume<<endl;
        out<<"Id: "<<cl.id<<endl;
        out<<"Email: "<<cl.email<<endl;
        out<<"Adresa: "<<cl.adresa<<endl;
        out<<"Data inregistrarii contului: "<<cl.data_inregistrare_cont<<endl;
        out<<"Balanta contului: "<<cl.balanta<<" RON"<<endl;
        out<<"Afisarea cosului de cumparaturi al clientului: "<<cl.cos_de_cumparaturi;
        return out;
    }
int Client::nr_clienti=0;
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
        if(!cmd.produse.empty())
        {
            for(int i=0;i<cmd.produse.size()-1;i++)
                out<<cmd.produse[i]->get_nume()<<", ";
            out<<cmd.produse[cmd.produse.size()-1]->get_nume();
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
///A DOUA IERARHIE || MODIFICATOR 2
class Vector_clienti : private vector<Client>
{
public:
    using vector<Client>::clear;
    void adaugare(Client c)
    {
        push_back(c);
    }
    void stergere(Client c)
    {
        if((*this).empty())
            throw Bad_delete("Nu se poate sterge din vectorul gol.");
        bool gasit=false;
        for(int i=0;i<size();i++)
            if((*this)[i].get_id()==c.get_id()){
                    (*this).erase((*this).begin()+i);
                    gasit=true;
            }
        if(!gasit)
            throw Bad_delete("Nu se poate sterge un element ce nu se afla in vector.");
    }
    int dimensiune()
    {
        return (*this).size();
    }
    friend ostream & operator << (ostream &out, Vector_clienti &vect);
};
    ostream & operator << (ostream &out, Vector_clienti &vect)
    {
        for(int i=0;i<vect.size();i++)
            out<<vect[i]<<endl;
        return out;
    }
///PRIMA IERARHIE || PARINTE DIAMANT 1
class Hrana : virtual public Produs
{
protected:
    int cantitate_grame;
    string compozitie;
    Data data_expirare;
public:
    Hrana():Produs()
    {
        cantitate_grame=0;
    }
    ///CONSTR. PARAM.
    Hrana(String n, double p, int s, string c, String t, String d, double r,int cant,string comp,Data d_exp):Produs(n,p,s,c,t,d,r)
    {
        cantitate_grame=cant;
        compozitie=comp;
        data_expirare=d_exp;
    }
    ~Hrana()=default;
    void set_cantitate(int cantitate_grame)
    {
        this -> cantitate_grame = cantitate_grame;
    }
    void set_compozitie(string compozitie)
    {
        this->compozitie = compozitie;
    }
    void set_data_expirare(Data data_expirare)
    {
        this->data_expirare = data_expirare;
    }
    Data get_data_expirare()
    {
        return data_expirare;
    }
    string get_compozitie()
    {
        return compozitie;
    }
    int get_cantitate()
    {
        return cantitate_grame;
    }
    string categorie_produs()
    {
        return "Hrana pentru animale";
    }
    string tip_asistenta()
    {
        return "Asistenta online disponibila. In magazine va stau la dispozitie angajatii fiecarui raion.";
    }
    bool verificare_valabilitate(Data d)
    {
        if(data_expirare.get_an()>d.get_an())
            return true;
        else if(data_expirare.get_luna()>d.get_luna())
            return true;
            else if(data_expirare.get_zi()>d.get_zi())
                    return true;
        return false;
    }
    double average_pret(Vector_produse *v)
    {
        int nr_hrana=0;
        int i;
        double suma=0,avg;
        for(i=0;i<v->size();i++)
            if((*v)[i]->categorie_produs()=="Hrana pentru animale"){
                suma+=(*v)[i]->get_pret();
                nr_hrana++;
            }
        avg=suma/nr_hrana;
        return avg;
    }
    void afisare()
    {
        cout<<"Fisa produsului \""<<nume<<"\""<<endl;
        cout<<"Pretul produsului: "<<pret<<" RON"<<endl;
        cout<<"Codul articolului: "<<get_cod_articol()<<endl;
        cout<<"Numarul de bucati aflate in stoc: "<<nr_bucati_stoc<<endl;
        cout<<"Descrierea produsului:"<<endl<<descriere<<endl;
        cout<<"Cantitatea in grame a produsului: "<<cantitate_grame<<endl;
        cout<<"Compozitie: "<<compozitie<<endl;
        cout<<"Data de expirare a produsului: "<<data_expirare<<endl;
        cout<<"Tara de provenienta a produsului este "<<tara_provenienta<<endl;
        cout<<"Reducerea valabila pentru acest produs este "<<reducere<<"%"<<endl;
    }
    friend ostream & operator << (ostream &out, Hrana &prd);
};
    ostream & operator << (ostream &out, Hrana &prd)
    {
        out<<"Fisa produsului \""<<prd.nume<<"\""<<endl;
        out<<"Pretul produsului: "<<prd.pret<<" RON"<<endl;
        out<<"Codul articolului: "<<prd.get_cod_articol()<<endl;
        out<<"Numarul de bucati aflate in stoc: "<<prd.nr_bucati_stoc<<endl;
        out<<"Descrierea produsului:"<<endl<<prd.descriere<<endl;
        out<<"Cantitatea in grame a produsului: "<<prd.cantitate_grame<<endl;
        out<<"Compozitie: "<<prd.compozitie<<endl;
        out<<"Data de expirare a produsului: "<<prd.data_expirare<<endl;
        out<<"Tara de provenienta a produsului este "<<prd.tara_provenienta<<endl;
        out<<"Reducerea valabila pentru acest produs este "<<prd.reducere<<"%"<<endl;
        return out;
    }
class Decoratiuni: public Produs
{
    float lungime,latime,inaltime;
    string materiale;
public:
    Decoratiuni():Produs()
    {
        lungime=latime=inaltime=0;
    }
    Decoratiuni(String n, double p, int s, string c, String t, String d, double r,float lungime,float latime,float inaltime,string materiale):Produs(n,p,s,c,t,d,r)
    {
        this->lungime=lungime;
        this->inaltime=inaltime;
        this->latime=latime;
        this->materiale=materiale;
    }
    ~Decoratiuni()=default;
    void set_lungime(float lungime)
    {
        this->lungime = lungime;
    }
    void set_latime(float latime)
    {
        this->latime = latime;
    }
    void set_inaltime(float inaltime)
    {
        this->inaltime = inaltime;
    }
    void set_materiale(string materiale)
    {
        this->materiale = materiale;
    }
    float get_lungime()
    {
        return lungime;
    }
    float get_latime()
    {
        return latime;
    }
    float get_inaltime()
    {
        return inaltime;
    }
    string get_materiale()
    {
        return materiale;
    }
    string categorie_produs()
    {
        return "Diverse decoratiuni";
    }
    string tip_asistenta()
    {
        return "Asistenta online/in magazine. Anumite decoratiuni beneficiaza de serviciu de montare.";
    }
    bool verificare_valabilitate(Data d)
    {
        return true;
    }
    double average_pret(Vector_produse *v)
    {
        int nr_dec=0;
        int i;
        double suma=0,avg;
        for(i=0;i<v->size();i++)
            if((*v)[i]->categorie_produs()=="Diverse decoratiuni"){
                suma+=(*v)[i]->get_pret();
                nr_dec++;
            }
        avg=suma/nr_dec;
        return avg;
    }
    void afisare()
    {
        cout<<"Fisa produsului \""<<nume<<"\""<<endl;
        cout<<"Pretul produsului: "<<pret<<" RON"<<endl;
        cout<<"Codul articolului: "<<get_cod_articol()<<endl;
        cout<<"Numarul de bucati aflate in stoc: "<<nr_bucati_stoc<<endl;
        cout<<"Descrierea produsului:"<<endl<<descriere<<endl;
        cout<<"Dimensiuni: lungime="<<lungime<<" cm, latime="<<latime<<" cm, inaltime="<<inaltime<<" cm."<<endl;
        cout<<"Materiale: "<<materiale<<endl;
        cout<<"Tara de provenienta a produsului este "<<tara_provenienta<<endl;
        cout<<"Reducerea valabila pentru acest produs este "<<reducere<<"%"<<endl;
    }
    friend ostream & operator << (ostream &out, Decoratiuni &prd);
};
ostream & operator << (ostream &out, Decoratiuni &prd)
    {
        out<<"Fisa produsului \""<<prd.nume<<"\""<<endl;
        out<<"Pretul produsului: "<<prd.pret<<" RON"<<endl;
        out<<"Codul articolului: "<<prd.get_cod_articol()<<endl;
        out<<"Numarul de bucati aflate in stoc: "<<prd.nr_bucati_stoc<<endl;
        out<<"Descrierea produsului:"<<endl<<prd.descriere<<endl;
        out<<"Dimensiuni: lungime="<<prd.lungime<<" cm, latime="<<prd.latime<<" cm, inaltime="<<prd.inaltime<<" cm."<<endl;
        out<<"Materiale: "<<prd.materiale<<endl;
        out<<"Tara de provenienta a produsului este "<<prd.tara_provenienta<<endl;
        out<<"Reducerea valabila pentru acest produs este "<<prd.reducere<<"%"<<endl;
        return out;
    }
///PARINTE DIAMANT 2
class Medicament : virtual public Produs
{
protected:
    string diagnostic;
    Data inceput_tratament;
    Data sfarsit_tratament;
public:
    Medicament():Produs()
    {
        diagnostic="placebo";
    }
    Medicament(String n, double p, int s, string c, String t, String d, double r,string diagnostic,
               Data inceput_tratament,Data sfarsit_tratament):Produs(n,p,s,c,t,d,r)
    {
        this->diagnostic = diagnostic;
        this->inceput_tratament = inceput_tratament;
        this->sfarsit_tratament = sfarsit_tratament;
    }
    ~Medicament()=default;
    void set_diagnostic(string diagnostic)
    {
        this->diagnostic = diagnostic;
    }
    void set_data_inceput_tratament(Data inceput_tratament)
    {
        this->inceput_tratament = inceput_tratament;
    }
    void set_data_sfarsit_tratament(Data sfarsit_tratament)
    {
        this->sfarsit_tratament = sfarsit_tratament;
    }
    string get_diagnostic()
    {
        return diagnostic;
    }
    Data get_data_inceput_tratament()
    {
        return inceput_tratament;
    }
    Data get_data_sfarsit_tratament()
    {
        return sfarsit_tratament;
    }
    string categorie_produs()
    {
        return "Medicament";
    }
    string tip_asistenta()
    {
        return "In magazine va stau la medici veterinari in sectiunea specifica.";
    }
    bool verificare_valabilitate(Data d)
    {
        if(sfarsit_tratament.get_an()>d.get_an())
            return true;
        else if(sfarsit_tratament.get_luna()>d.get_luna())
            return true;
            else if(sfarsit_tratament.get_zi()>d.get_zi())
                    return true;
        return false;
    }
    double average_pret(Vector_produse *v)
    {
        int nr_hrana=0;
        int i;
        double suma=0,avg;
        for(i=0;i<v->size();i++)
            if((*v)[i]->categorie_produs()=="Medicament"){
                suma+=(*v)[i]->get_pret();
                nr_hrana++;
            }
        avg=suma/nr_hrana;
        return avg;
    }
    void afisare()
    {
        cout<<"Fisa produsului \""<<nume<<"\""<<endl;
        cout<<"Pretul produsului: "<<pret<<" RON"<<endl;
        cout<<"Codul articolului: "<<get_cod_articol()<<endl;
        cout<<"Numarul de bucati aflate in stoc: "<<nr_bucati_stoc<<endl;
        cout<<"Descrierea produsului:"<<endl<<descriere<<endl;
        cout<<"Diagnostic: "<<diagnostic<<endl;
        cout<<"Perioada recomandata a tratamentului: "<<inceput_tratament<<" - "<<sfarsit_tratament<<endl;
        cout<<"Tara de provenienta a produsului este "<<tara_provenienta<<endl;
        cout<<"Reducerea valabila pentru acest produs este "<<reducere<<"%"<<endl;
    }
    friend ostream & operator << (ostream &out, Medicament &prd);
};
    ostream & operator << (ostream &out, Medicament &prd)
    {
        out<<"Fisa produsului \""<<prd.nume<<"\""<<endl;
        out<<"Pretul produsului: "<<prd.pret<<" RON"<<endl;
        out<<"Codul articolului: "<<prd.get_cod_articol()<<endl;
        out<<"Numarul de bucati aflate in stoc: "<<prd.nr_bucati_stoc<<endl;
        out<<"Descrierea produsului:"<<endl<<prd.descriere<<endl;
        out<<"Diagnostic: "<<prd.diagnostic<<endl;
        out<<"Perioada recomandata a tratamentului: "<<prd.inceput_tratament<<" - "<<prd.sfarsit_tratament<<endl;
        out<<"Tara de provenienta a produsului este "<<prd.tara_provenienta<<endl;
        out<<"Reducerea valabila pentru acest produs este "<<prd.reducere<<"%"<<endl;
        return out;
    }
///MOSTENIRE MULTIPLA || COPIL DIAMANT
class Hrana_medicala: public Hrana, public Medicament
{
public:
    Hrana_medicala():Produs(),Medicament()
    {
        diagnostic="placebo";
    }
    Hrana_medicala(String n, double p, int s, string c, String t, String d, double r,string diagnostic,
               Data inceput_tratament,Data sfarsit_tratament,int cant,string comp,Data d_exp):Hrana(n,p,s,c,t,d,r,cant,comp,d_exp),Medicament(n,p,s,c,t,d,r,diagnostic,inceput_tratament,sfarsit_tratament)
    {}
    ~Hrana_medicala()=default;
    string categorie_produs()
    {
        return "Hrana cu scop medicinal.";
    }
    string tip_asistenta()
    {
        return "In magazine va stau la medici veterinari in sectiunea specifica.";
    }
    bool verificare_valabilitate(Data d)
    {
        if(data_expirare.get_an()>d.get_an())
            return true;
        else if(data_expirare.get_luna()>d.get_luna())
            return true;
            else if(data_expirare.get_zi()>d.get_zi())
                    return true;
        return false;
    }
    double average_pret(Vector_produse *v)
    {
        int nr_hrana=0;
        int i;
        double suma=0,avg;
        for(i=0;i<v->size();i++)
            if((*v)[i]->categorie_produs()=="Hrana cu scop medicinal."){
                suma+=(*v)[i]->get_pret();
                nr_hrana++;
            }
        avg=suma/nr_hrana;
        return avg;
    }
    void afisare()
    {
        cout<<"Fisa produsului \""<<nume<<"\""<<endl;
        cout<<"Pretul produsului: "<<pret<<" RON"<<endl;
        cout<<"Codul articolului: "<<get_cod_articol()<<endl;
        cout<<"Numarul de bucati aflate in stoc: "<<nr_bucati_stoc<<endl;
        cout<<"Descrierea produsului:"<<endl<<descriere<<endl;
        cout<<"Cantitatea in grame a produsului: "<<cantitate_grame<<endl;
        cout<<"Compozitie: "<<compozitie<<endl;
        cout<<"Data de expirare a produsului: "<<data_expirare<<endl;
        cout<<"Diagnostic: "<<diagnostic<<endl;
        cout<<"Perioada recomandata a tratamentului: "<<inceput_tratament<<" - "<<sfarsit_tratament<<endl;
        cout<<"Tara de provenienta a produsului este "<<tara_provenienta<<endl;
        cout<<"Reducerea valabila pentru acest produs este "<<reducere<<"%"<<endl;
    }
    friend ostream & operator << (ostream &out, Hrana_medicala &prd);
};
    ostream & operator << (ostream &out, Hrana_medicala &prd)
    {
        out<<"Fisa produsului \""<<prd.nume<<"\""<<endl;
        out<<"Pretul produsului: "<<prd.pret<<" RON"<<endl;
        out<<"Codul articolului: "<<prd.get_cod_articol()<<endl;
        out<<"Numarul de bucati aflate in stoc: "<<prd.nr_bucati_stoc<<endl;
        out<<"Descrierea produsului:"<<endl<<prd.descriere<<endl;
        out<<"Cantitatea in grame a produsului: "<<prd.cantitate_grame<<endl;
        out<<"Compozitie: "<<prd.compozitie<<endl;
        out<<"Data de expirare a produsului: "<<prd.data_expirare<<endl;
        out<<"Diagnostic: "<<prd.diagnostic<<endl;
        out<<"Perioada recomandata a tratamentului: "<<prd.inceput_tratament<<" - "<<prd.sfarsit_tratament<<endl;
        out<<"Tara de provenienta a produsului este "<<prd.tara_provenienta<<endl;
        out<<"Reducerea valabila pentru acest produs este "<<prd.reducere<<"%"<<endl;
        return out;
    }

void testare2();
void testare_lambda();
void testare_mostenire_diamant();

///LAMBDA EXPRESIE
void sort_produse_din_vector(Vector_produse *vect, function<bool(Produs*,Produs*)> lambda) {
    int n = vect->size();
    for (int i = 0; i < n-1; i++) {
        bool swapped = false;
        for (int j = 0; j < n-i-1; j++) {
            if (lambda((*vect)[j+1],(*vect)[j])) {
                swap((*vect)[j],(*vect)[j+1]);
                swapped = true;
            }
        }
        if (!swapped) {
            // If no swaps were made, the array is already sorted
            break;
        }
    }
}
int main()
{
    testare2();
    //testare_lambda();
    //testare_mostenire_diamant();
    return 0;
}
void testare_mostenire_diamant()
{
    Hrana_medicala h1;
    cout<<h1;
}
void testare_lambda()
{
    Data d1(5,12,2025),d_curenta(2,5,2023);
    Produs *p1=new Hrana();
    Produs *p2=new Hrana("Stix",17.50,15,"#388894","Turcia","recompensa pentru papagali",0,20,"diverse seminte",d1);
    Produs *p3=new Decoratiuni();
    Vector_produse *p=new Vector_produse;
    p->adaugare(p1);
    p->adaugare(p2);
    p->adaugare(p3);
    cout<<*p<<endl;

    ///LAMBDA
    p3->set_pret(4);
    cout<<"AM UTILIZAT FUNCTIA LAMBDA"<<endl<<endl;
    sort_produse_din_vector(p, [](Produs* a, Produs* b) {
        return a->get_pret() > b->get_pret();
    });
    cout<<*p<<endl<<endl;
}
void testare2()
{
    Data d1(5,12,2025),d_curenta(2,5,2023);
    Produs *p1=new Hrana(); ///UPCASTING
    ///POLIMORFISM
    p1->afisare();

    ///CATCH AL DOILEA THROW
    cout<<endl;
    try{
        p1->schimbare_cod_articol("#54362993");
    }
    catch(Mesaj ms)
    {
        cerr<<"Incercati "<<ms.what()<<endl;
    }
    cout<<endl;
    ///

    p1->afisare();
    ///BLOC TRY
    try{
        Produs *p2=new Hrana("Stix",17.50,15,"#388894","Turcia","recompensa pentru papagali",0,20,"diverse seminte",d1);///UPCASTING

        ///POLIMORFISM
        cout<<endl<<"Verificare valabilitate:\n"<<p2->verificare_valabilitate(d_curenta)<<endl<<endl;
        Produs *p3=new Decoratiuni();///UPCASTING
        cout<<"Decoratiune: "<<endl;
        cout<<*p3;
        cout<<endl<<"     Vectorul de produse"<<endl<<endl;
        Vector_produse *p=new Vector_produse;
        p->adaugare(p1);
        p->adaugare(p2);///UPCASTING
        p->adaugare(p3);
        cout<<*p<<endl;

        ///POLIMORFISM
        int nr_hrana=0;
        int nr_decoratiuni=0;
        for(int i=0;i<p->size();i++)
            if((*p)[i]->categorie_produs()=="Hrana pentru animale")///HERE
                nr_hrana++;
            else {
                ///DYNAMIC_CAST
                Decoratiuni* tmp=dynamic_cast<Decoratiuni*>((*p)[i]);
                if(tmp){
                    nr_decoratiuni++;
                }
            }
        cout<<"Nr articole de tip hrana din vector: "<<nr_hrana<<endl;
        cout<<"Nr decoratiuni: "<<nr_decoratiuni<<endl;

        ///POLIMORFISM
        cout<<"PRET:"<<p2->average_pret(p)<<endl;

        //TESTARE ERORI
        Hrana p5;
        try{
            p->stergere(&p5);
        }
        catch(Bad_delete e1){
            cerr<<"EROARE: "<<e1.what()<<endl;
        }
        cout<<endl<<"Testare clasa Cos_cumparaturi"<<endl;
        Cos_cumparaturi cos(*p);
        cout<<cos;
    ///TRATARE
    }
    catch(bad_alloc bd){
        cerr<<"EROARE: Nu exista spatiu suficient disponibil."<<bd.what()<<endl;
    }
    catch(Bad_length bl){
        cerr<<"EROARE: "<<bl.what()<<endl;
    }
    //CLIENTI
    cout<<endl<<"Nr clienti: "<<Client::get_nr_clienti()<<endl;
    ///TESTARE METODA 1 STATICA
    Client g=Client::create_guest("guest14",d_curenta);
    cout<<g;
    cout<<"Nr clienti: "<<Client::get_nr_clienti();

}
