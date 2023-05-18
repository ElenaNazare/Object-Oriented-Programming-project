#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <vector>
#include <cstring>
#include <functional>
#include <algorithm>
#include <memory>
using namespace std;
/*
class Monetar
{
    double valoare;
    String currency;
};
*/

/// SMART POINTERS || REFERENCE_WRAPPER
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
    Data(const reference_wrapper<Data> copie)
    {
        zi = copie.get().zi;
        luna = copie.get().luna;
        an = copie.get().an;
    }
    void set_zi(const int zi)
    {
        this -> zi = zi;
    }
    void set_luna(const int luna)
    {
        this -> luna = luna;
    }
    void set_an(const int an)
    {
        this -> an = an;
    }
    int get_zi()const
    {
        return zi;
    }
    int get_luna()const
    {
        return luna;
    }
    int get_an()const
    {
        return an;
    }
    void operator = (const reference_wrapper<Data> copie)
    {
        zi = copie.get().zi;
        luna = copie.get().luna;
        an = copie.get().an;
    }
    void afisare()const
    {
        cout<<this->zi<<"/"<<this->luna<<"/"<<this->an;
    }
    friend ostream & operator << (ostream &out,const reference_wrapper<Data> d1);
};
    ostream & operator << (ostream &out,const reference_wrapper<Data> d1)
    {
        out<<d1.get().zi;
        out<<"/"<<d1.get().luna<<"/"<<d1.get().an;
        return out;
    }
template <typename T> class Vector_diverse;
class Produs;
//EXCEPTII
class Bad_delete : public exception
{
    string mesaj;
public:
    Bad_delete()
    {
        mesaj="";
    }
    Bad_delete(const string &mesaj)
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
    Bad_init(const string &mesaj)
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
    Bad_length(const string &mesaj)
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
    Mesaj(const string &mesaj)
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

