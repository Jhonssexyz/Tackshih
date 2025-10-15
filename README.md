⚔️ Tackshih: Uma Aventura em C
Um RPG de ação e exploração baseado em console, desenvolvido puramente em C.

📖 Visão Geral do Jogo
Tackshih é um projeto de jogo de console de estilo roguelike, onde o jogador (&) navega por diferentes ambientes de labirinto, enfrenta perigos e busca a saída para progredir. A sobrevivência depende da escolha inicial de dificuldade, que define as estatísticas do jogador, e da capacidade de evitar ou confrontar inimigos como Goblins e um Vampiro.

O jogo é dividido em fases progressivas, cada uma apresentando novos desafios e mecânicas.

✨ Características de Jogabilidade
Progressão em Múltiplas Fases: O jogo é estruturado em três fases distintas, cada uma com um mapa maior e desafios mais complexos.

Fase 1 (Iniciação): Um mapa 15x15, focado na exploração para encontrar a Chave (@) e abrir a Porta (D para =).

Fase 2 (Armadilhas): Um mapa 30x30, introduzindo Espinhos (#) que causam dano, exigindo que o jogador encontre um Botão (O) para desativá-los. Inimigos Goblins estão presentes.

Fase 3 (Confronto): Um grande mapa 40x40, onde o jogador deve enfrentar ou evadir o poderoso Vampiro (V), que o persegue ativamente, e utilizar Portais (> e <) para se movimentar.

Controles: A movimentação é feita pelas teclas W A S D, e a interação com objetos cruciais (chaves, portas, portais) é realizada pela tecla I.

🛡️ Classes de Personagem (Níveis de Dificuldade)
A escolha inicial no menu de dificuldade determina a "classe" do personagem, alterando drasticamente suas estatísticas base e definindo o estilo de jogo.


______________________________________________________________________________________________________________
  Opção	Nome Interno	Dificuldade	Foco	Vida (vida_pers)	Ataque (atq_pers)	Distância de Ataque (dist_pers) 
  1	G	Fácil	Balanceado	40	              15	          2             (Curta)                                                             
  2	A	Médio	Distância	  30	              10	          5             (Média)                 
  3	M	Inferno	Vidro Canhão	10	          25	          5             (Média)                 
_______________________________________________________________________________________________________________
