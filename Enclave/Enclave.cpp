

// #include <stdarg.h>
// #include <stdio.h>      /* vsnprintf */

#include "Enclave.h"
#include "Enclave_t.h" /* print_string */

// -------- SEALING & UNSEALING Functions
sgx_status_t seal_fbytes(const FByteArray *fbytes, sgx_sealed_data_t *sealed_data, size_t sealed_size)
{
    return sgx_seal_data(0, NULL, sizeof(FByteArray), (uint8_t *)fbytes, sealed_size, sealed_data);
}

sgx_status_t unseal_fbytes(const sgx_sealed_data_t *sealed_data, FByteArray *plaintext, uint32_t plaintext_size)
{
    return sgx_unseal_data(sealed_data, NULL, NULL, (uint8_t *)plaintext, &plaintext_size);
}

// -------------------------------------------

/*
 * printf:
 *   Invokes OCALL to display the enclave buffer to the terminal.
 */
void printf(const char *fmt, ...)
{
    char buf[BUFSIZ] = {'\0'};
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ, fmt, ap);
    va_end(ap);
    ocall_print_string(buf);
}

int addition(int a, int b)
{

    sgx_status_t ocall_status, sealing_status;
    int ocall_ret;

    // --------------------------------- SEALING & UNSEALING START
    // seal fbytes
    FByteArray *fbytes = (FByteArray *)malloc(sizeof(FByteArray));
    // hello world in fbytes->data where data is char[10000]
    strncpy(fbytes->data, "hello world", strlen("hello world") + 1);
    // store json string to fbytes->data and length is str length
    fbytes->len = strlen(fbytes->data);
    size_t sealed_fbytes_size = sizeof(sgx_sealed_data_t) + sizeof(FByteArray);
    uint8_t *sealed_fbytes_data = (uint8_t *)malloc(sealed_fbytes_size);
    sealing_status = seal_fbytes(fbytes, (sgx_sealed_data_t *)sealed_fbytes_data, sealed_fbytes_size);
    free(fbytes);
    if (sealing_status != SGX_SUCCESS)
    {
        free(sealed_fbytes_data);
        return 20;
    }
    // save fbytes
    // save fbytes
    ocall_status = ocall_save_fbytes(&ocall_ret, sealed_fbytes_data, sealed_fbytes_size);
    free(sealed_fbytes_data);
    if (ocall_ret != 0 || ocall_status != SGX_SUCCESS)
    {
        return 21;
    }

    // load fbytes
    FByteArray *loaded_fbytes = (FByteArray *)malloc(sizeof(FByteArray));
    size_t loaded_fbytes_size = sizeof(sgx_sealed_data_t) + sizeof(FByteArray);
    uint8_t *loaded_fbytes_data = (uint8_t *)malloc(loaded_fbytes_size);
    ocall_status = ocall_load_fbytes(&ocall_ret, loaded_fbytes_data, loaded_fbytes_size);

    if (ocall_ret != 0 || ocall_status != SGX_SUCCESS)
    {
        return 23;
    }

    sealing_status = unseal_fbytes((sgx_sealed_data_t *)loaded_fbytes_data, loaded_fbytes, loaded_fbytes_size);
    free(loaded_fbytes_data);
    if (sealing_status != SGX_SUCCESS)
    {
        free(loaded_fbytes);
        return 24;
    }

    // print loaded fbytes->data
    printf("Enclave.cpp : addition() loaded_fbytes->data -> %s\n", loaded_fbytes->data);

    // --------------------------------- SEALING & UNSEALING END

    // return sum
    return a + b;
}