    virtual double average_pret(const Vector_diverse<shared_ptr<Produs>> *v)const=0 ;
    virtual bool verificare_valabilitate(const Data d)const=0;
};
///
class Produs : public Interfata
{
    // idee: clasa reducere; valoarea din reducere reprezinta de fapt un procentaj
    // vector_recenzii recenzii;
    string cod_articol;
protected:
    double pret,reducere; // monetar pret; eventual
    int nr_bucati_stoc;
    string descriere,tara_provenienta,nume;
    void set_cod_articol(const string &cod_articol)
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
        string placeholder("placeholder");
        string cod_articol_default("#000000");
        reducere=0;
        pret=0;
        nr_bucati_stoc=0;
        descriere=placeholder;
        tara_provenienta=placeholder;
        nume=placeholder;
        cod_articol=cod_articol_default;
    }
    Produs(string nume, double pret, int bucati_stoc, string cod_articol, string tara_provenienta, string descriere, double reducere)
        //nume(n),pret(p),nr_bucati_stoc(s),cod_articol(c),tara_provenienta(t),descriere(d),reducere(r)
    {
        this->nume = nume;
        this->pret = pret;
        nr_bucati_stoc = bucati_stoc;
        if(cod_articol.size()!=7)
            throw Bad_length("Codul de articol nu este corespunzator standardului: nu are destule caractere.");
        this->cod_articol = cod_articol;
        this->tara_provenienta = tara_provenienta;
        this->descriere = descriere;
        this->reducere = reducere;
    };
    virtual ~Produs()=default;
    void set_nume(const string &nume)
    {
        this -> nume = nume;
    }
    virtual string categorie_produs()const=0;
    virtual string tip_asistenta()const
    {
        return "Intrebari frecvente pe pagina magazinului";
    }
    void set_tara(const string &tara)
    {
        this -> tara_provenienta = tara;
    }
    void set_descriere(const string &descriere)
    {
        this -> descriere = descriere;
    }
    void set_stoc(const int nr)
    {
        this -> nr_bucati_stoc = nr;
    }
    void set_pret(const double pret)
    {
        this -> pret = pret;
    }
    void set_reducere(const double reducere)
    {
        this -> reducere = reducere;
    }
    virtual double get_pret()const// GET PRET IN FUNCTIE DE REDUCERE< DE SETAT UN PRET DE BAZA
    {
        return pret;
    }
    double get_reducere()const
    {
        return reducere;
    }
    int get_stoc()const
    {
        return nr_bucati_stoc;
    }
    string get_nume()const
    {
        return nume;
    }
    string get_cod_articol()const
    {
        return cod_articol;
    }
    string get_descriere()const
    {
        return descriere;
    }
    string get_tara()const
    {
        return tara_provenienta;
    }
    //TRATAREA ERORILOR
    //AL DOILEA THROW
    void schimbare_cod_articol(const string str)
    {
        try{
            this->set_cod_articol(str);
        }
        //CATCH PRIMUL THROW
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
    virtual void afisare()const
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
    double average_pret(const Vector_diverse<shared_ptr<Produs>> * q)const{}
    bool verificare_valabilitate(const Data d)const=0;
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

///FUCTIE SABLON
template <typename D> void afisare_vector(D var)
{
     for(int i=0;i<var->size();i++)
        {
             (*var)[i]->afisare();
             cout<<endl;
        }
}
///SPECIALIZARE EXPLICITA
template <> void afisare_vector(int var)
{
    cout<<"Atentionare: functia apelata ar trebui folosita doar pentru vectori de date.\n";
    cout<<var<<endl;
}
template <> void afisare_vector(double var)
{
    cout<<"Atentionare: functia apelata ar trebui folosita doar pentru vectori de date.\n";
    cout<<var<<endl;
}
template <> void afisare_vector(float var)
{
    cout<<"Atentionare: functia apelata ar trebui folosita doar pentru vectori de date.\n";
    cout<<var<<endl;
}

class Client;
///FUNCTIE SABLON
template <typename S,typename T> void stergere_din_vector(S vect,T elem)
{
    if((*vect).empty())
                throw Bad_delete("Nu se poate sterge din vectorul gol.");
            bool gasit=false;
            for(int i=0;i<vect->size();i++)
                if((*vect)[i]->get_cod_articol()==elem->get_cod_articol()){
                    (*vect).erase((*vect).begin()+i);
                    gasit=true;
                }
            if(!gasit)
                throw Bad_delete("Nu se poate sterge un element ce nu se afla in vector.");
}
///CLASA SABLON
template <typename T>
class Vector_diverse : private vector<T>
{
public:
    using vector<T>::size;
    using vector<T>::operator[];
    using vector<T>::clear;
    using vector<T>::erase;
    using vector<T>::begin;
    using vector<T>::empty;
    using vector<T>::end;

    void adaugare(T p)
    {
        this->push_back(p);
    }
    void stergere(T p)
    {
        stergere_din_vector(this,p);
        /*
        if (is_base_of<shared_ptr<Produs>, T>::value) {
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
        */
    }
    /*
    void afisare()
    {
        for(int i=0;i<this->size();i++)
        {
             (*this)[i]->afisare();
             cout<<endl;
        }
    }
    */
};
class Cos_cumparaturi
{
    Vector_diverse<shared_ptr<Produs>> produse_cos;
    double total_cos;
public:
    ~Cos_cumparaturi()
    {
        produse_cos.clear();
    }
    Cos_cumparaturi()
    {
        total_cos=0;
    }
    Cos_cumparaturi(Vector_diverse<shared_ptr<Produs>> &v1)
    {
        double suma=0;
        for(int i=0;i<v1.size();i++)
            suma+=v1[i]->get_pret();
        total_cos=suma;
        produse_cos=v1;
    }
    Vector_diverse<shared_ptr<Produs>> get_produse_cos()const
    {
        return produse_cos;
    }
    double get_total_cos()const
    {
        return total_cos;
    }
    ///sa primesc un shared pointer ca parametru
    void adaugare_produs_cos(Produs &prd)
    {
        total_cos=total_cos+prd.get_pret();
        //modificare aici ca sa pot folosi shared_ptr
        shared_ptr<Produs> ptr_temp = shared_ptr<Produs>(&prd);
        produse_cos.adaugare(ptr_temp);
    }
    void stergere_produs_cos(int poz)//pozitia produsului in vectorul produse_cos
    {
        total_cos = total_cos - produse_cos[poz]->get_pret();
        produse_cos.erase(produse_cos.begin()+poz);
        //(*this).erase((*this).begin()+i)
    }
    friend ostream & operator << (ostream &out,const Cos_cumparaturi &cos1);
};
    ostream & operator << (ostream &out,const Cos_cumparaturi &cos1)
    {
        out<<"Cos:"<<endl;
        out<<"Numarul de produse din cos este: "<<cos1.produse_cos.size()<<endl;
        out<<"Produsele din cos sunt: ";
        if(!cos1.produse_cos.empty())
        {
            for(int i=0;i<cos1.produse_cos.size()-1;i++)
                out<<cos1.produse_cos[i]->get_nume()<<", ";
            out<<cos1.produse_cos[cos1.produse_cos.size()-1]->get_nume();
        }
        else out<<"";
        out<<endl;
        out<<"Pretul total al produselor din cos este "<<cos1.total_cos<<" RON"<<endl;
        return out;
    }
class Client
{
    static int nr_clienti;
    string id,nume,prenume,email,adresa;
    Data data_inregistrare_cont;
    double balanta;
    //clasa conversie balanta
    //istoric comenzi
    Cos_cumparaturi cos_de_cumparaturi;
public:
    Client()
    {
        string def("guest");
        Cos_cumparaturi cos_gol;
        nume=def;
        prenume="";
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
    Client(string n, string p, string e, string a, Data d, double b,Cos_cumparaturi cos)
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
    ///DESIGN PATTERN 1 || "STATIC FACTORY METHOD"
    static Client create_guest(string alias_tmp,Data data_curenta)
    {
        Cos_cumparaturi cos;
        Client g(alias_tmp,"","","",data_curenta,0,cos);
        return g;
    }
    void set_nume(const string &nume)
    {
        this -> nume = nume;
    }
    void set_prenume(const string &prenume)
    {
        this -> prenume = prenume;
    }
    void set_email(const string &email)
    {
        this -> email = email;
    }
    void set_adresa(const string &adresa)
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
    static int get_nr_clienti()
    {
        return nr_clienti;
    }
    string get_id()const
    {
        return id;
    }
    string get_nume()const
    {
        return nume;
    }
    string get_prenume()const
    {
        return prenume;
    }
    string get_email()const
    {
        return email;
    }
    string get_adresa()const
    {
        return adresa;
    }
    Data get_data_inr_cont()const
    {
        return data_inregistrare_cont;
    }
    Cos_cumparaturi get_cos()const
    {
        return cos_de_cumparaturi;
    }
    double get_balanta()const
    {
        return balanta;
    }
    // clasa comanda sa poata schimba balanta unui cont
    friend ostream & operator << (ostream &out,const Client &cl);
};
    ostream & operator << (ostream &out,const Client &cl)
    {
        out<<"Nume: "<<cl.nume<<" "<<endl<<"Prenume: "<<cl.prenume<<endl;
        out<<"Id: "<<cl.id<<endl;
        out<<"Email: "<<cl.email<<endl;
        out<<"Adresa: "<<cl.adresa<<endl;
        out<<"Data inregistrarii contului: ";
        cl.data_inregistrare_cont.afisare();
        cout<<endl;
        out<<"Balanta contului: "<<cl.balanta<<" RON"<<endl;
        ///HELP3 - de ce nu mai afiseaza
        out<<"Afisarea cosului de cumparaturi al clientului: "<<cl.cos_de_cumparaturi;
        return out;
    }
int Client::nr_clienti=0;
///SPECIALIZARE EXPLICITA
template <typename S> void stergere_din_vector(S vect,Client elem)
{
    if((*vect).empty())
            throw Bad_delete("Nu se poate sterge din vectorul gol.");
        bool gasit=false;
        for(int i=0;i<vect->size();i++)
            if((*vect)[i].get_id()==elem.get_id()){
                    (*vect).erase((*vect).begin()+i);
                    gasit=true;
            }
        if(!gasit)
            throw Bad_delete("Nu se poate sterge un element ce nu se afla in vector.");
}


class Comanda;

///DESIGN PATTERN 2 || SINGLETON

class Stocare_date
{
    Vector_diverse<Comanda*> comenzile_magazinului;
    Stocare_date(){}
    //privat constructorul de copiere
    Stocare_date(Stocare_date &s)
    {
        comenzile_magazinului = s.comenzile_magazinului;
    }
    void operator=(const Stocare_date & s)
    {
        comenzile_magazinului = s.comenzile_magazinului;
    }
public:
    void adaugare_comanda(Comanda * c)
    {
        comenzile_magazinului.adaugare(c);
    }
    void afisare()const
    {
        afisare_vector(&comenzile_magazinului);
    }
    void stergere_din_vectorul_comenzi(Comanda *c);
    static Stocare_date & get_instanta()
    {
        static Stocare_date s;
        return s;
    }
};
Stocare_date &stoc = Stocare_date::get_instanta();

class Comanda
{
    Client cont_client;
    Vector_diverse<shared_ptr<Produs>> produse;// cos_de_cumparaturi -> cos_de_cumparaturi ar trebui sa provina din cosul curent al clientului;
    string id_comanda,status,detalii_livrare;
    Data data_plasare_comanda;
    bool voucher;
    double valoare_voucher;//procentaj
    double pret_total;
    //metoda  : adaugare voucher;
public:
    Comanda()
    {
        Client client0;
        string placeholder("placeholder"),status_initial("?"),id("#00000000");
        Data data_standard(1,1,2000);
        Vector_diverse<shared_ptr<Produs>> vector_vid;

        cont_client=client0;
        id_comanda=id;
        status=status_initial;
        voucher=false;
        data_plasare_comanda=data_standard;
        valoare_voucher=0;

        produse=vector_vid;
        pret_total=0;

        stoc.adaugare_comanda(this);
    }
    // vectorul produse si pretul sunt luate din cosul curent al cumparatorului
    Comanda(Client c, string id, string s, string d, Data data, bool v, double val_v)
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

        stoc.adaugare_comanda(this);
    }
    Comanda(Comanda& comanda)=delete;
    void operator=(const Comanda& comanda)=delete;
    ~Comanda()
    {
        stoc.stergere_din_vectorul_comenzi(this);
    }
    void set_client(const Client client1)
    {
        cont_client = client1;
        produse = client1.get_cos().get_produse_cos();
        pret_total = client1.get_cos().get_total_cos();
    }
    void set_produse(const Vector_diverse<shared_ptr<Produs>> vect_prod)
    {
        //nu ar trebui folosit pe cont propriu, e setat in cont client
        produse = vect_prod;
    }
    void set_id_comanda(const string &id)
    {
        id_comanda = id;
    }
    void set_status(const string &status)
    {
        this -> status = status;
    }
    void set_detalii_livrare(const string& detalii_livrare)
    {
        this -> detalii_livrare = detalii_livrare;
    }
    void set_data_plasare_comanda(const Data data)
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
    Client get_client()const
    {
        return cont_client;
    }
    Vector_diverse<shared_ptr<Produs>> get_produse()const
    {
        return produse;
    }
    string get_id_comanda()const
    {
        return id_comanda;
    }
    string get_status()const
    {
        return status;
    }
    string get_detalii_livrare()const
    {
        return detalii_livrare;
    }
    Data get_data_plasare_comanda()const
    {
        return data_plasare_comanda;
    }
    bool get_voucher()const
    {
        return voucher;
    }
    double get_valoare_voucher()const
    {
        return valoare_voucher;
    }
    double get_pret_total()const
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
    void afisare()const
    {
        cout<<"Comanda cu id-ul "<<this->id_comanda<<" a clientului "<<this->cont_client.get_nume()<<" "<<this->cont_client.get_prenume()<<":"<<endl;
        cout<<"Produse: ";
        if(!this->produse.empty())
        {
            for(int i=0;i<this->produse.size()-1;i++)
                cout<<this->produse[i]->get_nume()<<", ";
            cout<<this->produse[this->produse.size()-1]->get_nume();
        }
        else cout<<"";
        cout<<endl;
        cout<<"Data plasarii comenzii: ";
        this->data_plasare_comanda.afisare();
        cout<<endl;
        cout<<"Statusul comenzii este: "<<this->status<<endl;
        cout<<"Detaliile de livrare ale comenzii: "<<this->detalii_livrare<<endl;
        cout<<"Total comanda: "<<this->pret_total<<" RON";
        if(this->voucher==true)
        {
            cout<<endl<<"Voucher disponibil: reducere "<<this->valoare_voucher<<"% din totalul comenzii."<<endl;
        }
        else cout<<endl;
    }
    friend ostream & operator << (ostream &out,const Comanda &cmd);
};
    ostream & operator << (ostream &out,const Comanda &cmd)
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
        out<<"Data plasarii comenzii: ";
        cmd.data_plasare_comanda.afisare();
        out<<endl;
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

    void Stocare_date:: stergere_din_vectorul_comenzi(Comanda *c)
    {
        if(comenzile_magazinului.empty())
            throw Bad_delete("Nu se poate sterge din vectorul gol.");
        bool gasit=false;
        for(int i=0;i<comenzile_magazinului.size();i++)
            if(comenzile_magazinului[i]->get_id_comanda()==c->get_id_comanda()){
                    comenzile_magazinului.erase(comenzile_magazinului.begin()+i);
                    gasit=true;
            }
    }

///Poate fi Vector_diverse<Client*>
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
    int dimensiune()const
    {
        return (*this).size();
    }
    friend ostream & operator << (ostream &out,const Vector_clienti &vect);
};
    ostream & operator << (ostream &out,const Vector_clienti &vect)
    {
        for(int i=0;i<vect.size();i++)
            out<<vect[i]<<endl;
        return out;
    }
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
    Hrana(string n, double p, int s, string c, string t, string d, double r,int cant,string comp,Data d_exp):Produs(n,p,s,c,t,d,r)
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
    void set_compozitie(const string &compozitie)
    {
        this->compozitie = compozitie;
    }
    void set_data_expirare(const Data data_expirare)
    {
        this->data_expirare = data_expirare;
    }
    Data get_data_expirare()const
    {
        return data_expirare;
    }
    string get_compozitie()const
    {
        return compozitie;
    }
    int get_cantitate()const
    {
        return cantitate_grame;
    }
    string categorie_produs()const
    {
        return "Hrana pentru animale";
    }
    string tip_asistenta()const
    {
        return "Asistenta online disponibila. In magazine va stau la dispozitie angajatii fiecarui raion.";
    }
    bool verificare_valabilitate(const Data d)const
    {
        if(data_expirare.get_an()>d.get_an())
            return true;
        else if(data_expirare.get_luna()>d.get_luna())
            return true;
            else if(data_expirare.get_zi()>d.get_zi())
                    return true;
        return false;
    }
    double average_pret(const Vector_diverse<shared_ptr<Produs>> *v)const
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
    void afisare()const
    {
        cout<<"Fisa produsului \""<<nume<<"\""<<endl;
        cout<<"Pretul produsului: "<<pret<<" RON"<<endl;
        cout<<"Codul articolului: "<<get_cod_articol()<<endl;
        cout<<"Numarul de bucati aflate in stoc: "<<nr_bucati_stoc<<endl;
        cout<<"Descrierea produsului:"<<endl<<descriere<<endl;
        cout<<"Cantitatea in grame a produsului: "<<cantitate_grame<<endl;
        cout<<"Compozitie: "<<compozitie<<endl;
        cout<<"Data de expirare a produsului: ";
        data_expirare.afisare();
        cout<<endl;
        cout<<"Tara de provenienta a produsului este "<<tara_provenienta<<endl;
        cout<<"Reducerea valabila pentru acest produs este "<<reducere<<"%"<<endl;
    }
    friend ostream & operator << (ostream &out,const Hrana &prd);
};
    ostream & operator << (ostream &out,const Hrana &prd)
    {
        out<<"Fisa produsului \""<<prd.nume<<"\""<<endl;
        out<<"Pretul produsului: "<<prd.pret<<" RON"<<endl;
        out<<"Codul articolului: "<<prd.get_cod_articol()<<endl;
        out<<"Numarul de bucati aflate in stoc: "<<prd.nr_bucati_stoc<<endl;
        out<<"Descrierea produsului:"<<endl<<prd.descriere<<endl;
        out<<"Cantitatea in grame a produsului: "<<prd.cantitate_grame<<endl;
        out<<"Compozitie: "<<prd.compozitie<<endl;
        out<<"Data de expirare a produsului: ";
        prd.data_expirare.afisare();
        out<<endl;
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
    Decoratiuni(string n, double p, int s, string c, string t, string d, double r,float lungime,float latime,float inaltime,string materiale):Produs(n,p,s,c,t,d,r)
    {
        this->lungime=lungime;
        this->inaltime=inaltime;
        this->latime=latime;
        this->materiale=materiale;
    }
    ///AICI HELP2
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
    void set_materiale(const string &materiale)
    {
        this->materiale = materiale;
    }
    float get_lungime()const
    {
        return lungime;
    }
    float get_latime()const
    {
        return latime;
    }
    float get_inaltime() const
    {
        return inaltime;
    }
    string get_materiale()const
    {
        return materiale;
    }
    string categorie_produs()const
    {
        return "Diverse decoratiuni";
    }
    string tip_asistenta()const
    {
        return "Asistenta online/in magazine. Anumite decoratiuni beneficiaza de serviciu de montare.";
    }
    bool verificare_valabilitate(const Data d)const
    {
        return true;
    }
    double average_pret(const Vector_diverse<shared_ptr<Produs>> *v)const
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
    void afisare()const
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
    friend ostream & operator << (ostream &out,const Decoratiuni &prd);
};
ostream & operator << (ostream &out,const Decoratiuni &prd)
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
    Medicament(string n, double p, int s, string c, string t, string d, double r,string diagnostic,
               Data inceput_tratament,Data sfarsit_tratament):Produs(n,p,s,c,t,d,r)
    {
        this->diagnostic = diagnostic;
        this->inceput_tratament = inceput_tratament;
        this->sfarsit_tratament = sfarsit_tratament;
    }
    ~Medicament()=default;
    void set_diagnostic(const string &diagnostic)
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
    string get_diagnostic()const
    {
        return diagnostic;
    }
    Data get_data_inceput_tratament()const
    {
        return inceput_tratament;
    }
    Data get_data_sfarsit_tratament()const
    {
        return sfarsit_tratament;
    }
    string categorie_produs()const
    {
        return "Medicament";
    }
    string tip_asistenta()const
    {
        return "In magazine va stau la medici veterinari in sectiunea specifica.";
    }
    bool verificare_valabilitate(const Data d)const
    {
        if(sfarsit_tratament.get_an()>d.get_an())
            return true;
        else if(sfarsit_tratament.get_luna()>d.get_luna())
            return true;
            else if(sfarsit_tratament.get_zi()>d.get_zi())
                    return true;
        return false;
    }
    double average_pret(const Vector_diverse<shared_ptr<Produs>> *v)const
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
    void afisare()const
    {
        cout<<"Fisa produsului \""<<nume<<"\""<<endl;
        cout<<"Pretul produsului: "<<pret<<" RON"<<endl;
        cout<<"Codul articolului: "<<get_cod_articol()<<endl;
        cout<<"Numarul de bucati aflate in stoc: "<<nr_bucati_stoc<<endl;
        cout<<"Descrierea produsului:"<<endl<<descriere<<endl;
        cout<<"Diagnostic: "<<diagnostic<<endl;
        cout<<"Perioada recomandata a tratamentului: ";
        inceput_tratament.afisare();
        cout<<" - ";
        sfarsit_tratament.afisare();
        cout<<endl;
        cout<<"Tara de provenienta a produsului este "<<tara_provenienta<<endl;
        cout<<"Reducerea valabila pentru acest produs este "<<reducere<<"%"<<endl;
    }
    friend ostream & operator << (ostream &out,const Medicament &prd);
};
///question
/*
    ostream & operator << (ostream &out,const Medicament &prd)
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
*/
    ostream & operator << (ostream &out,const Medicament &prd)
    {
        out<<"Fisa produsului \""<<prd.nume<<"\""<<endl;
        out<<"Pretul produsului: "<<prd.pret<<" RON"<<endl;
        out<<"Codul articolului: "<<prd.get_cod_articol()<<endl;
        out<<"Numarul de bucati aflate in stoc: "<<prd.nr_bucati_stoc<<endl;
        out<<"Descrierea produsului:"<<endl<<prd.descriere<<endl;
        out<<"Diagnostic: "<<prd.diagnostic<<endl;
        out<<"Perioada recomandata a tratamentului: ";
        prd.inceput_tratament.afisare();
        out<<" - ";
        prd.sfarsit_tratament.afisare();
        out<<endl;
        out<<"Tara de provenienta a produsului este "<<prd.tara_provenienta<<endl;
        out<<"Reducerea valabila pentru acest produs este "<<prd.reducere<<"%"<<endl;
        return out;
    }
