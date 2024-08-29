void iniciarGrafico(int x, int y, char textoTeste[15]);
void campoTexto(int x, int y, int altura, int largura, int corTexto, int corFundo, int corBorda, char texto[15]);
void cpf(int xMax, int yMax, char digito, char textoTeste[15], int tamanho);
void botao(int x, int y, int altura, int largura, int corTexto, int corFundo, int corBorda, int alinhamento ,char texto[15]);


void validarCpf(int x, int y, int verdadeiroCpf, int *digito, int *next, char textoTeste[], int votoComputado);
void barraDeDigitar(int digito, int tamanho,int *barraEscrever);
void aparecerBarraDeDigitar(int x, int y, int barraEscrever);

void candidatoEscolhido(int escolha, int x, int y);
void telaConfirmarVoto(int x, int y, int i);




void iniciarGrafico(int x, int y, char textoTeste[15]){

      readimagefile("img/branco.jpg",0,0,getmaxwidth(),getmaxheight());
      strcpy(textoTeste, "");
      campoTexto(x, y, 15, 100, 0, 15, 0, textoTeste);
      botao(x, y, 30, 45, 8, 15, 0, 0,"Continuar");
      setbkcolor(15);
      setcolor(0);
      settextstyle(8,0,5);
      outtextxy(((x/2)-420),((y/2)-380),"SISTEMA DE VOTAÇÃO DOS BILIONÁRIOS");
      setbkcolor(15);
      setcolor(0);
      settextstyle(8,0,1);
      outtextxy(((x/2)-75),((y/2)-40),"INSIRA SEU CPF");
}

 void campoTexto(int x, int y, int altura, int largura, int corTexto, int corFundo, int corBorda, char texto[14]){
      setfillstyle(1,15);
      bar(((x/2)+largura),((y/2)-altura),((x/2)-largura),((y/2)+altura));
      setlinestyle(0,0,1);
      setcolor(corBorda);
      rectangle(((x/2)+largura),((y/2)-altura),((x/2)-largura),((y/2)+altura));
      setcolor(corTexto);
      setbkcolor(corFundo);
      settextstyle(8,0,1);
      outtextxy(((x/2)-largura) + 5,(((y/2)-altura) + ((y/2)+altura) - altura)/2,texto);

 }

 void cpf(int xMax, int yMax, char digito, char textoTeste[15], int tamanho) {

      if(digito == 48 || digito == 49 || digito == 50 || digito == 51 || digito == 52 || digito == 53|| digito == 54 || digito == 55 ||
        digito == 56 || digito == 57 || digito == 8)
    {

     if(digito == 8)
            {
                tamanho = tamanho-1;
                if(tamanho == 3 || tamanho == 7 || tamanho == 11)
                {
                tamanho = tamanho-1;
                textoTeste[tamanho] = '\0';
                campoTexto(xMax, yMax, 15, 100, 0, 15, 0, textoTeste);

                }
                else
                {
                textoTeste[tamanho] = '\0';
                campoTexto(xMax, yMax, 15, 100, 0, 15, 0, textoTeste);
                }
            }

         if(tamanho < 14)
         {
             if(tamanho == 3 || tamanho == 7)
                strcat(textoTeste,".");
             if(tamanho == 11)
                strcat(textoTeste,"-");


             switch (digito)
                    {
                       case 48:
                       strcat(textoTeste,"0");
                       campoTexto(xMax, yMax, 15, 100, 0, 15, 0, textoTeste);
                       break;
                       case 49:
                       strcat(textoTeste,"1");
                       campoTexto(xMax, yMax, 15, 100, 0, 15, 0, textoTeste);
                       break;
                       case 50:
                       strcat(textoTeste,"2");
                       campoTexto(xMax, yMax, 15, 100, 0, 15, 0, textoTeste);
                       break;
                       case 51:
                       strcat(textoTeste,"3");
                       campoTexto(xMax, yMax, 15, 100, 0, 15, 0, textoTeste);
                       break;
                       case 52:
                       strcat(textoTeste,"4");
                       campoTexto(xMax, yMax, 15, 100, 0, 15, 0, textoTeste);
                       break;
                       case 53:
                       strcat(textoTeste,"5");
                       campoTexto(xMax, yMax, 15, 100, 0, 15, 0, textoTeste);
                       break;
                       case 54:
                       strcat(textoTeste,"6");
                       campoTexto(xMax, yMax, 15, 100, 0, 15, 0, textoTeste);
                       break;
                       case 55:
                       strcat(textoTeste,"7");
                       campoTexto(xMax, yMax, 15, 100, 0, 15, 0, textoTeste);
                       break;
                       case 56:
                       strcat(textoTeste,"8");
                       campoTexto(xMax, yMax, 15, 100, 0, 15, 0, textoTeste);
                       break;
                       case 57:
                       strcat(textoTeste,"9");
                       campoTexto(xMax, yMax, 15, 100, 0, 15, 0, textoTeste);
                       break;
                    }
         }

    }
 }

void botao(int x, int y, int altura, int largura, int corTexto, int corFundo, int corBorda, int alinhamento ,char texto[15]){
      setfillstyle(1,corFundo);

      bar(((x/2)+largura)+15,((y/2)+altura),((x/2)-largura)-15,((y/2)+(altura*2)));
      setlinestyle(0,0,1);
      setcolor(corBorda);
      rectangle(((x/2)+largura+15),((y/2)+altura),((x/2)-largura-15),((y/2)+(altura*2)));
      setbkcolor(corFundo);
      setcolor(corTexto);
      settextstyle(8,0,2);
      outtextxy(((x/2)-largura)-10+alinhamento,((y/2)+(altura*2) - altura + 7),texto);
}


