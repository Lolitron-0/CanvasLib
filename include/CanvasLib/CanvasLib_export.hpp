
#ifndef CANVASLIB_EXPORT_H
#define CANVASLIB_EXPORT_H

#ifdef CANVASLIB_STATIC_DEFINE
#  define CANVASLIB_EXPORT
#  define CANVASLIB_NO_EXPORT
#else
#  ifndef CANVASLIB_EXPORT
#    ifdef CanvasLib_CanvasLib_EXPORTS
        /* We are building this library */
#      define CANVASLIB_EXPORT 
#    else
        /* We are using this library */
#      define CANVASLIB_EXPORT 
#    endif
#  endif

#  ifndef CANVASLIB_NO_EXPORT
#    define CANVASLIB_NO_EXPORT 
#  endif
#endif

#ifndef CANVASLIB_DEPRECATED
#  define CANVASLIB_DEPRECATED __declspec(deprecated)
#endif

#ifndef CANVASLIB_DEPRECATED_EXPORT
#  define CANVASLIB_DEPRECATED_EXPORT CANVASLIB_EXPORT CANVASLIB_DEPRECATED
#endif

#ifndef CANVASLIB_DEPRECATED_NO_EXPORT
#  define CANVASLIB_DEPRECATED_NO_EXPORT CANVASLIB_NO_EXPORT CANVASLIB_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef CANVASLIB_NO_DEPRECATED
#    define CANVASLIB_NO_DEPRECATED
#  endif
#endif

/* This needs to suppress only for MSVC */
#if defined(_MSC_VER) && !defined(__ICL)
#  define CANVASLIB_SUPPRESS_C4251 _Pragma("warning(suppress:4251)")
#else
#  define CANVASLIB_SUPPRESS_C4251
#endif

#endif /* CANVASLIB_EXPORT_H */
