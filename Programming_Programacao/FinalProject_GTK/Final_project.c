/***********************************************************************
 *                                                                     *
 *             Trabalho final de Programação, opção 3                  *
 *                                                                     *
 *                 Duarte Marques - ist196523                          *
 *                 Rodrigo Simões - ist196564                          *
 *                                                                     *
 **********************************************************************/

// Compile: gcc `pkg-config --cflags gtk+-3.0` -o Final_project Final_project.c `pkg-config --libs gtk+-3.0` -lm

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>
#include <cairo.h>

// Declaração de variáveis

GtkWidget     *window                    ; // Janela

GtkWidget     *box_mae                   ; // Box para tudo o resto

GtkWidget     *box_options               ; // Box com a menubar, escalas e 'Show / hide graph', 'Start & Stop' e 'Reset' (à esquerda na janela)
GtkWidget     *box_menubar               ; // Sub box para a menubar
GtkWidget     *menubar                   ; // Menubar
GtkWidget     *box_pendulum_xy           ; // Sub box para as escalas do desenho
GtkWidget     *box_graph_y               ; // Sub box para as escalas yy dos gráficos
GtkWidget     *box_options_lower         ; // Sub box para botões em baixo ('Show / hide graph', 'Start & Stop' e 'Reset')
GtkWidget     *frame1, *frame2           ; // Frames para as escalas do desenho e dos gráficos, respetivamente            
GtkWidget     *box_frame1                ; // Box para a frame com escalas do desenho
GtkWidget     *box_frame2                ; // Box para a frame com as escalas dos gráficos

GtkWidget     *box_draws                 ; // Box com as boxes com as drawing areas
GtkWidget     *box_pendulum              ; // Box para draw_pendulum (desenhar objetos)
GtkWidget     *draw_pendulum             ; // Drawing area em box_pendulum
GtkWidget     *box_graph                 ; // Box para draw_graph
GtkWidget     *draw_graph                ; // Drawing area para gráfico

GtkWidget     *box_buttons               ; // Box com as boxes que têm os botões (à direita na janela)

GtkWidget     *box_m1                    ; // M1       (massa 1)
GtkWidget     *box_m2                    ; // M2       (massa 2)
GtkWidget     *box_v1                    ; // V1       (velocidade da massa 1)
GtkWidget     *box_v2                    ; // V2       (velocidade da massa 2)
GtkWidget     *box_k                     ; // K        (constante da mola)
GtkWidget     *box_r                     ; // R        (comprimento da mola)
GtkWidget     *box_s                     ; // S        (comprimento da barra)
GtkWidget     *box_ang1                  ; // Ângulo 1 (ângulo entre mola e vertical)
GtkWidget     *box_ang2                  ; // Ângulo 2 (ângulo entre barra e vertical)

// Labels, botões e adjustments respetivamente, para opções da esquerda

GtkWidget     *label_m1, *button_m1      ; // M1
GtkAdjustment *adj_m1                    ;
GtkWidget     *label_m2, *button_m2      ; // M2
GtkAdjustment *adj_m2                    ;
GtkWidget     *label_v1, *button_v1      ; // V1
GtkAdjustment *adj_v1                    ;
GtkWidget     *label_v2, *button_v2      ; // V2
GtkAdjustment *adj_v2                    ;
GtkWidget     *label_k, *button_k        ; // K
GtkAdjustment *adj_k                     ;
GtkWidget     *label_r, *button_r        ; // R
GtkAdjustment *adj_r                     ;
GtkWidget     *label_s, *button_s        ; // S
GtkAdjustment *adj_s                     ;
GtkWidget     *label_ang1, *button_ang1  ; // Ângulo 1
GtkAdjustment *adj_ang1                  ;
GtkWidget     *label_ang2, *button_ang2  ; // Ângulo 2
GtkAdjustment *adj_ang2                  ;

// Botões 'Reset', 'Start & Stop' e 'Graph', respetivamente

GtkWidget     *button_reset              ;
GtkWidget     *button_start_stop         ;
GtkWidget     *button_graph              ;

// Scales e respetivas labels

GtkWidget     *label_pendulo             ; // Label com texto "Pêndulo"
GtkWidget     *label_grafico             ; // Label com texto "Gráfico"

GtkWidget     *move_pendulum_x           ; // Para deslocar o desenho em xx
GtkWidget     *label_pendulum_x          ;

GtkWidget     *move_pendulum_y           ; // Para deslocar o desenho em yy
GtkWidget     *label_pendulum_y          ;

GtkWidget     *scale_pendulum            ;  // Para escalar o desenho
GtkWidget     *label_scale_pendulum      ;

GtkWidget     *scale_graph               ; // Para escalar o eixo yy dos gráficos
GtkWidget     *label_scale_graph         ;

GtkWidget     *move_graph_x1             ; // Para deslocar o eixo yy do gráfico x1 (t)
GtkWidget     *label_move_graph_x1       ;

GtkWidget     *move_graph_x2             ; // Para deslocar o eixo yy do gráfico x2 (t)
GtkWidget     *label_move_graph_x2       ;

GtkWidget     *move_graph_y1             ; // Para deslocar o eixo yy do gráfico y1 (t)
GtkWidget     *label_move_graph_y1       ;

GtkWidget     *move_graph_y2             ; // Para deslocar o eixo yy do gráfico y2 (t)
GtkWidget     *label_move_graph_y2       ;

GtkWidget     *move_graph_v1             ; // Para deslocar o eixo yy do gráfico v1 (t)
GtkWidget     *label_move_graph_v1       ;

GtkWidget     *move_graph_v2             ; // Para deslocar o eixo yy do gráfico v2 (t)
GtkWidget     *label_move_graph_v2       ;

// Valores base das variáveis

gdouble       m1   = 3.0                 ; // M1
gdouble       m2   = 3.0                 ; // M2
gdouble       v1   = 10.0                ; // V1
gdouble       v2   = 10.0                ; // V2
gdouble       k    = 150.0               ; // K
gdouble       r    = 2.0                 ; // R
gdouble       s    = 2.0                 ; // S
gdouble       ang1 = M_PI/4.             ; // Ângulo 1
gdouble       ang2 = M_PI/4              ; // Ângulo 2

// Valores para cálculos

gdouble       r_ponto    = 0.            ; // Valor inicial da derivada temporal de r
gdouble       ang1_ponto = 0.            ; // Valor inicial da derivada temporal de ang1
gdouble       ang2_ponto = 0.            ; // Valor inicial da derivada temporal de ang2
gdouble       l          = 2.0           ; // Valor inicial de r (comprimento da mola)

// Vetores com valores necessários para desenhar o pêndulo e o gráfico (1005 espaços para que se vá até ao fim do eixo xx do gráfico)

gdouble       x_m1 [1005]                ; // Abcissa da massa M1
gdouble       y_m1 [1005]                ; // Ordenada da massa M1
gdouble       x_m2 [1005]                ; // Abcissa da massa M2
gdouble       y_m2 [1005]                ; // Ordenada da massa M2
gdouble       v_m1 [1005]                ; // Velocidade da massa M1
gdouble       v_m2 [1005]                ; // Velocidade da massa M2

int           i = 0                      ; // Contador, para avançar nestes vetores

int           pediu_reset = 0            ; // Para saber se se pediu reset (se sim, pediu_reset é mudado para 1)


int           esconder_mostrar_graph = 0 ; // Mostrar ou esconder gráfico; quando é múltiplo de 2 (no início, por exemplo), NÃO se mostra o gráfico


gdouble       raio1 = 11.5               ; // Raio da massa 1 (para a desenhar)
gdouble       raio2 = 11.5               ; // Raio da massa 2 (para a desenhar)

// Opções da escolha dos gráficos; ficam, no início, zero; soma-se 1 quando se carrega na opção (%2 == 1)

int           escolha_graph_x1 = 1       ; // x1 (t) (este gráfico é logo desenhado) 
int           escolha_graph_x2 = 0       ; // x2 (t)
int           escolha_graph_y1 = 0       ; // y1 (t)
int           escolha_graph_y2 = 0       ; // y2 (t)
int           escolha_graph_v1 = 0       ; // v1 (t)
int           escolha_graph_v2 = 0       ; // v2 (t)

gdouble       dt = 0.00001               ; // Incremento para cálculos (escolheu-se um valor ideal, depois de testar várias vezes)

gint          comecar_parar_tudo = 0     ; // Valor que, quando NÃO é múltiplo de 2, mete tudo a mexer 

GtkAllocation alloc_graph                ; // Usada na função para desenhar o gráfico

GtkAllocation alloc_pendulum             ; // Usada na função para desenhar o pêndulo

// Desenho do gráfico - valores foram sendo testados para serem ideais

double        y_ref_graph_x1 = 95.       ; // x1 (t)
double        y_ref_graph_x2 = 105.      ; // x2 (t)
double        y_ref_graph_y1 = 135.      ; // y1 (t)
double        y_ref_graph_y2 = 175.      ; // y2 (t)
double        y_ref_graph_v1 = 45.       ; // v1 (t)
double        y_ref_graph_v2 = 25.       ; // v2 (t)
double        fator_graph    = 20.       ; // Fator de "ampliação" dos valores, para desenhar em pixeis e não unidades SI
int           j = 0                      ; // Contador para ler dos vetores com os valores

