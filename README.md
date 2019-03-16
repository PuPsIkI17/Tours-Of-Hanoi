# Tours-Of-Hanoi
Pislari Vadim -> Facultatea Automatica si Calculatoare -> Universitatea Politehnica Bucuresti

                                                 (Romanian language)
                                               -------DESCRIERE-------
  Turnurile din Hanoi este un joc matematic sau puzzle. Este format din trei tije și un număr variabil de discuri, de diferite mărimi, care pot fi poziționate pe oricare din cele 3 tije. Jocul începe având discurile așezate în stivă pe prima tijă, în ordinea descrescătoare a mărimii lor de la bază spre vârf (astfel încât să formeze un turn). Scopul jocului este acela de a muta întreaga stivă de pe tija inițială pe o tijă finală, respectând următoarele reguli: 
  ● La un moment dat se poate muta doar un singur disc.
  ● Fiecare mutare constă în luarea celui mai de sus disc de pe o tijă și glisarea lui pe o altă tijă, chiar și deasupra altor discuri, dacă ele care sunt deja prezente pe acea tijă. 
  ● Un disc mai mare nu poate fi poziționat deasupra unui disc mai mic. Numărul minim de mișcări pentru a rezolva jocul este 2n - 1, unde n este numărul de discuri. 
O simulare a jocului se poate vedea în următorul link: https://www.puzzle.ro/ro/play_toh.htm 
 
Proiectul isi propune gasirea unei rezolvari de joc folosind numărul minim de mutări, adică 2n - 1. Mutările pentru rezolvarea jocului în număr minim de pași sunt deterministe. Există o singură soluție de rezolvare în număr minim de mutări pentru fiecare sistem Hanoi. 
 
Implementarea proiectului consta în efectuarea unui set de operații descrise în fișierul de intrare. Se defineste un sistem Hanoi ca fiind un grup de 3 stive: A, B, C. Scopul jocului este mutarea tuturor discurilor de pe tija A pe tija C. Un disc Hanoi este descris prin două proprietăți: diametru și culoare. Exista mai multe sisteme Hanoi. În cadrul unuia, toate discurile au aceeași culoare. 
 
Exista urmatoarele instructiuni:
add [culoare_disc] [dimensiune_disc] - culoarea unui disc este un șir de caractere a..z (litere mici ale alfabetului englezesc) 
- toate discurile de aceeași culoare sunt adăugate în stiva A a sistemului Hanoi în ordine descrescătoare a diametrului, de sus în jos. 
- după inserarea oricărui disc într-o stivă aceasta rămâne ordonată 

play [culoare] [număr_mutări]
- operația cere simularea următoarelor [număr_mutări] mutări ale jocului în sistemul Hanoi de culoare [culoare]
- dacă [număr_mutări] este mai mare decât numărul de pași necesari pentru terminarea jocului, simularea se opreste și nu se vor mai face alte mutări. 

show [culoare] 
- operația cere afișarea stării curente a sistemului Hanoi de culoare [culoare] 
 
show_moves [culoare] [număr_mutări] - operația cere afișarea următoarelor [număr_mutări] mutări ce trebuie executate în sistemul Hanoi de culoare [culoare] pentru a termina jocul. Dacă numărul total de mutări existente în sistem este mai mic decât [număr_mutări] se vor afișa doar cele existente.  - afișarea se face pe o singură linie.
