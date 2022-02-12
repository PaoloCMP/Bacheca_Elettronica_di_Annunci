        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>
        #include <mysql.h>
        #include <time.h>
        #include <stdbool.h>
        #define MAX_SIZE 2000000
        #define CURRENT_YEAR 2022


        char categ[46];
        char gerCateg[46];
        char hub[3];
        char hub2[3];
        char hub3[3];
        char descrizione[1000];
        char stringa[46];
        char photo[1000];
        int id;
        int id_2;
        int prezzo;
        char mess[1000];
        char username[46];
        char pwd[46];
        char receiver[46];
        char comando1[1000];
        char comando2[1000];
        char comando3[1000];
        char comando4[1000];
        char comando5[1000];
        char comando6[1000];
        char comando7[1000];
        char comando8[1000];
        char comando9[1000];
        char comando10[1000];
        char comando11[1000];
        char comando12[1000];
        char comando13[1000];
        char richiestalog[1000];
        time_t ora;
        char orario[46];
        char binaryFoto[MAX_SIZE];
        MYSQL *conn;


        void  parseCreditCard(long long numberOfCC, char dateOfCC[46]){

            char *p;
            p = malloc(46*sizeof(char));
            strcpy(p, dateOfCC);
            long long t = numberOfCC;
            int j;
            int count=0;
            while (t){
                t /= 10;
                count++;
            }
            if (count != 16){
                printf("\nNumero carta credito non valido\n");
                exit(-1);
            }
            //printf("\n%i\n", count);
            for (int i=0; i<2; i++){
                p=strtok(p, "-");
                sscanf(p,"%d",&j);
                printf("%d\n",j);
                p=strtok(NULL, "-");
                //printf("%i",i);
                switch(i){
                case 0:
                    if (j>13){
                        printf("\nMese di scadenza non valido\n");
                        exit(-1);
                    }
                    break;
                case 1:
                    if (j<CURRENT_YEAR){
                        printf("\nAnno scadenza non valido\n");
                        exit(-1);
                    }
                    break;
                }

            }
                return;

        }

        void modInfoAnagrafiche(){

            MYSQL_STMT *stmt;
            stmt = mysql_stmt_init(conn);
            int t=0;
            char parameter[46];
            char temp[46];
            char q[128];
            long long numeroCarta = 0;
            MYSQL_BIND param_one[3];
            MYSQL_BIND param_two[3];

            printf("\nCosa vuoi cambiare?\n1. Indirizzo residenza\n2. Indirizzo fatturazione\n3. Dati carta credito\n");
            scanf("%i",&t);
            switch(t){
                case 1:
                    printf("\nInserisci nuovo indirizzo\n");
                    fflush(stdin);
                    fgets(parameter, 45, stdin);
                    strtok(parameter, "\n");
                    fflush(stdin);
                    strcpy(q, "call modInfo(?,?,?)");
                    if(mysql_stmt_prepare(stmt, q, strlen(q))) {
                                printf("\nErrore preparazione stamenent\n");
                                return;
                    }
                    // Prepare parameters
                    memset(param_one, 0, sizeof(param_one));


                    param_one[0].buffer_type = MYSQL_TYPE_VAR_STRING;
                    param_one[0].buffer = parameter;
                    param_one[0].buffer_length = strlen(parameter);

                    param_one[1].buffer_type = MYSQL_TYPE_VAR_STRING;
                    param_one[1].buffer = username;
                    param_one[1].buffer_length = strlen(username);

                    param_one[2].buffer_type = MYSQL_TYPE_LONG;
                    param_one[2].buffer = &t;
                    param_one[2].buffer_length = sizeof(t);


                    if (mysql_stmt_bind_param(stmt, param_one)){
                        printf("\nErrore binding...\n");
                        return;}

                    if(mysql_stmt_execute(stmt)){
                        printf("\nErrore esecuzione operazione\n");
                        return;}

                    else{
                        printf("\nIndirizzo cambiato!!!\n");}
                        fflush(stdin);
                        mysql_stmt_close(stmt);

                    break;



                case 2:
                    printf("\nInserisci nuovo indirizzo\n");
                    fflush(stdin);
                    fgets(parameter, 45, stdin);
                    strtok(parameter, "\n");
                    fflush(stdin);
                    strcpy(q, "call modInfo(?,?,?)");
                    if(mysql_stmt_prepare(stmt, q, strlen(q))) {
                                printf("\nErrore preparazione stamenent\n");
                                return;
                    }
                    // Prepare parameters
                    memset(param_one, 0, sizeof(param_one));


                    param_one[0].buffer_type = MYSQL_TYPE_VAR_STRING;
                    param_one[0].buffer = parameter;
                    param_one[0].buffer_length = strlen(parameter);

                    param_one[1].buffer_type = MYSQL_TYPE_VAR_STRING;
                    param_one[1].buffer = username;
                    param_one[1].buffer_length = strlen(username);

                    param_one[2].buffer_type = MYSQL_TYPE_LONG;
                    param_one[2].buffer = &t;
                    param_one[2].buffer_length = sizeof(t);


                    if (mysql_stmt_bind_param(stmt, param_one)){
                        printf("\nErrore binding...\n");
                        return;}

                    if(mysql_stmt_execute(stmt)){
                        printf("\nErrore esecuzione operazione\n");
                        return;}

                    else{
                        printf("\nIndirizzo cambiato!!!\n");}
                        fflush(stdin);
                        mysql_stmt_close(stmt);

                    break;


                case 3:
                    printf("\nInserisci numero carta\n");
                    fflush(stdin);
                    scanf("%lld",&numeroCarta);
                    fflush(stdin);
                    printf("\n");
                    printf("Inserisci mese scadenza: mm\n");
                    fgets(parameter, 45, stdin);
                    strtok(parameter, "\n");
                    fflush(stdin);
                    strcat(parameter, "-");
                    printf("\nInserisci anno di scadenza: yyyy\n");
                    fgets(temp, 45, stdin);
                    strtok(temp, "\n");
                    fflush(stdin);
                    strcat(parameter, temp);
                    parseCreditCard(numeroCarta, parameter);


                    strcpy(q, "call modInfoCarta(?,?,?)");
                    if(mysql_stmt_prepare(stmt, q, strlen(q))) {
                                printf("\nErrore preparazione stamenent\n");
                                return;
                    }
                    memset(param_two, 0, sizeof(param_two));


                    param_two[0].buffer_type = MYSQL_TYPE_VAR_STRING;
                    param_two[0].buffer = parameter;
                    param_two[0].buffer_length = strlen(parameter);

                    param_two[1].buffer_type = MYSQL_TYPE_VAR_STRING;
                    param_two[1].buffer = username;
                    param_two[1].buffer_length = strlen(username);

                    param_two[2].buffer_type = MYSQL_TYPE_LONGLONG;
                    param_two[2].buffer = &numeroCarta;
                    param_two[2].buffer_length = sizeof(numeroCarta);


                    if (mysql_stmt_bind_param(stmt, param_two)){
                        printf("\nErrore binding...\n");
                        return;}

                    if(mysql_stmt_execute(stmt)){
                        printf("\nErrore esecuzione operazione\n");
                        fprintf(stderr, "%s\n", mysql_error(conn));

                        return;}

                    else{
                        printf("\nDati aggiornati!!!\n");}
                        fflush(stdin);
                        mysql_stmt_close(stmt);
            }

            return;

        }



        void showImage(){
                MYSQL_RES *result;
                MYSQL_ROW row;
                int idInserzione;
                char q[128];
                printf("\nScrivi id Annuncio di cui vuoi vedere immagine:\n");
                scanf("%i", &idInserzione);
                fflush(stdin);
                snprintf(q, 128, "SELECT Foto FROM Annuncio WHERE idAnnuncio = %i", idInserzione);
                mysql_escape_string(q, q, strlen(q));
                //printf(q);
                if (mysql_query(conn,q)) {
                        fprintf(stderr, "%s\n", mysql_error(conn));
                        exit(-1);
                }
                result = mysql_store_result(conn);

                if (result == NULL ) {
                    fprintf(stderr,"%s\n",mysql_error(conn));
                    printf("\nImmagine non trovata\n");
                    return;
                }

                row = mysql_fetch_row(result);
                if (row == NULL){
                    printf("\nImmagine non trovata\n");
                    return;
                }
                unsigned long *lengths = mysql_fetch_lengths(result);
                printf("\n%ld\n", lengths[0]);


                if (lengths[0] == 0) {
                    printf("\nImmagine non disponibile\n");
                    return;
                }

                FILE *fp = fopen("tmp.jpg", "wb");
                if (fp == NULL) {
                    fprintf(stderr, "cannot open temporary file\n");
                    exit(-1);
                }

                fwrite(row[0], lengths[0], 1, fp);
                fclose(fp);
                ShellExecute(NULL, "open" ,"tmp.jpg",NULL,NULL,SW_SHOW);
                mysql_free_result(result);
                mysql_next_result(conn);

        }


        void registraRecapito(){
                MYSQL_STMT *stmt;
                char command[] = "call registraRecapito(?,?,?)";
                stmt = mysql_stmt_init(conn);
                char recapito[46];
                char tipo[46];
                int t=0;
                printf("\nInserimento recapito:\nTipo:\n1.Telefono\n2.Mail\n3.Altro\n");
                scanf("%i",&t);
                fflush(stdin);
                switch (t){
                        case 1:
                            strcpy(tipo, "telefono");
                            fgets(recapito, 45, stdin);
                            strtok(recapito,"\n");
                            break;

                        case 2:

                            strcpy(tipo, "Mail");
                            fgets(recapito, 45, stdin);
                            strtok(recapito,"\n");
                            break;

                        case 3:
                            strcpy(tipo, "altro");
                            fgets(recapito, 45, stdin);
                            strtok(recapito,"\n");
                            break;}

                MYSQL_BIND paramRecap[3];
                fflush(stdin);

                if(mysql_stmt_prepare(stmt, command, strlen(command))) {
                        printf("\nErrore preparazione stamenent\n");

                        return;
                    }
            // Prepare parameters
                memset(paramRecap, 0, sizeof(paramRecap));


                paramRecap[0].buffer_type = MYSQL_TYPE_VAR_STRING;
                paramRecap[0].buffer = recapito;
                paramRecap[0].buffer_length = strlen(recapito);

                paramRecap[1].buffer_type = MYSQL_TYPE_VAR_STRING;
                paramRecap[1].buffer = username;
                paramRecap[1].buffer_length = strlen(username);
               // paramRecap[1].is_null = 0;

                paramRecap[2].buffer_type = MYSQL_TYPE_VAR_STRING;
                paramRecap[2].buffer = tipo;
                paramRecap[2].buffer_length = strlen(tipo);
                paramRecap[2].is_null = 0;

                if (mysql_stmt_bind_param(stmt, paramRecap)){
                    printf("\nErrore binding...\n");
                    return;}

                if(mysql_stmt_execute(stmt)){
                    printf("\nErrore esecuzione operazione\n");
                    fprintf(stderr, "%s\n", mysql_error(conn));
                    return;}

                else{
                    printf("\nRecapito Inserito!!!\n");}
                    fflush(stdin);
                    mysql_stmt_close(stmt);
                    return;

            }


        void vediMessaggi(){
                MYSQL_STMT *stmt;
                strcpy(comando7,"call vediMessRicevuti(?);");
                MYSQL_BIND    bindMessRicevuti[4];
                MYSQL_RES     *prepare_meta_result_two;

                unsigned long length_two[4];
                int           param_count_two, row_count_two;
                my_bool       is_null_two[4];
                my_bool       error_two[4];

                stmt = mysql_stmt_init(conn);
                param_count_two= mysql_stmt_param_count(stmt);
                if (param_count_two != 0) /* validate parameter count */
                {
                  fprintf(stderr, " invalid parameter count returned by MySQL\n");
                  exit(-1);
                }
                MYSQL_BIND param7[1];
                if(mysql_stmt_prepare(stmt, comando7, strlen(comando7))) {
                            printf("\nerror_twoe preparazione stamenent\n");
                            return;
                }
        // Prepare parameters
                memset(param7, 0, sizeof(param7));

                param7[0].buffer_type = MYSQL_TYPE_VAR_STRING;
                param7[0].buffer = username;
                param7[0].buffer_length = strlen(username);


                if (mysql_stmt_bind_param(stmt, param7)){
                    printf("\nErrore binding...\n");
                    return;}

                if(mysql_stmt_execute(stmt)){
                    printf("\nErrore esecuzione operazione\n");
                    fprintf(stderr,"%s\n",mysql_error(conn));
                    return;}


                else{
                /* Fetch result set meta information */
                prepare_meta_result_two = mysql_stmt_result_metadata(stmt);
                if (!prepare_meta_result_two)
                {
                  fprintf(stderr," mysql_stmt_result_metadata(), returned no meta information\n");
                  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
                  exit(-1);
                }
                printf("\nRicevuti:\n");
                //*Prendo i risultati della query
                //Stampo a video i risultati della query
                printf("\nid Messaggio - Testo - Mittente - Annuncio\n");
                /* Bind the result buffers for all 8 columns before fetching them */

                memset(bindMessRicevuti, 0, sizeof(bindMessRicevuti));

                bindMessRicevuti[0].buffer_type= MYSQL_TYPE_LONG;
                bindMessRicevuti[0].buffer= (char *)&id;
                //bind[0].buffer_length= 45;
                bindMessRicevuti[0].is_null= &is_null_two[0];
                bindMessRicevuti[0].length= &length_two[0];
                bindMessRicevuti[0].error= &error_two[0];

                bindMessRicevuti[1].buffer_type= MYSQL_TYPE_VAR_STRING;
                bindMessRicevuti[1].buffer= (char *)mess;
                bindMessRicevuti[1].buffer_length= 1000;
                bindMessRicevuti[1].is_null= &is_null_two[1];
                bindMessRicevuti[1].length= &length_two[1];
                bindMessRicevuti[1].error= &error_two[1];

                bindMessRicevuti[2].buffer_type= MYSQL_TYPE_VAR_STRING;
                bindMessRicevuti[2].buffer= (char *)receiver;
                bindMessRicevuti[2].buffer_length= 45;
                bindMessRicevuti[2].is_null= &is_null_two[2];
                bindMessRicevuti[2].length= &length_two[2];
                bindMessRicevuti[2].error= &error_two[2];

                bindMessRicevuti[3].buffer_type= MYSQL_TYPE_LONG;
                bindMessRicevuti[3].buffer= (char *)&id_2;
                //bind[3].buffer_length= 45;
                bindMessRicevuti[3].is_null= &is_null_two[3];
                bindMessRicevuti[3].length= &length_two[3];
                bindMessRicevuti[3].error= &error_two[3];


                /* Bind the result buffers */
                if (mysql_stmt_bind_result(stmt, bindMessRicevuti))
                {
                  fprintf(stderr, " mysql_stmt_bind_result() failed\n");
                  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
                  exit(-1);
                }

                /* Now buffer all results to client (optional step) */
                if (mysql_stmt_store_result(stmt))
                {
                  fprintf(stderr, " mysql_stmt_store_result() failed\n");
                  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
                  exit(-1);
                }

                /* Fetch all rows */
                row_count_two= 0;
                while (!mysql_stmt_fetch(stmt))
                {
                  row_count_two++;

                  /* column 1 */
                  if (is_null_two[0])
                    fprintf(stdout, " NULL -");
                  else
                    fprintf(stdout, " %i - ", id);

                  /* column 2 */
                  if (is_null_two[1])
                    fprintf(stdout, " NULL -");
                  else
                    fprintf(stdout, " %s - ", mess);

                  /* column 3 */
                  if (is_null_two[2])
                    fprintf(stdout, " NULL -");
                  else
                    fprintf(stdout, " %s - ", receiver);

                  /* column 4 */
                  if (is_null_two[3])
                    fprintf(stdout, " NULL\n");
                  else
                    fprintf(stdout, "%i\n",id_2);

                }


                /* Free the prepared result metadata */
                mysql_free_result(prepare_meta_result_two);
                mysql_next_result(conn);
                mysql_stmt_close(stmt);}


                strcpy(comando7,"call vediMessInviati(?);");
                MYSQL_BIND    bindMessInviati[4];
                MYSQL_RES     *prepare_meta_result_three;

                unsigned long length_three[4];
                int           param_count_three, row_count_three;
                my_bool       is_null_three[4];
                my_bool       error_three[4];

                stmt = mysql_stmt_init(conn);
                param_count_three= mysql_stmt_param_count(stmt);
                if (param_count_three != 0) /* validate parameter count */
                {
                  fprintf(stderr, " invalid parameter count returned by MySQL\n");
                  exit(-1);
                }
                //MYSQL_BIND param7[1];
                if(mysql_stmt_prepare(stmt, comando7, strlen(comando7))) {
                            printf("\nErrore preparazione stamenent\n");
                            return;
                }
        // Prepare parameters
                memset(param7, 0, sizeof(param7));

                param7[0].buffer_type = MYSQL_TYPE_VAR_STRING;
                param7[0].buffer = username;
                param7[0].buffer_length = strlen(username);


                if (mysql_stmt_bind_param(stmt, param7)){
                    printf("\nErrore binding...\n");
                    return;}

                if(mysql_stmt_execute(stmt)){
                    printf("\nErrore esecuzione operazione\n");
                    fprintf(stderr,"%s\n",mysql_error(conn));
                    return;}


                else{
                /* Fetch result set meta information */
                prepare_meta_result_three = mysql_stmt_result_metadata(stmt);
                if (!prepare_meta_result_three)
                {
                  fprintf(stderr," mysql_stmt_result_metadata(), returned no meta information\n");
                  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
                  exit(-1);
                }
                printf("\nInviati:\n");
                //*Prendo i risultati della query
                //Stampo a video i risultati della query
                printf("\nid Messaggio - Testo - Destinatario - Annuncio\n");
                /* Bind the result buffers for all 8 columns before fetching them */

                memset(bindMessInviati, 0, sizeof(bindMessInviati));

                bindMessInviati[0].buffer_type= MYSQL_TYPE_LONG;
                bindMessInviati[0].buffer= &id;
                //bind[0].buffer_length= 45;
                bindMessInviati[0].is_null= &is_null_three[0];
                bindMessInviati[0].length= &length_three[0];
                bindMessInviati[0].error= &error_three[0];

                bindMessInviati[1].buffer_type= MYSQL_TYPE_VAR_STRING;
                bindMessInviati[1].buffer= (char *)mess;
                bindMessInviati[1].buffer_length= 1000;
                bindMessInviati[1].is_null= &is_null_three[1];
                bindMessInviati[1].length= &length_three[1];
                bindMessInviati[1].error= &error_three[1];

                bindMessInviati[2].buffer_type= MYSQL_TYPE_VAR_STRING;
                bindMessInviati[2].buffer= (char *)receiver;
                bindMessInviati[2].buffer_length= 45;
                bindMessInviati[2].is_null= &is_null_three[2];
                bindMessInviati[2].length= &length_three[2];
                bindMessInviati[2].error= &error_three[2];

                bindMessInviati[3].buffer_type= MYSQL_TYPE_LONG;
                bindMessInviati[3].buffer= &id_2;
                //bind[3].buffer_length= 45;
                bindMessInviati[3].is_null= &is_null_three[3];
                bindMessInviati[3].length= &length_three[3];
                bindMessInviati[3].error= &error_three[3];


                /* Bind the result buffers */
                if (mysql_stmt_bind_result(stmt, bindMessInviati))
                {
                  fprintf(stderr, " mysql_stmt_bind_result() failed\n");
                  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
                  exit(-1);
                }

                /* Now buffer all results to client (optional step) */
                if (mysql_stmt_store_result(stmt))
                {
                  fprintf(stderr, " mysql_stmt_store_result() failed\n");
                  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
                  exit(-1);
                }

                /* Fetch all rows */
                row_count_three= 0;
                //fprintf(stdout, "Fetching results ...\n");
                while (!mysql_stmt_fetch(stmt))
                {
                  row_count_three++;

                  /* column 1 */
                  if (is_null_three[0])
                    fprintf(stdout, " NULL -");
                  else
                    fprintf(stdout, " %i - ", id);

                  /* column 2 */
                  if (is_null_three[1])
                    fprintf(stdout, " NULL -");
                  else
                    fprintf(stdout, " %s - ", mess);

                  /* column 3 */
                  if (is_null_three[2])
                    fprintf(stdout, " NULL -");
                  else
                    fprintf(stdout, " %s - ", receiver);

                  /* column 4 */
                  if (is_null_three[3])
                    fprintf(stdout, " NULL\n");
                  else
                    fprintf(stdout, "%i\n",id_2);

                }


                /* Free the prepared result metadata */
                mysql_free_result(prepare_meta_result_three);
                mysql_next_result(conn);
                mysql_stmt_close(stmt);}
        }

        int readBin (){
           printf(photo);
           FILE *fp = fopen(photo, "rb");

          if (fp == NULL)
          {   fprintf(stderr, "\nImpossibile aprire immagine\n");
              exit(-1);
          }
          fseek(fp, 0, SEEK_END);
          if (ferror(fp)) {
              fprintf(stderr, "fseek() failed\n");
              int r = fclose(fp);
              if (r == EOF) {
                  fprintf(stderr, "cannot close file handler\n");
              }
              exit(-1);
          }
          int flen = ftell(fp);

          if (flen == -1 || flen > MAX_SIZE) {
              //printf("\n%i\n", flen);
              perror("\nErrore: impossibile aprire immagine o dimensione immagine superiore al consentito\n");
              int r = fclose(fp);
              if (r == EOF) {
                  fprintf(stderr, "cannot close file handler\n");
              }
              exit(-1);
          }
          fseek(fp, 0, SEEK_SET);
          if (ferror(fp)) {
              fprintf(stderr, "fseek() failed\n");
              int r = fclose(fp);
              if (r == EOF) {
                  fprintf(stderr, "cannot close file handler\n");
              }
              exit(-1);
          }
          char data[flen+1];

          int size = fread(data, 1, flen, fp);
          printf("%d - %d", flen, size);

          if (ferror(fp)) {

              fprintf(stderr, "fread() failed\n");
              int r = fclose(fp);

              if (r == EOF) {
                  fprintf(stderr, "cannot close file handler\n");
              }

              exit(-1);
          }

          int r = fclose(fp);

          if (r == EOF) {
              fprintf(stderr, "cannot close file handler\n");
          }
         memcpy(binaryFoto, data, sizeof(data));
         return 0;
        }

        bool checkUser(){
            //MYSQL *conn = &connessione; //il puntatore alla connessione a mysql
            //MYSQL_RES *res; //il puntatore alla risorsa mysql
            //MYSQL_ROW row;  // il vettore in cui verranno messi i risultati delle query
            MYSQL_STMT *stmt;

            char query[1000];
            stmt = mysql_stmt_init(conn);
            MYSQL_BIND param[2];
            strcpy(query,"call checkUser(?, ?);");
            if(mysql_stmt_prepare(stmt, query, strlen(query))) {
                        printf("\nErrore preparazione stamenent\n");
                        //printf(mysql_error(conn));
                        exit(-1);
            }
    // Prepare parameters
            memset(param, 0, sizeof(param));


            param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
            param[0].buffer = username;
            param[0].buffer_length = strlen(username);

            param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
            param[1].buffer = pwd;
            param[1].buffer_length = strlen(pwd);


            if (mysql_stmt_bind_param(stmt, param)){
                printf("\nErrore binding...\n");
                return FALSE;}

            if(mysql_stmt_execute(stmt)){
                printf("\nErrore esecuzione operazione\n");
                fprintf(stderr, "%s\n", mysql_error(conn));
                return FALSE;}

            else{

                return TRUE;}
            }


        void bacheca(){

            if (mysql_change_user(conn, "utente", "utente", "mydb"))
            {
                fprintf(stderr, "Failed to change user.  Error: %s\n", mysql_error(conn));
                exit(-1);
            }
            //char check[1];
            int i=0;



            //MYSQL *conn = &connection; //il puntatore alla connessione a mysql
            MYSQL_RES *res; //il puntatore alla risorsa mysql
            MYSQL_ROW row;  // il vettore in cui verranno messi i risultati delle query
            MYSQL_STMT *stmt;


            while (1){
                printf("\nCosa vuoi fare?:\n");
                printf("\n1.Visualizza Annunci");
                printf("\n2.Inserisci Annuncio");
                printf("\n3.Rimuovi Annuncio");
                printf("\n4.Modifica Nome");
                printf("\n5.Modifica Cognome");
                printf("\n6.Vedi annunci seguiti");
                printf("\n7.Vedi messaggi");
                printf("\n8.Invia Messaggio");
                printf("\n9.Segnala come venduto");
                printf("\n10.Segui annuncio");
                printf("\n11.Modifica Annuncio");
                printf("\n12.Invia una domanda");
                printf("\n13.Vedi domande degli annunci");
                printf("\n14.Registra Recapito");
                printf("\n15.Modifica altre info personali\n");
                scanf("%i",&i);
                fflush(stdin);




                switch (i){
                    case 15:
                            modInfoAnagrafiche();
                            break;

                    case 14:
                            registraRecapito();
                            break;
                    case 1 :

                        if (mysql_query(conn, "call bacheca();")) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            }
                        else{
                        //*Prendo i risultati della query*/
                        res = mysql_use_result(conn);

                        /* Stampo a video i risultati della query */
                        printf("\nid Annuncio - Descrizione -  Categoria - Venditore - Foto\n\n");
                        while ((row = mysql_fetch_row(res)) != NULL){
                        //nel vettore row ci sono i risultati adesso
                            printf("%s - %s - %s - %s - %s \n", row[0],row[1],row[3],row[4],row[2]);}

                        /* Distruggo il puntatore ai risultati della query
                        e chiudo la connessione al database */
                        /*mysql_free_result(res);*/
                        }
                        mysql_free_result(res);
                        mysql_next_result(conn);
                        char answer[1];
                        printf("\nVuoi vedere una foto? y,n\n");
                        scanf("%s", answer);
                        if (strcmp(answer,"y")==0){
                            showImage();
                        }

                        break;



                    case 3:

                        printf("\nScrivi idAnnuncio da rimuovere:\n");
                        scanf("%i", &id);

                        ora = time(NULL);
                        strcpy(orario,asctime(localtime(&ora)));
                        strtok(orario, "\n");

                        stmt = mysql_stmt_init(conn);
                        MYSQL_BIND param3[3];
                        strcpy(comando3,"call rimuoviAnnuncio(?,?,?)");
                        if(mysql_stmt_prepare(stmt, comando3, strlen(comando3))) {
                                    printf("\nErrore preparazione stamenent\n");
                                    exit(-1);
                        }
                // Prepare parameters
                        memset(param3, 0, sizeof(param3));

                        param3[0].buffer_type = MYSQL_TYPE_VAR_STRING;
                        param3[0].buffer = orario;
                        param3[0].buffer_length = strlen(orario);

                        param3[1].buffer_type = MYSQL_TYPE_LONG;
                        param3[1].buffer = &id;
                        param3[1].buffer_length = sizeof(id);

                        param3[2].buffer_type = MYSQL_TYPE_VAR_STRING;
                        param3[2].buffer = username;
                        param3[2].buffer_length = strlen(username);


                        if (mysql_stmt_bind_param(stmt, param3)){
                            printf("\nErrore binding...\n");
                            exit(-1);}

                        if(mysql_stmt_execute(stmt)){
                            printf("\nErrore esecuzione operazione\n");
                            fprintf(stderr,"%s\n",mysql_error(conn));
                            exit(-1);}

                        else{
                            printf("\nRimosso!!!\n");}
                            fflush(stdin);
                            mysql_stmt_close(stmt);
                        break;




                    case 4:
                        printf("\nScrivi il nuovo nome:\n");
                        char nomen[46];
                        fflush(stdin);
                        fgets(nomen,45,stdin);
                        strtok(nomen, "\n");


                        stmt = mysql_stmt_init(conn);
                        MYSQL_BIND param4[2];
                        strcpy(comando4,"UPDATE Utente SET Nome = ? WHERE Username = ? ;");
                        if(mysql_stmt_prepare(stmt, comando4, strlen(comando4))) {
                                    printf("\nErrore preparazione stamenent\n");
                                    exit(-1);
                        }
                        // Prepare parameters
                        memset(param4, 0, sizeof(param4));


                        param4[0].buffer_type = MYSQL_TYPE_VAR_STRING;
                        param4[0].buffer = nomen;
                        param4[0].buffer_length = strlen(nomen);

                        param4[1].buffer_type = MYSQL_TYPE_VAR_STRING;
                        param4[1].buffer = username;
                        param4[1].buffer_length = strlen(username);


                        if (mysql_stmt_bind_param(stmt, param4)){
                            printf("\nErrore binding...\n");
                            exit(-1);}

                        if(mysql_stmt_execute(stmt)){
                            printf("\nErrore esecuzione operazione\n");
                            exit(-1);}

                        else{
                            printf("\nNome cambiato!!!\n");}
                            fflush(stdin);
                            mysql_stmt_close(stmt);

                        break;


                    case 5:
                        printf("\nScrivi il nuovo cognome:\n");
                        char cognomen[46];
                        fflush(stdin);
                        fgets(cognomen,45,stdin);
                        strtok(cognomen, "\n");

                        stmt = mysql_stmt_init(conn);
                        MYSQL_BIND param5[2];
                        strcpy(comando5,"UPDATE Utente SET Cognome = ? WHERE Username = ? ;");
                        if(mysql_stmt_prepare(stmt, comando5, strlen(comando5))) {
                                    printf("\nErrore preparazione stamenent\n");
                                    exit(-1);
                        }
                // Prepare parameters
                        memset(param5, 0, sizeof(param5));


                        param5[0].buffer_type = MYSQL_TYPE_VAR_STRING;
                        param5[0].buffer = cognomen;
                        param5[0].buffer_length = strlen(cognomen);

                        param5[1].buffer_type = MYSQL_TYPE_VAR_STRING;
                        param5[1].buffer = username;
                        param5[1].buffer_length = strlen(username);


                        if (mysql_stmt_bind_param(stmt, param5)){
                            printf("\nErrore binding...\n");
                            exit(-1);}

                        if(mysql_stmt_execute(stmt)){
                            printf("\nErrore esecuzione operazione\n");
                            exit(-1);}

                        else{
                            printf("\nCognome cambiato!!!\n");}
                            fflush(stdin);
                            mysql_stmt_close(stmt);

                       break;


                    case 6:

                        strcpy(comando6,"call vediAnnunciSeguiti(?);");

                        MYSQL_BIND    bind[6];
                        MYSQL_RES     *prepare_meta_result;

                        unsigned long length[7];
                        int           param_count,row_count;
                        int           idAnnuncioSeguito;
                        char          descrizione[1000];
                        char          foto[3];
                        char          ultimaMod[45];
                        char          stato[45];
                        char          category[45];
                        char          venditore[45];
                        my_bool       is_null[7];
                        my_bool       error[7];

                        stmt = mysql_stmt_init(conn);
                        param_count= mysql_stmt_param_count(stmt);
                        if (param_count != 0) /* validate parameter count */
                        {
                          fprintf(stderr, " invalid parameter count returned by MySQL\n");
                          exit(-1);
                        }




                        MYSQL_BIND param6[1];
                        if(mysql_stmt_prepare(stmt, comando6, strlen(comando6))) {
                                    printf("\nErrore preparazione stamenent\n");
                                    exit(-1);
                        }
                // Prepare parameters
                        memset(param6, 0, sizeof(param6));

                        param6[0].buffer_type = MYSQL_TYPE_VAR_STRING;
                        param6[0].buffer = username;
                        param6[0].buffer_length = strlen(username);


                        if (mysql_stmt_bind_param(stmt, param6)){
                            printf("\nErrore binding...\n");
                            exit(-1);}

                        if(mysql_stmt_execute(stmt)){
                            printf("\nErrore esecuzione operazione\n");
                            fprintf(stderr,"%s\n",mysql_error(conn));
                            exit(-1);}


                        else{
                        /* Fetch result set meta information */
                        prepare_meta_result = mysql_stmt_result_metadata(stmt);
                        if (!prepare_meta_result)
                        {
                          fprintf(stderr," mysql_stmt_result_metadata(), returned no meta information\n");
                          fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
                          exit(-1);
                        }
                        printf("\nAnnunci seguiti:\n");
                        //*Prendo i risultati della query
                        //Stampo a video i risultati della query
                        printf("\nid Annuncio - Descrizione - UltimaModifica - Stato - Categoria - Venditore\n");


                        /* Bind the result buffers for all 8 columns before fetching them */

                        memset(bind, 0, sizeof(bind));

                        bind[0].buffer_type= MYSQL_TYPE_LONG;
                        bind[0].buffer= (char *)&idAnnuncioSeguito;
                        //bind[0].buffer_length= 45;
                        bind[0].is_null= &is_null[0];
                        bind[0].length= &length[0];
                        bind[0].error= &error[0];

                        bind[1].buffer_type= MYSQL_TYPE_VAR_STRING;
                        bind[1].buffer= (char *)descrizione;
                        bind[1].buffer_length= 1000;
                        bind[1].is_null= &is_null[1];
                        bind[1].length= &length[1];
                        bind[1].error= &error[1];

                        bind[2].buffer_type= MYSQL_TYPE_VAR_STRING;
                        bind[2].buffer= (char *)ultimaMod;
                        bind[2].buffer_length= 45;
                        bind[2].is_null= &is_null[2];
                        bind[2].length= &length[2];
                        bind[2].error= &error[2];

                        bind[3].buffer_type= MYSQL_TYPE_VAR_STRING;
                        bind[3].buffer= (char *)stato;
                        bind[3].buffer_length= 45;
                        bind[3].is_null= &is_null[3];
                        bind[3].length= &length[3];
                        bind[3].error= &error[3];

                        bind[4].buffer_type= MYSQL_TYPE_VAR_STRING;
                        bind[4].buffer= (char *)category;
                        bind[4].buffer_length= 45;
                        bind[4].is_null= &is_null[4];
                        bind[4].length= &length[4];
                        bind[4].error= &error[4];

                        bind[5].buffer_type= MYSQL_TYPE_VAR_STRING;
                        bind[5].buffer= (char *)venditore;
                        bind[5].buffer_length= 45;
                        bind[5].is_null= &is_null[5];
                        bind[5].length= &length[5];
                        bind[5].error= &error[5];

                        /* Bind the result buffers */
                        if (mysql_stmt_bind_result(stmt, bind))
                        {
                          fprintf(stderr, " mysql_stmt_bind_result() failed\n");
                          fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
                          exit(-1);
                        }

                        /* Now buffer all results to client (optional step) */
                        if (mysql_stmt_store_result(stmt))
                        {
                          fprintf(stderr, " mysql_stmt_store_result() failed\n");
                          fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
                          exit(-1);
                        }

                        /* Fetch all rows */
                        row_count= 0;
                        while (!mysql_stmt_fetch(stmt))
                        {
                          row_count++;

                          /* column 1 */
                          if (is_null[0])
                            fprintf(stdout, " NULL -");
                          else
                            fprintf(stdout, " %i - ", idAnnuncioSeguito);

                          /* column 2 */
                          if (is_null[1])
                            fprintf(stdout, " NULL -");
                          else
                            fprintf(stdout, " %s - ", descrizione);

                          /* column 3 */
                          if (is_null[2])
                            fprintf(stdout, " NULL -");
                          else
                            fprintf(stdout, " %s - ", ultimaMod);

                          /* column 4 */
                          if (is_null[3])
                            fprintf(stdout, " NULL -");
                          else
                            fprintf(stdout, "%s - ",stato);

                          if (is_null[4])
                            fprintf(stdout, " NULL -");
                          else
                            fprintf(stdout, " %s - ", category);

                          if (is_null[5])
                            fprintf(stdout, " NULL\n");
                          else
                            fprintf(stdout, " %s \n", venditore);

                         }


                        /* Free the prepared result metadata */
                        mysql_free_result(prepare_meta_result);
                        mysql_next_result(conn);


                        mysql_stmt_close(stmt);}

                        printf("\nVuoi vedere una foto? y,n\n");
                        scanf("%s", foto);
                        fflush(stdin);
                        if (strcmp(foto,"y")==0){
                            showImage();
                        }
                        break;


                    case 7:

                        vediMessaggi();

                        break;



                    case 10:
                        printf("\nScrivi idAnnuncio da seguire:\n");
                        scanf("%i", &id);

                        stmt = mysql_stmt_init(conn);
                        MYSQL_BIND param10[2];
                        strcpy(comando10,"INSERT INTO Segue VALUES(?, ?);");
                        if(mysql_stmt_prepare(stmt, comando10, strlen(comando10))) {
                                    printf("\nErrore preparazione stamenent\n");
                                    exit(-1);
                        }
                        // Prepare parameters
                        memset(param10, 0, sizeof(param10));


                        param10[0].buffer_type = MYSQL_TYPE_LONG;
                        param10[0].buffer = &id;
                        param10[0].buffer_length = sizeof(id);

                        param10[1].buffer_type = MYSQL_TYPE_VAR_STRING;
                        param10[1].buffer = username;
                        param10[1].buffer_length = strlen(username);




                        if (mysql_stmt_bind_param(stmt, param10)){
                            printf("\nErrore binding...\n");
                            exit(-1);}

                        if(mysql_stmt_execute(stmt)){
                            printf("\nErrore esecuzione operazione\n");
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(-1);}

                        else{

                            fflush(stdin);
                            mysql_stmt_close(stmt);
                            break;}


                    case 8:
                        printf("\nScrivi idAnnuncio scelto:\n");
                        scanf("%i", &id);

                        printf("\nScrivi username destinatario\n");
                        fflush(stdin);
                        fgets(receiver,45,stdin);
                        strtok(receiver, "\n");


                        printf("\nScrivi testo del messaggio:\n");
                        fflush(stdin);
                        fgets(mess,1000,stdin);
                        strtok(mess, "\n");


                        stmt = mysql_stmt_init(conn);
                        MYSQL_BIND param8[4];
                        strcpy(comando8,"Call inviaMessaggio(?, ?, ?, ?)");
                        if(mysql_stmt_prepare(stmt, comando8, strlen(comando8))) {
                                    printf("\nErrore preparazione stamenent\n");
                                    exit(-1);
                        }
                // Prepare parameters
                        memset(param8, 0, sizeof(param8));


                        param8[0].buffer_type = MYSQL_TYPE_VAR_STRING;
                        param8[0].buffer = mess;
                        param8[0].buffer_length = strlen(mess);

                        param8[1].buffer_type = MYSQL_TYPE_VAR_STRING;
                        param8[1].buffer = username;
                        param8[1].buffer_length = strlen(username);

                        param8[2].buffer_type = MYSQL_TYPE_LONG;
                        param8[2].buffer = &id;
                        param8[2].buffer_length = sizeof(id);

                        param8[3].buffer_type = MYSQL_TYPE_VAR_STRING;
                        param8[3].buffer = receiver;
                        param8[3].buffer_length = strlen(receiver);


                        if (mysql_stmt_bind_param(stmt, param8)){
                            printf("\nErrore binding...\n");
                            exit(-1);}

                        if(mysql_stmt_execute(stmt)){
                            printf("\nErrore esecuzione operazione\n");
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(-1);}

                        else{
                            printf("\nInviato!!!\n");}
                            fflush(stdin);
                            mysql_stmt_close(stmt);

                        break;

                    case 9:
                        printf("\nInserisci idAnnuncio venduto:\n");
                        scanf("%i",&id);

                        printf("\nInserisci prezzo di vendita:  -obbligatorio-\n");
                        scanf("%i",&prezzo);


                        ora = time(NULL);
                        strcpy(orario,asctime(localtime(&ora)));
                        strtok(orario, "\n");

                        stmt = mysql_stmt_init(conn);
                        MYSQL_BIND param9[4];
                        strcpy(comando9,"call segnaVenduto(?,?,?,?)");
                        if(mysql_stmt_prepare(stmt, comando9, strlen(comando9))) {
                                    printf("\nErrore preparazione stamenent\n");
                                    exit(-1);
                        }
                // Prepare parameters
                        memset(param9, 0, sizeof(param9));

                        param9[0].buffer_type = MYSQL_TYPE_VAR_STRING;
                        param9[0].buffer = orario;
                        param9[0].buffer_length = strlen(orario);

                        param9[1].buffer_type = MYSQL_TYPE_LONG;
                        param9[1].buffer = &id;
                        param9[1].buffer_length = sizeof(id);

                        param9[2].buffer_type = MYSQL_TYPE_VAR_STRING;
                        param9[2].buffer = username;
                        param9[2].buffer_length = strlen(username);

                        param9[3].buffer_type = MYSQL_TYPE_LONG;
                        param9[3].buffer = &prezzo;
                        param9[3].buffer_length = sizeof(prezzo);


                        if (mysql_stmt_bind_param(stmt, param9)){
                            printf("\nErrore binding...\n");
                            exit(-1);}

                        if(mysql_stmt_execute(stmt)){
                            printf("\nErrore esecuzione operazione\n");
                            fprintf(stderr,"%s\n",mysql_error(conn));
                            exit(-1);}

                        else{
                            printf("\nFatto!!!\n");}
                            fflush(stdin);
                            mysql_stmt_close(stmt);
                        break;



                    case 11:

                        printf("\nInserisci idAnnuncio da modificare:\n");
                        scanf("%i",&id);

                        printf("\nInserisci nuovo testo-\n");
                        fflush(stdin);
                        fgets(descrizione,1000,stdin);
                        strtok(descrizione, "\n");

                        ora = time(NULL);
                        strcpy(orario,asctime(localtime(&ora)));
                        strtok(orario, "\n");

                        stmt = mysql_stmt_init(conn);
                        MYSQL_BIND param11[4];
                        strcpy(comando11,"call modificaAnnuncio(?,?,?,?);");
                        if(mysql_stmt_prepare(stmt, comando11, strlen(comando11))) {
                                    printf("\nErrore preparazione stamenent\n");
                                    exit(-1);
                        }
                        // Prepare parameters
                        memset(param11, 0, sizeof(param11));


                        param11[0].buffer_type = MYSQL_TYPE_VAR_STRING;
                        param11[0].buffer = descrizione;
                        param11[0].buffer_length = strlen(descrizione);

                        param11[1].buffer_type = MYSQL_TYPE_VAR_STRING;
                        param11[1].buffer = orario;
                        param11[1].buffer_length = strlen(orario);

                        param11[2].buffer_type = MYSQL_TYPE_LONG;
                        param11[2].buffer = &id;
                        param11[2].buffer_length = sizeof(id);

                        param11[3].buffer_type = MYSQL_TYPE_VAR_STRING;
                        param11[3].buffer = username;
                        param11[3].buffer_length = strlen(username);




                        if (mysql_stmt_bind_param(stmt, param11)){
                            printf("\nErrore binding...\n");
                            exit(-1);}

                        if(mysql_stmt_execute(stmt)){
                            printf("\nErrore esecuzione operazione\n");
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(-1);}

                        else{

                            fflush(stdin);
                            mysql_stmt_close(stmt);
                            break;}


                    case 12:
                        printf("\nScrivi idAnnuncio scelto:\n");
                        scanf("%i", &id);


                        printf("\nScrivi testo della domanda:\n");
                        fflush(stdin);
                        fgets(descrizione,1000,stdin);
                        strtok(descrizione, "\n");


                        stmt = mysql_stmt_init(conn);
                        MYSQL_BIND param12[3];
                        strcpy(comando12,"Call inviaDomanda(?, ?, ?)");
                        if(mysql_stmt_prepare(stmt, comando12, strlen(comando12))) {
                                    printf("\nErrore preparazione stamenent\n");
                                    exit(-1);
                        }
                // Prepare parameters
                        memset(param12, 0, sizeof(param12));


                        param12[0].buffer_type = MYSQL_TYPE_VAR_STRING;
                        param12[0].buffer = descrizione;
                        param12[0].buffer_length = strlen(descrizione);

                        param12[1].buffer_type = MYSQL_TYPE_VAR_STRING;
                        param12[1].buffer = username;
                        param12[1].buffer_length = strlen(username);

                        param12[2].buffer_type = MYSQL_TYPE_LONG;
                        param12[2].buffer = &id;
                        param12[2].buffer_length = sizeof(id);


                        if (mysql_stmt_bind_param(stmt, param12)){
                            printf("\nErrore binding...\n");
                            exit(-1);}

                        if(mysql_stmt_execute(stmt)){
                            printf("\nErrore esecuzione operazione\n");
                            fprintf(stderr, "%s\n", mysql_error(conn));

                            exit(-1);}

                        else{
                            printf("\nInviata!!!\n");}
                            fflush(stdin);
                            mysql_stmt_close(stmt);

                        break;



                    case 13:
                        strcpy(comando13,"call domande()");
                        printf("\nDomande:\n");
                        if (mysql_query(conn, comando13)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            }
                        else{
                        //*Prendo i risultati della query*/
                        res = mysql_use_result(conn);

                        /* Stampo a video i risultati della query */
                        printf("\nidDomanda - Testo - Mittente - Annuncio\n");
                        while ((row = mysql_fetch_row(res)) != NULL){
                        //nel vettore row ci sono i risultati adesso
                        printf("%s - %s - %s - %s \n", row[0],row[1],row[2],row[3]);}

                        /* Distruggo il puntatore ai risultati della query
                        e chiudo la connessione al database */
                        mysql_free_result(res);
                        mysql_next_result(conn);}
                        break;



                    case 2:
                        strcpy(comando2,"call categorie()");
                        /*printf("\nCategorie:\n");*/
                        if (mysql_query(conn, comando2)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            }
                        else{
                        //*Prendo i risultati della query*/
                        res = mysql_use_result(conn);

                        /* Stampo a video i risultati della query */
                        printf("Categoria principale (- categoria gerarchica)\n");
                        while ((row = mysql_fetch_row(res)) != NULL){
                        //nel vettore row ci sono i risultati adesso
                        if (row[1] != NULL){
                            printf("%s (- %s)\n", row[0],row[1]);}
                        else
                            printf("%s\n", row[0]);}


                        /* Distruggo il puntatore ai risultati della query*/
                        mysql_free_result(res);
                        mysql_next_result(conn);
                        }
                        printf("\nScegli una categoria per il tuo annuncio:\n");
                        fflush(stdin);
                        fgets(categ,45,stdin);
                        strtok(categ,"\n");
                        printf("\nScrivi la descrizione del tuo annuncio: \n");
                        fflush(stdin);
                        fgets(descrizione,1000,stdin);
                        strtok(descrizione, "\n");

                        printf("\nVuoi inserire il link di una foto? si,no  -dim max %i MB-\n", MAX_SIZE/1000000);
                        scanf("%s",hub3);

                        if ((strcmp(hub3,"no"))==0){
                        /*printf("\nInserisci foto\n");
                        scanf("%s", stringa);*/
                        }
                        else if ((strcmp(hub3,"si"))==0)
                        {printf("\nInserisci foto\n");
                        fflush(stdin);
                        fgets(photo,1000,stdin);
                        strtok(photo, "\n");
                        readBin();
                        }
                        ora = time(NULL);
                        strcpy(orario,asctime(localtime(&ora)));
                        strtok(orario, "\n");


                        stmt = mysql_stmt_init(conn);
                        MYSQL_BIND param2[6];
                        strcpy(comando2,"call inserisciAnnuncio(?,?,?,?,?,?)");
                        if(mysql_stmt_prepare(stmt, comando2, strlen(comando2))) {
                                    printf("\nErrore preparazione stamenent\n");
                                    fprintf(stderr,"%s\n",mysql_error(conn));
                                    exit(-1);
                        }
                        // Prepare parameters
                        memset(param2, 0, sizeof(param2));


                        param2[0].buffer_type = MYSQL_TYPE_VAR_STRING;
                        param2[0].buffer = categ;
                        param2[0].buffer_length = strlen(categ);

                        param2[1].buffer_type = MYSQL_TYPE_VAR_STRING;
                        param2[1].buffer = username;
                        param2[1].buffer_length = strlen(username);

                        param2[2].buffer_type = MYSQL_TYPE_MEDIUM_BLOB;
                        param2[2].buffer = binaryFoto;
                        param2[2].buffer_length = sizeof(binaryFoto);

                        param2[3].buffer_type = MYSQL_TYPE_VAR_STRING;
                        param2[3].buffer = hub3;
                        param2[3].buffer_length = strlen(hub3);

                        param2[4].buffer_type = MYSQL_TYPE_VAR_STRING;
                        param2[4].buffer = orario;
                        param2[4].buffer_length = strlen(orario);

                        param2[5].buffer_type = MYSQL_TYPE_VAR_STRING;
                        param2[5].buffer = descrizione;
                        param2[5].buffer_length = strlen(descrizione);

                        if (mysql_stmt_bind_param(stmt, param2)){
                            printf("\nErrore binding...\n");
                            exit(-1);}

                        if(mysql_stmt_execute(stmt)){
                            printf("\nErrore esecuzione operazione\n");
                            fprintf(stderr,"%s\n",mysql_error(conn));
                            exit(-1);}
                        else{
                            fflush(stdin);
                            mysql_stmt_close(stmt);
                            printf("\nInserito!!!\n");}
                        break;

                        }


                        }


                }



        void registrazione(){
                    char nome[46];
                    char cognome[46];
                    char indirizzoResi[46];
                    char indirizzoFatt[46];
                    long long numeroCC;
                    char scadenzaCC[46];
                    char buf[5];
                    int check=0;
                    MYSQL_STMT *stmt;


                    //MYSQL_RES *res; //il puntatore alla risorsa mysql
                    //MYSQL_ROW row;  // il vettore in cui verranno messi i risultati delle query



                    printf("\nInserisci Username desiderato\n");
                    fflush(stdin);
                    fgets(username,45,stdin);
                    strtok(username, "\n");
                    printf("\nInserisci password desiderata\n");
                    fflush(stdin);
                    fgets(pwd,45,stdin);
                    strtok(pwd, "\n");
                    printf("\nInserisci il tuo nome:\n");
                    fflush(stdin);
                    fgets(nome,45,stdin);
                    strtok(nome, "\n");
                    printf("\nInserisci il tuo cognome\n");
                    fflush(stdin);
                    fgets(cognome,45,stdin);
                    strtok(cognome, "\n");
                    printf("\nInserisci indirizzo residenza\n");
                    fflush(stdin);
                    fgets(indirizzoResi,45,stdin);
                    strtok(indirizzoResi, "\n");
                    printf("\nVuoi inserire indirizzo fatturazione? y,no\n");
                    scanf("%s", hub);
                    if ((strcmp(hub,"y"))==0){
                        printf("\nInserisci indirizzo Fatt:\n");
                        fflush(stdin);
                        fgets(indirizzoFatt,45,stdin);
                        strtok(indirizzoFatt, "\n");
                        }
                    printf("\nVuoi inserire i dati della Carta di credito? yes,no   -non potrai inserire annunci senza-\n");
                    scanf("%s", hub2);
                    if ((strcmp(hub2,"yes")==0)){

                        printf("\nInserisci numero:\n");
                        //char numCC[46];
                        fflush(stdin);
                        scanf("%lld",&numeroCC);
                        fflush(stdin);

                        printf("\nInserisci mese di scadenza:  mm\n");
                        fflush(stdin);
                        fgets(scadenzaCC,45,stdin);
                        strtok(scadenzaCC, "\n");
                        fflush(stdin);
                        strcat(scadenzaCC,"-");
                        printf("\nInserisci anno di scadenza:  yyyy\n");
                        fflush(stdin);
                        fgets(buf,5,stdin);
                        strtok(buf, "\n");
                        fflush(stdin);
                        strcat(scadenzaCC,buf);
                        printf(scadenzaCC);

                        parseCreditCard(numeroCC, scadenzaCC);
                        }

                        char s[1];
                        char recapito[46];
                        char tipo[46];
                        //int pref = 1;
                        int t=0;
                        printf("\nInserimento recapito principale:\nTipo:\n1.Telefono\n2.Mail\n3.Altro\n");
                        scanf("%i",&t);
                        fflush(stdin);
                        switch (t){
                                case 1:
                                    strcpy(tipo, "telefono");
                                    fgets(recapito, 45, stdin);
                                    strtok(recapito,"\n");
                                    break;

                                case 2:

                                    strcpy(tipo, "Mail");
                                    fgets(recapito, 45, stdin);
                                    strtok(recapito,"\n");
                                    break;

                                case 3:
                                    strcpy(tipo, "altro");
                                    fgets(recapito, 45, stdin);
                                    strtok(recapito,"\n");
                                    break;}




                   if ((strcmp(hub,"y")==0) && (strcmp(hub2,"yes")==0)){
                        check = 0;
                   }
                   if ((strcmp(hub,"y")==0) && (strcmp(hub2,"no")== 0)){
                    check = 1;
                   }
                   if ((strcmp(hub,"no")==0) && (strcmp(hub2,"yes")== 0)){
                    check = 2;
                   }
                   if ((strcmp(hub,"no")==0) && (strcmp(hub2,"no")== 0)){
                    check = 3;
                   }

                   char richiesta[1000];

                    strcpy(richiesta, "Call registraUtente(?,?,?,?,?,?,?,?,?,?,?)");
                    stmt = mysql_stmt_init(conn);
                    MYSQL_BIND param1Reg[11];
                    fflush(stdin);

                    if(mysql_stmt_prepare(stmt, richiesta, strlen(richiesta))) {
                            printf("\nErrore preparazione stamenent\n");
                            return;
                        }
                        // Prepare parameters
                            memset(param1Reg, 0, sizeof(param1Reg));


                            param1Reg[0].buffer_type = MYSQL_TYPE_VAR_STRING;
                            param1Reg[0].buffer = username;
                            param1Reg[0].buffer_length = strlen(username);

                            param1Reg[1].buffer_type = MYSQL_TYPE_VAR_STRING;
                            param1Reg[1].buffer = nome;
                            param1Reg[1].buffer_length = strlen(nome);

                            param1Reg[2].buffer_type = MYSQL_TYPE_VAR_STRING;
                            param1Reg[2].buffer = cognome;
                            param1Reg[2].buffer_length = strlen(cognome);

                            param1Reg[3].buffer_type = MYSQL_TYPE_VAR_STRING;
                            param1Reg[3].buffer = indirizzoResi;
                            param1Reg[3].buffer_length = strlen(indirizzoResi);

                            param1Reg[4].buffer_type = MYSQL_TYPE_VAR_STRING;
                            param1Reg[4].buffer = indirizzoFatt;
                            param1Reg[4].buffer_length = strlen(indirizzoFatt);

                            param1Reg[5].buffer_type = MYSQL_TYPE_LONGLONG;
                            param1Reg[5].buffer = &numeroCC;
                            param1Reg[5].buffer_length = sizeof(numeroCC);

                            param1Reg[6].buffer_type = MYSQL_TYPE_VAR_STRING;
                            param1Reg[6].buffer = scadenzaCC;
                            param1Reg[6].buffer_length = strlen(scadenzaCC);

                            param1Reg[7].buffer_type = MYSQL_TYPE_LONG;
                            param1Reg[7].buffer = &check;
                            param1Reg[7].buffer_length = sizeof(check);

                            param1Reg[8].buffer_type = MYSQL_TYPE_VAR_STRING;
                            param1Reg[8].buffer = tipo;
                            param1Reg[8].buffer_length = strlen(tipo);

                            param1Reg[9].buffer_type = MYSQL_TYPE_VAR_STRING;
                            param1Reg[9].buffer = recapito;
                            param1Reg[9].buffer_length = strlen(recapito);

                            param1Reg[10].buffer_type = MYSQL_TYPE_VAR_STRING;
                            param1Reg[10].buffer = pwd;
                            param1Reg[10].buffer_length = strlen(pwd);


                            if (mysql_stmt_bind_param(stmt, param1Reg)){
                                printf("\nErrore binding...\n");
                                return;}

                            if(mysql_stmt_execute(stmt)){
                                printf("\nErrore esecuzione operazione\n");
                                fprintf(stderr,"%s\n",mysql_error(conn));
                                return;}

                            else{
                                mysql_stmt_close(stmt);
                                printf("\nQuanti recapiti vuoi ancora inserire?\n");
                                scanf("%s",s);
                                int i =  atoi(s);

                                for (int j=0; j<i; j++){
                                    registraRecapito();
                                }

                    printf("\nRegistrato!!!\n");

                    return;}
            }



        void gestore(){
            char op[1];
            char richiesta[1000];
            int check=0;
            MYSQL_STMT *stmt;
            MYSQL_RES *res; //il puntatore alla risorsa mysql
            MYSQL_ROW row;  // il vettore in cui verranno messi i risultati delle query


            while(1){
                strcpy(username, "gestore");
                printf("Inserire password:\n");
                fflush(stdin);
                fgets(pwd, 45, stdin);
                fflush(stdin);
                strtok(pwd, "\n");

                if (checkUser() == FALSE){
                    printf("Non Autorizzato\n\n");
                    return;
                }

                if (mysql_change_user(conn,username,pwd,"mydb"))
                {
                    fprintf(stderr, "Failed to change user.  Error: %s\n", mysql_error(conn));
                    printf("Accesso come amministratore fallito\n");
                    exit(-1);
                }
                else{
                    printf ("\nConnessione avvenuta con successo al server\n");


                    while(1){
                        printf("Cosa vuoi fare?\n");
                        printf("1. Crea Categoria\n2. Visualizza Report\n");
                        scanf("%s", op);


                        if (strcmp(op,"1")==0){
                            printf("\nScrivi il nome della categoria:\n");
                            fflush(stdin);
                            fgets(categ,45,stdin);
                            strtok(categ, "\n");
                            printf("\nVuoi farla dipendere da una categoria esistente? y,n\n");
                            fflush(stdin);
                            scanf("%s",op);
                            if (strcmp(op,"y")==0){
                                printf("\nScrivi il nome della sovracategoria:\n");
                                fflush(stdin);
                                fgets(gerCateg,45,stdin);
                                strtok(gerCateg, "\n");
                                fflush(stdin);
                                check = 1;
                                }
                            strcpy(richiesta, "Call creaCategoria(?,?,?)");
                            stmt = mysql_stmt_init(conn);
                            MYSQL_BIND param1Amm[3];
                            fflush(stdin);

                            if(mysql_stmt_prepare(stmt, richiesta, strlen(richiesta))) {
                                    printf("\nErrore preparazione stamenent\n");
                                    return;
                                }
                        // Prepare parameters
                            memset(param1Amm, 0, sizeof(param1Amm));


                            param1Amm[0].buffer_type = MYSQL_TYPE_VAR_STRING;
                            param1Amm[0].buffer = categ;
                            param1Amm[0].buffer_length = strlen(categ);

                            param1Amm[1].buffer_type = MYSQL_TYPE_VAR_STRING;
                            param1Amm[1].buffer = gerCateg;
                            param1Amm[1].buffer_length = strlen(gerCateg);
                            param1Amm[1].is_null = 0;

                            param1Amm[2].buffer_type = MYSQL_TYPE_LONG;
                            param1Amm[2].buffer = &check;
                            param1Amm[2].buffer_length = sizeof(check);


                            if (mysql_stmt_bind_param(stmt, param1Amm)){
                                printf("\nErrore binding...\n");
                                return;}

                            if(mysql_stmt_execute(stmt)){
                                printf("\nErrore esecuzione operazione\n");
                                return;}

                            else{
                                printf("\nCategoria Inserita!!!\n");}
                                check = 0;
                                fflush(stdin);
                                mysql_stmt_close(stmt);

                        }


                        else if (strcmp(op,"2")==0){

                            if (mysql_query(conn, "call vediReport()")) {
                                    fprintf(stderr, "%s\n", mysql_error(conn));
                                    exit(-1);
                                    }
                            else{
                            //*Prendo i risultati della query*/
                            res = mysql_use_result(conn);

                            /* Stampo a video i risultati della query */
                            printf("\nReport\n");
                            printf("Utente - N Annunci - Percentuale - Numero Carta - Scadenza Carta\n");
                            while ((row = mysql_fetch_row(res)) != NULL){
                            //nel vettore row ci sono i risultati adesso
                                printf("%s - %s - %s - %s - %s\n", row[0],row[1],row[2],row[3],row[4]);
                                }
                            mysql_next_result(conn);
                            char dom[1];
                            printf("\n\nVuoi segnare come riscossi questi annunci? y,n NB: Non saranno piu visibili nel report\n");
                            scanf("%s",dom);
                            if (strcmp(dom,"y")==0){
                                if (mysql_query(conn, "call segnaRiscosso()")) {
                                        fprintf(stderr, "%s\n", mysql_error(conn));
                                        printf("\nErrore\n");
                                        mysql_free_result(res);
                                        mysql_next_result(conn);

                                        /*exit(1);*/
                                }
                                else{
                                printf("\nSegnati!\n");
                                fflush(stdin);
                                mysql_free_result(res);
                                mysql_next_result(conn);


                                }}
                            else{
                            mysql_free_result(res);
                            mysql_next_result(conn);
                            fflush(stdin);
                            }


                        }}
                        else
                            printf("\nNon valido\n");
                        }

                }}

        }


        int main(void){
            char op[1];
            /* Dichiaro le variabili di connessione */
            char *server = "localhost";
            char *user = "login";
            char *password = "login";
            char *database = "mydb";

           /*Inizializzo la connessione*/
            conn = mysql_init(NULL);
            //MYSQL_STMT *stmt;


           /* Se possibile mi connetto al database altrimenti
           esco dal programma e scrivo un messaggio d'errore */
           if (!mysql_real_connect(conn, server,
                 user, password, database, 0, NULL, CLIENT_MULTI_STATEMENTS)) {
              fprintf(stderr, "%s\n", mysql_error(conn));
              printf("Connessione al server  non riuscita");
              exit(-1);
           }
           else{

            printf("\nBacheca elettronica di annunci.\nBenvenuto\nCosa vuoi fare?\n");

            while(1) {
                printf("1) Accedi\n");
                printf("2) Registrati\n");
                printf("3) Amministrazione\n\n");

                scanf("%s",op);
                if (strcmp(op,"1")== 0){
                    printf("\nInserisci username: \n");
                    fflush(stdin);
                    fgets(username,45,stdin);
                    strtok(username,"\n");
                    printf("\nInserisci password: \n");
                    fflush(stdin);
                    fgets(pwd,45,stdin);
                    strtok(pwd,"\n");
                    fflush(stdin);
                    if (checkUser()== TRUE){
                        bacheca();
                        }
                    }
                else if (strcmp(op,"2") ==0){
                    registrazione();
                    }
                else if (strcmp(op,"3")==0){
                    gestore();
                    //break;
                    }
                else
                    printf("\nValore non valido\n");

                 }
        }}