// Desenho do pêndulo

int           p = 0                      ; // Contador para ler dos vetores com os valores
double        x_ref = 400.               ; 
double        y_ref = 5.                 ;
double        fator = -70.               ; // Fator de escala (negativo para não ficar invertido), para desenhar em pixeis e não em SI
double        velocidade = 1.            ; // Para desenhar o movimento com maior ou menor velocidade



// Função para abrir o ficheiro LATEX

gboolean fich_latex ()
{
  // NOTA: talvez seja necessário dar permissão ao acesso do ficheiro, digitando no terminal:   chmod u+x Latex_file.pdf
  
  system ("xdg-open ficheiro_latex.pdf") ; // Comando utilizado para abrir o ficheiro
  return FALSE ;
}



// Função para abrir nova janela quando se carrega em "New" na menubar

gboolean nova_janela ()
{
  system ("./Trabalho_final&") ; // Executa o programa no terminal
  return FALSE                ;
}



// Função que mostra informações quando se clica em "Sobre" na menubar

gboolean sobre (GtkWidget *widget, gpointer data)
{
  GtkWidget *area    ; // Definir área
  GtkWidget *dialog  ; // Dialog box
  
  GtkWidget *label0 , *label1, *label2, *label3, *label4, *label5, *label6, *label7, *label8, *label9 ; // Labels

  dialog = gtk_dialog_new_with_buttons ("Informações", GTK_WINDOW (window), GTK_DIALOG_MODAL, "OK", GTK_RESPONSE_NONE, NULL) ; // Cria dialog box, com o botão OK, que faz fechar a caixa quando se toca no mesmo
  
  area = gtk_dialog_get_content_area (GTK_DIALOG (dialog)) ; // Adicionar a dialog box a area
  
  // Criar labels com texto e adicioná-las a area
  
  label0 = gtk_label_new ("MEFT")                             ;
  label1 = gtk_label_new ("")                                 ;
  label2 = gtk_label_new ("Trabalho final de Programação")    ; 
  label3 = gtk_label_new ("")                                 ;
  label4 = gtk_label_new ("'Pêndulo duplo com mola e barra'") ;
  label5 = gtk_label_new ("")                                 ;
  label6 = gtk_label_new ("Autores:")                         ;
  label7 = gtk_label_new (" -Duarte Marques (ist196523);")    ;
  label8 = gtk_label_new (" -Rodrigo Simões (ist196564).")    ;
  label9 = gtk_label_new ("")                                 ;

  gtk_container_add (GTK_CONTAINER (area), label0)            ;
  gtk_container_add (GTK_CONTAINER (area), label1)            ;
  gtk_container_add (GTK_CONTAINER (area), label2)            ;
  gtk_container_add (GTK_CONTAINER (area), label3)            ;
  gtk_container_add (GTK_CONTAINER (area), label4)            ;
  gtk_container_add (GTK_CONTAINER (area), label5)            ;
  gtk_container_add (GTK_CONTAINER (area), label6)            ;
  gtk_container_add (GTK_CONTAINER (area), label7)            ;
  gtk_container_add (GTK_CONTAINER (area), label8)            ;
  gtk_container_add (GTK_CONTAINER (area), label9)            ;
  
  g_signal_connect_swapped (dialog, "response", G_CALLBACK (gtk_widget_destroy), dialog) ; // Sair quando se carrega em X
  gtk_widget_show_all (dialog)                                                           ; // Mostrar a caixa de diálogo
  
  return FALSE ;
}



// Funções para selecionar a opção do gráfico

gboolean x1_t ()
{
  escolha_graph_x1 += 1 ;
  return FALSE          ;
}

gboolean x2_t ()
{
  escolha_graph_x2 += 1 ;
  return FALSE          ;
}

gboolean y1_t ()
{
  escolha_graph_y1 += 1 ;
  return FALSE          ;
}

gboolean y2_t ()
{
  escolha_graph_y2 += 1 ;
  return FALSE          ;
}

gboolean v1_t ()
{
  escolha_graph_v1 += 1 ;
  return FALSE          ;
}

gboolean v2_t ()
{
  escolha_graph_v2 += 1 ;
  return FALSE          ;
}




// Funções que aceleram o desenho e variam a escala de tempo do gráfico ('velocidade' é usado na função principal)

gboolean speed_025x ()
{
  velocidade = 0.25 ;
  return FALSE      ;
}

gboolean speed_05x ()
{
  velocidade = 0.5  ;
  return FALSE      ;
}

gboolean  speed_1x ()
{
  velocidade = 1.0  ;
  return FALSE      ;
}

gboolean speed_2x ()
{
  velocidade = 2.0  ;
  return FALSE      ;
}

gboolean speed_3x ()
{
  velocidade = 3.0  ;
  return FALSE      ;
}

gboolean speed_5x ()
{
  velocidade = 5.0  ;
  return FALSE      ; 
}




// Função que altera os valores das variáveis para o que se colocou na barra (trabalha-se com ponteiros para que se altere o valor)

gboolean obter_valor (GtkWidget *widget , double *valor)
{
  if (GTK_IS_SPIN_BUTTON (widget) != 0)
    *valor = gtk_spin_button_get_value (GTK_SPIN_BUTTON (widget)) ;
  
  return FALSE ;
}



// Função que altera os valores para o que se pôs na escala (tem de trabalhar com ponteiros para que se altere o valor)

gboolean obter_valor_da_escala (GtkWidget *scale, double *valor)
{
  *valor = gtk_range_get_value (GTK_RANGE (scale) ) ;
  return FALSE ;
}



// Função a executar quando se carrega em Start & Stop

gboolean start_stop (GtkWidget *widget, gpointer data)
{
  ++comecar_parar_tudo ; // Incrementar
  return FALSE         ;
}



// Função que desenha o gráfico

gboolean graph (GtkWidget *widget, cairo_t *cr, gpointer data)
{
  gtk_widget_get_allocation (draw_graph, &alloc_graph) ; // Obter o espaço da draw_graph e guardá-lo em alloc_graph

  cairo_set_source_rgb (cr, 0, 0, 0)                   ; // Selecionar a cor (preta, neste caso)
  cairo_paint (cr)                                     ; // Pintar a draw_graph  da cor escolhida
  
  cairo_set_line_width (cr, 2.)                        ; // Fixar a espessura da linha do gráfico

  // Move-se o "cursor" do cairo para a posição (t, x1 (t))
  
  if ( (escolha_graph_x1 % 2) == 1 )
    {
      cairo_stroke         (cr)          ; // Necessário para que os gráficos sejam desenhados em simultâneo em cores diferentes
      cairo_fill           (cr)          ; // Idem
      cairo_set_source_rgb (cr, 1, 1, 1) ; // Selecionar a cor (branca, neste caso)
      for ( j = 0 ; j < 1005 ; ++j )
	{
	  cairo_line_to (cr, j, y_ref_graph_x1 + x_m1 [j] * fator_graph) ; // Mover a linha para esta posição
	  if (j == 1005)
	    j = 0 ; // Quando se chega ao fim do vetor, voltar ao início
	}
    }

  // (t, x2 (t))
  
  if ( (escolha_graph_x2 % 2) == 1 )
    {
      cairo_stroke         (cr)          ; 
      cairo_fill           (cr)          ;
      cairo_set_source_rgb (cr, 1, 0, 0) ; // Cor vermelha
      for ( j = 0 ; j < 1005 ; ++j )
	{
	  cairo_line_to (cr, j, y_ref_graph_x2 + x_m2 [j] * fator_graph) ; 
	  if (j == 1005)
	    j = 0 ;
	}
    }

  // (t, y1 (t))
  
  if ( (escolha_graph_y1 % 2) == 1 )
    {
      cairo_stroke         (cr)          ;
      cairo_fill           (cr)          ;
      cairo_set_source_rgb (cr, 0, 1, 0) ; // Cor verde
      for ( j = 0 ; j < 1005 ; ++j )
	{
	  cairo_line_to (cr, j, y_ref_graph_y1 + y_m1 [j] * fator_graph) ;
	  if (j == 1005)
	    j = 0 ;
	}
    }

  // (t, y2 (t))
  
  if ( (escolha_graph_y2 % 2) == 1 )
    {
      cairo_stroke         (cr)          ;
      cairo_fill           (cr)          ;
      cairo_set_source_rgb (cr, 0, 0, 1) ; // Cor azul
      for ( j = 0 ; j < 1005 ; ++j )
	{
	  cairo_line_to (cr, j, y_ref_graph_y2 + y_m2 [j] * fator_graph) ;
	  if (j == 1005)
	    j = 0 ;
	}
    }

  // (t, v1 (t))
  
  if ( (escolha_graph_v1 % 2) == 1 )
    {
      cairo_stroke         (cr)          ;
      cairo_fill           (cr)          ;
      cairo_set_source_rgb (cr, 1, 1, 0) ; // Cor vermelha + verde = amarela
      for ( j = 0 ; j < 1005 ; ++j )
	{
	  cairo_line_to (cr, j, y_ref_graph_v1 + v_m1 [j] * fator_graph) ;
	  if (j == 1005)
	    j = 0 ;
	}
    }

  // (t, v2 (t))
  
  if ( (escolha_graph_v2 % 2) == 1 )
    {
      cairo_stroke         (cr)          ;
      cairo_fill           (cr)          ;
      cairo_set_source_rgb (cr, 0, 1, 1) ; // Cor verde + azul = azul clara
      for ( j = 0 ; j < 1005 ; ++j )
	{
	  cairo_line_to (cr, j, y_ref_graph_v2 + v_m2 [j] * fator_graph) ;
	  if (j == 1005)
	    j = 0 ;
	}
    }

  cairo_stroke (cr) ; // Necessário
  cairo_fill   (cr) ; // Necessário

  if (GTK_IS_WIDGET (widget) != 0)
    gtk_widget_queue_draw (widget) ; // Necessário
  
  return TRUE ;
}



