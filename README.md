**Compilando**:
```
make
```

**Executando**:
```
./eyes
```

**Executando treinamento**:
```
python svm.py
```

## Funcionamento

O objetivo final desse programa é de que seja identificado qual direção o olho
está apontando. Isso servirá para, num momento futuro, movimentar o mouse
na direção em que o olho aponta.

Num primeiro momento, as direções serão: cima, baixo, esquerda e direita.  
Quando uma maior experiência for desenvolvida na calibração do modelo,
as outras 4 direções referentes às diagonais serão adicionadas.

O **estado atual** do programa está marcado na *TODO list* abaixo. 

Os arquivos de imagem para treinamento são obtidos através da execução de `eyes` e servem 
de entrada para a calibração do modelo.

O treinamento é feito utilizando o script python `svm.py`. Atualmente, a taxa de acerto
é em torno de 87.5%.

O próximo passo é fazer o modelo treinado persistir para ser utilizado numa aplicação
que detecte o olho pela webcam e estime a direção do olhar.

## *TODO list*

- [x] Identificação da face (visão)
- [x] Identificação dos olhos (visão)
- [x] Extração da imagem dos olhos para treinamento (visão)
- [x] Pré-tratamento da imagem dos olhos antes do treinamento
  - [x] Aplicação de filtro *threshold* sobre a intensidade média da imagem (visão)
  - [x] Normalização do tamanho [60x60] (visão / aprendizado )
- [x] Treinamento do modelo de predição (aprendizado)
- [ ] Execução do programa com o modelo calibrado (aprendizado)
- [ ] Predição satisfatória da direção do olho (aprendizado)
- [ ] Fazer o mouse se movimentar na direção predita
- [ ] Programa completo em C++
- [ ] Construir um módulo do NodeJS utilizando N-API


**Exemplo de uso do programa completo em C++**:

```
$ ./eyetrack <condiçao> [arq_modelo] <dt>

  condição: 'cal' para calibrar ou 'use' para utilizar modelo calibrado 'arq_modelo'
  dt:       intervalo de tempo (em segundos) entre predições
```

A resposta do programa será uma string contendo a indicação da direção do olhar a cada período X de tempo.

