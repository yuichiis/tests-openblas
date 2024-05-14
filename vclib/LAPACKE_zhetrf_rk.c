#include <Windows.h>
#if _MSC_VER
#include <complex.h>
#define lapack_complex_float _Fcomplex
#define lapack_complex_double _Dcomplex
#endif
#include <lapacke.h>
#include "vclib.h"
static char msg_function_not_found[]  = "LAPACKE_zhetrf_rk not found\n";
typedef lapack_int (CALLBACK* PFNLAPACKE_zhetrf_rk)( /* LAPACKE_zhetrf_rk */
    int            /* matrix_layout */,
    char            /* uplo */,
    lapack_int            /* n */,
    lapack_complex_double *            /* a */,
    lapack_int            /* lda */,
    lapack_complex_double *            /* e */,
    lapack_int *            /* ipiv */
);
static PFNLAPACKE_zhetrf_rk _g_LAPACKE_zhetrf_rk = NULL;
lapack_int LAPACKE_zhetrf_rk(
    int            matrix_layout,
    char            uplo,
    lapack_int            n,
    lapack_complex_double *            a,
    lapack_int            lda,
    lapack_complex_double *            e,
    lapack_int *            ipiv
)
{
    if(_g_LAPACKE_zhetrf_rk==NULL) {
        _g_LAPACKE_zhetrf_rk = rindow_load_libopenblas_func("LAPACKE_zhetrf_rk"); 
        if(_g_LAPACKE_zhetrf_rk==NULL) {
            HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            WriteConsole(hStdOut, msg_function_not_found, sizeof(msg_function_not_found), NULL, NULL);
            return 0;
        }
    }
    return _g_LAPACKE_zhetrf_rk(
        matrix_layout,
        uplo,
        n,
        a,
        lda,
        e,
        ipiv    
    );
}