// Função que faz o desenho do pêndulo duplo

gboolean desenhar_pendulo (GtkWidget *widget, cairo_t *cr, gpointer data)
{
  // Variáveis usadas para desenhar a mola
  
  double x_ref1 = x_ref + 30. ;
  double x_ref2 = x_ref - 30. ;

  double y_ref1 = y_ref - 2.  ;
  double y_ref2 = y_ref + 2.  ;

  if (comecar_parar_tudo % 2 == 1)
    {
      if (p == 1005) 
	p  = 0; // Os vetores só vão até 1005 de espaço; faz-se isto quando se está em Start (a obter novos valores)
    }
    
  gtk_widget_get_allocation (draw_pendulum, &alloc_pendulum) ; // Obter o tamanho da drawing area draw_pendulum e guardar na variável alloc_pendulum

  cairo_set_source_rgb (cr, 1, 1, 1) ; // Fixar cor branca
  cairo_paint (cr)                   ; // Pintar o fundo

  // Desenhar a border da box
  
  GtkAllocation* alloc      = g_new (GtkAllocation, 1) ; // Usada para receber o tamanho da box com o desenho
  gtk_widget_get_allocation (box_pendulum, alloc)      ;
  cairo_set_source_rgb      (cr, 0, 0, 0)              ; // Preto
  cairo_set_line_width      (cr, 4.0)                  ; // Espessura
  cairo_move_to             (cr, 0, 0)                 ;
  cairo_line_to             (cr, alloc->width, 0)      ;
  cairo_line_to             (cr, alloc->width, 400)    ;
  cairo_line_to             (cr, 0, 400)               ;
  cairo_line_to             (cr, 0, 0)                 ;
  cairo_stroke              (cr)                       ;

  // Opções para centrar o desenho no ecrã se se variar a janela do tamanho mínimo ao máximo e vice-versa
  
  if (x_ref == 400.)
    {
      x_ref = (alloc->width) / 2. ;
    }

  if (x_ref == 502.5)
    {
      x_ref = (alloc->width) / 2. ;
    }
  
  // Desenhar a ponta inicial (pequeno círculo)

  cairo_set_source_rgb (cr, 1, 0, 0)                     ; // Vermelho
  cairo_arc            (cr, x_ref, y_ref, 3., 0, 2*M_PI) ; // Desenhar um arco (cr, x_centro, y_centro, raio, início do ângulo (rad), fim do ângulo)
  cairo_fill           (cr)                              ; // Necessário
  cairo_stroke         (cr)                              ; // Necessário

  // Desenhar a mola 

  cairo_set_source_rgb (cr, 0, 0, 0)      ; // Fixar cor preta
  cairo_set_line_width (cr, 1.5)          ; // Definir a espessura da linha 
  cairo_move_to        (cr, x_ref, y_ref) ; // Colocar na posição da bola vermelha

  // Desenho da mola (foi-se ajustando até se tornar ideal)
  
  cairo_line_to        (cr, x_ref + (6./30.)*(x_m1 [p] * fator*0.75), y_ref + (6./30.)*(y_m1 [p] * fator*0.85) )             ;

  cairo_set_line_width (cr, 0.5)                                                                                             ;

  cairo_line_to        (cr, x_ref1 + (6./30.)  * (x_m1 [p] * fator * 0.75), y_ref1 + (6./30.)   * (y_m1 [p] * fator * 0.85)) ;
  cairo_line_to        (cr, x_ref2 + (7./30.)  * (x_m1 [p] * fator * 0.75), y_ref2 + (7.5/30.)  * (y_m1 [p] * fator * 0.85)) ;
  cairo_line_to        (cr, x_ref1 + (8./30.)  * (x_m1 [p] * fator * 0.75), y_ref1 + (8./30.)   * (y_m1 [p] * fator * 0.85)) ;
  cairo_line_to        (cr, x_ref2 + (9./30.)  * (x_m1 [p] * fator * 0.75), y_ref2 + (9.5/30.)  * (y_m1 [p] * fator * 0.85)) ;
  cairo_line_to        (cr, x_ref1 + (10./30.) * (x_m1 [p] * fator * 0.75), y_ref1 + (10./30.)  * (y_m1 [p] * fator * 0.85)) ;
  cairo_line_to        (cr, x_ref2 + (11./30.) * (x_m1 [p] * fator * 0.75), y_ref2 + (11.5/30.) * (y_m1 [p] * fator * 0.85)) ;
  cairo_line_to        (cr, x_ref1 + (12./30.) * (x_m1 [p] * fator * 0.75), y_ref1 + (12./30.)  * (y_m1 [p] * fator * 0.85)) ;
  cairo_line_to        (cr, x_ref2 + (13./30.) * (x_m1 [p] * fator * 0.75), y_ref2 + (13.5/30.) * (y_m1 [p] * fator * 0.85)) ;
  cairo_line_to        (cr, x_ref1 + (14./30.) * (x_m1 [p] * fator * 0.75), y_ref1 + (14./30.)  * (y_m1 [p] * fator * 0.85)) ;
  cairo_line_to        (cr, x_ref2 + (15./30.) * (x_m1 [p] * fator * 0.75), y_ref2 + (15.5/30.) * (y_m1 [p] * fator * 0.85)) ;
  cairo_line_to        (cr, x_ref1 + (16./30.) * (x_m1 [p] * fator * 0.75), y_ref1 + (16./30.)  * (y_m1 [p] * fator * 0.85)) ;
  cairo_line_to        (cr, x_ref2 + (17./30.) * (x_m1 [p] * fator * 0.75), y_ref2 + (17.5/30.) * (y_m1 [p] * fator * 0.85)) ;
  cairo_line_to        (cr, x_ref1 + (18./30.) * (x_m1 [p] * fator * 0.75), y_ref1 + (18./30.)  * (y_m1 [p] * fator * 0.85)) ;
  cairo_line_to        (cr, x_ref2 + (19./30.) * (x_m1 [p] * fator * 0.75), y_ref2 + (19.5/30.) * (y_m1 [p] * fator * 0.85)) ;
  cairo_line_to        (cr, x_ref1 + (20./30.) * (x_m1 [p] * fator * 0.75), y_ref1 + (20./30.)  * (y_m1 [p] * fator * 0.85)) ;
  cairo_line_to        (cr, x_ref2 + (21./30.) * (x_m1 [p] * fator * 0.75), y_ref2 + (21.5/30.) * (y_m1 [p] * fator * 0.85)) ;
  cairo_line_to        (cr, x_ref1 + (22./30.) * (x_m1 [p] * fator * 0.75), y_ref1 + (22./30.)  * (y_m1 [p] * fator * 0.85)) ;
  cairo_line_to        (cr, x_ref2 + (24./30.) * (x_m1 [p] * fator * 0.75), y_ref2 + (24./30.)  * (y_m1 [p] * fator * 0.85)) ;

  cairo_line_to        (cr, x_ref + (24./30.) * (x_m1 [p] * fator * 0.75), y_ref + (24./30.) * (y_m1 [p] * fator * 0.85))    ;
  
  cairo_set_line_width (cr, 1.5)                                                                                             ;
  cairo_line_to        (cr, x_ref + (x_m1 [p] * fator), y_ref + (y_m1 [p] * fator) )                                         ; // Posição de M1
  cairo_stroke         (cr)                                                                                                  ;
  cairo_fill           (cr)                                                                                                  ;
  
  // Desenhar círculo (massa M1)
  
  cairo_set_source_rgb (cr, 0, 0, 0)                                                                  ; // Preto
  cairo_arc            (cr, x_ref + (x_m1 [p] * fator), y_ref + (y_m1 [p] * fator), raio1, 0, 2*M_PI) ; // Arco
  cairo_fill           (cr)                                                                           ;
  cairo_stroke         (cr)                                                                           ;

  // Desenhar a barra

  cairo_set_source_rgb (cr, 0, 0, 0)                                                ; // Preto
  cairo_set_line_width (cr, 4.)                                                     ; // Espessura
  cairo_move_to        (cr, x_ref + (x_m1 [p] * fator), y_ref + (y_m1 [p] * fator)) ; // Mover para posição da massa M1
  cairo_line_to        (cr, x_ref + (x_m2 [p] * fator), y_ref + (y_m2 [p] * fator)) ; // Até posição da massa M2
  cairo_stroke         (cr)                                                         ;
  cairo_fill           (cr)                                                         ;
  
  // Desenhar círculo (massa M2)
  
  cairo_set_source_rgb (cr, 0, 0, 0)                                                                  ; // Preto
  cairo_arc            (cr, x_ref + (x_m2 [p] * fator), y_ref + (y_m2 [p] * fator), raio2, 0, 2*M_PI) ; // Arco
  cairo_fill           (cr)                                                                           ;
  cairo_stroke         (cr)                                                                           ;
 
  if ( ( comecar_parar_tudo % 2 == 1 ) )
    ++p ; // Avançar nos vetores com os valores se se estiverem a calcular novos valores

  // Há um certo atraso entre esta função e os cálculos, logo é preciso, quando os cálculos param, avançar em p até chegar a i:
  
  if ( comecar_parar_tudo % 2 == 0 )
    {
      if ( p <= (i - 1) )
	p += 1         ; // Chegando a p=i, o desenho pára e posso mudar o desenho parado, em tempo real
      if ( (p <= (i - 1)) && (p % 6 == 0) )
	p += 1         ; // Soma-se outra vez de vem em quando (p%6=0) para que o desenho não pare com tanto atraso        
    }

  if (GTK_IS_WIDGET (draw_pendulum) != 0)
    {
      gtk_widget_queue_draw (draw_pendulum) ; // Necessário
    }

  
  if (pediu_reset == 1)
    {
      pediu_reset = 0 ; // Já não há pedido de reset
      p = i           ; // Para que volte mais rapidamente à posição inicial (faz-se isto porque p tem atraso face a i)

      // Nota: não se faz isso na paragem do desenho porque ficaria desagradável o boneco "saltar" para as coordenadas do vetor em i
    }

  return TRUE ;
}