class Hrana_medicala: public Hrana, public Medicament
{
public:
    Hrana_medicala():Produs(),Medicament()
    {
        diagnostic="placebo";
    }
    Hrana_medicala(string n, double p, int s, string c, string t, string d, double r,string diagnostic,
               Data inceput_tratament,Data sfarsit_tratament,int cant,string comp,Data d_exp):Hrana(n,p,s,c,t,d,r,cant,comp,d_exp),Medicament(n,p,s,c,t,d,r,diagnostic,inceput_tratament,sfarsit_tratament)
    {}
    ~Hrana_medicala()=default;
    string categorie_produs()const
    {
        return "Hrana cu scop medicinal.";
    }
    string tip_asistenta()const
    {
        return "In magazine va stau la medici veterinari in sectiunea specifica.";
    }
    bool verificare_valabilitate(const Data d)const
    {
        if(data_expirare.get_an()>d.get_an())
            return true;
        else if(data_expirare.get_luna()>d.get_luna())
            return true;
            else if(data_expirare.get_zi()>d.get_zi())
                    return true;
        return false;
    }
    double average_pret(const Vector_diverse<shared_ptr<Produs>> *v)const
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
    void afisare()const
    {
        cout<<"Fisa produsului \""<<nume<<"\""<<endl;
        cout<<"Pretul produsului: "<<pret<<" RON"<<endl;
        cout<<"Codul articolului: "<<get_cod_articol()<<endl;
        cout<<"Numarul de bucati aflate in stoc: "<<nr_bucati_stoc<<endl;
        cout<<"Descrierea produsului:"<<endl<<descriere<<endl;
        cout<<"Cantitatea in grame a produsului: "<<cantitate_grame<<endl;
        cout<<"Compozitie: "<<compozitie<<endl;
        cout<<"Data de expirare a produsului: ";
        data_expirare.afisare();
        cout<<endl;
        cout<<"Diagnostic: "<<diagnostic<<endl;
        cout<<"Perioada recomandata a tratamentului: ";
        inceput_tratament.afisare();
        cout<<" - ";
        sfarsit_tratament.afisare();
        cout<<endl;
        cout<<"Tara de provenienta a produsului este "<<tara_provenienta<<endl;
        cout<<"Reducerea valabila pentru acest produs este "<<reducere<<"%"<<endl;
    }
    friend ostream & operator << (ostream &out,const Hrana_medicala &prd);
};
    ostream & operator << (ostream &out,const Hrana_medicala &prd)
    {
        out<<"Fisa produsului \""<<prd.nume<<"\""<<endl;
        out<<"Pretul produsului: "<<prd.pret<<" RON"<<endl;
        out<<"Codul articolului: "<<prd.get_cod_articol()<<endl;
        out<<"Numarul de bucati aflate in stoc: "<<prd.nr_bucati_stoc<<endl;
        out<<"Descrierea produsului:"<<endl<<prd.descriere<<endl;
        out<<"Cantitatea in grame a produsului: "<<prd.cantitate_grame<<endl;
        out<<"Compozitie: "<<prd.compozitie<<endl;
        out<<"Data de expirare a produsului: ";
        prd.data_expirare.afisare();
        out<<endl;
        out<<"Diagnostic: "<<prd.diagnostic<<endl;
        out<<"Perioada recomandata a tratamentului: ";
        prd.inceput_tratament.afisare();
        out<<" - ";
        prd.sfarsit_tratament.afisare();
        out<<endl;
        out<<"Tara de provenienta a produsului este "<<prd.tara_provenienta<<endl;
        out<<"Reducerea valabila pentru acest produs este "<<prd.reducere<<"%"<<endl;
        return out;
    }

