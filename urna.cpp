#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <math.h>
#include <locale.h>
#include <time.h>
#include "urnavisual.h" //Biblioteca criada para juntar as funções gráficas do programa

struct candidato {          //Registro de dados do candidato
    char nomeCompleto[51];
    char empresa[21];
    char imagem[23];
    char descricao1[100];
    char descricao2[100];
    char descricao3[100];
    char descricao4[100];
    char descricao5[100];
    char descricao6[100];
    char descricao7[100];
    char descricao8[100];
    int x1;
    int x2;
    int y1;
    int y2;
    int votos;
};

struct eleitores {          //Registro de dados do eleitor
    char nomeCompleto[51];
    char cpf[14];
    char imagem[30];
    int voto;
};

struct eleitores listasEleitores[6];        //Vetor de registros totalizando 6 eleitores
struct candidato listasCandidatos[6];       //Vetor de registros totalizando 6 candidatos

void cadastroCandidato(int x, int y);       //Dados dos candidatos adicionados aos registros
void cadastroEleitores();                   //Dados dos eleitores adicionados aos registros

void bemVindoNome(int x, int y, char bemVindo[65], int indiceNome);    //Título de "Bem-vindo (nome do candidato)" após o login
void imagemCandidatos(int x, int y);                                    //Arranja na tela as imagens dos 6 candidatos
void selecionarCandidato(int x, int y,int msx, int msy);               //Detecta a posição do mouse, com base nisso seleciona um candidato e mostra isso ao usuário utilizando uma imagem escurecida dele
void escolherCandidato(int *i, int msx, int msy, int *next);           //Detecta a posição e o clique do mouse, com base nisso escolhe um candidato

void candidatoEscolhido(int *escolha, int x, int y);                    //Muda a tela para a do candidato escolhido

void telaCampeao(int x, int y);                                        //Mostra a tela do vencedor da eleição
void mostrarRanking(int x, int y);

 void ordenarRanking();

 void gerarVotos(int digito);



