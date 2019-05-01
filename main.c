#include "libraries.h"
#include "defines.h"
void texto(void *font, char *s, float x, float y){
    unsigned int i;
    glRasterPos2f(x, y);
    for (i = 0; i < strlen(s); i++)          //imprime caracter por caracter
        glutBitmapCharacter(font, s[i]);
}

void colisao(){
    if(obstaculo1.x <= personagem.x + personagem.lado && personagem.y <= obstaculo1.y + obsLado && obstaculo1.x >=-9){ //se o obstaculo 1 ocupar o mesmo x e y do personagem, ha colisao (-9 pois a flowey nao ocupa 100% exatos do quadrado)
        Mix_PlayChannel(-1, somColisao, 0);
        personagem.vidas--;
        obstaculo1.x = 100;
    }
    if(obstaculo2.x <= personagem.x + personagem.lado && obstaculo2.x >= -9 && personagem.y + personagem.lado >= obstaculo2.y && personagem.y <= obstaculo2.y){
        Mix_PlayChannel(-1, somColisao, 0);
        personagem.vidas--;
        obstaculo2.x = 150;
    }
    if(powerup.x <= personagem.x + personagem.lado && personagem.y <= powerup.y + obsLado && powerup.x >=-9){ //colisao com o powerup da uma vida a mais
        Mix_PlayChannel(-1, somVida, 0);
        personagem.vidas++;
        powerup.x = 2500;
        if(personagem.vidas >= 5) //impossivel ficar com mais que 4 vidas
            personagem.vidas = 4;
    }
}

void obstaculos(){
    if(obstaculo1.x <= -40) obstaculo1.x = 100;              //volta o(s) obstaculo(s) pro inicio da tela, pra ele(s) aparecer(em) de novo
    if(obstaculo2.x <= -40) obstaculo2.x = 100;
    obstaculo1.x -= obstaculo1.speed;     //obstaculo(s) fica(m) mais rapido(s) com o tempo
    obstaculo1.speed += 0.00017;
    obstaculo2.x -=obstaculo2.speed;
    obstaculo2.speed +=0.00015;

    if(obstaculo1.speed > 18 || obstaculo2.speed > 17){ //limita a velocidade pra nao ficar impossivel depois de um tempo
        obstaculo1.speed = 18;
        obstaculo2.speed = 15;
    }
    glutPostRedisplay();
}

void powerups(){
    powerup.x -= powerup.speed;             //o powerup age como um obstaculo, mas demora mais pra aparecer
    if(powerup.x <= -40) powerup.x = 2500;
}

