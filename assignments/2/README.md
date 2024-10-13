# Trabalho Prático 1

Nos exercícios seguintes é proposta a escrita de funções em _assembly_ para a arquitetura x86-64, usando a sintaxe AT&T, e seguindo os princípios básicos de geração de código do compilador de C da GNU

Deve submeter a sua realização de cada exercício aos testes anexos a este enunciado. As respetivas instruções de utilização estão incluídas no próprio pacote de testes.

Tenha o cuidado de apresentar o código de forma cuidada, apropriadamente indentado e comentado (siga as recomendações em anexo). Não é necessário relatório.

Encoraja-se a discussão de problemas e soluções com colegas. Tenha consciência que os exercícios só são benéficos na aprendizagem se forem realizados com honestidade académica. Contacte o docente se tiver dúvidas.

## Exercício 1

Escreva em assembly a função **rotate_right** que desloca para a direita (no sentido de maior peso para o de menor peso) o valor a 128 bit, que recebe no parâmetro **value**, o número de posições indicadas no parâmetro n. O valor numérico de 128 bit é formado pela concatenação de dois valores a 64 bit armazenados num array com duas posições, segundo o formato little-endian. Os bits que saem da posição de menor peso entram, pela mesma ordem, na posição de maior peso. Utilize a instrução assembly **shrd**.

```c
void rotate_right(unsigned long value[], size_t n);
```

## Exercício 2

Escreva em assembly a função **my_memcmp** segundo a definição de **memcmp** tal como está definida na biblioteca standard da linguagem C. Esta função compara os conteúdos de memória referenciados pelos parâmetros **ptr1** e **ptr2**. Na programação, procure minimizar o número de acessos à memória realizando, sempre que possível, acessos a palavras de 64 bits em endereços alinhados (i.e., endereços múltiplos de 8) e minimizar o número de iterações, mesmo que para isso tenha que aumentar a memória ocupada por código.

```c
int my_memcmp( const void *ptr1, const void *ptr2, size_t num );
```

```




```