main()
{
    srand(time(NULL));
    setlocale(LC_ALL,"Portuguese");

      int yMax = getmaxheight();
      int xMax = getmaxwidth();
      int digito;
      char textoTeste[15];
      int tamanho = 0;
      int contador = 0;
      int controle = 0;
      int verdadeiroCpf;
      int barraEscrever = 0;
      int next = 0;
      char bemVindo[65];
      int i;
      int guardaIndiceNome;
      int escolha = 6;
      char esc;
      int votoComputado = 0;
      int totalDeVotos = 0;
      int maior;
      char votos[5];
      char textoTotalDeVotos[20];

      cadastroEleitores();
      cadastroCandidato(xMax, yMax);
      initwindow(getmaxwidth(),getmaxheight(),"Sistema de votacao",0,0, false, true);

      while(next!=6) {
      contador=0;
      controle=0;

      while(next == 0)
      {

          if(totalDeVotos==3)
          {
              next=5;
          }

          votoComputado=0;

         if(controle==0){
         barraEscrever =0;
         iniciarGrafico(xMax, yMax, textoTeste);
         controle=1;
         }

         tamanho = strlen(textoTeste);


         if(tamanho == 14 && contador == 0)
           contador = 1;

         else if(tamanho < 14 && contador == 2)
            {
                botao(xMax, yMax, 30, 45, 8, 15, 0, 0,"Continuar");
                contador = 0;
            }

         if(contador == 1)
            {
                botao(xMax, yMax, 30, 45, 0, 15, 0, 0,"Continuar");
                contador = 2;
            }

            if(kbhit())
            {
               digito = getch();
               cpf(xMax, yMax, digito, textoTeste, tamanho);
               barraDeDigitar(digito, tamanho,&barraEscrever);
            }
            else if(tamanho < 14)
            {
               aparecerBarraDeDigitar(xMax, yMax, barraEscrever);
            }


         if (mousex() > ((xMax/2)-40) && mousex() < ((xMax/2)+40) &&
             mousey() < ((yMax/2)+(30*2)) && mousey() > ((yMax/2)+30) && tamanho ==14)
             {
                 botao(xMax, yMax, 30, 45, 15, 0, 0, 0,"Continuar");
                 delay(500);
                 botao(xMax, yMax, 30, 45, 0, 15, 0, 0,"Continuar");

             }

             if ((ismouseclick(WM_LBUTTONDOWN) &&
                  mousex() > ((xMax/2)-40) && mousex() < ((xMax/2)+40) &&
                  mousey() < ((yMax/2)+(30*2)) && mousey() > ((yMax/2)+30) || digito == 13) && tamanho ==14)
                {
                    for(i=0;i<6;i++)
                        {
                            verdadeiroCpf = strcmp(textoTeste,listasEleitores[i].cpf);
                            if(verdadeiroCpf == 0 && listasEleitores[i].voto==0)
                            {
                                guardaIndiceNome = i;
                                break;
                            }
                            if(listasEleitores[i].voto==1 && verdadeiroCpf==0)
                                votoComputado +=1;
                        }
                        validarCpf(xMax, yMax, verdadeiroCpf, &digito, &next, textoTeste, votoComputado);

                }

         clearmouseclick(WM_LBUTTONDOWN);
      }


       contador=0;

       while(next == 1)
      {

        if(contador==0){
        bemVindoNome(xMax, yMax, bemVindo, guardaIndiceNome);
        imagemCandidatos(xMax, yMax);
        contador=1;
        }

        if(ismouseclick(WM_LBUTTONDOWN))
        escolherCandidato(&escolha, mousex(), mousey(), &next);
        clearmouseclick(WM_LBUTTONDOWN);
        selecionarCandidato(xMax, yMax, mousex(), mousey());

        if(kbhit())
        {
            digito = getch();
            if(digito == 103)
            {
                gerarVotos(digito);
            }
        }

      }

      contador=0;
      controle=0;

      while(next==2){



        if(contador==0) {
        candidatoEscolhido(escolha, xMax, yMax);
        botao(xMax/2 - 500, yMax/2 -380, 30, 40, 0, 15, 0, 15,"Voltar");
        contador=1;
        }

        if(mousex() > (((xMax/2)-500)/2)-40-15 && mousex() < (((xMax/2)-500)/2)+40+15 &&
           mousey() > (((yMax/2)-380)/2)+30 &&  mousey() < (((yMax/2)-380)/2)+30*2)
        {
        botao(xMax/2 - 500, yMax/2 -380, 30, 40, 15, 0, 0, 15,"Voltar");
        delay(200);
        botao(xMax/2 - 500, yMax/2 -380, 30, 40, 0, 15, 0, 15,"Voltar");

        }

        if(ismouseclick(WM_LBUTTONDOWN) && mousex() > (((xMax/2)-500)/2)-40-15 && mousex() < (((xMax/2)-500)/2)+40+15 &&
           mousey() > (((yMax/2)-380)/2)+30 &&  mousey() < (((yMax/2)-380)/2)+30*2)
           {
               next=1;
           }

        if(mousex() > (((xMax/2)+500)/2)-40-15 && mousex() < (((xMax/2)+500)/2)+40+15 &&
           mousey() > (((3*yMax/2)-50)/2)+30 &&  mousey() < (((3*yMax/2)-50)/2)+30*2) {
           botao(xMax/2 + 500, 3*yMax/2 - 50, 30, 40, 15, 0, 0, 30,"Sim");
           delay(200);
           botao(xMax/2 + 500, 3*yMax/2 - 50, 30, 40, 0, 15, 0, 30,"Sim");
        }

        if(ismouseclick(WM_LBUTTONDOWN) &&
           mousex() > ((xMax/2 - 500)/2)-40 && mousex() < ((xMax/2 + 500)/2)+40 &&
           mousey() > ((3*yMax/2 -50)/2)+30 &&  mousey() < ((3*yMax/2 -50)/2)+(30*2))   //CLIQUE NO SIM
           {
               next=3;
           }

        if(mousex() > ((3*xMax/2 - 500)/2)-40 && mousex() < ((3*xMax/2 - 500)/2)+40 &&
           mousey() > ((3*yMax/2 -50)/2)+30 &&  mousey() < ((3*yMax/2 -50)/2)+(30*2)) {
           botao(3*xMax/2 - 500, 3*yMax/2 -50, 30, 40, 15, 0, 0, 33,"Não");
           delay(200);
           botao(3*xMax/2 - 500, 3*yMax/2 -50, 30, 40, 0, 15, 0, 33,"Não");
        }

        if(ismouseclick(WM_LBUTTONDOWN) &&
           mousex() > ((3*xMax/2 - 500)/2)-40 && mousex() < ((3*xMax/2 - 500)/2)+40 &&   //CLIQUE NO NÃO
           mousey() > ((3*yMax/2 -50)/2)+30 &&  mousey() < ((3*yMax/2 -50)/2)+(30*2))
           next=1;





         clearmouseclick(WM_LBUTTONDOWN);
        }

        contador=0;


        while(next==3){

            if(contador==0){
                telaConfirmarVoto(xMax, yMax, 0);
                contador=1;
            }

            if(mousex() < ((xMax/2 + 535)/2)+40+15 && mousex() > ((xMax/2 + 535)/2)-40-15
               && mousey() > ((3*yMax/2-400)/2)+30 && mousey() < ((3*yMax/2-400)/2)+30*2){
                  botao(xMax/2 + 535, 3*yMax/2 - 400, 30, 40, 15, 2, 2, 30,"Sim");
                  delay(200);
                  botao(xMax/2 + 535, 3*yMax/2 - 400, 30, 40, 0, 15, 0, 30,"Sim");
             }

             if(ismouseclick(WM_LBUTTONDOWN) && mousex() < ((xMax/2 + 535)/2)+40+15 && mousex() > ((xMax/2 + 535)/2)-40-15
               && mousey() > ((3*yMax/2-400)/2)+30 && mousey() < ((3*yMax/2-400)/2)+30*2)
                {
                    listasCandidatos[escolha].votos +=1;
                    listasEleitores[guardaIndiceNome].voto =1;
                    totalDeVotos += 1;
                    next=4;
                }

             if(mousex() < ((3*xMax/2 - 535)/2)+40+15 && mousex() > ((3*xMax/2 - 535)/2)-40-15
               && mousey() > ((3*yMax/2-400)/2)+30 && mousey() < ((3*yMax/2-400)/2)+30*2){
                   botao(3*xMax/2 - 535, 3*yMax/2 - 400, 30, 40, 15, 4, 4, 33,"Não");
                   delay(200);
                   botao(3*xMax/2 - 535, 3*yMax/2 - 400, 30, 40, 0, 15, 0, 33,"Não");
             }

             if(ismouseclick(WM_LBUTTONDOWN) && mousex() < ((3*xMax/2 - 535)/2)+40+15 && mousex() > ((3*xMax/2 - 535)/2)-40-15
               && mousey() > ((3*yMax/2-400)/2)+30 && mousey() < ((3*yMax/2-400)/2)+30*2)
               {
                   next=2;
               }



         clearmouseclick(WM_LBUTTONDOWN);
        }


        contador=0;
        while(next==4)
        {
            if(contador==0) {
            telaConfirmarVoto(xMax, yMax, 1);
            contador=1;
            }

            if(mousex() < ((xMax/2 + 760)/2)+40+15 && mousex() > ((xMax/2 + 760)/2)-40-15
               && mousey() > ((3*yMax/2-400)/2)+30 && mousey() < ((3*yMax/2-400)/2)+30*2){
                  botao(xMax/2 + 760, 3*yMax/2 - 400, 30, 40, 15, 0, 0, 16,"Fechar");
                  delay(200);
                  botao(xMax/2 + 760, 3*yMax/2 - 400, 30, 40, 0, 15, 0, 16,"Fechar");
             }

             if(ismouseclick(WM_LBUTTONDOWN) && mousex() < ((xMax/2 + 800)/2)+40+15 && mousex() > ((xMax/2 + 800)/2)-40-15
               && mousey() > ((3*yMax/2-400)/2)+30 && mousey() < ((3*yMax/2-400)/2)+30*2)
               {
                   next=0;
               }
         clearmouseclick(WM_LBUTTONDOWN);
        }

        contador=0;

        while(next==5)
        {
            if(contador==0)
            {
                telaCampeao(xMax, yMax);
                mostrarRanking(xMax, yMax);
                contador=1;
            }
        }

}

      closegraph();
}


