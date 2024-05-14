#include <Windows.h>
#if _MSC_VER
#include <complex.h>
#define lapack_complex_float _Fcomplex
#define lapack_complex_double _Dcomplex
#endif
#include <lapacke.h>
#include "vclib.h"
static char msg_function_not_found[]  = "LAPACKE_ztrcon_work not found\n";
typedef lapack_int (CALLBACK* PFNLAPACKE_ztrcon_work)( /* LAPACKE_ztrcon_work */
    int            /* matrix_layout */,
    char            /* norm */,
    char            /* uplo */,
    char            /* diag */,
    lapack_int            /* n */,
    const lapack_complex_double *            /* a */,
    lapack_int            /* lda */,
    double *            /* rcond */,
    lapack_complex_double *            /* work */,
    double *            /* rwork */
);
static PFNLAPACKE_ztrcon_work _g_LAPACKE_ztrcon_work = NULL;
lapack_int LAPACKE_ztrcon_work(
    int            matrix_layout,
    char            norm,
    char            uplo,
    char            diag,
    lapack_int            n,
    const lapack_complex_double *            a,
    lapack_int            lda,
    double *            rcond,
    lapack_complex_double *            work,
    double *            rwork
)
{
    if(_g_LAPACKE_ztrcon_work==NULL) {
        _g_LAPACKE_ztrcon_work = rindow_load_libopenblas_func("LAPACKE_ztrcon_work"); 
        if(_g_LAPACKE_ztrcon_work==NULL) {
            HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            WriteConsole(hStdOut, msg_function_not_found, sizeof(msg_function_not_found), NULL, NULL);
            return 0;
        }
    }
    return _g_LAPACKE_ztrcon_work(
        matrix_layout,
        norm,
        uplo,
        diag,
        n,
        a,
        lda,
        rcond,
        work,
        rwork    
    );
}