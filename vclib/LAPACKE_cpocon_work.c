#include <Windows.h>
#if _MSC_VER
#include <complex.h>
#define lapack_complex_float _Fcomplex
#define lapack_complex_double _Dcomplex
#endif
#include <lapacke.h>
#include "vclib.h"
static char msg_function_not_found[]  = "LAPACKE_cpocon_work not found\n";
typedef lapack_int (CALLBACK* PFNLAPACKE_cpocon_work)( /* LAPACKE_cpocon_work */
    int            /* matrix_layout */,
    char            /* uplo */,
    lapack_int            /* n */,
    const lapack_complex_float *            /* a */,
    lapack_int            /* lda */,
    float            /* anorm */,
    float *            /* rcond */,
    lapack_complex_float *            /* work */,
    float *            /* rwork */
);
static PFNLAPACKE_cpocon_work _g_LAPACKE_cpocon_work = NULL;
lapack_int LAPACKE_cpocon_work(
    int            matrix_layout,
    char            uplo,
    lapack_int            n,
    const lapack_complex_float *            a,
    lapack_int            lda,
    float            anorm,
    float *            rcond,
    lapack_complex_float *            work,
    float *            rwork
)
{
    if(_g_LAPACKE_cpocon_work==NULL) {
        _g_LAPACKE_cpocon_work = rindow_load_libopenblas_func("LAPACKE_cpocon_work"); 
        if(_g_LAPACKE_cpocon_work==NULL) {
            HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            WriteConsole(hStdOut, msg_function_not_found, sizeof(msg_function_not_found), NULL, NULL);
            return 0;
        }
    }
    return _g_LAPACKE_cpocon_work(
        matrix_layout,
        uplo,
        n,
        a,
        lda,
        anorm,
        rcond,
        work,
        rwork    
    );
}