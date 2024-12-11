# Exercício 4

Para criar a biblioteca de ligação dinâmica, `libpsc.so` 
decidimos juntar as funções do exercicio 1 num só ficheiro, `http_utils.c` 
para assim utilizar o header `http_utils.h`.

Foi assim criada uma estrutura de ficheiros:

```txt
exercício4
├── include
|   ├── http_utils.h
│   └── types.h
├── lib
│   └── libpsc.so
├── Makefile
├── README.md
├── src
│   ├── api.c
│	├── api.o
│   ├── http_utils.c
│   └── http_utils.o
└── test
    ├── main.c
    └── test_program

``` 

## Teste com valgrid

```bash
valgrind --leak-check=full -s .test//test_program
```

Output:

```txt
==490231== Memcheck, a memory error detector
==490231== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==490231== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==490231== Command: ./test/test_program
==490231== 
./test_program: error while loading shared libraries: libpsc.so: cannot open shared object file: No such file or directory
==490231== 
==490231== HEAP SUMMARY:
==490231==     in use at exit: 0 bytes in 0 blocks
==490231==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==490231== 
==490231== All heap blocks were freed -- no leaks are possible
==490231== 
==490231== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

```