void cadastroCandidato(int x, int y) {

    int i;

    strcpy(listasCandidatos[0].nomeCompleto, "Bill Gates");
    strcpy(listasCandidatos[1].nomeCompleto, "Elon Musk");
    strcpy(listasCandidatos[2].nomeCompleto, "Jeff Bezos");
    strcpy(listasCandidatos[3].nomeCompleto, "Luciano Hang");
    strcpy(listasCandidatos[4].nomeCompleto, "Steve Jobs");
    strcpy(listasCandidatos[5].nomeCompleto, "Mark Zuckerberg");

    strcpy(listasCandidatos[0].empresa, "Microsoft");
    strcpy(listasCandidatos[1].empresa, "SpaceX");
    strcpy(listasCandidatos[2].empresa, "Amazon");
    strcpy(listasCandidatos[3].empresa, "Havan");
    strcpy(listasCandidatos[4].empresa, "Apple");
    strcpy(listasCandidatos[5].empresa, "Facebook");


    strcpy(listasCandidatos[0].imagem, "img/billGates.jpg");
    strcpy(listasCandidatos[1].imagem, "img/elonMusk.jpg");
    strcpy(listasCandidatos[2].imagem, "img/jeffBezos.jpg");
    strcpy(listasCandidatos[3].imagem, "img/lucianoHang.jpg");
    strcpy(listasCandidatos[4].imagem, "img/steveJobs.jpg");
    strcpy(listasCandidatos[5].imagem, "img/markZuckerberg.jpg");

    strcpy(listasCandidatos[0].descricao1, "William Henry Gates III, mais conhecido como");
    strcpy(listasCandidatos[0].descricao2, "Bill Gates, nasceu em 1955 e atualmente tem 66 anos.");
    strcpy(listasCandidatos[0].descricao3, "Magnata, empresário, diretor executivo, investidor");
    strcpy(listasCandidatos[0].descricao4, "e filantropo americano, foi mais conhecido por,");
    strcpy(listasCandidatos[0].descricao5, "junto com seu sócio, fundar a maior e mais conhecida");
    strcpy(listasCandidatos[0].descricao6, "empresa de software do mundo a Microsoft.");

    strcpy(listasCandidatos[1].descricao1, "Elon Reeve Musk, conhecido apenas como Elon Musk,");
    strcpy(listasCandidatos[1].descricao2, "nasceu em 1971 e atualmente tem 51 anos de idade.");
    strcpy(listasCandidatos[1].descricao3, "Empreendedor e filantropo sul-africano naturalizado");
    strcpy(listasCandidatos[1].descricao4, "americano, Musk é o fundador diretor executivo e");
    strcpy(listasCandidatos[1].descricao5, "técnico da SpaceX CEO da Tesla; vice presidente");
    strcpy(listasCandidatos[1].descricao6, "da OpenAI e fundador e CEO da Neurolink.");

    strcpy(listasCandidatos[2].descricao1, "Jeffrey Preston Bezos, mais conhecido como");
    strcpy(listasCandidatos[2].descricao2, "Jeff Bezos, nasceu em 1964 e atualmente tem");
    strcpy(listasCandidatos[2].descricao3, "58 anos. Empresário americano, mais conhecido");
    strcpy(listasCandidatos[2].descricao4, "por fundar e ser o CEO de uma das mais");
    strcpy(listasCandidatos[2].descricao5, "importantes e famosas empresas de comércio ");
    strcpy(listasCandidatos[2].descricao6, "eletrônico do mundo Amazon.");

    strcpy(listasCandidatos[3].descricao1, "Luciano Hang, mais conhecido como velho da Havan,");
    strcpy(listasCandidatos[3].descricao2, "nasceu em 1962 e atualmente tem 59 anos.");
    strcpy(listasCandidatos[3].descricao3, "Co-fundador e proprietário de uma das maiores");
    strcpy(listasCandidatos[3].descricao4, "redes de lojas de departamento do país, Havan.");
    strcpy(listasCandidatos[3].descricao5, "Dito pela revista Forbes, como o 21° homem mais");
    strcpy(listasCandidatos[3].descricao6, "rico do Brasil.");

    strcpy(listasCandidatos[4].descricao1, "Steven Paul Jobs, mais conhecido como Steve Jobs,");
    strcpy(listasCandidatos[4].descricao2, "nasceu em 1955 e faleceu em 2011 com 56 anos.");
    strcpy(listasCandidatos[4].descricao3, "Inventor, empresário e magnata americano, é lembrado");
    strcpy(listasCandidatos[4].descricao4, "por ser o co-fundador, presidente e diretor");
    strcpy(listasCandidatos[4].descricao5, "executivo da Apple Inc. Revolucionou seis indústrias com");
    strcpy(listasCandidatos[4].descricao6, "suas invenções: indústrias de computadores pessoais,");
    strcpy(listasCandidatos[4].descricao7, "filmes de animação, música, telefones, tablets ");
    strcpy(listasCandidatos[4].descricao8, "e publicações digitais.");


    strcpy(listasCandidatos[5].descricao1, "Mark Elliot Zuckenberg, conhecido como Mark");
    strcpy(listasCandidatos[5].descricao2, "Zuckenberg,  nasceu em 1984 e atualmente tem");
    strcpy(listasCandidatos[5].descricao3, "38 anos. Programador e empresário norte-americano,");
    strcpy(listasCandidatos[5].descricao4, "é conhecido por ser um dos fundadores");
    strcpy(listasCandidatos[5].descricao5, "do Facebook, que atualmente tem uma empresa");
    strcpy(listasCandidatos[5].descricao6, "de redes sociais conhecida como META.");


    listasCandidatos[0].x1 = (x/2)-539;
    listasCandidatos[1].x1 = (x/2)-139;
    listasCandidatos[2].x1 = (x/2)+261;
    listasCandidatos[3].x1 = (x/2)-539;
    listasCandidatos[4].x1 = (x/2)-139;
    listasCandidatos[5].x1 = (x/2)+261;

    listasCandidatos[0].x2 = (x/2)-289;
    listasCandidatos[1].x2 = (x/2)+111;
    listasCandidatos[2].x2 = (x/2)+511;
    listasCandidatos[3].x2 = (x/2)-289;
    listasCandidatos[4].x2 = (x/2)+111;
    listasCandidatos[5].x2 = (x/2)+511;

    listasCandidatos[0].y1 = (y/2)-270;
    listasCandidatos[1].y1 = (y/2)-270;
    listasCandidatos[2].y1 = (y/2)-270;
    listasCandidatos[3].y1 = (y/2)+50;
    listasCandidatos[4].y1 = (y/2)+50;
    listasCandidatos[5].y1 = (y/2)+50;

    listasCandidatos[0].y2 = (y/2);
    listasCandidatos[1].y2 = (y/2);
    listasCandidatos[2].y2 = (y/2);
    listasCandidatos[3].y2 = (y/2) + 320;
    listasCandidatos[4].y2 = (y/2) + 320;
    listasCandidatos[5].y2 = (y/2) + 320;


    for(i=0;i<7;i++)
    listasCandidatos[i].votos = 0;



}

