/*---------------- UCITAVAMO U NIZ SVE VRIJEDNOSTI IZ DATOTEKE EVENT.dat -----------------*/
void input_all(vector <EVENT> &niz){
    FILE *fp = fopen("EVENT.dat", "rb");

    EVENT buff;

    while ( fread(&buff, sizeof(EVENT), 1, fp) ){
        niz.push_back(buff);
    }

    fclose(fp);
}
