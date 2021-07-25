# Bacheca_Elettronica_di_Annunci

Progetto realizzato per superare la prova pratica dell'esame di Basi di Dati - Ing. Informatica - UniRoma2.
Nel file "traccia.txt" è presente la specifica di progetto con i requisiti e le operazioni richieste. 

Il thin-client per interagire con la base di dati è stato scritto in C, con un'implementazione estremamente basata sul "cosa fa" e meno sul "come". Questo grande debito tecnico si è reso necessario per soddisfare le tempistiche di consegna. Prevedo di ristrutturarlo in seguito.
Ho comunque cercato di utilizzare il più possibile costrutti quale i 'prepared-statements' e 'stored-procedures' onde prevenire errori e garantire un livello base minimo di tutela da attacchi di sql-injections. Le password utente sono salvate mediante funzione hash.

OS utilizzato: Windows 10
Software utilizzati: CodeBlocks (thin client), compilatore GCC, flag -Wextra (0 errors, 0 warnings)
                     MySQLWorkbench e MYSQLServer 8.0 per la creazione e l'instanziazione della base di dati


 