void cadastroEleitores() {
    int i=0;
    strcpy(listasEleitores[0].nomeCompleto, "Larissa Fernandes");
    strcpy(listasEleitores[1].nomeCompleto, "Matilde Dias");
    strcpy(listasEleitores[2].nomeCompleto, "Lucas Castro");
    strcpy(listasEleitores[3].nomeCompleto, "Nicolash Barros");
    strcpy(listasEleitores[4].nomeCompleto, "Julieta Cavalcanti");




    strcpy(listasEleitores[0].cpf, "105.481.020-66");
    strcpy(listasEleitores[1].cpf, "625.461.080-93");
    strcpy(listasEleitores[2].cpf, "226.910.130-81");
    strcpy(listasEleitores[3].cpf, "842.465.760-85");
    strcpy(listasEleitores[4].cpf, "979.343.010-90");


    for(i=0;i<6;i++)
    {
        listasEleitores[i].voto = 0;
    }



}



void imagemCandidatos(int x, int y) {

      setfillstyle(1,8);
      bar((x/2)-534,(y/2)-265,(x/2)-284,(y/2)+5);
      readimagefile(listasCandidatos[0].imagem,((x/2)-539),((y/2)-270),((x/2)-289),((y/2)));
      setbkcolor(15);
      setcolor(0);
      settextstyle(8,0,3);
      outtextxy((x/2)-534,((y/2)+5),listasCandidatos[0].nomeCompleto); //Bill Gates

      setfillstyle(1,8);
      //bar(652,((y/2)-266),905,((y/2)+5));   //contorno
      bar((x/2)-134,((y/2)-265),((x/2)+116),((y/2)+5));   //sombra
      readimagefile(listasCandidatos[1].imagem,((x/2)-139),((y/2)-270),((x/2)+111),((y/2)));
      setbkcolor(15);
      setcolor(0);
      settextstyle(8,0,3);
      outtextxy((x/2)-134,((y/2)+5),listasCandidatos[1].nomeCompleto); //Elon Musk


      setfillstyle(1,8);
      bar(((x/2)+266),((y/2)-265),((x/2)+516),((y/2)+5));
      readimagefile(listasCandidatos[2].imagem,((x/2)+261),((y/2)-270),((x/2)+511),((y/2)));
      setbkcolor(15);
      setcolor(0);
      settextstyle(8,0,3);
      outtextxy((x/2)+266,((y/2)+5),listasCandidatos[2].nomeCompleto); //Jeff Bezos

      //-----------------------------------------------//

      setfillstyle(1,8);
      bar((x/2)-534,((y/2)+55),(x/2)-284,((y/2) + 325));
      readimagefile(listasCandidatos[3].imagem,(x/2)-539,((y/2)+50),((x/2)-289),((y/2) + 320));
      setbkcolor(15);
      setcolor(0);
      settextstyle(8,0,3);
      outtextxy((x/2)-534,((y/2)+325),listasCandidatos[3].nomeCompleto); //Luciano Hang

      setfillstyle(1,8);
      bar((x/2)-134,((y/2)+55),((x/2)+116),((y/2) + 325));
      readimagefile(listasCandidatos[4].imagem,((x/2)-139),((y/2)+50),((x/2)+111),((y/2) + 320)); //Steve Jobs
      setbkcolor(15);
      setcolor(0);
      settextstyle(8,0,3);
      outtextxy((x/2)-134,((y/2)+325),listasCandidatos[4].nomeCompleto);

      setfillstyle(1,8);
      bar((x/2)+266,((y/2)+55),(x/2)+516,((y/2) + 325));
      readimagefile(listasCandidatos[5].imagem,((x/2)+261),((y/2)+50),((x/2)+511),((y/2) + 320)); //Mark Zuckerberg
      setbkcolor(15);
      setcolor(0);
      settextstyle(8,0,3);
      outtextxy((x/2)+266,((y/2)+325),listasCandidatos[5].nomeCompleto);
}


