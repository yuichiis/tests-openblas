#include <Windows.h>
#if _MSC_VER
#include <complex.h>
#define lapack_complex_float _Fcomplex
#define lapack_complex_double _Dcomplex
#endif
#include <lapacke.h>
#include "vclib.h"
static char msg_function_not_found[]  = "LAPACKE_dorhr_col not found\n";
typedef lapack_int (CALLBACK* PFNLAPACKE_dorhr_col)( /* LAPACKE_dorhr_col */
    int            /* matrix_layout */,
    lapack_int            /* m */,
    lapack_int            /* n */,
    lapack_int            /* nb */,
    double *            /* a */,
    lapack_int            /* lda */,
    double *            /* t */,
    lapack_int            /* ldt */,
    double *            /* d */
);
static PFNLAPACKE_dorhr_col _g_LAPACKE_dorhr_col = NULL;
lapack_int LAPACKE_dorhr_col(
    int            matrix_layout,
    lapack_int            m,
    lapack_int            n,
    lapack_int            nb,
    double *            a,
    lapack_int            lda,
    double *            t,
    lapack_int            ldt,
    double *            d
)
{
    if(_g_LAPACKE_dorhr_col==NULL) {
        _g_LAPACKE_dorhr_col = rindow_load_libopenblas_func("LAPACKE_dorhr_col"); 
        if(_g_LAPACKE_dorhr_col==NULL) {
            HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            WriteConsole(hStdOut, msg_function_not_found, sizeof(msg_function_not_found), NULL, NULL);
            return 0;
        }
    }
    return _g_LAPACKE_dorhr_col(
        matrix_layout,
        m,
        n,
        nb,
        a,
        lda,
        t,
        ldt,
        d    
    );
}