# Exercício 3

As structs foram implementadas no `types.h`

As funções `Products *products_get();`, `Users *users_get();` e `bool cart_put(Cart *cart);` foram implentadas num unico ficheiro, `api.c`

## Teste com valgrind

```bash
valgrind --leak-check=full -s ./test_api
```

Output do valgrind:

```txt
==467002== Memcheck, a memory error detector
==467002== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==467002== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==467002== Command: ./test_api
==467002== 
Response: et","price":44.99,"quantity":4,"total":179.96,"discountPercentage":10.75,"discountedPrice":161,"thumbnail":"https://cdn.dummyjson.com/products/images/sports-accessories/Cricket%20Helmet/thumbnail.png"}],"total":179.96,"discountedTotal":161,"userId":1,"totalProducts":1,"totalQuantity":4}
==467002== 
==467002== HEAP SUMMARY:
==467002==     in use at exit: 0 bytes in 0 blocks
==467002==   total heap usage: 443,573 allocs, 443,573 frees, 81,881,817 bytes allocated
==467002== 
==467002== All heap blocks were freed -- no leaks are possible
==467002== 
==467002== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```