void bemVindoNome(int x, int y, char bemVindo[65], int indiceNome){
      int  i;
      strcpy(bemVindo, "BEM VINDO ");
      strcat(bemVindo, listasEleitores[indiceNome].nomeCompleto);
      readimagefile("img/branco.jpg",0,0,getmaxwidth(),getmaxheight());
      setbkcolor(15);
      setcolor(0);
      settextstyle(8,0,5);
      for(i=0;i<70;i++){
        bemVindo[i] = toupper(bemVindo[i]);
      }
      outtextxy(((x/2)-14*strlen(bemVindo)),((y/2)-380),bemVindo);
      setbkcolor(15);
      setcolor(0);
      settextstyle(8,0,3);
      outtextxy((x/2)-165,((y/2)-320),"ESCOLHA SEU CANDIDATO");
}


void escolherCandidato(int *i, int msx, int msy, int *next) //i = variavel de escolha, esta dirá qual candidato foi escolhido
{
  if (msx > (listasCandidatos[0].x1) && msx < (listasCandidatos[0].x2) &&
      msy > (listasCandidatos[0].y1) && msy < (listasCandidatos[0].y2))
      {
      *i=0;
      *next =2;
      }
  else if (msx > (listasCandidatos[1].x1) && msx < (listasCandidatos[1].x2) &&
      msy > (listasCandidatos[1].y1) && msy < (listasCandidatos[1].y2))
      {
      *i=1;
      *next =2;
      }

  else if (msx > (listasCandidatos[2].x1) && msx < (listasCandidatos[2].x2) &&
      msy > (listasCandidatos[2].y1) && msy < (listasCandidatos[2].y2))
      {
      *i=2;
      *next =2;
      }

  else if (msx > (listasCandidatos[3].x1) && msx < (listasCandidatos[3].x2) &&
      msy > (listasCandidatos[3].y1) && msy < (listasCandidatos[3].y2))
      {
      *i=3;
      *next =2;
      }

  else if (msx > (listasCandidatos[4].x1) && msx < (listasCandidatos[4].x2) &&
      msy > (listasCandidatos[4].y1) && msy < (listasCandidatos[4].y2))
      {
      *i=4;
      *next =2;
      }

  else if (msx > (listasCandidatos[5].x1) && msx < (listasCandidatos[5].x2) &&
      msy > (listasCandidatos[5].y1) && msy < (listasCandidatos[5].y2))
      {
      *i=5;
      *next =2;
      }

}

