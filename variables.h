typedef struct{
    float x, y;
    int lado, vidas;
    unsigned long long int score;
    char scoreString[20];   //string pra mostrar o score ate eu descobrir como printar int naquela bosta
}PERSONAGEM;

typedef struct{
    float x, y, speed;
}OBSTACULO;

float jValue = 5, jLimDown = 0;   //variaveis que auxiliam no pulo
float k = 0.0;                    //usei essa variavel pra fluir textura (iterar a cada frame), esta declarada aqui pois nao da pra usar loop for
float fundoPos = 0.0, estrelasPos = 0.0;
int abaixa = 0, jump = 0, colide = 0, menu = 1, pausa = 0, esc = 0, restart = 0, gameover = 0, musicamenutocando = 0, musicajogotocando = 0; //flags "booleanas"
GLuint MENULINK, MENUPLAY, LINK, FUNDO, ESTRELAS, OBS1, OBS2, PULO, MORTE, ABAIXA, HEARTS, VIDAS, VIDAS0, VIDAS1, VIDAS2, VIDAS3, VIDAEXTRA; //variaveis de textura
Mix_Music *musica, *somMenu, *somGameover; //variaveis de musica
Mix_Chunk *somColisao, *somVida;
PERSONAGEM personagem;                                 //declaracao dos obstaculos e do personagem
OBSTACULO obstaculo1, obstaculo2, powerup; 