void pular(){
    if(jump){                                //se pular, soma um numero empirico a posicao y
        personagem.y += jValue;
        if(personagem.y <= 0){               //se chegou no chao, finaliza o pulo
        	jValue = 5.5;
            personagem.y = 0;
            jump = 0;
        }
        jValue -= 0.5;                       //acao da gravidade
        glutPostRedisplay();
    }
}
void abaixar(){
	if(abaixa){                              					//diminui o lado do personagem se ele abaixar
		if(personagem.y > 0) personagem.y - 0.5;                //(tinham jeitos melhores de fazer isso mas nao achei sprite decente do link abaixando entao
		if(personagem.y <= 0) personagem.lado = 8.8;			//fiz assim pra nao ficar muito tosco)
	}
    else personagem.lado = 10;
    glutPostRedisplay();
}
void desenhaCena(){
    glClear(GL_COLOR_BUFFER_BIT); //limpa a tela
    glColor3f(1, 1, 1);
    glEnable(GL_TEXTURE_2D);      //habilita o uso de texturas
    glBindTexture(GL_TEXTURE_2D, FUNDO);    //binda e desenha o fundo
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex3f(fundoPos,          0, 0);
        glTexCoord2f(1, 0); glVertex3f(fundoPos+100,      0, 0);
        glTexCoord2f(1, 1); glVertex3f(fundoPos+100,    100, 0);
        glTexCoord2f(0, 1); glVertex3f(fundoPos,        100, 0);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex3f(fundoPos+100,      0, 0);	//sao dois pra imagem ficar andando
        glTexCoord2f(1, 0); glVertex3f(fundoPos+200,      0, 0);
        glTexCoord2f(1, 1); glVertex3f(fundoPos+200,    100, 0);
        glTexCoord2f(0, 1); glVertex3f(fundoPos+100,    100, 0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, ESTRELAS); //binda e desenha as estrelas
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex3f(estrelasPos,      55, 0);
        glTexCoord2f(1, 0); glVertex3f(estrelasPos+100,  55, 0);
        glTexCoord2f(1, 1); glVertex3f(estrelasPos+100, 100, 0);
        glTexCoord2f(0, 1); glVertex3f(estrelasPos,     100, 0);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex3f(estrelasPos+100,  55, 0);    //estrelas mesmo esquema
        glTexCoord2f(1, 0); glVertex3f(estrelasPos+200,  55, 0);
        glTexCoord2f(1, 1); glVertex3f(estrelasPos+200, 100, 0);
        glTexCoord2f(0, 1); glVertex3f(estrelasPos+100, 100, 0);
    glEnd();
    estrelasPos -= spdEstrelas; //as estrelas andam mais devagar que o fundo, que anda mais devagar que os objetos mais proximos do usuario
    fundoPos -= spdFundo;
    if(estrelasPos <= -100) estrelasPos = 0;
    if(fundoPos <= -100)    fundoPos = 0;

    if(!jump && !abaixa){       //se estiver andando, anima o personagem correndo
        k+=0.1;
        glBindTexture(GL_TEXTURE_2D, LINK);
        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(k-0.1, 0); glVertex3f(personagem.x, personagem.y, 0);
            glTexCoord2f(k, 0); glVertex3f(personagem.x + personagem.lado, personagem.y, 0);
            glTexCoord2f(k, 1); glVertex3f(personagem.x + personagem.lado, personagem.y + personagem.lado, 0);
            glTexCoord2f(k-0.1, 1); glVertex3f(personagem.x, personagem.y + personagem.lado, 0);
        glEnd();
        if(k >= 1.00) k = 0.0;
    }
    else{                      //se nao anima o pulo ou ele abaixando
	    if(jump)
	        glBindTexture(GL_TEXTURE_2D, PULO);
	    if(abaixa)
	        glBindTexture(GL_TEXTURE_2D, ABAIXA);
	    glBegin(GL_TRIANGLE_FAN);
	        glTexCoord2f(0, 0); glVertex3f(personagem.x, personagem.y, 0);
	        glTexCoord2f(1, 0); glVertex3f(personagem.x + personagem.lado, personagem.y, 0);
	        glTexCoord2f(1, 1); glVertex3f(personagem.x + personagem.lado, personagem.y + personagem.lado, 0);
	        glTexCoord2f(0, 1); glVertex3f(personagem.x, personagem.y + personagem.lado, 0);
	    glEnd();
    }
    glBindTexture(GL_TEXTURE_2D, OBS1);  //desenha a flowey
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex3f(obstaculo1.x, obstaculo1.y, 0);
        glTexCoord2f(1, 0); glVertex3f(obstaculo1.x + obsLado, obstaculo1.y, 0);
        glTexCoord2f(1, 1); glVertex3f(obstaculo1.x + obsLado, obstaculo1.y + obsLado, 0);
        glTexCoord2f(0, 1); glVertex3f(obstaculo1.x, obstaculo1.y + obsLado, 0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, OBS2);  //desenha a shuriken
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex3f(obstaculo2.x, obstaculo2.y, 0);
        glTexCoord2f(1, 0); glVertex3f(obstaculo2.x + obsLado, obstaculo2.y, 0);
        glTexCoord2f(1, 1); glVertex3f(obstaculo2.x + obsLado, obstaculo2.y + obsLado, 0);
        glTexCoord2f(0, 1); glVertex3f(obstaculo2.x, obstaculo2.y + obsLado, 0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, VIDAEXTRA); //desenha o powerup
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex3f(powerup.x, powerup.y, 0);
        glTexCoord2f(1, 0); glVertex3f(powerup.x + obsLado, powerup.y, 0);
        glTexCoord2f(1, 1); glVertex3f(powerup.x + obsLado, powerup.y + obsLado, 0);
        glTexCoord2f(0, 1); glVertex3f(powerup.x, powerup.y + obsLado, 0);
    glEnd();
    if(personagem.vidas == 0) glBindTexture(GL_TEXTURE_2D, VIDAS0); //nessa parte desenha o coracao indicando as vidas do personagem
    if(personagem.vidas == 1) glBindTexture(GL_TEXTURE_2D, VIDAS1);
    if(personagem.vidas == 2) glBindTexture(GL_TEXTURE_2D, VIDAS2);
    if(personagem.vidas == 3) glBindTexture(GL_TEXTURE_2D, VIDAS3);
    if(personagem.vidas == 4) glBindTexture(GL_TEXTURE_2D, VIDAS);
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex3f(5, 85, 0);
        glTexCoord2f(1, 0); glVertex3f(15, 85, 0);
        glTexCoord2f(1, 1); glVertex3f(15, 95, 0);
        glTexCoord2f(0, 1); glVertex3f(5, 95, 0);
    glEnd();
    if(gameover){ //aqui desenha a telinha de gameover
    glBindTexture(GL_TEXTURE_2D, MORTE);
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex3f(30, 50, 0);
        glTexCoord2f(1, 0); glVertex3f(75, 50, 0);
        glTexCoord2f(1, 1); glVertex3f(75, 70, 0);
        glTexCoord2f(0, 1); glVertex3f(30, 70, 0);
    glEnd();
    }
    glDisable(GL_TEXTURE_2D);
    if(obstaculo2.x + obsLado <= personagem.x && abaixa)  //aqui termina o "abaixa" quando passar pela shuriken
    	abaixa = 0;
    sprintf(personagem.scoreString, "SCORE: %llu", personagem.score);     //converte o score para string a ser printada
    glColor3f(.2, .8, .1);
    texto(GLUT_BITMAP_TIMES_ROMAN_24, personagem.scoreString, 70, 90);    //desenha a string com o score
    glutSwapBuffers();
}
void atualiza(int indice){
    if(!pausa && !esc && !restart && !gameover && !menu){                       //jogo rolando
	    if(!musicajogotocando){
	   		Mix_PlayMusic(musica, -1);
	    	musicajogotocando = 1;
	    	musicamenutocando = 0;
	    }
	    if(personagem.vidas == 0){
       		musicajogotocando = 0;
       		Mix_PlayMusic(somGameover, 0);
       		gameover = 1;
       	}
	    pular();
	    abaixar();
	    obstaculos();
	    colisao();
        powerups();
        personagem.score++;                                    //incremento de pontuacao
    }
    else if(menu){
    	if(!musicamenutocando){
    		Mix_PlayMusic(somMenu, -1);
    		musicamenutocando = 1;
    	}
    	glColor3f(.2, 1.0, .2);
        texto(GLUT_BITMAP_TIMES_ROMAN_24, "LINK RUNNER", 35, 10);
        texto(GLUT_BITMAP_TIMES_ROMAN_24, "PRESSIONE 'enter' PARA JOGAR", 26, 7);
        glEnd();
        glColor3f(1, 1, 1);
    	glEnable(GL_TEXTURE_2D);
    	glBindTexture(GL_TEXTURE_2D, MENULINK);    //binda o logo
    	glBegin(GL_TRIANGLE_FAN);
        	glTexCoord2f(0, 0); glVertex3f(20, 40,  0);
        	glTexCoord2f(1, 0); glVertex3f(80, 40,  0);
        	glTexCoord2f(1, 1); glVertex3f(80, 100, 0);
        	glTexCoord2f(0, 1); glVertex3f(20, 100, 0);
    	glEnd();
    	glBindTexture(GL_TEXTURE_2D, MENUPLAY);    //binda o play
    	glBegin(GL_TRIANGLE_FAN);
        	glTexCoord2f(0, 0); glVertex3f(40, 20, 0);
        	glTexCoord2f(1, 0); glVertex3f(60, 20, 0);
        	glTexCoord2f(1, 1); glVertex3f(60, 40, 0);
        	glTexCoord2f(0, 1); glVertex3f(40, 40, 0);
    	glEnd();
    	glDisable(GL_TEXTURE_2D);
    	glutSwapBuffers();
    }
    else if(pausa){
        glColor3f(.3, 1.0, .9);
        texto(GLUT_BITMAP_TIMES_ROMAN_24, "JOGO PAUSADO!", 30, 50);
        texto(GLUT_BITMAP_TIMES_ROMAN_10, "clique 'p' ou continue jogando", 40, 45);
        glEnd();
        glutSwapBuffers();
    }
    else if(esc){
        glColor3f(.3, 1.0, .9);
        texto(GLUT_BITMAP_TIMES_ROMAN_24, "VAI EMBORA NAO, RAPAZ", 30, 50);
        texto(GLUT_BITMAP_TIMES_ROMAN_10, "clique 'ESC' novamente para sair ou continue jogando", 40, 45);
        glEnd();
        glutSwapBuffers();
    }
    else if(restart){
        glColor3f(.3, 1.0, .9);
        texto(GLUT_BITMAP_TIMES_ROMAN_24, "DESEJA REINICIAR O JOGO?", 30, 50);
        texto(GLUT_BITMAP_TIMES_ROMAN_10, "clique 'r' novamente para reiniciar", 40, 45);
        glEnd();
        glutSwapBuffers();
    }
    else if(gameover){
        glColor3f(1.0, 0.0, 0.0);
        texto(GLUT_BITMAP_TIMES_ROMAN_24, "clique 'r' para reiniciar ou 'ESC' para sair", 25, 40);
        glEnd();
        glutSwapBuffers();
    }
    glutTimerFunc(25, atualiza, 0);
}
void redimensiona(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 100, 0.0, 100, 1.0, -1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void defineTexturas(){
	MENULINK =  SOIL_load_OGL_texture("LOGO.png",       SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	MENUPLAY =  SOIL_load_OGL_texture("PLAY.png",       SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    LINK     =  SOIL_load_OGL_texture("LINK.png",       SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    FUNDO    =  SOIL_load_OGL_texture("FUNDO.png",      SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    ESTRELAS =  SOIL_load_OGL_texture("ESTRELAS.png",   SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    OBS1     =  SOIL_load_OGL_texture("FLOWEY.png",     SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    OBS2     =  SOIL_load_OGL_texture("SHURIKEN.png",   SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    PULO     =  SOIL_load_OGL_texture("PULO.png",       SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    MORTE    =  SOIL_load_OGL_texture("GAMEOVER.png",   SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    ABAIXA   =  SOIL_load_OGL_texture("PULO.png",       SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    VIDAS    =  SOIL_load_OGL_texture("VIDAS.png",      SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    VIDAS0   =  SOIL_load_OGL_texture("VIDAS0.png",     SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    VIDAS1   =  SOIL_load_OGL_texture("VIDAS1.png",     SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    VIDAS2   =  SOIL_load_OGL_texture("VIDAS2.png",     SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    VIDAS3   =  SOIL_load_OGL_texture("VIDAS3.png",     SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    VIDAEXTRA = SOIL_load_OGL_texture("VIDAEXTRA.png",     SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (!MENULINK || !MENUPLAY || !LINK || !FUNDO || !ESTRELAS || !OBS1 || !OBS2 || !PULO || !MORTE || !ABAIXA || !VIDAS || !VIDAS0 || !VIDAS1 || !VIDAS2 || !VIDAS3 || !VIDAEXTRA)
        printf("Erro carregando textura: '%s'\n", SOIL_last_result());
}
void defineSons(){
	musica =      Mix_LoadMUS("spearofjustice.mp3");
    somMenu =     Mix_LoadMUS("musicamenu.mp3");
    somGameover = Mix_LoadMUS("gameover.mp3");
    somColisao =  Mix_LoadWAV("colide.wav");
    somVida =     Mix_LoadWAV("powerupsound.wav");
}
void definePersonagem(){
	personagem.x =     0; 
    personagem.y =     0;
    personagem.lado = 10;
    personagem.vidas = 4;
    personagem.score = 0;
}
void defineObstaculos(){
	obstaculo1.x =   100;
    obstaculo1.y =     0;
    obstaculo1.speed = 2;
    obstaculo2.x =   150;
    obstaculo2.y =     9;
    obstaculo2.speed = 2;
    powerup.x =     2500;
    powerup.y =        0;
    powerup.speed =    2;
}
void inicializa(){
    defineTexturas();
    defineSons();
    definePersonagem();
    defineObstaculos();
    Mix_PlayMusic(musica, -1);
}
void teclado(unsigned char key, int x, int y){
    switch(key){
    case 27:                                      //ESC
        if(!pausa && !restart){
        	if(!esc && !gameover) esc = 1;
            else exit(0);
        }
        break;
    case 'w':
    case 'W':
    case 32:  //spacebar tambem pula
        if(esc) esc = 0;
        if(restart) restart = 0;
        if(pausa) pausa = 0;
        if(abaixa) abaixa = 0;
        jump = 1;
        break;
    case 'p':
    case 'P':
        if(!esc && !restart && !gameover && !pausa)
        	pausa = 1;
            else pausa = 0;
        break;
    case 's':
    case 'S':
        abaixa = 1;
        break;
    case 'r':
    case 'R':
        if(!esc && !pausa && !gameover && !restart) restart = 1;
        else if(gameover && !pausa && !esc){
        	gameover = 0;
            inicializa();
        }
        else if(!pausa && !esc){
        	restart = 0;
        	inicializa();
        }
        break;
    case 13:     //se clicar enter no menu, inicia o jogo
        if(menu){
        	menu = 0;
        	inicializa();
        }
        break;
    default:
        break;
   }
}
void main(int argc, char **argv){
    glutInit(&argc, argv);
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Link Runner");
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    inicializa();
    glutDisplayFunc(desenhaCena);
    glutReshapeFunc(redimensiona);
    glutKeyboardFunc(teclado);
    glutTimerFunc(25, atualiza, 0);
    glutMainLoop();
}