void selecionarCandidato(int x, int y, int msx, int msy){

    if (msx > (listasCandidatos[0].x1) && msx < (listasCandidatos[0].x2) &&
      msy > (listasCandidatos[0].y1) && msy < (listasCandidatos[0].y2))
      {
          readimagefile("img/billGatesSelecionado.jpg",((x/2)-539),((y/2)-270),((x/2)-289),((y/2)));
      }

      else if (msx > (listasCandidatos[1].x1) && msx < (listasCandidatos[1].x2) &&
      msy > (listasCandidatos[1].y1) && msy < (listasCandidatos[1].y2))
      {
          readimagefile("img/elonMuskSelecionado.jpg",((x/2)-139),((y/2)-270),((x/2)+111),((y/2)));
      }

     else if (msx > (listasCandidatos[2].x1) && msx < (listasCandidatos[2].x2) &&
      msy > (listasCandidatos[2].y1) && msy < (listasCandidatos[2].y2))
      {
          readimagefile("img/jeffBezosSelecionado.jpg",((x/2)+261),((y/2)-270),((x/2)+511),((y/2)));
      }

     else if (msx > (listasCandidatos[3].x1) && msx < (listasCandidatos[3].x2) &&
      msy > (listasCandidatos[3].y1) && msy < (listasCandidatos[3].y2))
      {
          readimagefile("img/lucianoHangSelecionado.jpg",(x/2)-539,((y/2)+50),((x/2)-289),((y/2) + 320));
      }

      else if (msx > (listasCandidatos[4].x1) && msx < (listasCandidatos[4].x2) &&
      msy > (listasCandidatos[4].y1) && msy < (listasCandidatos[4].y2))
      {
          readimagefile("img/steveJobsSelecionado.jpg",((x/2)-139),((y/2)+50),((x/2)+111),((y/2) + 320));
      }

      else if (msx > (listasCandidatos[5].x1) && msx < (listasCandidatos[5].x2) &&
      msy > (listasCandidatos[5].y1) && msy < (listasCandidatos[5].y2))
      {
          readimagefile("img/markZuckerbergSelecionado.jpg",((x/2)+261),((y/2)+50),((x/2)+511),((y/2) + 320));
      }
      else {
        readimagefile(listasCandidatos[0].imagem,((x/2)-539),((y/2)-270),((x/2)-289),((y/2)));
        readimagefile(listasCandidatos[1].imagem,((x/2)-139),((y/2)-270),((x/2)+111),((y/2)));
        readimagefile(listasCandidatos[2].imagem,((x/2)+261),((y/2)-270),((x/2)+511),((y/2)));
        readimagefile(listasCandidatos[3].imagem,(x/2)-539,((y/2)+50),((x/2)-289),((y/2) + 320));
        readimagefile(listasCandidatos[4].imagem,((x/2)-139),((y/2)+50),((x/2)+111),((y/2) + 320));
        readimagefile(listasCandidatos[5].imagem,((x/2)+261),((y/2)+50),((x/2)+511),((y/2) + 320));
      }

}


