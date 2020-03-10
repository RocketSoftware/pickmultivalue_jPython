#define makeVarToObjFuncs(type) \
/* Get object from a VAR (BASIC) */ \
type * getPtrFor ## type(VAR* v_ptr, DPSTRUCT * dp) \
{ \
    type * ptr; \
    if (LEN_IB(v_ptr) != sizeof(ptr)) \
    { \
        STORE_VBS(v_ptr, (STRING*)"Invalid pointer"); \
        return 0; \
    } \
 \
    ptr = *((type**)VAR_STRING_ADDR(v_ptr)); \
 \
    return ptr; \
} \
/* Convert object to a VAR (BASIC) */ \
void storePtrFrom ## type(type * ptr, VAR * v_ptr, DPSTRUCT * dp) \
{ \
    VAR_MAKE_STRING_VBIS(v_ptr, sizeof(ptr), (STRING*)&ptr); \
}
