# Proiect - POO

## Numele proiectului:
  Aplicatie Petshop 
  
## Tema aleasa:
  Gestionarea unui Petsop

## Clasele din proiect:

#### Clasa Data 
- retine o data calendaristica de tipul dd/mm/year;
#### Clasa String
- este un vector de char-uri alocat dinamic, echivalentul lui "string";
#### Clasa Produs
- este o clasa de baza pentru aplicatie
- reprezinta tipurile de produse ce se pot vinde in petshop;
#### Clasa Vecto_produse
- o clasa ce retine mai multe produse intr-un vector alocat dinamic
- are utilitate in alte doua clase importante
#### Clasa Cos_cumparaturi
- a fost creata pentru a putea retine simultan o multime de produse si pretul total al acestora;
- pretul se modifica in timp real, cand sunt adaugate sau sterse produse din cos;
#### Clasa Client
- retine detalii personale ale clientilor;
- dispune de un cos de cumparaturi unde se pot adauga produsele dorite;
- retine balanta fiecarui utilizator;
#### Clasa Comanda
- preia din contul clientului care a finalizat comanda produsele si pretul total al acestor;
- retine date despre livrare si are optiunea de a aplica vouchere;

## Functionalitatile aplicatiei:
- poate retine mai multi clienti si selectia de produse a fiecaruia(intr-un cos de cumparaturi);
- produselor din petshop le pot fi aplicate anumite reduceri;
- pot fi inregistrate comenzi ale clientilor;