void candidatoEscolhido(int escolha, int x, int y)
{
    readimagefile("img/branco.jpg",0,0,getmaxwidth(),getmaxheight());

    setbkcolor(15);
    setcolor(0);
    settextstyle(4,0,5);
    outtextxy(((x/2)-12*strlen(listasCandidatos[escolha].nomeCompleto)),((y/2)-380),listasCandidatos[escolha].nomeCompleto);

    readimagefile(listasCandidatos[escolha].imagem,((x/4)-50),((y/2)-300),(x/4)+200,((y/2)-30));

    setbkcolor(15);
    setcolor(0);
    settextstyle(4,0,2);
    outtextxy((x/4)+220,((y/2)-300),listasCandidatos[escolha].descricao1);
    outtextxy((x/4)+220,((y/2)-262),listasCandidatos[escolha].descricao2);
    outtextxy((x/4)+220,((y/2)-224),listasCandidatos[escolha].descricao3);
    outtextxy((x/4)+220,((y/2)-186),listasCandidatos[escolha].descricao4);
    outtextxy((x/4)+220,((y/2)-148),listasCandidatos[escolha].descricao5);
    outtextxy((x/4)+220,((y/2)-110),listasCandidatos[escolha].descricao6);
    outtextxy((x/4)+220,((y/2)-72),listasCandidatos[escolha].descricao7);
    outtextxy((x/4)+220,((y/2)-34),listasCandidatos[escolha].descricao8);




    setlinestyle(0,0,1);
    setcolor(0);
    rectangle((x/2)-320,(y/2) + 300,(x/2)+330,(y/2)+50);

    setbkcolor(15);
    setcolor(0);
    settextstyle(10,0,3);
    outtextxy((x/2) - 245,(y/2) + 120,"DESEJA VOTAR NESTE CANDIDATO?");

    botao(x/2 + 500, 3*y/2 - 50, 30, 40, 0, 15, 0, 30,"Sim");
    botao(3*x/2 - 500, 3*y/2 -50, 30, 40, 0, 15, 0, 35,"Não");

}