void validarCpf(int x, int y, int verdadeiroCpf, int *digito, int *next, char textoTeste[], int votoComputado){
    if(verdadeiroCpf==0 && votoComputado==0){
    setbkcolor(15);
    setcolor(15);
    settextstyle(8,0,1);
    outtextxy(((x/2)-150),((y/2)-40),"Voto ja registrado deste CPF!!!");

    setbkcolor(15);
    setcolor(15);
    settextstyle(8,0,1);
    outtextxy(((x/2)-120),((y/2)-40),"Insira um CPF valido!!!");

    setbkcolor(15);
    setcolor(2);
    settextstyle(8,0,1);
    outtextxy(((x/2)-60),((y/2)-40),"CPF validado");

    delay(500);
    setbkcolor(15);
    setcolor(15);
    settextstyle(8,0,1);
    outtextxy(((x/2)-60),((y/2)-40),"CPF validado");

    setbkcolor(15);
    setcolor(2);
    settextstyle(8,0,1);
    outtextxy(((x/2)-50),((y/2)-40),"Entrando...");
    delay(500);
    *digito = '\0';
    textoTeste[14] = '\0';
    *next = 1;
    }

    else if(verdadeiroCpf==1 && votoComputado==0)
    {
    setbkcolor(15);
    setcolor(15);
    settextstyle(8,0,1);
    outtextxy(((x/2)-50),((y/2)-40),"CPF validado");
    setbkcolor(15);
    setcolor(15);
    settextstyle(8,0,1);
    outtextxy(((x/2)-150),((y/2)-40),"Voto ja registrado deste CPF!!!");
    setbkcolor(15);
    setcolor(4);
    settextstyle(8,0,1);
    outtextxy(((x/2)-120),((y/2)-40),"Insira um CPF valido!!!");
    *digito = '\0';
    }

    else
    {
    setbkcolor(15);
    setcolor(15);
    settextstyle(8,0,1);
    outtextxy(((x/2)-50),((y/2)-40),"CPF validado");
    setbkcolor(15);
    setcolor(4);
    settextstyle(8,0,1);
    outtextxy(((x/2)-150),((y/2)-40),"Voto ja registrado deste CPF!!!");
    *digito = '\0';
    }
}

void barraDeDigitar(int digito, int tamanho,int *barraEscrever){
    if(digito == 48 || digito == 49 || digito == 50 || digito == 51 || digito == 52 || digito == 53|| digito == 54 || digito == 55 ||
    digito == 56 || digito == 57 || digito == 8)
    {

    if(digito == 8 && tamanho > 0)
    *barraEscrever -= 12;
    else if(digito != 8 && tamanho <14)
    *barraEscrever +=12;

    if(tamanho == 3 || tamanho == 7 || tamanho == 11)
    *barraEscrever +=8;

    if(digito == 8 && (tamanho == 4 || tamanho == 8 || tamanho == 12))
    *barraEscrever -= 8;

    if(digito == 8 && (tamanho == 3 || tamanho == 7 || tamanho == 11))
    *barraEscrever -= 8;

    }


}

void aparecerBarraDeDigitar(int x, int y, int barraEscrever){
    setfillstyle(1,15);
    bar((x/2)-96+barraEscrever,((y/2)-10),((x/2))-95+barraEscrever,((y/2)+10));
    setlinestyle(0,0,3);
    setcolor(0);
    delay(200);
    setfillstyle(1,0);
    bar((x/2)-96+barraEscrever,((y/2)-10),((x/2))-95+barraEscrever,((y/2)+10));
    setlinestyle(0,0,3);
    setcolor(0);
    delay(200);
}





void telaConfirmarVoto(int x, int y, int i){

    if(i==0)
    {
        setfillstyle(1,15);
        bar((x/2)-300,(y/2)-150,(x/2)+300,(y/2)+150);
        setlinestyle(0,0,2);
        setcolor(0);
        rectangle((x/2)-300,(y/2)-150,(x/2)+300,(y/2)+150);

        setbkcolor(15);
        setcolor(0);
        settextstyle(10,0,2);
        outtextxy((x/2) - 150,(y/2) - 110, "Deseja confirmar seu voto?");
        botao(x/2 + 535, 3*y/2 - 400, 30, 40, 0, 15, 0, 30,"Sim");
        botao(3*x/2 - 535, 3*y/2 - 400, 30, 40, 0, 15, 0, 33,"Não");
    }
    else if(i==1)
    {
        setfillstyle(1,15);
        bar((x/2)-300,(y/2)-150,(x/2)+300,(y/2)+150);
        setlinestyle(0,0,2);
        setcolor(0);
        rectangle((x/2)-300,(y/2)-150,(x/2)+300,(y/2)+150);

        setbkcolor(15);
        setcolor(0);
        settextstyle(10,0,2);
        outtextxy((x/2) - 170,(y/2) - 110, "Voto registrado com sucesso!!");
        botao(x/2 + 760, 3*y/2 - 400, 30, 40, 0, 15, 0, 16,"Fechar");
    }



}

