# Exercício 5

## meter bibloteca no path

```bash
export LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH
```

## teste com valgrind

```bash
valgrind --leak-check=full -s ./test/test_program
```

Output do valgrind **TUDO FODIDO**

```txt
oicnanev@CodePoetry:~/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5$ valgrind --leak-check=full -s ./test/test_program
==514996== Memcheck, a memory error detector
==514996== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==514996== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==514996== Command: ./test/test_program
==514996== 

Listando utilizadores:
ID: 1, Nome: (null)
ID: 2, Nome: (null)
ID: 3, Nome: (null)
ID: 4, Nome: (null)
ID: 5, Nome: (null)
ID: 6, Nome: (null)
ID: 7, Nome: (null)
ID: 8, Nome: (null)
ID: 9, Nome: (null)
ID: 10, Nome: (null)
ID: 11, Nome: (null)
ID: 12, Nome: (null)
ID: 13, Nome: (null)
ID: 14, Nome: (null)
ID: 15, Nome: (null)
ID: 16, Nome: (null)
ID: 17, Nome: (null)
ID: 18, Nome: (null)
ID: 19, Nome: (null)
ID: 20, Nome: (null)
ID: 21, Nome: (null)
ID: 22, Nome: (null)
ID: 23, Nome: (null)
ID: 24, Nome: (null)
ID: 25, Nome: (null)
ID: 26, Nome: (null)
ID: 27, Nome: (null)
ID: 28, Nome: (null)
ID: 29, Nome: (null)
ID: 30, Nome: (null)

Definindo o utilizador corrente como o usuário de ID 1:
Utilizador corrente definido: (null)

Listando produtos na categoria 'eletrônicos' (por preço crescente):

Listando produtos na categoria 'eletrônicos' (preço crescente):

Carrinho de compras (vazio):

Adicionando produtos ao carrinho:

Carrinho de compras com produtos:
Produto ID: 1, Quantidade: 2
Produto ID: 3, Quantidade: 1

Finalizando a compra...
==514996== Conditional jump or move depends on uninitialised value(s)
==514996==    at 0x484F229: strlen (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x48E7D97: __printf_buffer (vfprintf-process-arg.c:435)
==514996==    by 0x48E8591: __vfprintf_internal (vfprintf-internal.c:1559)
==514996==    by 0x48DD1A2: printf (printf.c:33)
==514996==    by 0x485BB11: http_post_json (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x485C2AA: cart_put (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x1096E6: main (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/test/test_program)
==514996== 
Response: 
==514996== Invalid read of size 8
==514996==    at 0x4AF2D7B: curl_slist_free_all (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x485BB2E: http_post_json (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x485C2AA: cart_put (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x1096E6: main (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/test/test_program)
==514996==  Address 0x734d3a4 is 52 bytes inside a block of size 152 free'd
==514996==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x597B1CF: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x4D9505D: gnutls_x509_crt_deinit (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA0D47: gnutls_x509_trust_list_deinit (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D11B86: gnutls_certificate_free_credentials (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4B114F1: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4B10CEF: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AB55A6: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AA8E20: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4B0959C: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AAE3F5: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AE5E62: curl_multi_cleanup (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==  Block was alloc'd at
==514996==    at 0x484D953: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x597B3AA: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x597B508: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x5984FE4: asn1_der_decoding2 (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x4D95332: gnutls_x509_crt_import (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D95D01: gnutls_x509_crt_list_import (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D96072: gnutls_x509_crt_list_import2 (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA4904: gnutls_x509_trust_list_add_trust_mem (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA4CEC: gnutls_x509_trust_list_add_trust_file (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA5145: ??? (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA51A4: gnutls_x509_trust_list_add_trust_dir (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D231ED: gnutls_certificate_set_x509_trust_dir (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996== 
==514996== Invalid read of size 8
==514996==    at 0x4AF2D7F: curl_slist_free_all (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x485BB2E: http_post_json (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x485C2AA: cart_put (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x1096E6: main (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/test/test_program)
==514996==  Address 0x734d39c is 44 bytes inside a block of size 152 free'd
==514996==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x597B1CF: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x4D9505D: gnutls_x509_crt_deinit (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA0D47: gnutls_x509_trust_list_deinit (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D11B86: gnutls_certificate_free_credentials (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4B114F1: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4B10CEF: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AB55A6: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AA8E20: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4B0959C: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AAE3F5: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AE5E62: curl_multi_cleanup (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==  Block was alloc'd at
==514996==    at 0x484D953: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x597B3AA: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x597B508: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x5984FE4: asn1_der_decoding2 (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x4D95332: gnutls_x509_crt_import (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D95D01: gnutls_x509_crt_list_import (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D96072: gnutls_x509_crt_list_import2 (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA4904: gnutls_x509_trust_list_add_trust_mem (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA4CEC: gnutls_x509_trust_list_add_trust_file (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA5145: ??? (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA51A4: gnutls_x509_trust_list_add_trust_dir (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D231ED: gnutls_certificate_set_x509_trust_dir (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996== 
==514996== Invalid write of size 8
==514996==    at 0x4AF2D89: curl_slist_free_all (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x485BB2E: http_post_json (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x485C2AA: cart_put (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x1096E6: main (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/test/test_program)
==514996==  Address 0x734d39c is 44 bytes inside a block of size 152 free'd
==514996==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x597B1CF: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x4D9505D: gnutls_x509_crt_deinit (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA0D47: gnutls_x509_trust_list_deinit (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D11B86: gnutls_certificate_free_credentials (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4B114F1: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4B10CEF: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AB55A6: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AA8E20: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4B0959C: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AAE3F5: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AE5E62: curl_multi_cleanup (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==  Block was alloc'd at
==514996==    at 0x484D953: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x597B3AA: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x597B508: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x5984FE4: asn1_der_decoding2 (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x4D95332: gnutls_x509_crt_import (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D95D01: gnutls_x509_crt_list_import (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D96072: gnutls_x509_crt_list_import2 (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA4904: gnutls_x509_trust_list_add_trust_mem (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA4CEC: gnutls_x509_trust_list_add_trust_file (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA5145: ??? (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA51A4: gnutls_x509_trust_list_add_trust_dir (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D231ED: gnutls_certificate_set_x509_trust_dir (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996== 
==514996== Invalid free() / delete / delete[] / realloc()
==514996==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x4AF2D99: curl_slist_free_all (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x485BB2E: http_post_json (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x485C2AA: cart_put (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x1096E6: main (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/test/test_program)
==514996==  Address 0x734d39c is 44 bytes inside a block of size 152 free'd
==514996==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x597B1CF: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x4D9505D: gnutls_x509_crt_deinit (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA0D47: gnutls_x509_trust_list_deinit (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D11B86: gnutls_certificate_free_credentials (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4B114F1: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4B10CEF: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AB55A6: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AA8E20: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4B0959C: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AAE3F5: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AE5E62: curl_multi_cleanup (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==  Block was alloc'd at
==514996==    at 0x484D953: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x597B3AA: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x597B508: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x5984FE4: asn1_der_decoding2 (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x4D95332: gnutls_x509_crt_import (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D95D01: gnutls_x509_crt_list_import (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D96072: gnutls_x509_crt_list_import2 (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA4904: gnutls_x509_trust_list_add_trust_mem (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA4CEC: gnutls_x509_trust_list_add_trust_file (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA5145: ??? (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA51A4: gnutls_x509_trust_list_add_trust_dir (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D231ED: gnutls_certificate_set_x509_trust_dir (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996== 
Compra finalizada com sucesso!
*** stack smashing detected ***: terminated
==514996== 
==514996== Process terminating with default action of signal 6 (SIGABRT)
==514996==    at 0x491BB1C: __pthread_kill_implementation (pthread_kill.c:44)
==514996==    by 0x491BB1C: __pthread_kill_internal (pthread_kill.c:78)
==514996==    by 0x491BB1C: pthread_kill@@GLIBC_2.34 (pthread_kill.c:89)
==514996==    by 0x48C226D: raise (raise.c:26)
==514996==    by 0x48A58FE: abort (abort.c:79)
==514996==    by 0x48A67B5: __libc_message_impl.cold (libc_fatal.c:132)
==514996==    by 0x49B3C18: __fortify_fail (fortify_fail.c:24)
==514996==    by 0x49B4EA3: __stack_chk_fail (stack_chk_fail.c:24)
==514996==    by 0x10976C: main (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/test/test_program)
==514996== 
==514996== HEAP SUMMARY:
==514996==     in use at exit: 113,219 bytes in 809 blocks
==514996==   total heap usage: 443,576 allocs, 442,768 frees, 323,669,951 bytes allocated
==514996== 
==514996== 47 (16 direct, 31 indirect) bytes in 1 blocks are definitely lost in loss record 35 of 66
==514996==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x4AF2D19: curl_slist_append (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x485B9D4: http_post_json (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x485C2AA: cart_put (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x1096E6: main (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/test/test_program)
==514996== 
==514996== 290 bytes in 30 blocks are definitely lost in loss record 52 of 66
==514996==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x493134E: strdup (strdup.c:42)
==514996==    by 0x485BF90: products_get (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x10948C: main (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/test/test_program)
==514996== 
==514996== 336 bytes in 1 blocks are possibly lost in loss record 53 of 66
==514996==    at 0x484D953: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x40145AB: calloc (rtld-malloc.h:44)
==514996==    by 0x40145AB: allocate_dtv (dl-tls.c:370)
==514996==    by 0x40145AB: _dl_allocate_tls (dl-tls.c:629)
==514996==    by 0x491A606: allocate_stack (allocatestack.c:429)
==514996==    by 0x491A606: pthread_create@@GLIBC_2.34 (pthread_create.c:655)
==514996==    by 0x4AC81DC: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4B08366: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AECED1: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AED5A9: curl_multi_perform (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4ABBE7A: curl_easy_perform (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x485B83C: http_get_json (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x485C002: users_get (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x109447: main (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/test/test_program)
==514996== 
==514996== 2,304 bytes in 1 blocks are possibly lost in loss record 62 of 66
==514996==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x4004EDC: malloc (rtld-malloc.h:56)
==514996==    by 0x4004EDC: _dlfo_mappings_segment_allocate (dl-find_object.c:217)
==514996==    by 0x4004EDC: _dl_find_object_update_1 (dl-find_object.c:671)
==514996==    by 0x4004EDC: _dl_find_object_update (dl-find_object.c:805)
==514996==    by 0x400DC37: dl_open_worker_begin (dl-open.c:756)
==514996==    by 0x400151B: _dl_catch_exception (dl-catch.c:237)
==514996==    by 0x400CD1F: dl_open_worker (dl-open.c:803)
==514996==    by 0x400151B: _dl_catch_exception (dl-catch.c:237)
==514996==    by 0x400D163: _dl_open (dl-open.c:905)
==514996==    by 0x4A010D4: do_dlopen (dl-libc.c:95)
==514996==    by 0x400151B: _dl_catch_exception (dl-catch.c:237)
==514996==    by 0x4001668: _dl_catch_error (dl-catch.c:256)
==514996==    by 0x4A014EE: dlerror_run (dl-libc.c:45)
==514996==    by 0x4A014EE: __libc_dlopen_mode (dl-libc.c:162)
==514996==    by 0x49D0A0E: module_load (nss_module.c:187)
==514996== 
==514996== 3,590 bytes in 30 blocks are definitely lost in loss record 63 of 66
==514996==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x493134E: strdup (strdup.c:42)
==514996==    by 0x485BF53: products_get (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x10948C: main (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/test/test_program)
==514996== 
==514996== LEAK SUMMARY:
==514996==    definitely lost: 3,896 bytes in 61 blocks
==514996==    indirectly lost: 31 bytes in 1 blocks
==514996==      possibly lost: 2,640 bytes in 2 blocks
==514996==    still reachable: 106,652 bytes in 745 blocks
==514996==         suppressed: 0 bytes in 0 blocks
==514996== Reachable blocks (those to which a pointer was found) are not shown.
==514996== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==514996== 
==514996== Use --track-origins=yes to see where uninitialised values come from
==514996== ERROR SUMMARY: 10 errors from 10 contexts (suppressed: 0 from 0)
==514996== 
==514996== 1 errors in context 1 of 10:
==514996== Invalid free() / delete / delete[] / realloc()
==514996==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x4AF2D99: curl_slist_free_all (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x485BB2E: http_post_json (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x485C2AA: cart_put (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x1096E6: main (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/test/test_program)
==514996==  Address 0x734d39c is 44 bytes inside a block of size 152 free'd
==514996==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x597B1CF: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x4D9505D: gnutls_x509_crt_deinit (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA0D47: gnutls_x509_trust_list_deinit (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D11B86: gnutls_certificate_free_credentials (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4B114F1: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4B10CEF: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AB55A6: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AA8E20: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4B0959C: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AAE3F5: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AE5E62: curl_multi_cleanup (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==  Block was alloc'd at
==514996==    at 0x484D953: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x597B3AA: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x597B508: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x5984FE4: asn1_der_decoding2 (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x4D95332: gnutls_x509_crt_import (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D95D01: gnutls_x509_crt_list_import (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D96072: gnutls_x509_crt_list_import2 (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA4904: gnutls_x509_trust_list_add_trust_mem (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA4CEC: gnutls_x509_trust_list_add_trust_file (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA5145: ??? (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA51A4: gnutls_x509_trust_list_add_trust_dir (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D231ED: gnutls_certificate_set_x509_trust_dir (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996== 
==514996== 
==514996== 1 errors in context 2 of 10:
==514996== Invalid write of size 8
==514996==    at 0x4AF2D89: curl_slist_free_all (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x485BB2E: http_post_json (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x485C2AA: cart_put (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x1096E6: main (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/test/test_program)
==514996==  Address 0x734d39c is 44 bytes inside a block of size 152 free'd
==514996==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x597B1CF: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x4D9505D: gnutls_x509_crt_deinit (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA0D47: gnutls_x509_trust_list_deinit (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D11B86: gnutls_certificate_free_credentials (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4B114F1: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4B10CEF: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AB55A6: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AA8E20: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4B0959C: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AAE3F5: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AE5E62: curl_multi_cleanup (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==  Block was alloc'd at
==514996==    at 0x484D953: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x597B3AA: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x597B508: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x5984FE4: asn1_der_decoding2 (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x4D95332: gnutls_x509_crt_import (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D95D01: gnutls_x509_crt_list_import (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D96072: gnutls_x509_crt_list_import2 (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA4904: gnutls_x509_trust_list_add_trust_mem (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA4CEC: gnutls_x509_trust_list_add_trust_file (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA5145: ??? (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA51A4: gnutls_x509_trust_list_add_trust_dir (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D231ED: gnutls_certificate_set_x509_trust_dir (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996== 
==514996== 
==514996== 1 errors in context 3 of 10:
==514996== Invalid read of size 8
==514996==    at 0x4AF2D7F: curl_slist_free_all (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x485BB2E: http_post_json (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x485C2AA: cart_put (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x1096E6: main (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/test/test_program)
==514996==  Address 0x734d39c is 44 bytes inside a block of size 152 free'd
==514996==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x597B1CF: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x4D9505D: gnutls_x509_crt_deinit (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA0D47: gnutls_x509_trust_list_deinit (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D11B86: gnutls_certificate_free_credentials (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4B114F1: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4B10CEF: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AB55A6: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AA8E20: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4B0959C: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AAE3F5: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AE5E62: curl_multi_cleanup (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==  Block was alloc'd at
==514996==    at 0x484D953: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x597B3AA: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x597B508: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x5984FE4: asn1_der_decoding2 (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x4D95332: gnutls_x509_crt_import (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D95D01: gnutls_x509_crt_list_import (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D96072: gnutls_x509_crt_list_import2 (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA4904: gnutls_x509_trust_list_add_trust_mem (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA4CEC: gnutls_x509_trust_list_add_trust_file (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA5145: ??? (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA51A4: gnutls_x509_trust_list_add_trust_dir (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D231ED: gnutls_certificate_set_x509_trust_dir (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996== 
==514996== 
==514996== 1 errors in context 4 of 10:
==514996== Invalid read of size 8
==514996==    at 0x4AF2D7B: curl_slist_free_all (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x485BB2E: http_post_json (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x485C2AA: cart_put (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x1096E6: main (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/test/test_program)
==514996==  Address 0x734d3a4 is 52 bytes inside a block of size 152 free'd
==514996==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x597B1CF: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x4D9505D: gnutls_x509_crt_deinit (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA0D47: gnutls_x509_trust_list_deinit (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D11B86: gnutls_certificate_free_credentials (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4B114F1: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4B10CEF: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AB55A6: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AA8E20: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4B0959C: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AAE3F5: ??? (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==    by 0x4AE5E62: curl_multi_cleanup (in /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0)
==514996==  Block was alloc'd at
==514996==    at 0x484D953: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x597B3AA: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x597B508: ??? (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x5984FE4: asn1_der_decoding2 (in /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3)
==514996==    by 0x4D95332: gnutls_x509_crt_import (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D95D01: gnutls_x509_crt_list_import (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D96072: gnutls_x509_crt_list_import2 (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA4904: gnutls_x509_trust_list_add_trust_mem (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA4CEC: gnutls_x509_trust_list_add_trust_file (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA5145: ??? (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4DA51A4: gnutls_x509_trust_list_add_trust_dir (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996==    by 0x4D231ED: gnutls_certificate_set_x509_trust_dir (in /usr/lib/x86_64-linux-gnu/libgnutls.so.30.37.1)
==514996== 
==514996== 
==514996== 1 errors in context 5 of 10:
==514996== Conditional jump or move depends on uninitialised value(s)
==514996==    at 0x484F229: strlen (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==514996==    by 0x48E7D97: __printf_buffer (vfprintf-process-arg.c:435)
==514996==    by 0x48E8591: __vfprintf_internal (vfprintf-internal.c:1559)
==514996==    by 0x48DD1A2: printf (printf.c:33)
==514996==    by 0x485BB11: http_post_json (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x485C2AA: cart_put (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/lib/libpsc.so)
==514996==    by 0x1096E6: main (in /home/oicnanev/Projects/PSC-ISEL2425/assignments/3/tp2_entrega/exercicio5/test/test_program)
==514996== 
==514996== ERROR SUMMARY: 10 errors from 10 contexts (suppressed: 0 from 0)
Aborted (core dumped)
```