void telaCampeao(int x, int y)
{
    int maior;
    char votos[5];
    char textoTotalDeVotos[20];
    int guardaIndiceNome = 0;
    int i;

            readimagefile("img/branco.jpg",0,0,getmaxwidth(),getmaxheight());
            setbkcolor(15);
            setcolor(0);
            settextstyle(8,0,5);
            outtextxy(((x/2)-310),((y/2)-380),"O BILIONARIO VENCEDOR É:");

            maior = listasCandidatos[0].votos;

            for(i=1;i<6;i++)
            {
                if(maior < listasCandidatos[i].votos)
                {
                    maior=listasCandidatos[i].votos;
                    guardaIndiceNome = i;
                }
            }


                setbkcolor(15);
                setcolor(0);
                settextstyle(8,0,5);
                outtextxy(((x/2)-15*strlen(listasCandidatos[guardaIndiceNome].nomeCompleto))+5,((y/2)-300),listasCandidatos[guardaIndiceNome].nomeCompleto);
                readimagefile(listasCandidatos[guardaIndiceNome].imagem,(x/2)-139,(y/2)-240,(x/2)+111,(y/2)+30);

                strcat(textoTotalDeVotos, "COM UM TOTAL DE ");
                sprintf(votos, "%d", listasCandidatos[guardaIndiceNome].votos);

                strcat(textoTotalDeVotos, votos);
                strcat(textoTotalDeVotos, " VOTOS");

                setbkcolor(15);
                setcolor(0);
                settextstyle(8,0,2);
                outtextxy((x/2)-150,((y/2)+50),textoTotalDeVotos);



}

void mostrarRanking(int x, int y){
    int maior= 0;
    int i, j;
    int guardaIndiceNome= 0;
    char votos[2];
    char textoTotalDeVotos[50];
    char numero[2];
    int contador = 1;
    char contadorChar[2];


    maior = listasCandidatos[0].votos;

            for(i=1;i<6;i++)
            {
                if(maior < listasCandidatos[i].votos)
                {
                    maior=listasCandidatos[i].votos;
                    guardaIndiceNome = i;
                }
            }

    for(i=0;i<6;i++)
    {
        sprintf(contadorChar, "%d", contador);
        setbkcolor(15);
        setcolor(0);
        settextstyle(8,0,2);
        outtextxy((x/2)-165,((y/2)+60+(i+1)*20),contadorChar);
        contador++;
    }



     ordenarRanking();

    for(i=0;i<6;i++)
    {


            strcpy(textoTotalDeVotos, "º - ");
            strcat(textoTotalDeVotos,listasCandidatos[i].nomeCompleto);
            strcat(textoTotalDeVotos, " - ");
            sprintf(votos, "%d", listasCandidatos[i].votos);
            strcat(textoTotalDeVotos, votos);
            strcat(textoTotalDeVotos, " VOTOS");


            setbkcolor(15);
            setcolor(0);
            settextstyle(8,0,2);
            outtextxy((x/2)-150,((y/2)+60+(i+1)*20),textoTotalDeVotos);

            setbkcolor(15);
            setcolor(15);
            settextstyle(8,0,2);
            outtextxy((x/2)-170,((y/2)+60+(0+1)*20),"----------------------------------------------------------");









        }

    }





void ordenarRanking()
{
   int i, j, indiceMaior, trocar ;
   char trocaNome[51];



    for(i=0;i<6;i++)
    {
        indiceMaior = i; //Inicia guardando o indice do maior como I
        for(j=i+1;j<6;j++)
        {
            if(listasCandidatos[j].votos > listasCandidatos[i].votos)  //Compara o vetor de indice I com o todos os outro Indices
                indiceMaior = j;   //Se esse indice for maior que o indice de I, maior guarda o indice de J

        }

        if(i != indiceMaior)   //Se o indice I diferente do indice do maior guardado, ele troca o valor do maior guardado com o indice do maior achado
        {
            trocar = listasCandidatos[i].votos;
            listasCandidatos[i].votos = listasCandidatos[indiceMaior].votos;
            listasCandidatos[indiceMaior].votos = trocar;

            strcpy(trocaNome,listasCandidatos[i].nomeCompleto);
            strcpy(listasCandidatos[i].nomeCompleto,listasCandidatos[indiceMaior].nomeCompleto);
            strcpy(listasCandidatos[indiceMaior].nomeCompleto,trocaNome);

        }

    }

}

void gerarVotos(int digito){
      int n;

      n = rand()%6;
      listasCandidatos[n].votos += 1;
      printf("%s ganhou um voto, e agora tem: %d\n", listasCandidatos[n].nomeCompleto, listasCandidatos[n].votos);

}
/*
void voltar(char esc, int *next)
{
    if(esc==27)
        *next = 2;
}
*/