// Função a executar quando se carrega em Reset

gboolean reset (GtkWidget *widget, gpointer data)
{
  pediu_reset = 1 ; // Atribuir 1 a pediu_reset

  // Pôr os valores iniciais nas variáveis e nos respetivos buttons

  m1   = 3.0                                                        ; // M1
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (button_m1), 3.)       ;
  
  m2   = 3.0                                                        ; // M2
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (button_m2), 3.)       ;
  
  v1   = 10.0                                                       ; // V1
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (button_v1), 10.)      ;
  
  v2   = 10.0                                                       ; // V2
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (button_v2), 10.)      ;
  
  k    = 150.0                                                      ; // K
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (button_k), 150.)      ;
  
  r    = 2.0                                                        ; // R
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (button_r), 2.)        ;
  
  s    = 2.0                                                        ; // S
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (button_s), 2.)        ;
  
  ang1 = M_PI/4                                                     ; // Ângulo 1
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (button_ang1), M_PI/4) ;
  
  ang2 = M_PI/4                                                     ; // Ângulo 2
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (button_ang2), M_PI/4) ;

  r_ponto    = 0. ; // Derivada temporal de r
  ang1_ponto = 0. ; // Derivada temporal de ang1
  ang2_ponto = 0. ; // Derivada temporal de ang2
  
  return TRUE;
}




// Função que inicia as coisas e faz contas

gboolean funcao_principal (GtkWidget *widget)
{
  int contas = 0 ; // É utilizado para variar a velocidade do desenho; se se fizerem as mesmas contas mais vezes, a velocidade aumenta

  // Conectar com a função obter_valor, que altera os valores conforme o que se pôs na barra
  
  if (GTK_IS_SPIN_BUTTON (button_m1) != 0)   
    g_signal_connect (G_OBJECT (button_m1)  , "value-changed", G_CALLBACK (obter_valor), &m1)   ; // Recebe o valor de M1
      
  if (GTK_IS_SPIN_BUTTON (button_m2) != 0)
    g_signal_connect (G_OBJECT (button_m2)  , "value-changed", G_CALLBACK (obter_valor), &m2)   ; // Recebe o valor de M2
      
  if (GTK_IS_SPIN_BUTTON (button_v1) != 0)
    g_signal_connect (G_OBJECT (button_v1)  , "value-changed", G_CALLBACK (obter_valor), &v1)   ; // Recebe o valor de V1
      
  if (GTK_IS_SPIN_BUTTON (button_v2) != 0)
    g_signal_connect (G_OBJECT (button_v2)  , "value-changed", G_CALLBACK (obter_valor), &v2)   ; // Recebe o valor de V2

  if (GTK_IS_SPIN_BUTTON (button_k) != 0)
    g_signal_connect (G_OBJECT (button_k)   , "value-changed", G_CALLBACK (obter_valor), &k)    ; // Recebe o valor de K
      
  if (GTK_IS_SPIN_BUTTON (button_r) != 0)
    g_signal_connect (G_OBJECT (button_r)   , "value-changed", G_CALLBACK (obter_valor), &r)    ; // Recebe o valor de R
      
  if (GTK_IS_SPIN_BUTTON (button_s) != 0)
    g_signal_connect (G_OBJECT (button_s)   , "value-changed", G_CALLBACK (obter_valor), &s)    ; // Recebe o valor de S

  if (GTK_IS_SPIN_BUTTON (button_ang1) != 0)
    g_signal_connect (G_OBJECT (button_ang1), "value-changed", G_CALLBACK (obter_valor), &ang1) ; // Recebe o valor do Ângulo 1
      
  if (GTK_IS_SPIN_BUTTON (button_ang2) != 0)
    g_signal_connect (G_OBJECT (button_ang2), "value-changed", G_CALLBACK (obter_valor), &ang2) ; // Recebe o valor do Ângulo 2

  if (comecar_parar_tudo % 2 == 1)
    {
      if (i == 1005)
	i = 0 ; // Porque os vetores só têm 1005 de espaço
    }

  if (comecar_parar_tudo % 2 == 1)
    {  
      // Velocidade é, inicialmente, 1; o dt=0.00001 não varia; logo, fazendo 2000 contas, é como se fosse dt=0.00001*2000=0.2

      for ( contas = 0 ; contas < 2000 * velocidade ; ++contas)
	{
	  // Calcular r ponto (r_ponto (t + dt) = r_ponto (t) + dt * r_ponto_ponto)

	  r_ponto = r_ponto + dt * ( ( m2 * k * (l - r) * sin (ang1 - ang2) * sin (ang1 - ang2) ) / ( m1 * (m1 + m2) ) + r * ang1_ponto * ang1_ponto + ( m2 * s * ang2_ponto * ang2_ponto * cos (ang1 - ang2) ) / (m1 + m2) + ( k * (l - r) ) / ( m1 + m2 ) + 9.81 * cos (ang1) ) ;

	  // Calcular ang1 ponto (ang1_ponto (t + dt) =  ang1_ponto (t) + dt * ang1_ponto_ponto)

	  ang1_ponto = ang1_ponto + dt * ( ( m2 * k * (l - r) * sin (ang1 - ang2) * cos (ang1 - ang2) ) / ( m1 * (m1 + m2) * r ) - ( 2 * r_ponto * ang1_ponto ) / r - ( m2 * s * ang2_ponto * ang2_ponto * sin (ang1 - ang2) ) / ( (m1 + m2) * r ) - ( 9.81 * sin (ang1) ) / r ) ;

	  // Calcular ang2 ponto (ang2_ponto (t + dt) = ang2_ponto (t) + dt * ang2_ponto_ponto)
  
	  ang2_ponto = ang2_ponto + dt * ( ( -k * (l - r) * sin (ang1 - ang2) ) / ( s * m1 ) ) ;

	  // Calcular r (r (t + dt) = r (t) + dt * r_ponto)

	  r = r + dt * r_ponto ;

	  // Calcular ang1 (ang1 (t + dt) = ang1 (t) + dt * ang1_ponto)

	  ang1 = ang1 + dt * ang1_ponto ;
  
	  // Calcular ang2 (ang2 (t + dt) = ang2 (t) + dt * ang2_ponto)

	  ang2 = ang2 + dt * ang2_ponto ;

	  if ( (comecar_parar_tudo % 2 == 0) & (comecar_parar_tudo > 0) )
	    break ; // Quando se pede para parar, se pararmos estes numerosos cálculos, o desenho pára mais depressa	  
	}
    }
  
  // Calcular a abcissa da massa M1 e guardar no respetivo vetor

  x_m1 [i] = r * sin (ang1) ;

  // Calcular a ordenada da massa M1 e guardar no respetivo vetor

  y_m1 [i] = -r * cos (ang1) ;

  // Calcular a abcissa da massa M2 e guardar no respetivo vetor

  x_m2 [i] = r * sin (ang1) + s * sin (ang2);

  // Calcular a ordenada da massa M2 e guardar no respetivo vetor

  y_m2 [i] = -r * cos (ang1) - s * cos (ang2) ;
  
  // Calcular a velocidade da massa M1 e guardar no respetivo vetor

  v_m1 [i] = sqrt ( ( r * ang1_ponto * cos (ang1) + r_ponto * sin (ang1) ) * ( r * ang1_ponto * cos (ang1) + r_ponto * sin (ang1) ) + ( r * ang1_ponto * sin (ang1) - r_ponto * cos (ang1) ) * ( r * ang1_ponto * sin (ang1) - r_ponto * cos (ang1) ) ) ;

  // Calcular a velocidade da massa M2 e guardar no respetivo vetor

  v_m2 [i] = sqrt ( ( r * ang1_ponto * cos (ang1) + r_ponto * sin (ang1) + s * ang2_ponto * cos (ang2) ) * ( r * ang1_ponto * cos (ang1) + r_ponto * sin (ang1) + s * ang2_ponto * cos (ang2) ) + ( -r_ponto * cos (ang1) + r * ang1_ponto * sin (ang1) + s * ang2_ponto * sin (ang2) ) * ( -r_ponto * cos (ang1) + r * ang1_ponto * sin (ang1) + s * ang2_ponto * sin (ang2) ) );


  if (comecar_parar_tudo % 2 == 1)
    i++ ; // Incrementar i, para a próxima chamada da função

  return TRUE;
}



