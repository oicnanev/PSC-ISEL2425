# Exercício 2

## Valgrind

```bash
valgrind --leak-check=full -s ./http_post_json
```  

Output:

```txt
==450812== Memcheck, a memory error detector
==450812== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==450812== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==450812== Command: ./http_post_json
==450812== 
Response: 44.99,"quantity":4,"total":179.96,"discountPercentage":10.75,"discountedPrice":161,"thumbnail":"https://cdn.dummyjson.com/products/images/sports-accessories/Cricket%20Helmet/thumbnail.png"}],"total":179.96,"discountedTotal":161,"userId":1,"totalProducts":1,"totalQuantity":4}
==450812== 
==450812== HEAP SUMMARY:
==450812==     in use at exit: 0 bytes in 0 blocks
==450812==   total heap usage: 144,669 allocs, 144,669 frees, 26,841,270 bytes allocated
==450812== 
==450812== All heap blocks were freed -- no leaks are possible
==450812== 
==450812== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
``` 
