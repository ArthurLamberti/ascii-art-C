<h1 align="center">Ascii Art</h1>
<p align="center">Programa pra transformar imagem em Ascii Art, transformando em tons de cinza, podendo redimensionar a imagem</p>
<p align="center">Trabalho feito na disciplina de Programacao de Software Basico - PUCRS</p>
<p align="center">
 <a href="#Objetivo">Objetivo</a> •
 <a href="#Tecnologias">Tecnologias</a> • 
 <a href="#Features">Features</a> • 
 <a href="#Rodando a aplicacao">Rodando a aplicacao</a> • 
</p>
<h4 align="center">Entregue conforme requisitado</h4>

### Objetivo
  <p>Essa aplicacao tem como objetivo transformar de acordo com um fator de reducao, qualquer imagem para uma ASCII Art</p>

### Tecnologias
  <p>Para a realizacao da aplicacao, foi utilizado a linguagem de programacao C, alem de utilizar a lib SOIL</p>

### Features

- [x] Conversao de imagem para tons de cinza
- [x] Ler o fator de reducao
- [x] Fazer proporcao de pixels para tamanho do caracter
- [x] Calcular tom medio dos pixels conforme proporcao
- [x] Gerar o caracter de acordo com o tom medio
- [x] Gerar saida.html com o conteudo formatado para vizualizacao
- [ ] Ter opcao de vizualizar imagem colorida

### Pre Requisitos
Em caso de utilizar linux, sera necessario a instalacao dos pacotes de desenvolvimento do OpenGL</br>
$ sudo apt-get install freeglut3-dev


### Rodando a aplicacao
<p>Clone esse repositorio</p>
$ git clone https://github.com/ArthurLamberti/ascii-art-C.git
<p>Va para a pasta da aplicacao no terminal/cmd</p>
$ cd ascii-art-C
<p>Instale e compile a aplicacao</p>
<p>Para linux e MacOS</p>
$ make
<p>Para Windows</p>
$ mingw32-make -f Makefile.mk
<p>Passe uma imagem em formato .png e o fator de reducao para o loader</p>
$ ./loader pathToImage.png 0
