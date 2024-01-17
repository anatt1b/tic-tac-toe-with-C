#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>


// Initializing global variables. Näitä voidaan käyttää ohjelman kaikissa eri vaiheissa.
char board[3][3];
const char PLAYER = 'X';
const char COMPLAYER = 'O';


// Funktioiden eli aliohjelmien declarointi. alempana koodissa funktioille määritetään toiminnot.
void resetboard();
void printBoard();
int checkFreeSpaces();
void playermove();
void compMove();
char checkWinner();
void printWinner(char);

// Pääohjelma
int main(){
    printf("|--------- Tic Tac Toe ---------|\n\n");
    printf("INSTRUCTIONS\n\n");
    printf("PLAYER vs COMPUTER\n");
    printf("Choose row 1-3 and then choose column 1-3.\n\n");
    
     //Alustetaan merkkimuuttuja winner tyhjäksi.
    char winner = ' ';
    
    //Kutsutaan funktiota alustamaan pelilauta tyhjillä soluilla
    resetboard();

    // Silmukalla aloitetaan pääfunktio.
    // voittaja ei ole selvillä ja laudalla on vapaata tilaa
    while(winner ==' ' && checkFreeSpaces())
    {
        //Funktio kutsu laudan tulostukseen, jotta pelaaja näkee pelitilanteen.
        printBoard();

        //Funktio kutsu pelaajan liikulle
        playermove();

        // Kutsutaan checkWinner funktiota tarkistamaan onko pelaaja voittanut.
        // Voittajan merkki tallennetaan winner-muuttujaan (PLAYER = 'X' TAI COMPLAYER = 'Y')
        // jos toinen ehdoista toteutuu
        winner = checkWinner();

        // Tarkistetaan onko peli päättynyt pelaajan siirron jälkeen. 
        // Jos winner-muuttuja ei ole välilyönti tai pelilaudalla ei ole enää tyhjiä soluja, peli on päättynyt ja silmukka keskeytetään.
        if(winner != ' ' || checkFreeSpaces() == 0)
        {
            break;
        }
        compMove();
        winner = checkWinner();
        if(winner != ' ' || checkFreeSpaces() == 0)
        {
            break;
        }
    }

    // Kutsutaan funktio tulostamaan pelitaulu pelin jälkeen,
    // jotta tulosta voi tarkastella.
    printBoard();

    // Tulosta voittaja tai tasapeli.
    printWinner(winner);

    return 0;
}
// Alustetaan pelilauta tyhjäksi sisäkkäisillä silmukoilla.
// i silmukka alustaa Y-akselin solut eli rivit ylhäältä alas.
// j silmukka alustaa X-akselin solut eli sarakkeet pysty suunnassa vasemmalta oikealle.
void resetboard(){ 

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            // asetetaan solut tyhjiksi iteraattorien osoittamissa paikoissa.
            board[i][j] = ' ';
        }
    }
}

// Laudan tulostus funktio.
void printBoard(){ 
    
    // Tulostetaan vaakasuora viiva
    printf("columns:   1    2    3\n");
    printf("          ""-------------\n");
    // pelilaudan ensimmäisen rivi tulostetaan, joka koostuu kolmesta solusta, eroteltuna pystyviivoin ja välilyönnein. 
    // %c on muotoilumerkintä merkkimuuttujille, ja se korvataan pelilaudan solujen arvoilla board[0][0], board[0][1] ja board[0][2]. 
    printf("1.row     ""| %c | %c | %c |\n", board[0][0], board[0][1], board[0][2]);
    printf("          ""|---|---|---|\n");
    printf("2.row     ""| %c | %c | %c |\n", board[1][0], board[1][1], board[1][2]);
    printf("          ""|---|---|---|\n");
    printf("3.row     ""| %c | %c | %c |\n", board[2][0], board[2][1], board[2][2]);
    printf("          ""-------------\n");
    printf("\n");

    
}

// Funktio vapaan tilan tarkastukseen laudalta.
int checkFreeSpaces(){ 
    // luodaan kokonaislukumuuttuja ja asetetaan sen arvo 9 (solujen määrä laudassa.)
    int freespaces = 9;


    for(int i = 0; i < 3; i++){

        for(int j = 0; j < 3; j++){
            // Tämä rivi tarkistaa onko pelilaudan solussa, joka sijaitsee silmukan indeksien i ja j osoittamassa paikassa, merkki eri kuin välilyönti (merkki ' '). 
            // Jos solussa on jokin muu merkki kuin välilyönti, se ei ole tyhjä.
            if(board[i][j] != ' '){
                // Aina, kun silmukasta löytyy jo täytetty solu vähennetään freespaces muuttujasta 1 solu.
                freespaces--;
            }

        }
    }
    // Kun jokainen solu on käyty läpi palautetaan funktiolle jäljellä oleva arvo.
    return freespaces;
    
}