// Função para mostrar ou esconder o gráfico

gboolean show_hide_graph (GtkWidget *widget, gpointer data)
{
  ++ esconder_mostrar_graph ; // Incrementar g

  // Se se quer desenhar o gráfico, então esconder_mostrar_graph NÃO é múltiplo de 2, porque o seu valor inicial é 0

  // Mostrar

  if (esconder_mostrar_graph % 2 == 1)
    {
      gtk_widget_set_size_request (GTK_WIDGET (box_graph) , 300, 200)            ; // Criar espaço na box_graph (que está escondida)
      gtk_widget_set_size_request (GTK_WIDGET (draw_graph), 300, 200)            ; // Criar espaço na drawing area que está na box_graph
      g_signal_connect (G_OBJECT (draw_graph), "draw", G_CALLBACK (graph), NULL) ; // Desenhar em draw_graph o gráfico, executando a função graph
      gtk_widget_show (box_graph)                                                ; // Mostrar a box_graph
      gtk_widget_show (draw_graph)                                               ; // Mostrar a sua drawing area, draw_graph
    }
  
  // Esconder
  
  if (esconder_mostrar_graph % 2 == 0)
    {
      gtk_widget_hide   (draw_graph)                    ; // Esconder a drawing area
      gtk_widget_hide   (box_graph)                     ; // Esconder a box
      gtk_window_resize (GTK_WINDOW (window), 500, 100) ; // Novo tamanho mínimo para a window
    }

  return FALSE ;
}



// Função para que as opções na menubar tenham um boneco, além de nome

GtkWidget *criar_com_simbolo (gchar *label_name, gchar *icon_name)
{
  GtkWidget *image, *box, *label, *menu_item ;

  menu_item = gtk_menu_item_new ()                   ; // O item
  box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0)  ; // Criar box
  gtk_container_add (GTK_CONTAINER (menu_item), box) ; // Adicionar box ao item 

  // Ícone
  
  if (icon_name)
    {
      image = gtk_image_new_from_icon_name (icon_name, GTK_ICON_SIZE_MENU) ;
      gtk_box_pack_start (GTK_BOX (box), image, FALSE, FALSE, 0)           ; // Adiconar à box
    }

  // Nome
  
  if (label_name)
    {
      label = gtk_label_new (label_name)                        ;
      gtk_box_pack_start (GTK_BOX (box), label, FALSE, TRUE, 0) ; // Adiconar à box
    }

  return menu_item ;
}



// Função que cria a menubar

GtkWidget *criar_barra_de_menus (GtkWidget *window)
{
  // Variáveis necessárias
  
  GtkAccelGroup *accel_group = NULL                                                 ;

  GtkWidget     *menubar                                                            ;

  GtkWidget     *mib_window , *menu_window                                          ;
  GtkWidget     *mi_new     , *mi_quit                                              ;           

  GtkWidget     *mib_opcoes , *menu_opcoes                                          ;
  GtkWidget     *mib_grafico, *menu_grafico                                         ;
  GtkWidget     *mi_x1_t    , *mi_x2_t     , *mi_y1_t, *mi_y2_t, *mi_v1_t, *mi_v2_t ;
  GtkWidget     *mib_speed  , *menu_speed                                           ;
  GtkWidget     *mi_025x    , *mi_05x      , *mi_1x  , *mi_2x  , *mi_3x  , *mi_5x   ;
  
  GtkWidget     *mib_info   , *menu_info                                            ;
  GtkWidget     *mi_ajuda   , *mi_sobre                                             ; 

  accel_group = gtk_accel_group_new ()                          ; // Criar accel_group (para as várias opções)
  gtk_window_add_accel_group (GTK_WINDOW (window), accel_group) ; // Adicionar à janela

  menubar = gtk_menu_bar_new () ; // Criar a menubar

  // WINDOW

  mib_window = gtk_menu_item_new_with_label ("Window")                                ; // Criar item
  gtk_menu_shell_append (GTK_MENU_SHELL (menubar), mib_window)                        ; // Adicioná-la à menubar

  menu_window = gtk_menu_new ()                                                       ; // Criar menu para adicionar opções
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (mib_window), menu_window)                 ; // Torná-lo um submenu do original

  // New

  mi_new = criar_com_simbolo ("New", "window-new")                                    ; // Criar a subopção "New" com a função definida
  gtk_menu_shell_append (GTK_MENU_SHELL (menu_window), mi_new)                        ; // Adicionar ao submenu
  g_signal_connect (G_OBJECT (mi_new), "activate", G_CALLBACK (nova_janela), NULL)    ; // Abrir nova window se for clicado
  
  // Quit

  mi_quit = criar_com_simbolo ("Quit", "application-exit")                            ; // "Quit"
  gtk_menu_shell_append (GTK_MENU_SHELL (menu_window), mi_quit)                       ; // Adicionar ao submenu
  g_signal_connect (G_OBJECT (mi_quit), "activate", G_CALLBACK (gtk_main_quit), NULL) ; // Fechar a window 

  
  // OPÇÕES
  
  mib_opcoes = gtk_menu_item_new_with_label ("Opções")                                ; // Criar item
  gtk_menu_shell_append (GTK_MENU_SHELL (menubar), mib_opcoes)                        ; // Adicioná-lo à menubar

  menu_opcoes = gtk_menu_new ();                                                      ; // Criar menu para adicionar opções 
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (mib_opcoes), menu_opcoes)                 ; // Torná-lo um submenu do original

  // Gráfico

  mib_grafico = gtk_menu_item_new_with_label ("Gráfico")                              ; // Criar a opção
  gtk_menu_shell_append (GTK_MENU_SHELL (menu_opcoes), mib_grafico)                   ; // Adicionar ao submenu

  menu_grafico = gtk_menu_new ()                                                      ;  
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (mib_grafico), menu_grafico)               ; // Criar submenu do submenu

  mi_x1_t = gtk_menu_item_new_with_label ("x1 (t)")                                   ; // Opção 
  gtk_menu_shell_append (GTK_MENU_SHELL (menu_grafico), mi_x1_t)                      ; // Adicionar ao submenu do submenu
  g_signal_connect (G_OBJECT (mi_x1_t), "activate", G_CALLBACK (x1_t), NULL)          ; // Desenhar gráfico, ativando a função definida
  
  mi_x2_t = gtk_menu_item_new_with_label ("x2 (t)")                                   ;  
  gtk_menu_shell_append (GTK_MENU_SHELL (menu_grafico), mi_x2_t)                      ;
  g_signal_connect (G_OBJECT (mi_x2_t), "activate", G_CALLBACK (x2_t), NULL)          ;
 
  mi_y1_t = gtk_menu_item_new_with_label ("y1 (t)")                                   ;
  gtk_menu_shell_append (GTK_MENU_SHELL (menu_grafico), mi_y1_t)                      ;
  g_signal_connect (G_OBJECT (mi_y1_t), "activate", G_CALLBACK (y1_t), NULL)          ;
  
  mi_y2_t = gtk_menu_item_new_with_label ("y2 (t)")                                   ;
  gtk_menu_shell_append (GTK_MENU_SHELL (menu_grafico), mi_y2_t)                      ;
  g_signal_connect (G_OBJECT (mi_y2_t), "activate", G_CALLBACK (y2_t), NULL)          ;
 
  mi_v1_t = gtk_menu_item_new_with_label ("v1 (t)")                                   ;
  gtk_menu_shell_append (GTK_MENU_SHELL (menu_grafico), mi_v1_t)                      ;
  g_signal_connect (G_OBJECT (mi_v1_t), "activate", G_CALLBACK (v1_t), NULL)          ;

  mi_v2_t = gtk_menu_item_new_with_label ("v2 (t)")                                   ;
  gtk_menu_shell_append (GTK_MENU_SHELL (menu_grafico), mi_v2_t)                      ;
  g_signal_connect (G_OBJECT (mi_v2_t), "activate", G_CALLBACK (v2_t), NULL)          ;

  // Velocidade
  
  mib_speed = gtk_menu_item_new_with_label ("Velocidade")                             ; // Opção
  gtk_menu_shell_append (GTK_MENU_SHELL (menu_opcoes), mib_speed)                     ; // Adicionar ao submenu

  menu_speed = gtk_menu_new ()                                                        ; 
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (mib_speed), menu_speed)                   ; // Criar submenu do submenu
  
  mi_025x = gtk_menu_item_new_with_label ("0.25x")                                    ; // Criar item
  gtk_menu_shell_append (GTK_MENU_SHELL (menu_speed), mi_025x)                        ; // Adicionar ao submenu do submenu
  g_signal_connect (G_OBJECT (mi_025x), "activate", G_CALLBACK (speed_025x), NULL)    ; // Ativar função da velocidade

  mi_05x = gtk_menu_item_new_with_label ("0.5x")                                      ;
  gtk_menu_shell_append (GTK_MENU_SHELL (menu_speed), mi_05x)                         ;
  g_signal_connect (G_OBJECT (mi_05x), "activate", G_CALLBACK (speed_05x), NULL)      ;
  
  mi_1x = gtk_menu_item_new_with_label ("1x")                                         ;
  gtk_menu_shell_append (GTK_MENU_SHELL (menu_speed), mi_1x)                          ;
  g_signal_connect (G_OBJECT (mi_1x), "activate", G_CALLBACK (speed_1x), NULL)        ;
  
  mi_2x = gtk_menu_item_new_with_label ("2x")                                         ;
  gtk_menu_shell_append (GTK_MENU_SHELL (menu_speed), mi_2x)                          ;
  g_signal_connect (G_OBJECT (mi_2x), "activate", G_CALLBACK (speed_2x), NULL)        ;

  mi_3x = gtk_menu_item_new_with_label ("3x")                                         ;
  gtk_menu_shell_append (GTK_MENU_SHELL (menu_speed), mi_3x)                          ;
  g_signal_connect (G_OBJECT (mi_3x), "activate", G_CALLBACK (speed_3x), NULL)        ;

  mi_5x = gtk_menu_item_new_with_label ("5x")                                         ;
  gtk_menu_shell_append (GTK_MENU_SHELL (menu_speed), mi_5x)                          ;
  g_signal_connect (G_OBJECT (mi_5x), "activate", G_CALLBACK (speed_5x), NULL)        ;

  
  // INFO

  mib_info = gtk_menu_item_new_with_label ("Info")                                    ; // Criar opção
  gtk_menu_shell_append (GTK_MENU_SHELL (menubar), mib_info)                          ; // Adicionar à menubar
  
  menu_info = gtk_menu_new ()                                                         ; // Criar submenu
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (mib_info), menu_info)                     ; // Torná-lo submenu

  // Ajuda

  mi_ajuda = criar_com_simbolo ("Ajuda", "help-contents")                             ; // Subopção "Ajuda"
  gtk_menu_shell_append (GTK_MENU_SHELL (menu_info), mi_ajuda)                        ; // Adicionar ao submenu
  g_signal_connect (G_OBJECT (mi_ajuda), "activate", G_CALLBACK (fich_latex), NULL)   ; // Função para mostrar o ficheiro LATEX

  // Sobre
  
  mi_sobre = criar_com_simbolo ("Sobre", "help-about")                                ; // Criar a subopção "Sobre"
  gtk_menu_shell_append (GTK_MENU_SHELL (menu_info), mi_sobre)                        ; // Adicionar ao submenu
  g_signal_connect (G_OBJECT (mi_sobre), "activate", G_CALLBACK (sobre), NULL)        ; // Ativar função 'sobre'

  return menubar;
}



