# InterSchem

Proiect InterSchem realizat de:  
Antohi Robert  
Apetrii Radu-Andrei  

Programul permite reprezentarea schemelor logice, salvarea acestora in fisiere, deschiderea schemelor logice din fisiere si executarea lor.  
De dezvoltat in continuare:
 - Codificarea schemei logice in C++

Instructiuni pentru comenzile din consola:
 - La inceputul executarii programului se deschide consola in care putem da diferite comenzi: edit <nume_fisier>, exe <nume_fisier>, cpp <nume_fisier>, exit.  
 - Comanda "edit <nume_fisier>" ne permite sa editam o schema logica si sa o salvam in fisierul cu numele dorit; daca fisierul nu exista, va fi creat unul cu acel nume, iar daca exista deja, vom putea modifica continutul salvat in acesta
 - Comanda "exe <nume_fisier>" ne permite sa executam schema logica salvata in fisierul cu numele dorit; daca fisierul nu exista, in consola va aparea o eroare
 - Comanda "cpp <nume_fisier>" ne permite sa vizualizam codificarea schemei logice din fisierul cu numele dorit
 - Comanda "exit" ne permite sa incheiem rularea programului
 - Daca introducem o comanda invalida, vom fi atentionati si indemnati sa citim/recitim README-ul  
Instructiuni pentru editarea schemei logice din fereastra grafica: 
 - Pentru a adauga un bloc logic in schema si a-l desena pe ecran se selecteaza tipul de bloc din dreapta ecranului si se plaseaza in locul dorit cu click stanga
 - Pentru a desena o legatura intre 2 blocuri este necesara selectarea acestora folosind click dreapta
 - Pentru a muta un bloc, se da click stanga pe acesta si se apasa click dreapta pe noua pozitie; legaturile cu alte blocuri se muta in timp real, odata cu blocul respectiv
 - Pentru a sterge un bloc, se da click stanga pe acesta si se apasa tasta Backspace; legaturile acestuia cu celelalte blocuri se sterg, de asemenea
 - Pentru a edita continutul unui bloc, se da click stanga pe acesta pentru a fi selectat si se apasa tasta "Insert"; dupa ce terminam de scris continutul dorit, se apasa tasta Enter, iar textul scris de la tastatura va aparea pe ecran, in interiorul blocului. Nota: Blocurile de START si STOP nu pot fi editate! 
 - Dupa ce am terminat de editat schema, se apasa tasta Esc pentru a salva si a reveni la meniul din consola.
