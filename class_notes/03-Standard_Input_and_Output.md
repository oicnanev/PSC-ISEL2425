# Standard Input and Output

## Modelo de ficheiro

![Modelo de ficheiro](./img/stdin_out.png)

O conteúdo de um ficheiro pode ser interpretado em modo de texto "**t**" ou em modo binário "**b**". Em modo binário o ficheiro é encarado como uma sequência de bytes indiferenciados. Em modo de texto, é encarado como uma sequência de linhas de texto, em cada linha é formada por uma sequência de caracteres imprimíveis e treminada por um mercador de fim de linha. No Unix o marcador é o caracter ```\n```, no Windows, o marcador é a sequência ```\n\r```.

Todos os ficheiros, incluindo os que têm texto, podem ser interpretados em binário.

As transferências de dados entre a memória e o ficheiro processam-se a partir de um indicador de posição associado ao ficheiro (*file pointer*). O indicador de posição avança automaticamente após cada operação de transferência de um número igaul ao número de *bytes* transferidos.

Na operação de abertura, o indicador de posição é colocado no início (opções "r" e "w") ou para além do fim (opção "a").

Existem funções para modificar o indicador de posição de um ficheiro aberto.

## Suportes físicos

Os dispositivos a considerar são:

- ecrã
- teclado
- ficheiros de disco

Os dispositivos são representados por variáveis do tipo ponteiro para FILE (*file descriptor*). No início da execução de um programa, existem disponíveis três destas variáveis que representam o teclado e o ecrã

- **FILE *stdin = &struct_stdin**
- **FILE *stdout = &struct_stdout**
- **FILE *stderr = &struct_stderr**

## Modo texto

O texto é enviado ou recolhido dos dispositivos como uma sequência de linhas. As linhas formadas por caracteres e terminadas por um caracter marcador de fim de linha - **\n**

No ecrã, a escrita do caracter **\n** provoca uma mudança de linha. No teclado, a tecla ```ENTER``` produz o caracter **\n**.

## Output

A escrita é realizada no dispositivo indicado no parâmetro **stream**. Se for **stdout** será no ecrã.

- A função **fputs** escreve a *string* indicada por **s** e acrescenta o caracter **\n**, o que provoca uma mudança de linha.

```c
int fputs(const *s, FILE *stream);
```

- A função **printf** escreve o texto indicado em **format**, substituindo os campos da formatação **%** pela representação dos valores passados nos restantes parâmetros.

```c
int fprintf(FILE *stream, const char *format, ...);
```

- A função **fputch** escreve um caracter

```c
int fputch(int c, FILE *stream);
```

As três funções seguintes equivalem às anteriores com **stdout** como argumento no parâmetros **stream**.

```c
int puts(const char *s);
int printf(const char *format, ...);
int putchar(int c);
```

Para atualizar o ficheiro em disco com dados que estejam em *buffers* intermédios, resultantes de operações de escrita anteriores

```c
int fflush(FILE *stream);
```

Especificações de conversão das funções *printf*:

- **%<flags><width><.precision><leght><conversion>**
- **flags**:
    * **+** imprime o sinal
    * **-** ajuste à esquerda
    * **space** se não for um sinal
    * **0** preencher com zeros
    * **#** modo de escrita alternativa
- **width** dimensão mínima do campo
- **.precision** dimensão máxima para uma string ou casas decimais
- **length**:
	- **h** short
	- **l** long
	- **L** long
- **conversion** d, i, o, x, X, u, c, s, f, e, E, g, G, p, n, %

## Input

A leitura é relaizada do dispisitivo indicado no parâmetro **stream**. Se for **stdin** será do teclado.

```c

```