void testare2();
void testare3();
void testare_lambda();

void sort_produse_din_vector(Vector_diverse<Produs*> *const vect, function<bool(Produs*,Produs*)> lambda) {
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
    //testare3();
    testare2();
    //testare_lambda();
    return 0;
}
void testare3()
{
    afisare_vector(1);
}
void testare_lambda()
{
    ///SMART POINTERS || SHARED_PTR
    Data d1(5,12,2025);
    shared_ptr<Produs>p1=shared_ptr<Hrana>(new Hrana());
    shared_ptr<Produs>p2=shared_ptr<Hrana>(new Hrana("Stix",17.50,15,"#388894","Turcia","recompensa pentru papagali",0,20,"diverse seminte",d1));
    shared_ptr<Produs>p3=shared_ptr<Decoratiuni>(new Decoratiuni());
    p3->schimbare_cod_articol("#439937");
    Vector_diverse<shared_ptr<Produs>> *p=new Vector_diverse<shared_ptr<Produs>>;
    p->adaugare(p1);
    p->adaugare(p2);
    p->adaugare(p3);
    afisare_vector(p);   //p->afisare();

    ///FUNCTIE UTILITARA2 || MIN_ELEMENT DIN <ALGORITHM>
    auto j=min_element(p->begin(),p->end(), [](shared_ptr<Produs> a, shared_ptr<Produs> b) {
        return a->get_pret() < b->get_pret();
    });
    cout<<"Produsul cel mai ieftin din vector:\n";
    cout<<*(*j)<<endl;


    ///LAMBDA
    p3->set_pret(4);
    cout<<"AM UTILIZAT FUNCTIA LAMBDA"<<endl<<endl;

    ///FUNCTIE UTILITARA || SORT DIN <ALGORITHM>
    sort(p->begin(),p->end(), [](shared_ptr<Produs> a, shared_ptr<Produs> b) {
        return a->get_pret() > b->get_pret();
    });

    /*
    VARIANTA CU SORT IMPLEMENTAT IN FUCNTIE:
    sort_produse_din_vector(p, [](Produs* a, Produs* b) {
        return a->get_pret() > b->get_pret();
    });
    */

    p->stergere(p3);
    afisare_vector(p);   //p->afisare();
}
void afis_stoc(shared_ptr<Comanda> c2)
{
    stoc.afisare();
}

