#include <Windows.h>
#if _MSC_VER
#include <complex.h>
#define lapack_complex_float _Fcomplex
#define lapack_complex_double _Dcomplex
#endif
#include <lapacke.h>
#include "vclib.h"
static char msg_function_not_found[]  = "LAPACKE_zgecon not found\n";
typedef lapack_int (CALLBACK* PFNLAPACKE_zgecon)( /* LAPACKE_zgecon */
    int            /* matrix_layout */,
    char            /* norm */,
    lapack_int            /* n */,
    const lapack_complex_double *            /* a */,
    lapack_int            /* lda */,
    double            /* anorm */,
    double *            /* rcond */
);
static PFNLAPACKE_zgecon _g_LAPACKE_zgecon = NULL;
lapack_int LAPACKE_zgecon(
    int            matrix_layout,
    char            norm,
    lapack_int            n,
    const lapack_complex_double *            a,
    lapack_int            lda,
    double            anorm,
    double *            rcond
)
{
    if(_g_LAPACKE_zgecon==NULL) {
        _g_LAPACKE_zgecon = rindow_load_libopenblas_func("LAPACKE_zgecon"); 
        if(_g_LAPACKE_zgecon==NULL) {
            HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            WriteConsole(hStdOut, msg_function_not_found, sizeof(msg_function_not_found), NULL, NULL);
            return 0;
        }
    }
    return _g_LAPACKE_zgecon(
        matrix_layout,
        norm,
        n,
        a,
        lda,
        anorm,
        rcond    
    );
}