// funktio pelaajan liikkumiselle laudalla.
void playermove(){ 

    // luodaan kokonaislukumuuttujat joita äytetään pelaajan syöttämien rivin ja sarakkeen tallentamiseen.
    int x, y;
    
    // Do - while silmukka. Silmukka suoritetaan vähintään kerran, jos pelaaja tekee kelvollisen valinnan
    // eli valitsee tyhjän solun. Silmukka siis tarkistaa onko pelaajan valitsema solu tyhjä ja jos ei ole
    // antaa se virhe ilmoituksen.
    do
    {
        printf("\nEnter row 1-3: ");
        scanf("%d", &x);
        // Onnistuneessa valinnassa vähennetään muuttujan arvoa yhdellä
        // eli täytetty solu ei ole enää tyhjä.
        x--;

        printf("\nEnter column 1-3: ");
        scanf("%d", &y);
        y--;

        // Tarkistetaan, onko pelaajan valitsema solu pelilaudalla jo varattu eli sen arvo ei ole välilyönti ' '. 
        // Jos solu ei ole tyhjä, tulostetaan "INVALID MOVE" ilmoitus ja pelaajaa pyydetään syöttämään uusi siirto.
        if(board[x][y] !=' '){
            printf("\nINVALID MOVE\n");
        }

        // Jos valittu solu on tyhjä, eli ehto if(board[x][y] != ' ') ei ole tosi, niin pelaajan merkki (globaali muuttuja PLAYER = 'X') asetetaan kyseiseen ruutuun pelilaudalla
        //  ja silmukan suoritus päättyy break-lauseeseen. 
        // Pelaaja onnistui tekemään kelvollisen siirron, joten silmukka päättyy komennolla break;.
        else{
            board[x][y] = PLAYER;
            break;
    }
    } while (board[x][y] != ' ');
    
    
    
}

// Funktio tietokone vastustajan liikkeille
void compMove(){ 
    // luodaan rng eli RandomNumberGenerator. 
    // Tällä saadaan erilaisia satunnaislukuja joka kerta, kun ohjelma suoritetaan.
    srand(time(0));

    // määritellään kaksi kokonaislukumuuttujaa x ja y, 
    // joita käytetään tietokoneen generoiman siirron tallentamiseen.
    int x;
    int y;
    
    // Tarkistetaan onko pelilaudalla vielä vapaata tilaa (tyhjiä soluja) kutsumalla checkFreeSpaces-funktiota. 
    // Jos pelilaudalla on ainakin yksi tyhjä ruutu, tietokone voi tehdä siirron.
    if(checkFreeSpaces() > 0)
    {

        // Do - while silmukkaa suoritetaan niin kauan kuin tietokoneen generoimat satunnaiset x ja y koordinaatit osoittavat pelilaudan soluun, joka ei ole tyhjä (sen arvo ei ole välilyönti ' '). 
        // Eli tietokone yrittää uudelleen, kunnes se löytää tyhjän ruudun.
        do
        {
            // generoidaan satunnaisia lukuja(koordinaatteja) indeksien sisällä(pelilaudalla)
            // rand()-funktio palauttaa satunnaisen kokonaisluvun, ja % 3 varmistaa, että arvot ovat välillä 0-2, mikä vastaa pelilaudan indeksejä.
            x = rand() % 3;
            y = rand() % 3;
            
            // Tarkistetaan onko solu jo käytössä
        } while (board[x][y] !=' ');

        // Kun löydetään tyhjä solu (board[x][y] == ' '), tietokoneen merkki (globaasli muuttuja COMPLAYER = 'Y') asetetaan kyseiseen soluun pelilaudalla.
        board[x][y] = COMPLAYER;
    }

    // Jos pelilaudalla ei ole yhtään tyhjää solua kutsutaan printwinner funktiota ilmoittamaan tasapelistä.
    else
    {
        printWinner(' ');
    }
    
}
char checkWinner(){ 
    //Silmukka käy läpi vaakarivit
    for(int i = 0; i < 3; i++){
        // ehtolauseella tarkistetaan, ovatko kaikissa soluissa tietyllä rivillä samat merkit. 
        // Jos kaikki solut ovat samat, niin kyseessä on voitto, ja funktio palauttaa voittajan merkin (joko pelaajan tai tietokoneen).
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2]){
            // Palautus arvona käy kaikki ylläolevat solumerkinnät.
            return board[i][0];
        }
    }
    //Silmukka käy läpi sarakkeet
    for(int i = 0; i < 3; i++){
        if(board[0][i] == board[1][i] && board[0][i] == board[2][i]){
        return board[0][i];
        }
    }
    //Ehtolause tarkistaa, ovatko solut diagonaalilla (ylhäältä vasemmalta[0][0] alas oikealle[2][2]) samat merkit. 
    if(board[0][0] == board[1][1] && board[0][0] == board[2][2]){
        // Palautetaan solussa [0][0], [1][1] tai [2][2] oleva arvo voittajana
        return board[0][0];
    }
    //Ehtolause tarkistaa, ovatko solut diagonaalilla (ylhäältä oikealta[0][2] alas vasemmalle[2][0]) samat merkit.
     if(board[0][2] == board[1][1] && board[0][2] == board[2][0]){
        // Palautetaan solussa [0][2], [1][1] tai [2][0] oleva arvo voittajana
        return board[0][2];
    }
    // Jos yllä olevat tarkistukset eivät täyty palautus arvo on tyhjä (' ') eli peli jatkuu.
    return ' ';
}

// Funktio voittajan tarkistamiseen

    void printWinner(char winner){
    // Ternary-operaattori tarkistaa voittajan merkin ja valitsee tulostettavan viestin sen perusteella.
    char *message = (winner == PLAYER) ? "YOU WIN! GGWP! :)" :  (winner == COMPLAYER) ? "YOU LOSE O-('',Q)" :   "DRAW";

    printf("\n%s\n", message);
}
