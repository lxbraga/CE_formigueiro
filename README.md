# Computação Escalável - A1

> Fundação Getúlio Vargas RJ - Escola de Matemática Aplicada<br>
> Graduação em Ciência de Dados e Inteligência Artificial<br>
> Disciplina: Computação Escalável<br>
> Alunos: Gianlucca Devigili, Maisa Fraiz, Lucas Braga, Victor Bombarda<br>

## Engenharia de Software

### Requisitos do Sistema:

#### Formiga:
1. As formigas devem ser capazes de se mover pelo mapa;
   + Cada formiga toma suas decisões individualmente;
2. As formigas devem ser capazes de perceber seu ambiente em volta;
   + Cada formiga tem um campo de visão limitado informado na entrada do programa;
   + Ao ver uma unidade de feromônio, a formiga deve seguir o rastro em direção à comida (ou seja, direção contrária ao formigueiro);
   + Ao ver uma unidade de comida, a formiga deve seguir em sua direção;
   + Ao ver uma formiga de otura colônia, a formiga deve atacá-la;
   + Ao ver uma formiga da própria colônia carregando comida, se a própria formiga não estiver carregando comida nem seguindo um rastro de feromônio, esta deve proteger a formiga que carrega comida de outros ataques;
3. As formigas devem ser capazes de transportar comida;
   + As formigas devem escolher o melhor caminho (linha reta) para chegar à colônia;
   + As formigas sabem a direção exata do formigueiro;
4. As formigas devem ser capazes de soltar feromônios;
   + As formigas devem soltar feromônios quando estiverem carregando comida para indicar o caminho para a comida;
5. As formigas devem ser capazes de atacar outras formigas;
   + as formigas podem atacar formigas de outras colônias;
   + o resultado dos ataques deve ser decidido aleatoriamente;
   + a quantidade de formigas deve influenciar no resultado do ataque;
6. As formigas devem ser capazes de proteger outras formigas;
   + formigas que não estão carregando comida podem proteger formigas da própria colônia de ataques;