void testare2()
{
    ///USING CHRONO LIBRARY
    auto now = chrono::system_clock::now();
    time_t current_time = chrono::system_clock::to_time_t(now);
    tm* local_time = localtime(&current_time);
    int day = local_time->tm_mday;
    int month = local_time->tm_mon + 1;
    int year = local_time->tm_year + 1900;
    cout<<day<<" "<<month<<" "<<year<<endl;
    Data d_curenta(day,month,year);

    Data d1(5,12,2025);
    shared_ptr<Produs>p1=shared_ptr<Hrana>(new Hrana()); ///UPCASTING
    ///POLIMORFISM
    p1->afisare();

    ///CATCH AL DOILEA THROW
    cout<<endl;
    try{
        p1->schimbare_cod_articol("543993");
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
        shared_ptr<Produs>p2=shared_ptr<Hrana>(new Hrana("Stix",17.50,15,"#388894","Turcia","recompensa pentru papagali",0,20,"diverse seminte",d1));///UPCASTING

        ///POLIMORFISM
        cout<<endl<<"Verificare valabilitate:\n"<<p2->verificare_valabilitate(d_curenta)<<endl<<endl;
        shared_ptr<Produs>p3=shared_ptr<Decoratiuni>(new Decoratiuni());///UPCASTING
        cout<<"Decoratiune: "<<endl;
        cout<<*p3;
        cout<<endl<<"     Vectorul de produse"<<endl<<endl;
        Vector_diverse<shared_ptr<Produs>> *p=new Vector_diverse<shared_ptr<Produs>>;
        p->adaugare(p1);
        p->adaugare(p2);///UPCASTING
        p->adaugare(p3);
        afisare_vector(p);  //p->afisare();
        cout<<endl;

        ///POLIMORFISM
        int nr_hrana=0;
        int nr_decoratiuni=0;
        for(int i=0;i<p->size();i++)
            if((*p)[i]->categorie_produs()=="Hrana pentru animale")///HERE
                nr_hrana++;
            else {
                ///DYNAMIC_CAST
                shared_ptr<Produs> bazaPtr = make_shared<Decoratiuni>();
                if(auto derivataPtr = dynamic_pointer_cast<Decoratiuni>(bazaPtr)){
                    nr_decoratiuni++;
                }
            }
        cout<<"Nr articole de tip hrana din vector: "<<nr_hrana<<endl;
        cout<<"Nr decoratiuni: "<<nr_decoratiuni<<endl;

        ///POLIMORFISM
        cout<<"PRET:"<<p2->average_pret(p)<<endl;

        //TESTARE ERORI

        shared_ptr<Produs> p5 = shared_ptr<Hrana>(new Hrana());

        //p5.schimbare_cod_articol("#672483");
        try{
            shared_ptr<Produs> pointer_p5 = shared_ptr<Produs>(p5);
            p->stergere(pointer_p5);
        }
        catch(Bad_delete e1){
            cerr<<"EROARE: "<<e1.what()<<endl;
        }
        cout<<endl<<"Testare clasa Cos_cumparaturi"<<endl;

        ///
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
    shared_ptr<Comanda> c1=shared_ptr<Comanda>(new Comanda(g,"#824713757","in procesare","",d_curenta,0,0));
    shared_ptr<Comanda> c2=shared_ptr<Comanda>(new Comanda());
    cout<<endl<<endl<<"Afisare stoc:"<<endl;
    stoc.afisare();
    /*
    cout<<endl<<"Afisul din functie:"<<endl;
    afis_stoc(c2);
    cout<<endl<<"Afisul 2 main:"<<endl;
    stoc.afisare();
    */
}