// Função para criar as escalas (recebe mínimo e máximo da escala e orientação)

GtkWidget *criar_scale (double minimo, double maximo, double inicial)
{
  GtkWidget *escala ;

  escala = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL, minimo, maximo, 1.) ; // Criar a escala
  gtk_scale_set_draw_value          (GTK_SCALE (escala), FALSE)                      ; // Não mostrar o valor (daí o FALSE)
  gtk_range_set_value               (GTK_RANGE (escala), inicial)                    ; // Valor inicial

  return escala     ;
}



// Main

int main (int argc, char **argv)
{
  gtk_init (&argc, &argv) ; // Iniciar o programa

  // Iniciar a janela
 
  window = gtk_window_new     (GTK_WINDOW_TOPLEVEL)                                                          ; // Tipo
  gtk_window_set_default_size (GTK_WINDOW (window), 800, 600)                                                ; // Dimensões iniciais
  gtk_window_set_title        (GTK_WINDOW (window), "Trabalho final de Programação")                         ; // Título
  gtk_window_set_position     (GTK_WINDOW (window), GTK_WIN_POS_CENTER)                                      ; // Posição

  // Adicionar boxes
  
  box_mae = gtk_box_new       (GTK_ORIENTATION_HORIZONTAL, 0)                                                ; // Box mãe
  gtk_container_add           (GTK_CONTAINER (window), box_mae)                                              ; // Adicionar à window

  box_options                 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0)                                    ; // Box com menubar, escalas e opções
  box_draws                   = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0)                                    ; // Box com pêndulo e gráfico
  box_buttons                 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0)                                    ; // Box com as variáveis
   
  gtk_box_pack_start          (GTK_BOX (box_mae), GTK_WIDGET (box_options), FALSE, FALSE, 0)                 ;  // Adicionar box_options a box_mae
  gtk_box_pack_start          (GTK_BOX (box_mae), GTK_WIDGET (box_draws)  , TRUE , TRUE, 10)                 ;  // Adicionar box_draws
  gtk_box_pack_end            (GTK_BOX (box_mae), GTK_WIDGET (box_buttons), FALSE, TRUE , 0)                 ;  // Adicionar box_buttons

  // Boxes para menubar, frames, escalas e buttons (à esquerda na janela)

  box_menubar                 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0)                                    ; // Menubar
  gtk_box_pack_start          (GTK_BOX (box_options), GTK_WIDGET (box_menubar), FALSE , TRUE, 0)             ; // Adicionar menubar a box_options
  
  box_frame1                  = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0)                                    ; // Box para frame1
  gtk_box_pack_start          (GTK_BOX (box_options), GTK_WIDGET (box_frame1), FALSE, TRUE, 5)               ; // Adicionar à box_options
  frame1                      = gtk_frame_new (NULL)                                                         ; // Criar frame 1
  label_pendulo               = gtk_label_new ("Pêndulo")                                                    ; // Texto da frame 1
  gtk_frame_set_label_widget  (GTK_FRAME (frame1), label_pendulo)                                            ; // Pôr label no topo
  gtk_frame_set_label_align   (GTK_FRAME (frame1), 0.1, 0.5)                                                 ; // Alinhar a label da frame
  gtk_box_pack_start          (GTK_BOX (box_frame1), frame1, FALSE, TRUE, 0)                                 ; // Adionar à box_frame1

  box_pendulum_xy             = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0)                                    ; // Box para scales do pêndulo
  gtk_container_add           (GTK_CONTAINER (frame1), box_pendulum_xy)                                      ; // Adicionar à frame 1
  
  box_frame2                  = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0)                                    ; // Comandos para a frame 2
  gtk_box_pack_start          (GTK_BOX (box_options), GTK_WIDGET (box_frame2), FALSE, TRUE, 5)               ;
  frame2                      = gtk_frame_new (NULL)                                                         ;
  label_grafico               = gtk_label_new ("Gráficos")                                                   ;
  gtk_frame_set_label_widget  (GTK_FRAME (frame2), label_grafico)                                            ;
  gtk_frame_set_label_align   (GTK_FRAME (frame2), 0.1, 0.5)                                                 ;
  gtk_box_pack_start          (GTK_BOX (box_frame2), frame2, FALSE, TRUE, 0)                                 ;
  
  box_graph_y                 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0)                                    ; // Box para scales do gráfico
  gtk_container_add           (GTK_CONTAINER (frame2), box_graph_y)                                          ; // Adicionar à frame 2
  
  box_options_lower           = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0)                                    ; // Box para opções no fim
  gtk_box_pack_end            (GTK_BOX (box_options), GTK_WIDGET (box_options_lower) , FALSE , TRUE, 1)      ;

  // Boxes para desenho e gráficos (a meio da janela)
  
  box_pendulum                = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0)                                  ; // Box com pêndulo
  box_graph                   = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0)                                  ; // Box com o gráfico
  
  gtk_box_pack_start          (GTK_BOX (box_draws), GTK_WIDGET (box_pendulum), TRUE, FALSE, 0)               ; // Pôr box_pendulum na box_draws
  gtk_box_pack_end            (GTK_BOX (box_draws), GTK_WIDGET (box_graph)   , TRUE, FALSE, 0)               ; // Pôr box_graph na box_draws

  draw_pendulum               = gtk_drawing_area_new ()                                                      ; // Área de desenho para o pêndulo
  draw_graph                  = gtk_drawing_area_new ()                                                      ; // Área de desenho para o gráfico
  
  gtk_box_pack_start          (GTK_BOX (box_pendulum), GTK_WIDGET (draw_pendulum), TRUE, TRUE, 0)            ; // Pôr draw_pendulum na box
  gtk_box_pack_end            (GTK_BOX (box_graph)   , GTK_WIDGET (draw_graph)   , TRUE, TRUE, 0)            ; // Pôr draw_graph na box

  gtk_widget_set_size_request (GTK_WIDGET (box_pendulum), 800, 400)                                          ; // Tamanho mínimo para a box
  
  // Boxes para as variáveis, na box_buttons (à direita na janela)

  box_m1                      = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0)                                  ; // M1
  gtk_box_pack_start          (GTK_BOX (box_buttons), GTK_WIDGET (box_m1)  , TRUE , TRUE, 0 )                ;
  
  box_m2                      = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0)                                  ; // M2
  gtk_box_pack_start          (GTK_BOX (box_buttons), GTK_WIDGET (box_m2)  , TRUE , TRUE, 10)                ;
  
  box_v1                      = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0)                                  ; // V1
  gtk_box_pack_start          (GTK_BOX (box_buttons), GTK_WIDGET (box_v1)  , TRUE , TRUE, 10)                ;
  
  box_v2                      = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0)                                  ; // V2
  gtk_box_pack_start          (GTK_BOX (box_buttons), GTK_WIDGET (box_v2)  , TRUE , TRUE, 10)                ;
  
  box_k                       = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0)                                  ; // K
  gtk_box_pack_start          (GTK_BOX (box_buttons), GTK_WIDGET (box_k)   , TRUE , TRUE, 10)                ;
  
  box_r                       = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0)                                  ; // R
  gtk_box_pack_start          (GTK_BOX (box_buttons), GTK_WIDGET (box_r)   , TRUE , TRUE, 10)                ;
  
  box_s                       = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0)                                  ; // S
  gtk_box_pack_start          (GTK_BOX (box_buttons), GTK_WIDGET (box_s)   , TRUE , TRUE, 10)                ;
  
  box_ang1                    = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0)                                  ; // Ângulo 1
  gtk_box_pack_start          (GTK_BOX (box_buttons), GTK_WIDGET (box_ang1), TRUE , TRUE, 10)                ;
  
  box_ang2                    = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0)                                  ; // Ângulo 2
  gtk_box_pack_start          (GTK_BOX (box_buttons), GTK_WIDGET (box_ang2), TRUE , TRUE, 10)                ;


  // Criar labels, adjustments e buttons para estas variáveis
  
  label_m1                    = gtk_label_new       (" M1 ")                                                 ; // Criar a label
  adj_m1                      = gtk_adjustment_new  (3., 0.5, 1000., 0.5, 0., 0.)                            ; // Adjustment e buttons
  // Nota: estrutura do gtka_djustement_new é 'valor inicial, mínimo, máximo, incremento, etc.' 
  button_m1                   = gtk_spin_button_new (GTK_ADJUSTMENT (adj_m1), 1., 1)                         ; // Necessário;1-nº de casas decimais

  label_m2                    = gtk_label_new       (" M2 ")                                                 ;
  adj_m2                      = gtk_adjustment_new  (3., 0.5, 1000., 0.5, 0., 0.)                            ;
  button_m2                   = gtk_spin_button_new (GTK_ADJUSTMENT (adj_m2), 1., 1)                         ;
    
  label_v1                    = gtk_label_new       (" V1 ")                                                 ;
  adj_v1                      = gtk_adjustment_new  (10., 0., 200., 0.5, 0., 0.)                             ;
  button_v1                   = gtk_spin_button_new (GTK_ADJUSTMENT (adj_v1), 1., 1)                         ;
    
  label_v2                    = gtk_label_new       (" V2 ")                                                 ;
  adj_v2                      = gtk_adjustment_new  (10., 0., 200., 0.5, 0., 0.)                             ;
  button_v2                   = gtk_spin_button_new (GTK_ADJUSTMENT (adj_v2), 1., 1)                         ;
  
  label_k                     = gtk_label_new       (" K ")                                                  ;
  adj_k                       = gtk_adjustment_new  (150., 1., 1000., 0.5, 0., 0.)                           ;
  button_k                    = gtk_spin_button_new (GTK_ADJUSTMENT (adj_k), 1., 1)                          ; 
  
  label_r                     = gtk_label_new       (" R ")                                                  ;
  adj_r                       = gtk_adjustment_new  (2., 0.1, 100., 0.5, 0., 0.)                             ;
  button_r                    = gtk_spin_button_new (GTK_ADJUSTMENT (adj_r), 1., 1)                          ;
  
  label_s                     = gtk_label_new       (" S ")                                                  ;
  adj_s                       = gtk_adjustment_new  (2., 0.1, 100., 0.5, 0., 0.)                             ;
  button_s                    = gtk_spin_button_new (GTK_ADJUSTMENT (adj_s), 1., 1)                          ;

  label_ang1                  = gtk_label_new       (" Ângulo 1 ")                                           ;
  adj_ang1                    = gtk_adjustment_new  (M_PI/4, 0., 2*M_PI, 0.2, 0., 0.)                        ;
  button_ang1                 = gtk_spin_button_new (GTK_ADJUSTMENT (adj_ang1), 1., 2)                       ;
  
  label_ang2                  = gtk_label_new       (" Ângulo 2 ")                                           ;
  adj_ang2                    = gtk_adjustment_new  (M_PI/4, 0., 2*M_PI, 0.2, 0., 0.)                        ;
  button_ang2                 = gtk_spin_button_new (GTK_ADJUSTMENT (adj_ang2), 1., 2)                       ;
  
  // Adicionar labels e botões das variáveis às respetivas boxes
  
  gtk_box_pack_start          (GTK_BOX (box_m1)  , GTK_WIDGET (button_m1)  , FALSE, TRUE, 0)                 ;
  gtk_box_pack_start          (GTK_BOX (box_m1)  , GTK_WIDGET (label_m1)   , FALSE, TRUE, 0)                 ; // M1
  
  gtk_box_pack_start          (GTK_BOX (box_m2)  , GTK_WIDGET (button_m2)  , FALSE, TRUE, 0)                 ;
  gtk_box_pack_start          (GTK_BOX (box_m2)  , GTK_WIDGET (label_m2)   , FALSE, TRUE, 0)                 ; // M2
  
  gtk_box_pack_start          (GTK_BOX (box_v1)  , GTK_WIDGET (button_v1)  , FALSE, TRUE, 0)                 ;
  gtk_box_pack_start          (GTK_BOX (box_v1)  , GTK_WIDGET (label_v1)   , FALSE, TRUE, 0)                 ; // V1
  
  gtk_box_pack_start          (GTK_BOX (box_v2)  , GTK_WIDGET (button_v2)  , FALSE, TRUE, 0)                 ;
  gtk_box_pack_start          (GTK_BOX (box_v2)  , GTK_WIDGET (label_v2)   , FALSE, TRUE, 0)                 ; // V2
  
  gtk_box_pack_start          (GTK_BOX (box_k)   , GTK_WIDGET (button_k)   , FALSE, TRUE, 0)                 ;
  gtk_box_pack_start          (GTK_BOX (box_k)   , GTK_WIDGET (label_k)    , FALSE, TRUE, 0)                 ; // K
  
  gtk_box_pack_start          (GTK_BOX (box_r)   , GTK_WIDGET (button_r)   , FALSE, TRUE, 0)                 ;
  gtk_box_pack_start          (GTK_BOX (box_r)   , GTK_WIDGET (label_r)    , FALSE, TRUE, 0)                 ; // R
  
  gtk_box_pack_start          (GTK_BOX (box_s)   , GTK_WIDGET (button_s)   , FALSE, TRUE, 0)                 ;
  gtk_box_pack_start          (GTK_BOX (box_s)   , GTK_WIDGET (label_s)    , FALSE, TRUE, 0)                 ; // S
  
  gtk_box_pack_start          (GTK_BOX (box_ang1), GTK_WIDGET (button_ang1), FALSE, TRUE, 0)                 ;
  gtk_box_pack_start          (GTK_BOX (box_ang1), GTK_WIDGET (label_ang1) , FALSE, TRUE, 0)                 ; // Ângulo 1
  
  gtk_box_pack_start          (GTK_BOX (box_ang2), GTK_WIDGET (button_ang2), FALSE, TRUE, 0)                 ;
  gtk_box_pack_start          (GTK_BOX (box_ang2), GTK_WIDGET (label_ang2) , FALSE, TRUE, 0)                 ; // Ângulo 2

  // Menubar

  menubar                     = criar_barra_de_menus (window)                                                ; // Criar menubar
  gtk_box_pack_start          (GTK_BOX (box_menubar), menubar, FALSE, FALSE, 0)                              ; // Adicionar à box_menubar

  // Criar escalas com labels
  
  label_pendulum_x            = gtk_label_new ("Posição em xx")                                              ; // Label da posição do desenho em xx
  gtk_box_pack_start          (GTK_BOX (box_pendulum_xy), GTK_WIDGET (label_pendulum_x), FALSE, TRUE, 0)     ; // Adicionar à box respetiva
  move_pendulum_x             = criar_scale (0., 1005., 400.)                                                 ; // Criar a scale
  gtk_box_pack_start          (GTK_BOX (box_pendulum_xy), move_pendulum_x, FALSE, FALSE, 5)                  ; // Adicionar à box

  label_pendulum_y            = gtk_label_new ("Posição em yy")                                              ; // Posição do desenho em yy
  gtk_box_pack_start          (GTK_BOX (box_pendulum_xy), GTK_WIDGET (label_pendulum_y), FALSE, TRUE, 0)     ;
  move_pendulum_y             = criar_scale (0., 400., 5.)                                                   ; 
  gtk_box_pack_start          (GTK_BOX (box_pendulum_xy), move_pendulum_y, FALSE, FALSE, 5)                  ;

  label_scale_pendulum        = gtk_label_new ("Escala do desenho")                                          ; // Escala do pêndulo
  gtk_box_pack_start          (GTK_BOX (box_pendulum_xy), GTK_WIDGET (label_scale_pendulum), FALSE, TRUE, 0) ;
  scale_pendulum              = criar_scale (-500., 200., -50.)                                              ;
  gtk_box_pack_start          (GTK_BOX (box_pendulum_xy), scale_pendulum, FALSE, FALSE, 5)                   ;

  label_scale_graph           = gtk_label_new ("Escala do eixo yy")                                          ; // Escala dos gráficos
  gtk_box_pack_start          (GTK_BOX (box_graph_y), GTK_WIDGET (label_scale_graph), FALSE, TRUE, 0)        ;
  scale_graph = criar_scale   (-450., 500., 20.)                                                             ;
  gtk_box_pack_start          (GTK_BOX (box_graph_y), scale_graph, FALSE, FALSE, 5)                          ;

  label_move_graph_x1         = gtk_label_new ("Posição do eixo de x1 (t)")                                  ; // Posição do gráfico x1 (t)
  gtk_box_pack_start          (GTK_BOX (box_graph_y), GTK_WIDGET (label_move_graph_x1), FALSE, TRUE, 0)      ;
  move_graph_x1               = criar_scale (-305., 495., 95.)                                               ;
  gtk_box_pack_start          (GTK_BOX (box_graph_y), move_graph_x1, FALSE, FALSE, 5)                        ;

  label_move_graph_x2         = gtk_label_new ("Posição do eixo de x2 (t)")                                  ; // Posição do gráfico x2 (t)
  gtk_box_pack_start          (GTK_BOX (box_graph_y), GTK_WIDGET (label_move_graph_x2), FALSE, TRUE, 0)      ;
  move_graph_x2               = criar_scale (-295., 505., 105.)                                              ;
  gtk_box_pack_start          (GTK_BOX (box_graph_y), move_graph_x2, FALSE, FALSE, 5)                        ;

  label_move_graph_y1         = gtk_label_new ("Posição do eixo de y1 (t)")                                  ; // Posição do gráfico y1 (t)
  gtk_box_pack_start          (GTK_BOX (box_graph_y), GTK_WIDGET (label_move_graph_y1), FALSE, TRUE, 0)      ;
  move_graph_y1               = criar_scale (-265., 535., 135.)                                              ;
  gtk_box_pack_start          (GTK_BOX (box_graph_y), move_graph_y1, FALSE, FALSE, 5)                        ;

  label_move_graph_y2         = gtk_label_new ("Posição do eixo de y2 (t)")                                  ; // Posição do gráfico y2 (t)
  gtk_box_pack_start          (GTK_BOX (box_graph_y), GTK_WIDGET (label_move_graph_y2), FALSE, TRUE, 0)      ;
  move_graph_y2               = criar_scale (-225., 575., 175.)                                              ;
  gtk_box_pack_start          (GTK_BOX (box_graph_y), move_graph_y2, FALSE, FALSE, 5)                        ;

  label_move_graph_v1         = gtk_label_new ("Posição do eixo de v1 (t)")                                  ; // Posição do gráfico v1 (t)
  gtk_box_pack_start          (GTK_BOX (box_graph_y), GTK_WIDGET (label_move_graph_v1), FALSE, TRUE, 0)      ;
  move_graph_v1               = criar_scale (-355., 445., 45.)                                               ;
  gtk_box_pack_start          (GTK_BOX (box_graph_y), move_graph_v1, FALSE, FALSE, 5)                        ;

  label_move_graph_v2         = gtk_label_new ("Posição do eixo de v2 (t)")                                  ; // Posição do gráfico v2 (t)
  gtk_box_pack_start          (GTK_BOX (box_graph_y), GTK_WIDGET (label_move_graph_v2), FALSE, TRUE, 0)      ;
  move_graph_v2               = criar_scale (-375., 425., 25.)                                               ;
  gtk_box_pack_start          (GTK_BOX (box_graph_y), move_graph_v2, FALSE, FALSE, 5)                        ;
  
  // No caso das escalas terem sido usadas, alterar os valores das variáveis respetivas

  g_signal_connect            (G_OBJECT (move_pendulum_x), "value-changed", G_CALLBACK (obter_valor_da_escala), &x_ref)          ;
  g_signal_connect            (G_OBJECT (move_pendulum_y), "value-changed", G_CALLBACK (obter_valor_da_escala), &y_ref)          ;
  g_signal_connect            (G_OBJECT (scale_pendulum) , "value-changed", G_CALLBACK (obter_valor_da_escala), &fator)          ; 
  g_signal_connect            (G_OBJECT (scale_graph)    , "value-changed", G_CALLBACK (obter_valor_da_escala), &fator_graph)    ;
  g_signal_connect            (G_OBJECT (move_graph_x1)  , "value-changed", G_CALLBACK (obter_valor_da_escala), &y_ref_graph_x1) ;
  g_signal_connect            (G_OBJECT (move_graph_x2)  , "value-changed", G_CALLBACK (obter_valor_da_escala), &y_ref_graph_x2) ;
  g_signal_connect            (G_OBJECT (move_graph_y1)  , "value-changed", G_CALLBACK (obter_valor_da_escala), &y_ref_graph_y1) ;
  g_signal_connect            (G_OBJECT (move_graph_y2)  , "value-changed", G_CALLBACK (obter_valor_da_escala), &y_ref_graph_y2) ;
  g_signal_connect            (G_OBJECT (move_graph_v1)  , "value-changed", G_CALLBACK (obter_valor_da_escala), &y_ref_graph_v1) ;
  g_signal_connect            (G_OBJECT (move_graph_v2)  , "value-changed", G_CALLBACK (obter_valor_da_escala), &y_ref_graph_v2) ;
  
  // Botões de 'Reset', 'Start & Stop' e 'Show / hide graph'
  
  button_reset                = gtk_button_new_with_label ("Reset")                                          ;
  button_start_stop           = gtk_toggle_button_new_with_label ("Start & Stop")                            ;
  button_graph                = gtk_toggle_button_new_with_label ("Show / hide graph")                       ;

  // Adicioná-los à box_options_lower
  
  gtk_box_pack_end            (GTK_BOX (box_options_lower), GTK_WIDGET (button_reset)     , FALSE, FALSE, 0) ;
  gtk_box_pack_end            (GTK_BOX (box_options_lower), GTK_WIDGET (button_start_stop), FALSE, FALSE, 0) ;
  gtk_box_pack_end            (GTK_BOX (box_options_lower), GTK_WIDGET (button_graph)     , FALSE, FALSE, 0) ;

  // Chamar a função_principal em intervalos regulares de inteiros (10 milissegundos)
  
  g_timeout_add               (10, (GSourceFunc)funcao_principal, draw_pendulum)                             ;
  
  g_signal_connect            (G_OBJECT (draw_pendulum)    , "draw"   , G_CALLBACK (desenhar_pendulo), NULL) ; // Função que faz os desenhos
  g_signal_connect            (G_OBJECT (button_reset)     , "clicked", G_CALLBACK (reset)           , NULL) ; // Clicando em 'Reset'
  g_signal_connect            (G_OBJECT (button_start_stop), "clicked", G_CALLBACK (start_stop)      , NULL) ; // Clicando em 'Start&Stop' 
  g_signal_connect            (G_OBJECT (button_graph)     , "clicked", G_CALLBACK (show_hide_graph) , NULL) ; // Clicando em 'Show / hide graph

  // Parar programa se carregar no canto superior direito
  
  g_signal_connect           (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), NULL)                ;

  // Mostrar todo o conteúdo da janela
  
  gtk_widget_show_all        (window)                                                                        ;

  // Finalizar o programa
  
  gtk_main () ;
  return 0    ;
}
