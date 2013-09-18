# 1 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
struct __C1; struct __C2; struct __C3; struct __type_info; struct __class_type_info; struct __si_class_type_info; struct __C5; struct __C6; union __C7; struct __C8;
# 1292 "/usr/local/cuda-5.0/include/driver_types.h"
struct CUstream_st;




struct CUevent_st;
# 206 "/usr/include/libio.h" 3
enum __codecvt_result {

__codecvt_ok,
__codecvt_partial,
__codecvt_error,
__codecvt_noconv};
# 271 "/usr/include/libio.h" 3
struct _IO_FILE;
# 199 "/usr/include/math.h" 3
enum _ZUt_ {
FP_NAN,

FP_INFINITE,

FP_ZERO,

FP_SUBNORMAL,

FP_NORMAL};
# 292 "/usr/include/math.h" 3
enum _LIB_VERSION_TYPE {
_IEEE_ = (-1),
_SVID_,
_XOPEN_,
_POSIX_,
_ISOC_};
# 28 "/usr/include/bits/locale.h" 3
enum _ZUt0_ {
__LC_CTYPE,
__LC_NUMERIC,
__LC_TIME,
__LC_COLLATE,
__LC_MONETARY,
__LC_MESSAGES,
__LC_ALL,
__LC_PAPER,
__LC_NAME,
__LC_ADDRESS,
__LC_TELEPHONE,
__LC_MEASUREMENT,
__LC_IDENTIFICATION};
# 49 "/usr/include/ctype.h" 3
enum _ZUt1_ {
_ISupper = 256,
_ISlower = 512,
_ISalpha = 1024,
_ISdigit = 2048,
_ISxdigit = 4096,
_ISspace = 8192,
_ISprint = 16384,
_ISgraph = 32768,
_ISblank = 1,
_IScntrl,
_ISpunct = 4,
_ISalnum = 8};
# 35 "/usr/include/pthread.h" 3
enum _ZUt2_ {
PTHREAD_CREATE_JOINABLE,

PTHREAD_CREATE_DETACHED};
# 45 "/usr/include/pthread.h" 3
enum _ZUt3_ {
PTHREAD_MUTEX_TIMED_NP,
PTHREAD_MUTEX_RECURSIVE_NP,
PTHREAD_MUTEX_ERRORCHECK_NP,
PTHREAD_MUTEX_ADAPTIVE_NP,


PTHREAD_MUTEX_NORMAL = 0,
PTHREAD_MUTEX_RECURSIVE,
PTHREAD_MUTEX_ERRORCHECK,
PTHREAD_MUTEX_DEFAULT = 0,



PTHREAD_MUTEX_FAST_NP = 0};
# 67 "/usr/include/pthread.h" 3
enum _ZUt4_ {
PTHREAD_MUTEX_STALLED,
PTHREAD_MUTEX_STALLED_NP = 0,
PTHREAD_MUTEX_ROBUST,
PTHREAD_MUTEX_ROBUST_NP = 1};
# 79 "/usr/include/pthread.h" 3
enum _ZUt5_ {
PTHREAD_PRIO_NONE,
PTHREAD_PRIO_INHERIT,
PTHREAD_PRIO_PROTECT};
# 116 "/usr/include/pthread.h" 3
enum _ZUt6_ {
PTHREAD_RWLOCK_PREFER_READER_NP,
PTHREAD_RWLOCK_PREFER_WRITER_NP,
PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP,
PTHREAD_RWLOCK_DEFAULT_NP = 0};
# 148 "/usr/include/pthread.h" 3
enum _ZUt7_ {
PTHREAD_INHERIT_SCHED,

PTHREAD_EXPLICIT_SCHED};
# 158 "/usr/include/pthread.h" 3
enum _ZUt8_ {
PTHREAD_SCOPE_SYSTEM,

PTHREAD_SCOPE_PROCESS};
# 168 "/usr/include/pthread.h" 3
enum _ZUt9_ {
PTHREAD_PROCESS_PRIVATE,

PTHREAD_PROCESS_SHARED};
# 192 "/usr/include/pthread.h" 3
enum _ZUt10_ {
PTHREAD_CANCEL_ENABLE,

PTHREAD_CANCEL_DISABLE};



enum _ZUt11_ {
PTHREAD_CANCEL_DEFERRED,

PTHREAD_CANCEL_ASYNCHRONOUS};
# 27 "/usr/include/bits/confname.h" 3
enum _ZUt12_ {
_PC_LINK_MAX,

_PC_MAX_CANON,

_PC_MAX_INPUT,

_PC_NAME_MAX,

_PC_PATH_MAX,

_PC_PIPE_BUF,

_PC_CHOWN_RESTRICTED,

_PC_NO_TRUNC,

_PC_VDISABLE,

_PC_SYNC_IO,

_PC_ASYNC_IO,

_PC_PRIO_IO,

_PC_SOCK_MAXBUF,

_PC_FILESIZEBITS,

_PC_REC_INCR_XFER_SIZE,

_PC_REC_MAX_XFER_SIZE,

_PC_REC_MIN_XFER_SIZE,

_PC_REC_XFER_ALIGN,

_PC_ALLOC_SIZE_MIN,

_PC_SYMLINK_MAX,

_PC_2_SYMLINKS};
# 74 "/usr/include/bits/confname.h" 3
enum _ZUt13_ {
_SC_ARG_MAX,

_SC_CHILD_MAX,

_SC_CLK_TCK,

_SC_NGROUPS_MAX,

_SC_OPEN_MAX,

_SC_STREAM_MAX,

_SC_TZNAME_MAX,

_SC_JOB_CONTROL,

_SC_SAVED_IDS,

_SC_REALTIME_SIGNALS,

_SC_PRIORITY_SCHEDULING,

_SC_TIMERS,

_SC_ASYNCHRONOUS_IO,

_SC_PRIORITIZED_IO,

_SC_SYNCHRONIZED_IO,

_SC_FSYNC,

_SC_MAPPED_FILES,

_SC_MEMLOCK,

_SC_MEMLOCK_RANGE,

_SC_MEMORY_PROTECTION,

_SC_MESSAGE_PASSING,

_SC_SEMAPHORES,

_SC_SHARED_MEMORY_OBJECTS,

_SC_AIO_LISTIO_MAX,

_SC_AIO_MAX,

_SC_AIO_PRIO_DELTA_MAX,

_SC_DELAYTIMER_MAX,

_SC_MQ_OPEN_MAX,

_SC_MQ_PRIO_MAX,

_SC_VERSION,

_SC_PAGESIZE,


_SC_RTSIG_MAX,

_SC_SEM_NSEMS_MAX,

_SC_SEM_VALUE_MAX,

_SC_SIGQUEUE_MAX,

_SC_TIMER_MAX,




_SC_BC_BASE_MAX,

_SC_BC_DIM_MAX,

_SC_BC_SCALE_MAX,

_SC_BC_STRING_MAX,

_SC_COLL_WEIGHTS_MAX,

_SC_EQUIV_CLASS_MAX,

_SC_EXPR_NEST_MAX,

_SC_LINE_MAX,

_SC_RE_DUP_MAX,

_SC_CHARCLASS_NAME_MAX,


_SC_2_VERSION,

_SC_2_C_BIND,

_SC_2_C_DEV,

_SC_2_FORT_DEV,

_SC_2_FORT_RUN,

_SC_2_SW_DEV,

_SC_2_LOCALEDEF,


_SC_PII,

_SC_PII_XTI,

_SC_PII_SOCKET,

_SC_PII_INTERNET,

_SC_PII_OSI,

_SC_POLL,

_SC_SELECT,

_SC_UIO_MAXIOV,

_SC_IOV_MAX = 60,

_SC_PII_INTERNET_STREAM,

_SC_PII_INTERNET_DGRAM,

_SC_PII_OSI_COTS,

_SC_PII_OSI_CLTS,

_SC_PII_OSI_M,

_SC_T_IOV_MAX,



_SC_THREADS,

_SC_THREAD_SAFE_FUNCTIONS,

_SC_GETGR_R_SIZE_MAX,

_SC_GETPW_R_SIZE_MAX,

_SC_LOGIN_NAME_MAX,

_SC_TTY_NAME_MAX,

_SC_THREAD_DESTRUCTOR_ITERATIONS,

_SC_THREAD_KEYS_MAX,

_SC_THREAD_STACK_MIN,

_SC_THREAD_THREADS_MAX,

_SC_THREAD_ATTR_STACKADDR,

_SC_THREAD_ATTR_STACKSIZE,

_SC_THREAD_PRIORITY_SCHEDULING,

_SC_THREAD_PRIO_INHERIT,

_SC_THREAD_PRIO_PROTECT,

_SC_THREAD_PROCESS_SHARED,


_SC_NPROCESSORS_CONF,

_SC_NPROCESSORS_ONLN,

_SC_PHYS_PAGES,

_SC_AVPHYS_PAGES,

_SC_ATEXIT_MAX,

_SC_PASS_MAX,


_SC_XOPEN_VERSION,

_SC_XOPEN_XCU_VERSION,

_SC_XOPEN_UNIX,

_SC_XOPEN_CRYPT,

_SC_XOPEN_ENH_I18N,

_SC_XOPEN_SHM,


_SC_2_CHAR_TERM,

_SC_2_C_VERSION,

_SC_2_UPE,


_SC_XOPEN_XPG2,

_SC_XOPEN_XPG3,

_SC_XOPEN_XPG4,


_SC_CHAR_BIT,

_SC_CHAR_MAX,

_SC_CHAR_MIN,

_SC_INT_MAX,

_SC_INT_MIN,

_SC_LONG_BIT,

_SC_WORD_BIT,

_SC_MB_LEN_MAX,

_SC_NZERO,

_SC_SSIZE_MAX,

_SC_SCHAR_MAX,

_SC_SCHAR_MIN,

_SC_SHRT_MAX,

_SC_SHRT_MIN,

_SC_UCHAR_MAX,

_SC_UINT_MAX,

_SC_ULONG_MAX,

_SC_USHRT_MAX,


_SC_NL_ARGMAX,

_SC_NL_LANGMAX,

_SC_NL_MSGMAX,

_SC_NL_NMAX,

_SC_NL_SETMAX,

_SC_NL_TEXTMAX,


_SC_XBS5_ILP32_OFF32,

_SC_XBS5_ILP32_OFFBIG,

_SC_XBS5_LP64_OFF64,

_SC_XBS5_LPBIG_OFFBIG,


_SC_XOPEN_LEGACY,

_SC_XOPEN_REALTIME,

_SC_XOPEN_REALTIME_THREADS,


_SC_ADVISORY_INFO,

_SC_BARRIERS,

_SC_BASE,

_SC_C_LANG_SUPPORT,

_SC_C_LANG_SUPPORT_R,

_SC_CLOCK_SELECTION,

_SC_CPUTIME,

_SC_THREAD_CPUTIME,

_SC_DEVICE_IO,

_SC_DEVICE_SPECIFIC,

_SC_DEVICE_SPECIFIC_R,

_SC_FD_MGMT,

_SC_FIFO,

_SC_PIPE,

_SC_FILE_ATTRIBUTES,

_SC_FILE_LOCKING,

_SC_FILE_SYSTEM,

_SC_MONOTONIC_CLOCK,

_SC_MULTI_PROCESS,

_SC_SINGLE_PROCESS,

_SC_NETWORKING,

_SC_READER_WRITER_LOCKS,

_SC_SPIN_LOCKS,

_SC_REGEXP,

_SC_REGEX_VERSION,

_SC_SHELL,

_SC_SIGNALS,

_SC_SPAWN,

_SC_SPORADIC_SERVER,

_SC_THREAD_SPORADIC_SERVER,

_SC_SYSTEM_DATABASE,

_SC_SYSTEM_DATABASE_R,

_SC_TIMEOUTS,

_SC_TYPED_MEMORY_OBJECTS,

_SC_USER_GROUPS,

_SC_USER_GROUPS_R,

_SC_2_PBS,

_SC_2_PBS_ACCOUNTING,

_SC_2_PBS_LOCATE,

_SC_2_PBS_MESSAGE,

_SC_2_PBS_TRACK,

_SC_SYMLOOP_MAX,

_SC_STREAMS,

_SC_2_PBS_CHECKPOINT,


_SC_V6_ILP32_OFF32,

_SC_V6_ILP32_OFFBIG,

_SC_V6_LP64_OFF64,

_SC_V6_LPBIG_OFFBIG,


_SC_HOST_NAME_MAX,

_SC_TRACE,

_SC_TRACE_EVENT_FILTER,

_SC_TRACE_INHERIT,

_SC_TRACE_LOG,


_SC_LEVEL1_ICACHE_SIZE,

_SC_LEVEL1_ICACHE_ASSOC,

_SC_LEVEL1_ICACHE_LINESIZE,

_SC_LEVEL1_DCACHE_SIZE,

_SC_LEVEL1_DCACHE_ASSOC,

_SC_LEVEL1_DCACHE_LINESIZE,

_SC_LEVEL2_CACHE_SIZE,

_SC_LEVEL2_CACHE_ASSOC,

_SC_LEVEL2_CACHE_LINESIZE,

_SC_LEVEL3_CACHE_SIZE,

_SC_LEVEL3_CACHE_ASSOC,

_SC_LEVEL3_CACHE_LINESIZE,

_SC_LEVEL4_CACHE_SIZE,

_SC_LEVEL4_CACHE_ASSOC,

_SC_LEVEL4_CACHE_LINESIZE,



_SC_IPV6 = 235,

_SC_RAW_SOCKETS,


_SC_V7_ILP32_OFF32,

_SC_V7_ILP32_OFFBIG,

_SC_V7_LP64_OFF64,

_SC_V7_LPBIG_OFFBIG,


_SC_SS_REPL_MAX,


_SC_TRACE_EVENT_NAME_MAX,

_SC_TRACE_NAME_MAX,

_SC_TRACE_SYS_MAX,

_SC_TRACE_USER_EVENT_MAX,


_SC_XOPEN_STREAMS,


_SC_THREAD_ROBUST_PRIO_INHERIT,

_SC_THREAD_ROBUST_PRIO_PROTECT};
# 536 "/usr/include/bits/confname.h" 3
enum _ZUt14_ {
_CS_PATH,


_CS_V6_WIDTH_RESTRICTED_ENVS,



_CS_GNU_LIBC_VERSION,

_CS_GNU_LIBPTHREAD_VERSION,


_CS_V5_WIDTH_RESTRICTED_ENVS,



_CS_V7_WIDTH_RESTRICTED_ENVS,



_CS_LFS_CFLAGS = 1000,

_CS_LFS_LDFLAGS,

_CS_LFS_LIBS,

_CS_LFS_LINTFLAGS,

_CS_LFS64_CFLAGS,

_CS_LFS64_LDFLAGS,

_CS_LFS64_LIBS,

_CS_LFS64_LINTFLAGS,


_CS_XBS5_ILP32_OFF32_CFLAGS = 1100,

_CS_XBS5_ILP32_OFF32_LDFLAGS,

_CS_XBS5_ILP32_OFF32_LIBS,

_CS_XBS5_ILP32_OFF32_LINTFLAGS,

_CS_XBS5_ILP32_OFFBIG_CFLAGS,

_CS_XBS5_ILP32_OFFBIG_LDFLAGS,

_CS_XBS5_ILP32_OFFBIG_LIBS,

_CS_XBS5_ILP32_OFFBIG_LINTFLAGS,

_CS_XBS5_LP64_OFF64_CFLAGS,

_CS_XBS5_LP64_OFF64_LDFLAGS,

_CS_XBS5_LP64_OFF64_LIBS,

_CS_XBS5_LP64_OFF64_LINTFLAGS,

_CS_XBS5_LPBIG_OFFBIG_CFLAGS,

_CS_XBS5_LPBIG_OFFBIG_LDFLAGS,

_CS_XBS5_LPBIG_OFFBIG_LIBS,

_CS_XBS5_LPBIG_OFFBIG_LINTFLAGS,


_CS_POSIX_V6_ILP32_OFF32_CFLAGS,

_CS_POSIX_V6_ILP32_OFF32_LDFLAGS,

_CS_POSIX_V6_ILP32_OFF32_LIBS,

_CS_POSIX_V6_ILP32_OFF32_LINTFLAGS,

_CS_POSIX_V6_ILP32_OFFBIG_CFLAGS,

_CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS,

_CS_POSIX_V6_ILP32_OFFBIG_LIBS,

_CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS,

_CS_POSIX_V6_LP64_OFF64_CFLAGS,

_CS_POSIX_V6_LP64_OFF64_LDFLAGS,

_CS_POSIX_V6_LP64_OFF64_LIBS,

_CS_POSIX_V6_LP64_OFF64_LINTFLAGS,

_CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS,

_CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS,

_CS_POSIX_V6_LPBIG_OFFBIG_LIBS,

_CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS,


_CS_POSIX_V7_ILP32_OFF32_CFLAGS,

_CS_POSIX_V7_ILP32_OFF32_LDFLAGS,

_CS_POSIX_V7_ILP32_OFF32_LIBS,

_CS_POSIX_V7_ILP32_OFF32_LINTFLAGS,

_CS_POSIX_V7_ILP32_OFFBIG_CFLAGS,

_CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS,

_CS_POSIX_V7_ILP32_OFFBIG_LIBS,

_CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS,

_CS_POSIX_V7_LP64_OFF64_CFLAGS,

_CS_POSIX_V7_LP64_OFF64_LDFLAGS,

_CS_POSIX_V7_LP64_OFF64_LIBS,

_CS_POSIX_V7_LP64_OFF64_LINTFLAGS,

_CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS,

_CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS,

_CS_POSIX_V7_LPBIG_OFFBIG_LIBS,

_CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS,


_CS_V6_ENV,

_CS_V7_ENV};
# 73 "/usr/include/wctype.h" 3
enum _ZUt15_ {
__ISwupper,
__ISwlower,
__ISwalpha,
__ISwdigit,
__ISwxdigit,
__ISwspace,
__ISwprint,
__ISwgraph,
__ISwblank,
__ISwcntrl,
__ISwpunct,
__ISwalnum,

_ISwupper = 16777216,
_ISwlower = 33554432,
_ISwalpha = 67108864,
_ISwdigit = 134217728,
_ISwxdigit = 268435456,
_ISwspace = 536870912,
_ISwprint = 1073741824,
_ISwgraph = (-2147483647-1),
_ISwblank = 65536,
_ISwcntrl = 131072,
_ISwpunct = 262144,
_ISwalnum = 524288};
# 198 "/usr/local/cuda-5.0/include/cuda.h"
enum CUipcMem_flags_enum {
CU_IPC_MEM_LAZY_ENABLE_PEER_ACCESS = 1};
# 207 "/usr/local/cuda-5.0/include/cuda.h"
enum CUctx_flags_enum {
CU_CTX_SCHED_AUTO,
CU_CTX_SCHED_SPIN,
CU_CTX_SCHED_YIELD,
CU_CTX_SCHED_BLOCKING_SYNC = 4,
CU_CTX_BLOCKING_SYNC = 4,


CU_CTX_SCHED_MASK = 7,
CU_CTX_MAP_HOST,
CU_CTX_LMEM_RESIZE_TO_MAX = 16,
CU_CTX_FLAGS_MASK = 31};
# 224 "/usr/local/cuda-5.0/include/cuda.h"
enum CUstream_flags_enum {
CU_STREAM_DEFAULT,
CU_STREAM_NON_BLOCKING};
# 232 "/usr/local/cuda-5.0/include/cuda.h"
enum CUevent_flags_enum {
CU_EVENT_DEFAULT,
CU_EVENT_BLOCKING_SYNC,
CU_EVENT_DISABLE_TIMING,
CU_EVENT_INTERPROCESS = 4};
# 242 "/usr/local/cuda-5.0/include/cuda.h"
enum CUarray_format_enum {
CU_AD_FORMAT_UNSIGNED_INT8 = 1,
CU_AD_FORMAT_UNSIGNED_INT16,
CU_AD_FORMAT_UNSIGNED_INT32,
CU_AD_FORMAT_SIGNED_INT8 = 8,
CU_AD_FORMAT_SIGNED_INT16,
CU_AD_FORMAT_SIGNED_INT32,
CU_AD_FORMAT_HALF = 16,
CU_AD_FORMAT_FLOAT = 32};
# 256 "/usr/local/cuda-5.0/include/cuda.h"
enum CUaddress_mode_enum {
CU_TR_ADDRESS_MODE_WRAP,
CU_TR_ADDRESS_MODE_CLAMP,
CU_TR_ADDRESS_MODE_MIRROR,
CU_TR_ADDRESS_MODE_BORDER};
# 266 "/usr/local/cuda-5.0/include/cuda.h"
enum CUfilter_mode_enum {
CU_TR_FILTER_MODE_POINT,
CU_TR_FILTER_MODE_LINEAR};
# 274 "/usr/local/cuda-5.0/include/cuda.h"
enum CUdevice_attribute_enum {
CU_DEVICE_ATTRIBUTE_MAX_THREADS_PER_BLOCK = 1,
CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_X,
CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_Y,
CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_Z,
CU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_X,
CU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_Y,
CU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_Z,
CU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_BLOCK,
CU_DEVICE_ATTRIBUTE_SHARED_MEMORY_PER_BLOCK = 8,
CU_DEVICE_ATTRIBUTE_TOTAL_CONSTANT_MEMORY,
CU_DEVICE_ATTRIBUTE_WARP_SIZE,
CU_DEVICE_ATTRIBUTE_MAX_PITCH,
CU_DEVICE_ATTRIBUTE_MAX_REGISTERS_PER_BLOCK,
CU_DEVICE_ATTRIBUTE_REGISTERS_PER_BLOCK = 12,
CU_DEVICE_ATTRIBUTE_CLOCK_RATE,
CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT,
CU_DEVICE_ATTRIBUTE_GPU_OVERLAP,
CU_DEVICE_ATTRIBUTE_MULTIPROCESSOR_COUNT,
CU_DEVICE_ATTRIBUTE_KERNEL_EXEC_TIMEOUT,
CU_DEVICE_ATTRIBUTE_INTEGRATED,
CU_DEVICE_ATTRIBUTE_CAN_MAP_HOST_MEMORY,
CU_DEVICE_ATTRIBUTE_COMPUTE_MODE,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_WIDTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_WIDTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_HEIGHT,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_WIDTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_HEIGHT,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_DEPTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_WIDTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_HEIGHT,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_LAYERS,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_ARRAY_WIDTH = 27,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_ARRAY_HEIGHT,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_ARRAY_NUMSLICES,
CU_DEVICE_ATTRIBUTE_SURFACE_ALIGNMENT,
CU_DEVICE_ATTRIBUTE_CONCURRENT_KERNELS,
CU_DEVICE_ATTRIBUTE_ECC_ENABLED,
CU_DEVICE_ATTRIBUTE_PCI_BUS_ID,
CU_DEVICE_ATTRIBUTE_PCI_DEVICE_ID,
CU_DEVICE_ATTRIBUTE_TCC_DRIVER,
CU_DEVICE_ATTRIBUTE_MEMORY_CLOCK_RATE,
CU_DEVICE_ATTRIBUTE_GLOBAL_MEMORY_BUS_WIDTH,
CU_DEVICE_ATTRIBUTE_L2_CACHE_SIZE,
CU_DEVICE_ATTRIBUTE_MAX_THREADS_PER_MULTIPROCESSOR,
CU_DEVICE_ATTRIBUTE_ASYNC_ENGINE_COUNT,
CU_DEVICE_ATTRIBUTE_UNIFIED_ADDRESSING,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_LAYERED_WIDTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_LAYERED_LAYERS,
CU_DEVICE_ATTRIBUTE_CAN_TEX2D_GATHER,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_GATHER_WIDTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_GATHER_HEIGHT,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_WIDTH_ALTERNATE,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_HEIGHT_ALTERNATE,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_DEPTH_ALTERNATE,
CU_DEVICE_ATTRIBUTE_PCI_DOMAIN_ID,
CU_DEVICE_ATTRIBUTE_TEXTURE_PITCH_ALIGNMENT,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURECUBEMAP_WIDTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURECUBEMAP_LAYERED_WIDTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURECUBEMAP_LAYERED_LAYERS,
CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE1D_WIDTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_WIDTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_HEIGHT,
CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE3D_WIDTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE3D_HEIGHT,
CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE3D_DEPTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE1D_LAYERED_WIDTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE1D_LAYERED_LAYERS,
CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_LAYERED_WIDTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_LAYERED_HEIGHT,
CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_LAYERED_LAYERS,
CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACECUBEMAP_WIDTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACECUBEMAP_LAYERED_WIDTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACECUBEMAP_LAYERED_LAYERS,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_LINEAR_WIDTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_WIDTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_HEIGHT,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_PITCH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_MIPMAPPED_WIDTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_MIPMAPPED_HEIGHT,
CU_DEVICE_ATTRIBUTE_COMPUTE_CAPABILITY_MAJOR,
CU_DEVICE_ATTRIBUTE_COMPUTE_CAPABILITY_MINOR,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_MIPMAPPED_WIDTH,
CU_DEVICE_ATTRIBUTE_MAX};
# 379 "/usr/local/cuda-5.0/include/cuda.h"
enum CUpointer_attribute_enum {
CU_POINTER_ATTRIBUTE_CONTEXT = 1,
CU_POINTER_ATTRIBUTE_MEMORY_TYPE,
CU_POINTER_ATTRIBUTE_DEVICE_POINTER,
CU_POINTER_ATTRIBUTE_HOST_POINTER,
CU_POINTER_ATTRIBUTE_P2P_TOKENS};
# 390 "/usr/local/cuda-5.0/include/cuda.h"
enum CUfunction_attribute_enum {
# 396 "/usr/local/cuda-5.0/include/cuda.h"
CU_FUNC_ATTRIBUTE_MAX_THREADS_PER_BLOCK,
# 403 "/usr/local/cuda-5.0/include/cuda.h"
CU_FUNC_ATTRIBUTE_SHARED_SIZE_BYTES,
# 409 "/usr/local/cuda-5.0/include/cuda.h"
CU_FUNC_ATTRIBUTE_CONST_SIZE_BYTES,




CU_FUNC_ATTRIBUTE_LOCAL_SIZE_BYTES,




CU_FUNC_ATTRIBUTE_NUM_REGS,
# 428 "/usr/local/cuda-5.0/include/cuda.h"
CU_FUNC_ATTRIBUTE_PTX_VERSION,
# 437 "/usr/local/cuda-5.0/include/cuda.h"
CU_FUNC_ATTRIBUTE_BINARY_VERSION,

CU_FUNC_ATTRIBUTE_MAX};
# 445 "/usr/local/cuda-5.0/include/cuda.h"
enum CUfunc_cache_enum {
CU_FUNC_CACHE_PREFER_NONE,
CU_FUNC_CACHE_PREFER_SHARED,
CU_FUNC_CACHE_PREFER_L1,
CU_FUNC_CACHE_PREFER_EQUAL};
# 455 "/usr/local/cuda-5.0/include/cuda.h"
enum CUsharedconfig_enum {
CU_SHARED_MEM_CONFIG_DEFAULT_BANK_SIZE,
CU_SHARED_MEM_CONFIG_FOUR_BYTE_BANK_SIZE,
CU_SHARED_MEM_CONFIG_EIGHT_BYTE_BANK_SIZE};
# 464 "/usr/local/cuda-5.0/include/cuda.h"
enum CUmemorytype_enum {
CU_MEMORYTYPE_HOST = 1,
CU_MEMORYTYPE_DEVICE,
CU_MEMORYTYPE_ARRAY,
CU_MEMORYTYPE_UNIFIED};
# 474 "/usr/local/cuda-5.0/include/cuda.h"
enum CUcomputemode_enum {
CU_COMPUTEMODE_DEFAULT,
CU_COMPUTEMODE_EXCLUSIVE,
CU_COMPUTEMODE_PROHIBITED,
CU_COMPUTEMODE_EXCLUSIVE_PROCESS};
# 484 "/usr/local/cuda-5.0/include/cuda.h"
enum CUjit_option_enum {
# 490 "/usr/local/cuda-5.0/include/cuda.h"
CU_JIT_MAX_REGISTERS,
# 503 "/usr/local/cuda-5.0/include/cuda.h"
CU_JIT_THREADS_PER_BLOCK,
# 510 "/usr/local/cuda-5.0/include/cuda.h"
CU_JIT_WALL_TIME,
# 518 "/usr/local/cuda-5.0/include/cuda.h"
CU_JIT_INFO_LOG_BUFFER,
# 526 "/usr/local/cuda-5.0/include/cuda.h"
CU_JIT_INFO_LOG_BUFFER_SIZE_BYTES,
# 534 "/usr/local/cuda-5.0/include/cuda.h"
CU_JIT_ERROR_LOG_BUFFER,
# 542 "/usr/local/cuda-5.0/include/cuda.h"
CU_JIT_ERROR_LOG_BUFFER_SIZE_BYTES,
# 549 "/usr/local/cuda-5.0/include/cuda.h"
CU_JIT_OPTIMIZATION_LEVEL,
# 556 "/usr/local/cuda-5.0/include/cuda.h"
CU_JIT_TARGET_FROM_CUCONTEXT,
# 562 "/usr/local/cuda-5.0/include/cuda.h"
CU_JIT_TARGET,
# 569 "/usr/local/cuda-5.0/include/cuda.h"
CU_JIT_FALLBACK_STRATEGY};
# 576 "/usr/local/cuda-5.0/include/cuda.h"
enum CUjit_target_enum {

CU_TARGET_COMPUTE_10,
CU_TARGET_COMPUTE_11,
CU_TARGET_COMPUTE_12,
CU_TARGET_COMPUTE_13,
CU_TARGET_COMPUTE_20,
CU_TARGET_COMPUTE_21,
CU_TARGET_COMPUTE_30,
CU_TARGET_COMPUTE_35};
# 591 "/usr/local/cuda-5.0/include/cuda.h"
enum CUjit_fallback_enum {

CU_PREFER_PTX,

CU_PREFER_BINARY};
# 602 "/usr/local/cuda-5.0/include/cuda.h"
enum CUgraphicsRegisterFlags_enum {
CU_GRAPHICS_REGISTER_FLAGS_NONE,
CU_GRAPHICS_REGISTER_FLAGS_READ_ONLY,
CU_GRAPHICS_REGISTER_FLAGS_WRITE_DISCARD,
CU_GRAPHICS_REGISTER_FLAGS_SURFACE_LDST = 4,
CU_GRAPHICS_REGISTER_FLAGS_TEXTURE_GATHER = 8};
# 613 "/usr/local/cuda-5.0/include/cuda.h"
enum CUgraphicsMapResourceFlags_enum {
CU_GRAPHICS_MAP_RESOURCE_FLAGS_NONE,
CU_GRAPHICS_MAP_RESOURCE_FLAGS_READ_ONLY,
CU_GRAPHICS_MAP_RESOURCE_FLAGS_WRITE_DISCARD};
# 622 "/usr/local/cuda-5.0/include/cuda.h"
enum CUarray_cubemap_face_enum {
CU_CUBEMAP_FACE_POSITIVE_X,
CU_CUBEMAP_FACE_NEGATIVE_X,
CU_CUBEMAP_FACE_POSITIVE_Y,
CU_CUBEMAP_FACE_NEGATIVE_Y,
CU_CUBEMAP_FACE_POSITIVE_Z,
CU_CUBEMAP_FACE_NEGATIVE_Z};
# 634 "/usr/local/cuda-5.0/include/cuda.h"
enum CUlimit_enum {
CU_LIMIT_STACK_SIZE,
CU_LIMIT_PRINTF_FIFO_SIZE,
CU_LIMIT_MALLOC_HEAP_SIZE,
CU_LIMIT_DEV_RUNTIME_SYNC_DEPTH,
CU_LIMIT_DEV_RUNTIME_PENDING_LAUNCH_COUNT};
# 645 "/usr/local/cuda-5.0/include/cuda.h"
enum CUresourcetype_enum {
CU_RESOURCE_TYPE_ARRAY,
CU_RESOURCE_TYPE_MIPMAPPED_ARRAY,
CU_RESOURCE_TYPE_LINEAR,
CU_RESOURCE_TYPE_PITCH2D};
# 655 "/usr/local/cuda-5.0/include/cuda.h"
enum cudaError_enum {
# 661 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_SUCCESS,
# 667 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_INVALID_VALUE,
# 673 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_OUT_OF_MEMORY,
# 679 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_NOT_INITIALIZED,




CUDA_ERROR_DEINITIALIZED,
# 691 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_PROFILER_DISABLED,
# 699 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_PROFILER_NOT_INITIALIZED,
# 706 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_PROFILER_ALREADY_STARTED,
# 713 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_PROFILER_ALREADY_STOPPED,
# 719 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_NO_DEVICE = 100,
# 725 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_INVALID_DEVICE,
# 732 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_INVALID_IMAGE = 200,
# 742 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_INVALID_CONTEXT,
# 751 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_CONTEXT_ALREADY_CURRENT,




CUDA_ERROR_MAP_FAILED = 205,




CUDA_ERROR_UNMAP_FAILED,
# 767 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_ARRAY_IS_MAPPED,




CUDA_ERROR_ALREADY_MAPPED,
# 780 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_NO_BINARY_FOR_GPU,




CUDA_ERROR_ALREADY_ACQUIRED,




CUDA_ERROR_NOT_MAPPED,
# 796 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_NOT_MAPPED_AS_ARRAY,
# 802 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_NOT_MAPPED_AS_POINTER,
# 808 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_ECC_UNCORRECTABLE,
# 814 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_UNSUPPORTED_LIMIT,
# 821 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_CONTEXT_ALREADY_IN_USE,
# 827 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_PEER_ACCESS_UNSUPPORTED,




CUDA_ERROR_INVALID_SOURCE = 300,




CUDA_ERROR_FILE_NOT_FOUND,




CUDA_ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND,




CUDA_ERROR_SHARED_OBJECT_INIT_FAILED,




CUDA_ERROR_OPERATING_SYSTEM,
# 859 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_INVALID_HANDLE = 400,
# 866 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_NOT_FOUND = 500,
# 875 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_NOT_READY = 600,
# 886 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_LAUNCH_FAILED = 700,
# 897 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_LAUNCH_OUT_OF_RESOURCES,
# 908 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_LAUNCH_TIMEOUT,
# 914 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING,
# 921 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_PEER_ACCESS_ALREADY_ENABLED,
# 928 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_PEER_ACCESS_NOT_ENABLED,
# 934 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_PRIMARY_CONTEXT_ACTIVE = 708,
# 941 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_CONTEXT_IS_DESTROYED,
# 949 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_ASSERT,
# 956 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_TOO_MANY_PEERS,
# 962 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_HOST_MEMORY_ALREADY_REGISTERED,
# 968 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_HOST_MEMORY_NOT_REGISTERED,




CUDA_ERROR_NOT_PERMITTED = 800,
# 979 "/usr/local/cuda-5.0/include/cuda.h"
CUDA_ERROR_NOT_SUPPORTED,




CUDA_ERROR_UNKNOWN = 999};
# 1213 "/usr/local/cuda-5.0/include/cuda.h"
enum CUresourceViewFormat_enum {

CU_RES_VIEW_FORMAT_NONE,
CU_RES_VIEW_FORMAT_UINT_1X8,
CU_RES_VIEW_FORMAT_UINT_2X8,
CU_RES_VIEW_FORMAT_UINT_4X8,
CU_RES_VIEW_FORMAT_SINT_1X8,
CU_RES_VIEW_FORMAT_SINT_2X8,
CU_RES_VIEW_FORMAT_SINT_4X8,
CU_RES_VIEW_FORMAT_UINT_1X16,
CU_RES_VIEW_FORMAT_UINT_2X16,
CU_RES_VIEW_FORMAT_UINT_4X16,
CU_RES_VIEW_FORMAT_SINT_1X16,
CU_RES_VIEW_FORMAT_SINT_2X16,
CU_RES_VIEW_FORMAT_SINT_4X16,
CU_RES_VIEW_FORMAT_UINT_1X32,
CU_RES_VIEW_FORMAT_UINT_2X32,
CU_RES_VIEW_FORMAT_UINT_4X32,
CU_RES_VIEW_FORMAT_SINT_1X32,
CU_RES_VIEW_FORMAT_SINT_2X32,
CU_RES_VIEW_FORMAT_SINT_4X32,
CU_RES_VIEW_FORMAT_FLOAT_1X16,
CU_RES_VIEW_FORMAT_FLOAT_2X16,
CU_RES_VIEW_FORMAT_FLOAT_4X16,
CU_RES_VIEW_FORMAT_FLOAT_1X32,
CU_RES_VIEW_FORMAT_FLOAT_2X32,
CU_RES_VIEW_FORMAT_FLOAT_4X32,
CU_RES_VIEW_FORMAT_UNSIGNED_BC1,
CU_RES_VIEW_FORMAT_UNSIGNED_BC2,
CU_RES_VIEW_FORMAT_UNSIGNED_BC3,
CU_RES_VIEW_FORMAT_UNSIGNED_BC4,
CU_RES_VIEW_FORMAT_SIGNED_BC4,
CU_RES_VIEW_FORMAT_UNSIGNED_BC5,
CU_RES_VIEW_FORMAT_SIGNED_BC5,
CU_RES_VIEW_FORMAT_UNSIGNED_BC6H,
CU_RES_VIEW_FORMAT_SIGNED_BC6H,
CU_RES_VIEW_FORMAT_UNSIGNED_BC7};
# 75 "/usr/local/cuda-5.0/include/cufft.h"
enum cufftResult_t {
CUFFT_SUCCESS,
CUFFT_INVALID_PLAN,
CUFFT_ALLOC_FAILED,
CUFFT_INVALID_TYPE,
CUFFT_INVALID_VALUE,
CUFFT_INTERNAL_ERROR,
CUFFT_EXEC_FAILED,
CUFFT_SETUP_FAILED,
CUFFT_INVALID_SIZE,
CUFFT_UNALIGNED_DATA};
# 108 "/usr/local/cuda-5.0/include/cufft.h"
enum cufftType_t {
CUFFT_R2C = 42,
CUFFT_C2R = 44,
CUFFT_C2C = 41,
CUFFT_D2Z = 106,
CUFFT_Z2D = 108,
CUFFT_Z2Z = 105};
# 139 "/usr/local/cuda-5.0/include/cufft.h"
enum cufftCompatibility_t {
CUFFT_COMPATIBILITY_NATIVE,
CUFFT_COMPATIBILITY_FFTW_PADDING,
CUFFT_COMPATIBILITY_FFTW_ASYMMETRIC,
CUFFT_COMPATIBILITY_FFTW_ALL};
# 57 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/cudatypes.h"
struct SoADeviceObject;
# 272 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/cudatypes.h"
enum CudaNonbondedMethod {

NO_CUTOFF,
CUTOFF,
PERIODIC,
EWALD,
PARTICLE_MESH_EWALD};


enum ExpressionOp {
VARIABLE0, VARIABLE1, VARIABLE2, VARIABLE3, VARIABLE4, VARIABLE5, VARIABLE6, VARIABLE7, VARIABLE8, MULTIPLY, DIVIDE, ADD, SUBTRACT, POWER, MULTIPLY_CONSTANT, POWER_CONSTANT, ADD_CONSTANT,
GLOBAL, CONSTANT, CUSTOM, CUSTOM_DERIV, NEGATE, RECIPROCAL, SQRT, EXP, LOG, SQUARE, CUBE, STEP, SIN, COS, SEC, CSC, TAN, COT, ASIN, ACOS, ATAN, SINH, COSH, TANH, ERF, ERFC,
MIN, MAX, ABS};
# 294 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/cudatypes.h"
struct cudaGmxSimulation;
# 30 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/cudaCompact.h"
struct compactionPlan;
# 257 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/basic_string.h" 3
struct _ZNSs12_Alloc_hiderE;
# 52 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stringfwd.h" 3
struct _ZSs;
# 39 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/gputypes.h"
struct gpuAtomType;
# 73 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZNSt12_Vector_baseIiSaIiEE12_Vector_implE;
# 69 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt12_Vector_baseIiSaIiEE;
# 170 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt6vectorIiSaIiEE;
# 45 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/gputypes.h"
struct gpuMoleculeGroup;
# 65 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/cudatypes.h"
struct _Z10CUDAStreamI6float4E;
# 50 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/gputypes.h"
struct gpuTabulatedFunction;
# 58 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/gputypes.h"
enum SM_VERSION {

SM_10,
SM_11,
SM_12,
SM_20};
# 65 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/cudatypes.h"
struct _Z10CUDAStreamI6float2E; struct _Z10CUDAStreamI4int4E; struct _Z10CUDAStreamI4int2E; struct _Z10CUDAStreamImE; struct _Z10CUDAStreamI5uint4E;
# 73 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZNSt12_Vector_baseIPN6OpenMM13CudaForceInfoESaIS2_EE12_Vector_implE;
# 69 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt12_Vector_baseIPN6OpenMM13CudaForceInfoESaIS2_EE;
# 170 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt6vectorIPN6OpenMM13CudaForceInfoESaIS2_EE;
# 73 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZNSt12_Vector_baseISt6vectorIiSaIiEESaIS2_EE12_Vector_implE;
# 69 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt12_Vector_baseISt6vectorIiSaIiEESaIS2_EE;
# 170 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt6vectorIS_IiSaIiEESaIS1_EE;
# 73 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZNSt12_Vector_baseI16gpuMoleculeGroupSaIS0_EE12_Vector_implE;
# 69 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt12_Vector_baseI16gpuMoleculeGroupSaIS0_EE;
# 170 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt6vectorI16gpuMoleculeGroupSaIS0_EE;
# 73 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZNSt12_Vector_baseI4int3SaIS0_EE12_Vector_implE;
# 69 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt12_Vector_baseI4int3SaIS0_EE;
# 170 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt6vectorI4int3SaIS0_EE;
# 69 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/gputypes.h"
struct _gpuContext;
# 44 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//amoebaCudaTypes.h"
enum CudaAmoebaNonbondedMethod {

AMOEBA_NO_CUTOFF,
AMOEBA_PARTICLE_MESH_EWALD};
# 53 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//amoebaCudaTypes.h"
struct cudaAmoebaGmxSimulation;
# 37 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//amoebaGpuTypes.h"
struct _amoebaGpuContext;
# 53 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
struct GrycukParticle;
# 65 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/cudatypes.h"
struct _Z10CUDAStreamIiE; struct _Z10CUDAStreamIjE;
# 260 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
struct GrycukChainRuleParticle;
# 65 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/cudatypes.h"
struct _Z10CUDAStreamIfE;
# 59 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/exception" 3
struct _ZSt9exception;
# 54 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/new" 3
struct _ZSt9bad_alloc;
# 124 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt9__is_voidIvEUt_E { _ZNSt9__is_voidIvE7__valueE = 1};
# 144 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIbEUt_E { _ZNSt12__is_integerIbE7__valueE = 1};
# 151 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIcEUt_E { _ZNSt12__is_integerIcE7__valueE = 1};
# 158 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIaEUt_E { _ZNSt12__is_integerIaE7__valueE = 1};
# 165 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIhEUt_E { _ZNSt12__is_integerIhE7__valueE = 1};
# 173 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIwEUt_E { _ZNSt12__is_integerIwE7__valueE = 1};
# 197 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIsEUt_E { _ZNSt12__is_integerIsE7__valueE = 1};
# 204 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerItEUt_E { _ZNSt12__is_integerItE7__valueE = 1};
# 211 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIiEUt_E { _ZNSt12__is_integerIiE7__valueE = 1};
# 218 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIjEUt_E { _ZNSt12__is_integerIjE7__valueE = 1};
# 225 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIlEUt_E { _ZNSt12__is_integerIlE7__valueE = 1};
# 232 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerImEUt_E { _ZNSt12__is_integerImE7__valueE = 1};
# 239 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIxEUt_E { _ZNSt12__is_integerIxE7__valueE = 1};
# 246 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIyEUt_E { _ZNSt12__is_integerIyE7__valueE = 1};
# 264 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt13__is_floatingIfEUt_E { _ZNSt13__is_floatingIfE7__valueE = 1};
# 271 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt13__is_floatingIdEUt_E { _ZNSt13__is_floatingIdE7__valueE = 1};
# 278 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt13__is_floatingIeEUt_E { _ZNSt13__is_floatingIeE7__valueE = 1};
# 354 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt9__is_charIcEUt_E { _ZNSt9__is_charIcE7__valueE = 1};
# 362 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt9__is_charIwEUt_E { _ZNSt9__is_charIwE7__valueE = 1};
# 377 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt9__is_byteIcEUt_E { _ZNSt9__is_byteIcE7__valueE = 1};
# 384 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt9__is_byteIaEUt_E { _ZNSt9__is_byteIaE7__valueE = 1};
# 391 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt9__is_byteIhEUt_E { _ZNSt9__is_byteIhE7__valueE = 1};
# 153 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/limits" 3
enum _ZSt17float_round_style {

_ZSt19round_indeterminate = (-1),
_ZSt17round_toward_zero,
_ZSt16round_to_nearest,
_ZSt21round_toward_infinity,
_ZSt25round_toward_neg_infinity};
# 168 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/limits" 3
enum _ZSt18float_denorm_style {


_ZSt20denorm_indeterminate = (-1),

_ZSt13denorm_absent,

_ZSt14denorm_present};
# 237 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/char_traits.h" 3
struct _ZSt11char_traitsIcE;
# 45 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stringfwd.h" 3
struct _ZSaIcE;
# 140 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/basic_string.h" 3
struct _ZNSs9_Rep_baseE;
# 147 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/basic_string.h" 3
struct _ZNSs4_RepE;
# 302 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/locale_classes.h" 3
enum _ZNSt6localeUt_E { _ZNSt6locale18_S_categories_sizeE = 12};
# 60 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/ios_base.h" 3
enum _ZSt13_Ios_Fmtflags {

_ZSt12_S_boolalpha = 1,
_ZSt6_S_dec,
_ZSt8_S_fixed = 4,
_ZSt6_S_hex = 8,
_ZSt11_S_internal = 16,
_ZSt7_S_left = 32,
_ZSt6_S_oct = 64,
_ZSt8_S_right = 128,
_ZSt13_S_scientific = 256,
_ZSt11_S_showbase = 512,
_ZSt12_S_showpoint = 1024,
_ZSt10_S_showpos = 2048,
_ZSt9_S_skipws = 4096,
_ZSt10_S_unitbuf = 8192,
_ZSt12_S_uppercase = 16384,
_ZSt14_S_adjustfield = 176,
_ZSt12_S_basefield = 74,
_ZSt13_S_floatfield = 260,
_ZSt19_S_ios_fmtflags_end = 65536};
# 112 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/ios_base.h" 3
enum _ZSt13_Ios_Openmode {

_ZSt6_S_app = 1,
_ZSt6_S_ate,
_ZSt6_S_bin = 4,
_ZSt5_S_in = 8,
_ZSt6_S_out = 16,
_ZSt8_S_trunc = 32,
_ZSt19_S_ios_openmode_end = 65536};
# 152 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/ios_base.h" 3
enum _ZSt12_Ios_Iostate {

_ZSt10_S_goodbit,
_ZSt9_S_badbit,
_ZSt9_S_eofbit,
_ZSt10_S_failbit = 4,
_ZSt18_S_ios_iostate_end = 65536};
# 189 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/ios_base.h" 3
enum _ZSt12_Ios_Seekdir {

_ZSt6_S_beg,
_ZSt6_S_cur,
_ZSt6_S_end,
_ZSt18_S_ios_seekdir_end = 65536};
# 427 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/ios_base.h" 3
enum _ZNSt8ios_base5eventE {

_ZNSt8ios_base11erase_eventE,
_ZNSt8ios_base11imbue_eventE,
_ZNSt8ios_base13copyfmt_eventE};
# 515 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/ios_base.h" 3
enum _ZNSt8ios_baseUt_E { _ZNSt8ios_base18_S_local_word_sizeE = 8};
# 537 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/ios_base.h" 3
struct _ZNSt8ios_base4InitE;
# 1521 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/locale_facets.h" 3
enum _ZNSt10__num_baseUt_E {
_ZNSt10__num_base9_S_ominusE,
_ZNSt10__num_base8_S_oplusE,
_ZNSt10__num_base5_S_oxE,
_ZNSt10__num_base5_S_oXE,
_ZNSt10__num_base10_S_odigitsE,
_ZNSt10__num_base14_S_odigits_endE = 20,
_ZNSt10__num_base11_S_oudigitsE = 20,
_ZNSt10__num_base15_S_oudigits_endE = 36,
_ZNSt10__num_base5_S_oeE = 18,
_ZNSt10__num_base5_S_oEE = 34,
_ZNSt10__num_base7_S_oendE = 36};
# 1547 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/locale_facets.h" 3
enum _ZNSt10__num_baseUt0_E {
_ZNSt10__num_base9_S_iminusE,
_ZNSt10__num_base8_S_iplusE,
_ZNSt10__num_base5_S_ixE,
_ZNSt10__num_base5_S_iXE,
_ZNSt10__num_base8_S_izeroE,
_ZNSt10__num_base5_S_ieE = 18,
_ZNSt10__num_base5_S_iEE = 24,
_ZNSt10__num_base7_S_iendE = 26};
# 134 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIdEUt_E { _ZNSt12__is_integerIdE7__valueE};
# 65 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_bvector.h" 3
enum _ZStUt_ { _ZSt11_S_word_bit = 64};
# 86 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
struct _ZSaIiE; struct _ZSaIPN6OpenMM13CudaForceInfoEE; struct _ZSaISt6vectorIiSaIiEEE; struct _ZSaI16gpuMoleculeGroupE; struct _ZSaI4int3E;
# 85 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_tree.h" 3
enum _ZSt14_Rb_tree_color { _ZSt6_S_red, _ZSt8_S_black};
# 86 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
struct _ZSaISt6vectorIdSaIdEEE;
# 73 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE12_Vector_implE;
# 69 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE;
# 170 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt6vectorIS_IdSaIdEESaIS1_EE;
# 305 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt20__is_normal_iteratorIPmEUt_E { _ZNSt20__is_normal_iteratorIPmE7__valueE};
# 256 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt13__is_floatingIiEUt_E { _ZNSt13__is_floatingIiE7__valueE};
# 94 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt9__traitorISt12__is_integerIiESt13__is_floatingIiEEUt_E { _ZNSt9__traitorISt12__is_integerIiESt13__is_floatingIiEE7__valueE = 1};
# 288 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_pointerIiEUt_E { _ZNSt12__is_pointerIiE7__valueE};
# 94 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt9__traitorISt15__is_arithmeticIiESt12__is_pointerIiEEUt_E { _ZNSt9__traitorISt15__is_arithmeticIiESt12__is_pointerIiEE7__valueE = 1};
# 401 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt18__is_move_iteratorIPiEUt_E { _ZNSt18__is_move_iteratorIPiE7__valueE};
# 305 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt20__is_normal_iteratorIPiEUt_E { _ZNSt20__is_normal_iteratorIPiE7__valueE};
# 295 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_pointerIPiEUt_E { _ZNSt12__is_pointerIPiE7__valueE = 1};
# 109 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/cpp_type_traits.h" 3
enum _ZNSt10__are_sameIiiEUt_E { _ZNSt10__are_sameIiiE7__valueE = 1}; enum _ZNSt10__are_sameIPiS0_EUt_E { _ZNSt10__are_sameIPiS0_E7__valueE = 1};
# 86 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
struct _ZSaIdE;
# 73 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZNSt12_Vector_baseIdSaIdEE12_Vector_implE;
# 69 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt12_Vector_baseIdSaIdEE;
# 170 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt6vectorIdSaIdEE;
# 51 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/ext/new_allocator.h" 3
struct _ZN9__gnu_cxx13new_allocatorIcEE; struct _ZN9__gnu_cxx13new_allocatorIiEE; struct _ZN9__gnu_cxx13new_allocatorIPN6OpenMM13CudaForceInfoEEE; struct _ZN9__gnu_cxx13new_allocatorISt6vectorIiSaIiEEEE; struct _ZN9__gnu_cxx13new_allocatorI16gpuMoleculeGroupEE; struct _ZN9__gnu_cxx13new_allocatorI4int3EE; struct _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEEE;
# 668 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_iterator.h" 3
struct _ZN9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEE;
# 51 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/ext/new_allocator.h" 3
struct _ZN9__gnu_cxx13new_allocatorIdEE;
# 44 "/home/saifmulla/openmm/OpenMM/openmmapi/include/openmm/OpenMMException.h"
struct _ZN6OpenMM15OpenMMExceptionE;
# 36 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/gputypes.h"
struct _ZN6OpenMM13CudaForceInfoE;
# 149 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/include/stddef.h" 3
typedef long ptrdiff_t;
# 211 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/include/stddef.h" 3
typedef unsigned long size_t;
#include "crt/host_runtime.h"
struct __C3 { struct __C2 *regions; void **obj_table; struct __C1 *array_table; unsigned short saved_region_number;char __nv_no_debug_dummy_end_padding_0[6];}; struct __type_info { const long *__vptr; const char *__name;}; struct __class_type_info { struct __type_info base;}; struct __si_class_type_info { struct __class_type_info base; const struct __class_type_info *base_type;}; struct __C5 { const struct __type_info *tinfo; unsigned char flags; unsigned char *ptr_flags;}; struct __C6 { long setjmp_buffer[25]; struct __C5 *catch_entries; void *rtinfo; unsigned short region_number;char __nv_no_debug_dummy_end_padding_0[6];}; union __C7 { struct __C6 try_block; struct __C3 function; struct __C5 *throw_spec;}; struct __C8 { struct __C8 *next; unsigned char kind; union __C7 variant;};
# 49 "/usr/include/stdio.h" 3
typedef struct _IO_FILE FILE;
# 50 "/usr/include/bits/pthreadtypes.h" 3
typedef unsigned long pthread_t;
# 32 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/x86_64-redhat-linux/bits/atomic_word.h" 3
typedef int _Atomic_word;
# 60 "/usr/local/cuda-5.0/include/cuComplex.h"
typedef struct float2 cuFloatComplex;
# 282 "/usr/local/cuda-5.0/include/cuComplex.h"
typedef cuFloatComplex cuComplex;
# 100 "/usr/local/cuda-5.0/include/cufft.h"
typedef cuComplex cufftComplex;
# 154 "/usr/local/cuda-5.0/include/cufft.h"
typedef int cufftHandle;
# 57 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/cudatypes.h"
struct SoADeviceObject { const long *__vptr;};
# 294 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/cudatypes.h"
struct cudaGmxSimulation {

unsigned atoms;
unsigned paddedNumberOfAtoms;
unsigned blocks;
unsigned blocksPerSM;
unsigned nonbond_blocks;
unsigned bornForce2_blocks;
unsigned interaction_blocks;
unsigned threads_per_block;
unsigned nonbond_threads_per_block;
unsigned bornForce2_threads_per_block;
unsigned max_update_threads_per_block;
unsigned update_threads_per_block;
unsigned bf_reduce_threads_per_block;
unsigned bsf_reduce_threads_per_block;
unsigned max_shake_threads_per_block;
unsigned shake_threads_per_block;
unsigned settle_threads_per_block;
unsigned ccma_threads_per_block;
unsigned max_localForces_threads_per_block;
unsigned localForces_threads_per_block;
unsigned random_threads_per_block;
unsigned interaction_threads_per_block;
unsigned custom_exception_threads_per_block;
unsigned customExpressionStackSize;
unsigned workUnits;
unsigned *pWorkUnit;
unsigned *pInteractingWorkUnit;
unsigned *pInteractionFlag;
struct float2 *pStepSize;
float *pLangevinParameters;
float errorTol;
size_t *pInteractionCount;
unsigned nonbond_workBlock;
unsigned bornForce2_workBlock;
unsigned workUnitsPerSM;
unsigned nbWorkUnitsPerBlock;
unsigned nbWorkUnitsPerBlockRemainder;
unsigned bf2WorkUnitsPerBlock;
unsigned bf2WorkUnitsPerBlockRemainder;


unsigned stride;
unsigned stride2;
unsigned stride3;
unsigned stride4;
unsigned nonbondOutputBuffers;
unsigned outputBuffers;
unsigned energyOutputBuffers;
float bigFloat;
float epsfac;
enum CudaNonbondedMethod nonbondedMethod;
enum CudaNonbondedMethod customNonbondedMethod;
float nonbondedCutoff;
float nonbondedCutoffSqr;
float periodicBoxSizeX;
float periodicBoxSizeY;
float periodicBoxSizeZ;
float invPeriodicBoxSizeX;
float invPeriodicBoxSizeY;
float invPeriodicBoxSizeZ;
float recipBoxSizeX;
float recipBoxSizeY;
float recipBoxSizeZ;
float cellVolume;
float alphaEwald;
float factorEwald;
int kmaxX;
int kmaxY;
int kmaxZ;
float reactionFieldK;
float reactionFieldC;
float probeRadius;
float surfaceAreaFactor;
float electricConstant;
float forceConversionFactor;
float preFactor;
float dielectricOffset;
float alphaOBC;
float betaOBC;
float gammaOBC;
float deltaT;
float oneOverDeltaT;
float T;
float kT;
float noiseAmplitude;
float tau;
float tauDeltaT;
float collisionFrequency;
struct float2 *pObcData;
int gbviBornRadiusScalingMethod;
float gbviQuinticLowerLimitFactor;
float gbviQuinticUpperBornRadiusLimit;
struct float4 *pGBVIData;
float *pGBVISwitchDerivative;
struct float2 *pAttr;
struct float4 *pCustomParams;
unsigned customExceptions;
unsigned customParameters;
struct int4 *pCustomBondID;
struct float4 *pCustomBondParams;
unsigned customBonds;
unsigned customBondParameters;
struct int4 *pCustomAngleID1;
struct int2 *pCustomAngleID2;
struct float4 *pCustomAngleParams;
unsigned customAngles;
unsigned customAngleParameters;
struct int4 *pCustomTorsionID1;
struct int4 *pCustomTorsionID2;
struct float4 *pCustomTorsionParams;
unsigned customTorsions;
unsigned customTorsionParameters;
int *pCustomExternalID;
struct float4 *pCustomExternalParams;
unsigned customExternals;
unsigned customExternalParameters;
struct float4 *pTabulatedFunctionCoefficients[4];
struct float4 *pTabulatedFunctionParams;
struct float2 *pEwaldCosSinSum;
float *pTabulatedErfc;
int tabulatedErfcSize;
float tabulatedErfcScale;
struct int3 pmeGridSize;
struct int3 pmeGroupSize;
cufftComplex *pPmeGrid;
float *pPmeBsplineModuli[3];
struct float4 *pPmeBsplineTheta;
struct float4 *pPmeBsplineDtheta;
int *pPmeAtomRange;
struct int2 *pPmeAtomGridIndex;
unsigned bonds;
struct int4 *pBondID;
struct float2 *pBondParameter;
unsigned bond_angles;
struct int4 *pBondAngleID1;
struct int2 *pBondAngleID2;
struct float2 *pBondAngleParameter;
unsigned dihedrals;
struct int4 *pDihedralID1;
struct int4 *pDihedralID2;
struct float4 *pDihedralParameter;
unsigned rb_dihedrals;
struct int4 *pRbDihedralID1;
struct int4 *pRbDihedralID2;
struct float4 *pRbDihedralParameter1;
struct float2 *pRbDihedralParameter2;
unsigned LJ14s;
struct int4 *pLJ14ID;
struct float4 *pLJ14Parameter;
float inverseTotalMass;
unsigned ShakeConstraints;
unsigned settleConstraints;
unsigned ccmaConstraints;
unsigned rigidClusters;
unsigned maxRigidClusterSize;
unsigned clusterShakeBlockSize;
unsigned maxShakeIterations;
unsigned degreesOfFreedom;
float shakeTolerance;
float InvMassJ;
int *pNonShakeID;
struct int4 *pShakeID;
struct float4 *pShakeParameter;
struct int4 *pSettleID;
struct float2 *pSettleParameter;
unsigned *pExclusion;
unsigned *pExclusionIndex;
unsigned bond_offset;
unsigned bond_angle_offset;
unsigned dihedral_offset;
unsigned rb_dihedral_offset;
unsigned LJ14_offset;
int *pAtomIndex;
struct float4 *pGridBoundingBox;
struct float4 *pGridCenter;
struct int2 *pCcmaAtoms;
struct float4 *pCcmaDistance;
float *pCcmaDelta1;
float *pCcmaDelta2;
int *pCcmaAtomConstraints;
int *pCcmaNumAtomConstraints;
int *ccmaConvergedDeviceMarker;
float *pCcmaReducedMass;
unsigned *pConstraintMatrixColumn;
float *pConstraintMatrixValue;


struct float4 *pPosq;
struct float4 *pPosqP;
struct float4 *pOldPosq;
struct float4 *pVelm4;
struct float4 *pForce4;
float *pEnergy;
float *pBornForce;
float *pBornSum;
float *pBornRadii;
float *pObcChain;
struct float4 *pLinearMomentum;


struct float4 *pRandom4;
struct float2 *pRandom2;
struct uint4 *pRandomSeed;
int *pRandomPosition;
unsigned randoms;
unsigned totalRandoms;
unsigned randomIterations;
unsigned randomFrames;};
# 30 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/cudaCompact.h"
struct compactionPlan {
char valid;
unsigned *dgBlockCounts;
unsigned nThreadBlocks;
char stageOutput;char __nv_no_debug_dummy_end_padding_0[3];};
# 56 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stringfwd.h" 3
typedef struct _ZSs _ZSt6string;
# 257 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/basic_string.h" 3
struct _ZNSs12_Alloc_hiderE {




char *_M_p;};
# 52 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stringfwd.h" 3
struct _ZSs {
# 274 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/basic_string.h" 3
struct _ZNSs12_Alloc_hiderE _M_dataplus;};
# 91 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
typedef int *_ZNSaIiE7pointerE;
# 73 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZNSt12_Vector_baseIiSaIiEE12_Vector_implE {


_ZNSaIiE7pointerE _M_start;
_ZNSaIiE7pointerE _M_finish;
_ZNSaIiE7pointerE _M_end_of_storage;};
# 69 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt12_Vector_baseIiSaIiEE {
# 136 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZNSt12_Vector_baseIiSaIiEE12_Vector_implE _M_impl;};
# 170 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt6vectorIiSaIiEE { struct _ZSt12_Vector_baseIiSaIiEE __b_St12_Vector_baseIiSaIiEE;};
# 50 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/gputypes.h"
struct gpuTabulatedFunction {


_ZSt6string name;
double min; double max;
struct _Z10CUDAStreamI6float4E *coefficients;};
# 91 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
typedef struct _ZN6OpenMM13CudaForceInfoE **_ZNSaIPN6OpenMM13CudaForceInfoEE7pointerE;
# 73 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZNSt12_Vector_baseIPN6OpenMM13CudaForceInfoESaIS2_EE12_Vector_implE {


_ZNSaIPN6OpenMM13CudaForceInfoEE7pointerE _M_start;
_ZNSaIPN6OpenMM13CudaForceInfoEE7pointerE _M_finish;
_ZNSaIPN6OpenMM13CudaForceInfoEE7pointerE _M_end_of_storage;};
# 69 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt12_Vector_baseIPN6OpenMM13CudaForceInfoESaIS2_EE {
# 136 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZNSt12_Vector_baseIPN6OpenMM13CudaForceInfoESaIS2_EE12_Vector_implE _M_impl;};
# 170 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt6vectorIPN6OpenMM13CudaForceInfoESaIS2_EE { struct _ZSt12_Vector_baseIPN6OpenMM13CudaForceInfoESaIS2_EE __b_St12_Vector_baseIPN6OpenMM13CudaForceInfoESaIS2_EE;};
# 91 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
typedef struct _ZSt6vectorIiSaIiEE *_ZNSaISt6vectorIiSaIiEEE7pointerE;
# 73 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZNSt12_Vector_baseISt6vectorIiSaIiEESaIS2_EE12_Vector_implE {


_ZNSaISt6vectorIiSaIiEEE7pointerE _M_start;
_ZNSaISt6vectorIiSaIiEEE7pointerE _M_finish;
_ZNSaISt6vectorIiSaIiEEE7pointerE _M_end_of_storage;};
# 69 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt12_Vector_baseISt6vectorIiSaIiEESaIS2_EE {
# 136 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZNSt12_Vector_baseISt6vectorIiSaIiEESaIS2_EE12_Vector_implE _M_impl;};
# 170 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt6vectorIS_IiSaIiEESaIS1_EE { struct _ZSt12_Vector_baseISt6vectorIiSaIiEESaIS2_EE __b_St12_Vector_baseISt6vectorIiSaIiEESaIS2_EE;};
# 91 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
typedef struct gpuMoleculeGroup *_ZNSaI16gpuMoleculeGroupE7pointerE;
# 73 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZNSt12_Vector_baseI16gpuMoleculeGroupSaIS0_EE12_Vector_implE {


_ZNSaI16gpuMoleculeGroupE7pointerE _M_start;
_ZNSaI16gpuMoleculeGroupE7pointerE _M_finish;
_ZNSaI16gpuMoleculeGroupE7pointerE _M_end_of_storage;};
# 69 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt12_Vector_baseI16gpuMoleculeGroupSaIS0_EE {
# 136 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZNSt12_Vector_baseI16gpuMoleculeGroupSaIS0_EE12_Vector_implE _M_impl;};
# 170 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt6vectorI16gpuMoleculeGroupSaIS0_EE { struct _ZSt12_Vector_baseI16gpuMoleculeGroupSaIS0_EE __b_St12_Vector_baseI16gpuMoleculeGroupSaIS0_EE;};
# 91 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
typedef struct int3 *_ZNSaI4int3E7pointerE;
# 73 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZNSt12_Vector_baseI4int3SaIS0_EE12_Vector_implE {


_ZNSaI4int3E7pointerE _M_start;
_ZNSaI4int3E7pointerE _M_finish;
_ZNSaI4int3E7pointerE _M_end_of_storage;};
# 69 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt12_Vector_baseI4int3SaIS0_EE {
# 136 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZNSt12_Vector_baseI4int3SaIS0_EE12_Vector_implE _M_impl;};
# 170 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt6vectorI4int3SaIS0_EE { struct _ZSt12_Vector_baseI4int3SaIS0_EE __b_St12_Vector_baseI4int3SaIS0_EE;};
# 69 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/gputypes.h"
struct _gpuContext {



int natoms;
int device;
char useBlockingSync;
struct gpuAtomType *gpAtomTable;
int gAtomTypes;
unsigned blocksPerSM;
unsigned sharedMemoryPerBlock;
struct cudaGmxSimulation sim;
unsigned *pOutputBufferCounter;
struct _ZSt6vectorIPN6OpenMM13CudaForceInfoESaIS2_EE forces;
struct _ZSt6vectorIS_IiSaIiEESaIS1_EE exclusions;
unsigned char *pAtomSymbol;
struct _ZSt6vectorI16gpuMoleculeGroupSaIS0_EE moleculeGroups;
struct gpuTabulatedFunction tabulatedFunctions[4];
struct _ZSt6vectorI4int3SaIS0_EE posCellOffsets;
int iterations;
float epsfac;
float solventDielectric;
float soluteDielectric;
int grid;
char bCalculateCM;
char bRemoveCM;
char bRecalculateBornRadii;
char bOutputBufferPerWarp;
char bIncludeGBSA;
char bIncludeGBVI;
char tabulatedFunctionsChanged;
unsigned long seed;
enum SM_VERSION sm_version;
struct compactionPlan compactPlan;
cufftHandle fftplan;
struct _Z10CUDAStreamI6float4E *psPosq4;
struct _Z10CUDAStreamI6float4E *psPosqP4;
struct _Z10CUDAStreamI6float4E *psOldPosq4;
struct _Z10CUDAStreamI6float4E *psVelm4;
struct _Z10CUDAStreamI6float4E *psForce4;
struct _Z10CUDAStreamIfE *psEnergy;
struct _Z10CUDAStreamI6float2E *psSigEps2;
struct _Z10CUDAStreamI6float4E *psCustomParams;
struct _Z10CUDAStreamI4int4E *psCustomBondID;
struct _Z10CUDAStreamI6float4E *psCustomBondParams;
struct _Z10CUDAStreamI4int4E *psCustomAngleID1;
struct _Z10CUDAStreamI4int2E *psCustomAngleID2;
struct _Z10CUDAStreamI6float4E *psCustomAngleParams;
struct _Z10CUDAStreamI4int4E *psCustomTorsionID1;
struct _Z10CUDAStreamI4int4E *psCustomTorsionID2;
struct _Z10CUDAStreamI6float4E *psCustomTorsionParams;
struct _Z10CUDAStreamIiE *psCustomExternalID;
struct _Z10CUDAStreamI6float4E *psCustomExternalParams;
struct _Z10CUDAStreamI6float4E *psTabulatedFunctionParams;
struct _Z10CUDAStreamI6float2E *psEwaldCosSinSum;
struct _Z10CUDAStreamIfE *psTabulatedErfc;
struct _Z10CUDAStreamI6float2E *psPmeGrid;
struct _Z10CUDAStreamIfE *psPmeBsplineModuli[3];
struct _Z10CUDAStreamI6float4E *psPmeBsplineTheta;
struct _Z10CUDAStreamI6float4E *psPmeBsplineDtheta;
struct _Z10CUDAStreamIiE *psPmeAtomRange;
struct _Z10CUDAStreamI4int2E *psPmeAtomGridIndex;
struct _Z10CUDAStreamI6float2E *psObcData;
struct _Z10CUDAStreamI6float4E *psGBVIData;
struct _Z10CUDAStreamIfE *psGBVISwitchDerivative;
struct _Z10CUDAStreamIfE *psObcChain;
struct _Z10CUDAStreamIfE *psBornForce;
struct _Z10CUDAStreamIfE *psBornRadii;
struct _Z10CUDAStreamIfE *psBornSum;
struct _Z10CUDAStreamI4int4E *psBondID;
struct _Z10CUDAStreamI6float2E *psBondParameter;
struct _Z10CUDAStreamI4int4E *psBondAngleID1;
struct _Z10CUDAStreamI4int2E *psBondAngleID2;
struct _Z10CUDAStreamI6float2E *psBondAngleParameter;
struct _Z10CUDAStreamI4int4E *psDihedralID1;
struct _Z10CUDAStreamI4int4E *psDihedralID2;
struct _Z10CUDAStreamI6float4E *psDihedralParameter;
struct _Z10CUDAStreamI4int4E *psRbDihedralID1;
struct _Z10CUDAStreamI4int4E *psRbDihedralID2;
struct _Z10CUDAStreamI6float4E *psRbDihedralParameter1;
struct _Z10CUDAStreamI6float2E *psRbDihedralParameter2;
struct _Z10CUDAStreamI4int4E *psLJ14ID;
struct _Z10CUDAStreamI6float4E *psLJ14Parameter;
struct _Z10CUDAStreamI4int4E *psShakeID;
struct _Z10CUDAStreamI6float4E *psShakeParameter;
struct _Z10CUDAStreamI4int4E *psSettleID;
struct _Z10CUDAStreamI6float2E *psSettleParameter;
struct _Z10CUDAStreamIjE *psExclusion;
struct _Z10CUDAStreamIjE *psExclusionIndex;
struct _Z10CUDAStreamIjE *psWorkUnit;
struct _Z10CUDAStreamIjE *psInteractingWorkUnit;
struct _Z10CUDAStreamIjE *psInteractionFlag;
struct _Z10CUDAStreamImE *psInteractionCount;
struct _Z10CUDAStreamI6float2E *psStepSize;
struct _Z10CUDAStreamIfE *psLangevinParameters;
struct _Z10CUDAStreamI6float4E *psRandom4;
struct _Z10CUDAStreamI6float2E *psRandom2;
struct _Z10CUDAStreamI5uint4E *psRandomSeed;
struct _Z10CUDAStreamIiE *psRandomPosition;
struct _Z10CUDAStreamI6float4E *psLinearMomentum;
struct _Z10CUDAStreamIiE *psAtomIndex;
struct _Z10CUDAStreamI6float4E *psGridBoundingBox;
struct _Z10CUDAStreamI6float4E *psGridCenter;
struct _Z10CUDAStreamI4int2E *psCcmaAtoms;
struct _Z10CUDAStreamI6float4E *psCcmaDistance;
struct _Z10CUDAStreamIiE *psCcmaAtomConstraints;
struct _Z10CUDAStreamIiE *psCcmaNumAtomConstraints;
struct _Z10CUDAStreamIfE *psCcmaDelta1;
struct _Z10CUDAStreamIfE *psCcmaDelta2;
int *ccmaConvergedHostMarker;
struct CUevent_st *ccmaEvent;
struct _Z10CUDAStreamIfE *psCcmaReducedMass;
struct _Z10CUDAStreamIfE *psRigidClusterMatrix;
struct _Z10CUDAStreamIjE *psRigidClusterConstraintIndex;
struct _Z10CUDAStreamIjE *psRigidClusterMatrixIndex;
struct _Z10CUDAStreamIjE *psConstraintMatrixColumn;
struct _Z10CUDAStreamIfE *psConstraintMatrixValue;};


typedef struct _gpuContext *gpuContext;
# 53 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//amoebaCudaTypes.h"
struct cudaAmoebaGmxSimulation {



unsigned amoebaBonds;
struct int4 *pAmoebaBondID;
struct float2 *pAmoebaBondParameter;
float amoebaBondCubicParameter;
float amoebaBondQuarticicParameter;
unsigned amoebaBond_offset;


unsigned amoebaAngles;
struct int4 *pAmoebaAngleID1;
struct int2 *pAmoebaAngleID2;
struct float2 *pAmoebaAngleParameter;
unsigned amoebaAngle_offset;

float amoebaAngleCubicK;
float amoebaAngleQuarticK;
float amoebaAnglePenticK;
float amoebaAngleSexticK;

unsigned amoebaInPlaneAngles;
struct int4 *pAmoebaInPlaneAngleID1;
struct int4 *pAmoebaInPlaneAngleID2;
struct float2 *pAmoebaInPlaneAngleParameter;
unsigned amoebaInPlaneAngle_offset;

float amoebaInPlaneAngleCubicK;
float amoebaInPlaneAngleQuarticK;
float amoebaInPlaneAnglePenticK;
float amoebaInPlaneAngleSexticK;

unsigned amoebaTorsions;
struct int4 *pAmoebaTorsionID1;
struct int4 *pAmoebaTorsionID2;
struct float4 *pAmoebaTorsionParameter1;
struct float2 *pAmoebaTorsionParameter2;
unsigned amoebaTorsion_offset;

unsigned amoebaPiTorsions;
struct int4 *pAmoebaPiTorsionID1;
struct int4 *pAmoebaPiTorsionID2;
struct int4 *pAmoebaPiTorsionID3;
float *pAmoebaPiTorsionParameter;
unsigned amoebaPiTorsion_offset;

unsigned amoebaStretchBends;
struct int4 *pAmoebaStretchBendID1;
struct int2 *pAmoebaStretchBendID2;
struct float4 *pAmoebaStretchBendParameter;
unsigned amoebaStretchBend_offset;

unsigned amoebaOutOfPlaneBends;
struct int4 *pAmoebaOutOfPlaneBendID1;
struct int4 *pAmoebaOutOfPlaneBendID2;
float *pAmoebaOutOfPlaneBendParameter;
unsigned amoebaOutOfPlaneBend_offset;
float amoebaOutOfPlaneBendCubicK;
float amoebaOutOfPlaneBendQuarticK;
float amoebaOutOfPlaneBendPenticK;
float amoebaOutOfPlaneBendSexticK;

unsigned amoebaTorsionTorsions;
struct int4 *pAmoebaTorsionTorsionID1;
struct int4 *pAmoebaTorsionTorsionID2;
struct int4 *pAmoebaTorsionTorsionID3;
unsigned amoebaTorsionTorsion_offset;


int amoebaTorTorGridOffset[12];
int amoebaTorTorGridNy[12];
float amoebaTorTorGridBegin[12];
float amoebaTorTorGridDelta[12];
struct float4 *pAmoebaTorsionTorsionGrids;

unsigned amoebaUreyBradleys;
struct int4 *pAmoebaUreyBradleyID;
struct float2 *pAmoebaUreyBradleyParameter;
float amoebaUreyBradleyCubicParameter;
float amoebaUreyBradleyQuarticicParameter;
unsigned amoebaUreyBradley_offset;

float sqrtPi;
float scalingDistanceCutoff;
struct float2 *pDampingFactorAndThole;
int polarizationType;

struct int4 *pMultipoleParticlesIdsAndAxisType;
struct int4 *pMultipoleParticlesTorqueBufferIndices;
int maxTorqueBufferIndex;
struct float4 *pTorqueMapForce4;

float *pMolecularDipole;
float *pMolecularQuadrupole;

float *pLabFrameDipole;
float *pLabFrameQuadrupole;

float *pInducedDipole;
float *pInducedDipolePolar;

float *pInducedDipoleS;
float *pInducedDipolePolarS;

float *pTorque;

float *pWorkArray_3_1;
float *pWorkArray_3_2;
float *pWorkArray_1_1;
float *pWorkArray_1_2;

int vdwUsePBC;
float vdwCutoff;
float vdwCutoff2;
float vdwTaperCutoff;
float vdwTaperCutoff2;
float vdwTaperDelta;


float vdwTaperTable[101];
float vdw_dTaperTable[101];

unsigned amoebaVdwNonReductions;
int *pAmoebaVdwNonReductionID;
unsigned *pVdwWorkUnit;

unsigned amoebaVdwReductions;
struct int4 *pAmoebaVdwReductionID;
float *pAmoebaVdwReduction;
int *pVdwExclusionIndicesIndex;
int *pVdwExclusionIndices;



float epso;
float epsh;
float rmino;
float rminh;
float awater;
float shctd;
float dispoff;
float totalMaxWcaDispersionEnergy;
struct float2 *pWcaDispersionRadiusEpsilon;


int *pScaleIndicesIndex;
int *pD_ScaleIndices;
struct int2 *pP_ScaleIndices;
struct int2 *pM_ScaleIndices;

float electric;
float gkc;

float dielec;
float dwater;
float fc;
float fd;
float fq;



struct float4 *pThetai1;
struct float4 *pThetai2;
struct float4 *pThetai3;
struct int4 *pIgrid;
float *pPhi;
float *pPhid;
float *pPhip;
float *pPhidp;};
# 37 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//amoebaGpuTypes.h"
struct _amoebaGpuContext {

struct _gpuContext *gpuContext;
struct cudaAmoebaGmxSimulation amoebaSim;

FILE *log;

struct _Z10CUDAStreamI4int4E *psAmoebaBondID;
struct _Z10CUDAStreamI6float2E *psAmoebaBondParameter;

struct _Z10CUDAStreamI4int4E *psAmoebaUreyBradleyID;
struct _Z10CUDAStreamI6float2E *psAmoebaUreyBradleyParameter;

struct _Z10CUDAStreamI4int4E *psAmoebaAngleID1;
struct _Z10CUDAStreamI4int2E *psAmoebaAngleID2;
struct _Z10CUDAStreamI6float2E *psAmoebaAngleParameter;

struct _Z10CUDAStreamI4int4E *psAmoebaInPlaneAngleID1;
struct _Z10CUDAStreamI4int4E *psAmoebaInPlaneAngleID2;
struct _Z10CUDAStreamI6float2E *psAmoebaInPlaneAngleParameter;

struct _Z10CUDAStreamI4int4E *psAmoebaTorsionID1;
struct _Z10CUDAStreamI4int4E *psAmoebaTorsionID2;
struct _Z10CUDAStreamI6float4E *psAmoebaTorsionParameter1;
struct _Z10CUDAStreamI6float2E *psAmoebaTorsionParameter2;

struct _Z10CUDAStreamI4int4E *psAmoebaPiTorsionID1;
struct _Z10CUDAStreamI4int4E *psAmoebaPiTorsionID2;
struct _Z10CUDAStreamI4int4E *psAmoebaPiTorsionID3;
struct _Z10CUDAStreamIfE *psAmoebaPiTorsionParameter;

struct _Z10CUDAStreamI4int4E *psAmoebaStretchBendID1;
struct _Z10CUDAStreamI4int2E *psAmoebaStretchBendID2;
struct _Z10CUDAStreamI6float4E *psAmoebaStretchBendParameter;

struct _Z10CUDAStreamI4int4E *psAmoebaOutOfPlaneBendID1;
struct _Z10CUDAStreamI4int4E *psAmoebaOutOfPlaneBendID2;
struct _Z10CUDAStreamIfE *psAmoebaOutOfPlaneBendParameter;

struct _Z10CUDAStreamI4int4E *psAmoebaTorsionTorsionID1;
struct _Z10CUDAStreamI4int4E *psAmoebaTorsionTorsionID2;
struct _Z10CUDAStreamI4int4E *psAmoebaTorsionTorsionID3;
struct _Z10CUDAStreamI6float4E *psAmoebaTorsionTorsionGrids;

unsigned workUnits;



struct _Z10CUDAStreamIfE *psWorkArray_3_1;
struct _Z10CUDAStreamIfE *psWorkArray_3_2;
struct _Z10CUDAStreamIfE *psWorkArray_3_3;
struct _Z10CUDAStreamIfE *psWorkArray_3_4;

struct _Z10CUDAStreamIfE *psWorkArray_1_1;
struct _Z10CUDAStreamIfE *psWorkArray_1_2;

struct _Z10CUDAStreamIiE *psScalingIndicesIndex;
struct _Z10CUDAStreamIiE *ps_D_ScaleIndices;
struct _Z10CUDAStreamI4int2E *ps_P_ScaleIndices;
struct _Z10CUDAStreamI4int2E *ps_M_ScaleIndices;

int maxCovalentDegreeSz;
float solventDielectric;



struct _Z10CUDAStreamI4int4E *psMultipoleParticlesIdsAndAxisType;



int torqueMapForce4Delete;
struct _Z10CUDAStreamI4int4E *psMultipoleParticlesTorqueBufferIndices;
struct _Z10CUDAStreamI6float4E *psTorqueMapForce4;

struct _Z10CUDAStreamIfE *psMolecularDipole;
struct _Z10CUDAStreamIfE *psMolecularQuadrupole;



struct _Z10CUDAStreamIfE *psLabFrameDipole;
struct _Z10CUDAStreamIfE *psLabFrameQuadrupole;



struct _Z10CUDAStreamI6float2E *psDampingFactorAndThole;



struct _ZSt6vectorIiSaIiEE covalentDegree;
struct _ZSt6vectorIiSaIiEE polarizationDegree;



struct _Z10CUDAStreamIfE *psE_Field;
struct _Z10CUDAStreamIfE *psE_FieldPolar;

int multipoleNonbondedMethod;
double cutoffDistance;



int mutualInducedIterativeMethod;
int mutualInducedMaxIterations;
int mutualInducedConverged;
int mutualInducedDone;

int epsilonThreadsPerBlock;
float mutualInducedTargetEpsilon;
float mutualInducedCurrentEpsilon;
struct _Z10CUDAStreamIfE *psInducedDipole;
struct _Z10CUDAStreamIfE *psInducedDipolePolar;
struct _Z10CUDAStreamIfE *psPolarizability;
struct _Z10CUDAStreamIfE *psCurrentEpsilon;



unsigned numberOfSorWorkVectors;
struct _Z10CUDAStreamIfE *psWorkVector[4];



struct _Z10CUDAStreamIfE *psTorque;



struct _Z10CUDAStreamIfE *psGk_Field;
struct _Z10CUDAStreamIfE *psInducedDipoleS;
struct _Z10CUDAStreamIfE *psInducedDipolePolarS;
struct _Z10CUDAStreamIfE *psBorn;
struct _Z10CUDAStreamIfE *psBornPolar;

int includeObcCavityTerm;



struct _Z10CUDAStreamI6float2E *psVdwSigmaEpsilon;

struct _Z10CUDAStreamIiE *psAmoebaVdwNonReductionID;
struct _Z10CUDAStreamI4int4E *psAmoebaVdwReductionID;
struct _Z10CUDAStreamIfE *psAmoebaVdwReduction;
struct _Z10CUDAStreamI6float4E *psAmoebaVdwCoordinates;

struct _Z10CUDAStreamIjE *psVdwWorkUnit;
struct _Z10CUDAStreamIiE *psVdwExclusionIndicesIndex;
struct _Z10CUDAStreamIiE *psVdwExclusionIndices;

int vdwSigmaCombiningRule;
int vdwEpsilonCombiningRule;
struct _ZSt6vectorIS_IiSaIiEESaIS1_EE vdwExclusions;



struct _Z10CUDAStreamI6float2E *psWcaDispersionRadiusEpsilon;



struct _Z10CUDAStreamI6float4E *psThetai1;
struct _Z10CUDAStreamI6float4E *psThetai2;
struct _Z10CUDAStreamI6float4E *psThetai3;
struct _Z10CUDAStreamI4int4E *psIgrid;
struct _Z10CUDAStreamIfE *psPhi;
struct _Z10CUDAStreamIfE *psPhid;
struct _Z10CUDAStreamIfE *psPhip;
struct _Z10CUDAStreamIfE *psPhidp;};


typedef struct _amoebaGpuContext *amoebaGpuContext;
# 42 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//amoebaCudaKernels.h"
typedef struct _ZSt6vectorIS_IdSaIdEESaIS1_EE VectorOfDoubleVectors;
# 53 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
struct GrycukParticle {

float x;
float y;
float z;

float radius;
float scaledRadius;

float bornSum;};
# 65 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/cudatypes.h"
struct _Z10CUDAStreamIiE { struct SoADeviceObject __b_15SoADeviceObject;

unsigned _length;
unsigned _subStreams;
unsigned _stride;
int **_pSysStream;
int **_pDevStream;
int *_pSysData;
int *_pDevData;
_ZSt6string _name;};
# 65 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/cudatypes.h"
struct _Z10CUDAStreamIjE { struct SoADeviceObject __b_15SoADeviceObject;

unsigned _length;
unsigned _subStreams;
unsigned _stride;
unsigned **_pSysStream;
unsigned **_pDevStream;
unsigned *_pSysData;
unsigned *_pDevData;
_ZSt6string _name;};
# 260 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
struct GrycukChainRuleParticle {

float x;
float y;
float z;

float radius;
float scaledRadius;

float bornRadius;
float bornForce;

float force[3];};
# 65 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/cudatypes.h"
struct _Z10CUDAStreamIfE { struct SoADeviceObject __b_15SoADeviceObject;

unsigned _length;
unsigned _subStreams;
unsigned _stride;
float **_pSysStream;
float **_pDevStream;
float *_pSysData;
float *_pDevData;
_ZSt6string _name;};
# 59 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/exception" 3
struct _ZSt9exception { const long *__vptr;};
# 54 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/new" 3
struct _ZSt9bad_alloc { struct _ZSt9exception __b_St9exception;};
# 89 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
typedef size_t _ZNSaIcE9size_typeE;
# 45 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stringfwd.h" 3
struct _ZSaIcE {char __nv_no_debug_dummy_end_padding_0;};
# 112 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/basic_string.h" 3
typedef struct _ZSaIcE _ZNSs14allocator_typeE;
typedef _ZNSaIcE9size_typeE _ZNSs9size_typeE;
# 140 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/basic_string.h" 3
struct _ZNSs9_Rep_baseE {

_ZNSs9size_typeE _M_length;
_ZNSs9size_typeE _M_capacity;
_Atomic_word _M_refcount;char __nv_no_debug_dummy_end_padding_0[4];};


struct _ZNSs4_RepE { struct _ZNSs9_Rep_baseE __b_NSs9_Rep_baseE;};
# 537 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/ios_base.h" 3
struct _ZNSt8ios_base4InitE {char __nv_no_debug_dummy_end_padding_0;};
# 99 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
typedef struct _ZSaIiE _ZNSaIiE6rebindIiE5otherE;
# 86 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
struct _ZSaIiE {char __nv_no_debug_dummy_end_padding_0;};
# 71 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
typedef _ZNSaIiE6rebindIiE5otherE _ZNSt12_Vector_baseIiSaIiEE14_Tp_alloc_typeE;
# 181 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
typedef int _ZNSt6vectorIiSaIiEE10value_typeE;
typedef _ZNSaIiE7pointerE _ZNSt6vectorIiSaIiEE7pointerE;



typedef struct _ZN9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEE _ZNSt6vectorIiSaIiEE8iteratorE;




typedef size_t _ZNSt6vectorIiSaIiEE9size_typeE;
# 99 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
typedef struct _ZSaIPN6OpenMM13CudaForceInfoEE _ZNSaIPN6OpenMM13CudaForceInfoEE6rebindIS1_E5otherE;
# 86 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
struct _ZSaIPN6OpenMM13CudaForceInfoEE {char __nv_no_debug_dummy_end_padding_0;};
# 71 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
typedef _ZNSaIPN6OpenMM13CudaForceInfoEE6rebindIS1_E5otherE _ZNSt12_Vector_baseIPN6OpenMM13CudaForceInfoESaIS2_EE14_Tp_alloc_typeE;
# 99 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
typedef struct _ZSaISt6vectorIiSaIiEEE _ZNSaISt6vectorIiSaIiEEE6rebindIS1_E5otherE;
# 86 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
struct _ZSaISt6vectorIiSaIiEEE {char __nv_no_debug_dummy_end_padding_0;};
# 71 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
typedef _ZNSaISt6vectorIiSaIiEEE6rebindIS1_E5otherE _ZNSt12_Vector_baseISt6vectorIiSaIiEESaIS2_EE14_Tp_alloc_typeE;
# 99 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
typedef struct _ZSaI16gpuMoleculeGroupE _ZNSaI16gpuMoleculeGroupE6rebindIS_E5otherE;
# 86 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
struct _ZSaI16gpuMoleculeGroupE {char __nv_no_debug_dummy_end_padding_0;};
# 71 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
typedef _ZNSaI16gpuMoleculeGroupE6rebindIS_E5otherE _ZNSt12_Vector_baseI16gpuMoleculeGroupSaIS0_EE14_Tp_alloc_typeE;
# 99 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
typedef struct _ZSaI4int3E _ZNSaI4int3E6rebindIS_E5otherE;
# 86 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
struct _ZSaI4int3E {char __nv_no_debug_dummy_end_padding_0;};
# 71 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
typedef _ZNSaI4int3E6rebindIS_E5otherE _ZNSt12_Vector_baseI4int3SaIS0_EE14_Tp_alloc_typeE;
# 91 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
typedef struct _ZSt6vectorIdSaIdEE *_ZNSaISt6vectorIdSaIdEEE7pointerE;
# 99 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
typedef struct _ZSaISt6vectorIdSaIdEEE _ZNSaISt6vectorIdSaIdEEE6rebindIS1_E5otherE;
# 86 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
struct _ZSaISt6vectorIdSaIdEEE {char __nv_no_debug_dummy_end_padding_0;};
# 71 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
typedef _ZNSaISt6vectorIdSaIdEEE6rebindIS1_E5otherE _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE14_Tp_alloc_typeE;

struct _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE12_Vector_implE {


_ZNSaISt6vectorIdSaIdEEE7pointerE _M_start;
_ZNSaISt6vectorIdSaIdEEE7pointerE _M_finish;
_ZNSaISt6vectorIdSaIdEEE7pointerE _M_end_of_storage;};
# 69 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE {
# 136 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE12_Vector_implE _M_impl;};
# 170 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt6vectorIS_IdSaIdEESaIS1_EE { struct _ZSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE __b_St12_Vector_baseISt6vectorIdSaIdEESaIS2_EE;};
# 91 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
typedef double *_ZNSaIdE7pointerE;
# 99 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
typedef struct _ZSaIdE _ZNSaIdE6rebindIdE5otherE;
# 86 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
struct _ZSaIdE {char __nv_no_debug_dummy_end_padding_0;};
# 71 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
typedef _ZNSaIdE6rebindIdE5otherE _ZNSt12_Vector_baseIdSaIdEE14_Tp_alloc_typeE;

struct _ZNSt12_Vector_baseIdSaIdEE12_Vector_implE {


_ZNSaIdE7pointerE _M_start;
_ZNSaIdE7pointerE _M_finish;
_ZNSaIdE7pointerE _M_end_of_storage;};
# 69 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt12_Vector_baseIdSaIdEE {
# 136 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZNSt12_Vector_baseIdSaIdEE12_Vector_implE _M_impl;};
# 170 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
struct _ZSt6vectorIdSaIdEE { struct _ZSt12_Vector_baseIdSaIdEE __b_St12_Vector_baseIdSaIdEE;};
# 51 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/ext/new_allocator.h" 3
struct _ZN9__gnu_cxx13new_allocatorIcEE {char __nv_no_debug_dummy_end_padding_0;};


typedef size_t _ZN9__gnu_cxx13new_allocatorIiE9size_typeE;

typedef int *_ZN9__gnu_cxx13new_allocatorIiE7pointerE;
# 51 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/ext/new_allocator.h" 3
struct _ZN9__gnu_cxx13new_allocatorIiEE {char __nv_no_debug_dummy_end_padding_0;}; struct _ZN9__gnu_cxx13new_allocatorIPN6OpenMM13CudaForceInfoEEE {char __nv_no_debug_dummy_end_padding_0;}; struct _ZN9__gnu_cxx13new_allocatorISt6vectorIiSaIiEEEE {char __nv_no_debug_dummy_end_padding_0;}; struct _ZN9__gnu_cxx13new_allocatorI16gpuMoleculeGroupEE {char __nv_no_debug_dummy_end_padding_0;}; struct _ZN9__gnu_cxx13new_allocatorI4int3EE {char __nv_no_debug_dummy_end_padding_0;}; struct _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEEE {char __nv_no_debug_dummy_end_padding_0;};
# 668 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_iterator.h" 3
struct _ZN9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEE {


_ZNSt6vectorIiSaIiEE7pointerE _M_current;};
# 51 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/ext/new_allocator.h" 3
struct _ZN9__gnu_cxx13new_allocatorIdEE {char __nv_no_debug_dummy_end_padding_0;};
# 44 "/home/saifmulla/openmm/OpenMM/openmmapi/include/openmm/OpenMMException.h"
struct _ZN6OpenMM15OpenMMExceptionE { struct _ZSt9exception __b_St9exception;
# 54 "/home/saifmulla/openmm/OpenMM/openmmapi/include/openmm/OpenMMException.h"
_ZSt6string message;};
void *memcpy(void*, const void*, size_t); void *memset(void*, int, size_t);
# 989 "/usr/local/cuda-5.0/include/cuda_runtime_api.h"
extern enum cudaError cudaGetLastError(void);
# 1044 "/usr/local/cuda-5.0/include/cuda_runtime_api.h"
extern const char *cudaGetErrorString(enum cudaError);
# 2049 "/usr/local/cuda-5.0/include/cuda_runtime_api.h"
extern enum cudaError cudaConfigureCall(struct dim3, struct dim3, size_t, struct CUstream_st *);
# 2320 "/usr/local/cuda-5.0/include/cuda_runtime_api.h"
extern enum cudaError cudaMalloc(void **, size_t);
# 3610 "/usr/local/cuda-5.0/include/cuda_runtime_api.h"
extern enum cudaError cudaMemcpyToSymbol(const void *, const void *, size_t, size_t, enum cudaMemcpyKind);
# 3645 "/usr/local/cuda-5.0/include/cuda_runtime_api.h"
extern enum cudaError cudaMemcpyFromSymbol(void *, const void *, size_t, size_t, enum cudaMemcpyKind);
# 497 "/usr/include/pthread.h" 3
extern __attribute__((visibility("default"))) int pthread_cancel(pthread_t);
# 127 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/x86_64-redhat-linux/bits/gthr-default.h" 3
static __attribute__((__weakref__("pthread_cancel"))) __attribute__((visibility("default"))) int _Z22__gthrw_pthread_cancelm(pthread_t);
# 238 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/x86_64-redhat-linux/bits/gthr-default.h" 3
static __inline__ __attribute__((visibility("default"))) int _Z18__gthread_active_pv(void);
extern int setjmp();
extern void __exception_caught();
# 154 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//amoebaCudaKernels.h"
extern void _Z22cudaLoadCudaFloatArrayiiP10CUDAStreamIfERSt6vectorIS2_IdSaIdEESaIS4_EEPif(int, int, struct _Z10CUDAStreamIfE *, VectorOfDoubleVectors *, int *, float);


extern void _Z36cudaWriteVectorOfDoubleVectorsToFileRKSsRSt6vectorIiSaIiEERS1_IS1_IdSaIdEESaIS6_EE(const _ZSt6string *, struct _ZSt6vectorIiSaIiEE *, VectorOfDoubleVectors *);
# 170 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//amoebaCudaKernels.h"
extern unsigned _Z18getThreadsPerBlockP17_amoebaGpuContextjj(amoebaGpuContext, unsigned, unsigned);




extern void _Z29reduceAndCopyCUDAStreamFloat4P10CUDAStreamI6float4EPS_IfEf(struct _Z10CUDAStreamI6float4E *, struct _Z10CUDAStreamIfE *, float);
# 33 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
extern void _Z27SetCalculateAmoebaGrycukSimP17_amoebaGpuContext(amoebaGpuContext);
# 317 "/usr/local/cuda-5.0/include/cuda_runtime.h"
extern  __attribute__((__weak__)) /* COMDAT group: _Z18cudaMemcpyToSymbolI17cudaGmxSimulationE9cudaErrorRKT_PKvmm14cudaMemcpyKind */ __inline__ enum cudaError _Z18cudaMemcpyToSymbolI17cudaGmxSimulationE9cudaErrorRKT_PKvmm14cudaMemcpyKind(const struct cudaGmxSimulation *, const void *, size_t, size_t, enum cudaMemcpyKind);
# 317 "/usr/local/cuda-5.0/include/cuda_runtime.h"
extern  __attribute__((__weak__)) /* COMDAT group: _Z18cudaMemcpyToSymbolI23cudaAmoebaGmxSimulationE9cudaErrorRKT_PKvmm14cudaMemcpyKind */ __inline__ enum cudaError _Z18cudaMemcpyToSymbolI23cudaAmoebaGmxSimulationE9cudaErrorRKT_PKvmm14cudaMemcpyKind(const struct cudaAmoebaGmxSimulation *, const void *, size_t, size_t, enum cudaMemcpyKind);
extern void *__throw_setup_dtor();
extern __attribute__((__noreturn__)) void __throw();
# 43 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
extern void _Z27GetCalculateAmoebaGrycukSimP17_amoebaGpuContext(amoebaGpuContext);
# 415 "/usr/local/cuda-5.0/include/cuda_runtime.h"
extern  __attribute__((__weak__)) /* COMDAT group: _Z20cudaMemcpyFromSymbolI17cudaGmxSimulationE9cudaErrorPvRKT_mm14cudaMemcpyKind */ __inline__ enum cudaError _Z20cudaMemcpyFromSymbolI17cudaGmxSimulationE9cudaErrorPvRKT_mm14cudaMemcpyKind(void *, const struct cudaGmxSimulation *, size_t, size_t, enum cudaMemcpyKind);
# 415 "/usr/local/cuda-5.0/include/cuda_runtime.h"
extern  __attribute__((__weak__)) /* COMDAT group: _Z20cudaMemcpyFromSymbolI23cudaAmoebaGmxSimulationE9cudaErrorPvRKT_mm14cudaMemcpyKind */ __inline__ enum cudaError _Z20cudaMemcpyFromSymbolI23cudaAmoebaGmxSimulationE9cudaErrorPvRKT_mm14cudaMemcpyKind(void *, const struct cudaAmoebaGmxSimulation *, size_t, size_t, enum cudaMemcpyKind);
# 188 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
extern void _Z24kReduceGrycukGbsaBornSumP17_amoebaGpuContext(amoebaGpuContext);
# 224 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
extern void _Z31kCalculateAmoebaGrycukBornRadiiP17_amoebaGpuContext(amoebaGpuContext);
# 379 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
extern void _Z27kCalculateGrycukGbsaForces2P17_amoebaGpuContext(amoebaGpuContext);
extern __attribute__((__noreturn__)) void __rethrow();
extern void __suppress_optim_on_vars_in_try();
extern int __cudaLaunch();
extern int __cudaSetupArgSimple();
# 98 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/cudatypes.h"
extern  __attribute__((__weak__)) /* COMDAT group: _ZN10CUDAStreamIfEC1EjiSs */ void _ZN10CUDAStreamIfEC1EjiSs(struct _Z10CUDAStreamIfE *const, unsigned, int, _ZSt6string *);
extern  __attribute__((__weak__)) /* COMDAT group: _ZN10CUDAStreamIfEC2EjiSs */ void _ZN10CUDAStreamIfEC2EjiSs(struct _Z10CUDAStreamIfE *const, unsigned, int, _ZSt6string *);
# 122 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/cudatypes.h"
extern  __attribute__((__weak__)) /* COMDAT group: _ZN10CUDAStreamIfE8AllocateEv */ void _ZN10CUDAStreamIfE8AllocateEv(struct _Z10CUDAStreamIfE *const);
# 62 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/exception" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt9exceptionC1Ev */ __inline__ __attribute__((visibility("default"))) void _ZNSt9exceptionC1Ev(struct _ZSt9exception *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt9exceptionC2Ev */ __inline__ __attribute__((visibility("default"))) void _ZNSt9exceptionC2Ev(struct _ZSt9exception *const);
# 63 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/exception" 3
extern __attribute__((visibility("default"))) void _ZNSt9exceptionD1Ev(struct _ZSt9exception *const);
extern __attribute__((visibility("default"))) void _ZNSt9exceptionD2Ev(struct _ZSt9exception *const);
# 101 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
extern __inline__ __attribute__((visibility("default"))) void _ZNSaIcEC1Ev(struct _ZSaIcE *const);
extern __inline__ __attribute__((visibility("default"))) void _ZNSaIcEC2Ev(struct _ZSaIcE *const);
# 109 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
extern __inline__ __attribute__((visibility("default"))) void _ZNSaIcED1Ev(struct _ZSaIcE *const);
extern __inline__ __attribute__((visibility("default"))) void _ZNSaIcED2Ev(struct _ZSaIcE *const);
# 436 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/basic_string.h" 3
extern __attribute__((visibility("default"))) void _ZNSsC1ERKSs(struct _ZSs *const, const struct _ZSs *);
# 471 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/basic_string.h" 3
extern __attribute__((visibility("default"))) void _ZNSsC1EPKcRKSaIcE(struct _ZSs *const, const char *, const struct _ZSaIcE *);
# 502 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/basic_string.h" 3
extern __inline__ __attribute__((visibility("default"))) void _ZNSsD1Ev(struct _ZSs *const);
extern __inline__ __attribute__((visibility("default"))) void _ZNSsD2Ev(struct _ZSs *const);
# 860 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/basic_string.h" 3
extern __attribute__((visibility("default"))) struct _ZSs *_ZNSs6appendEPKcm(struct _ZSs *const, const char *, _ZNSs9size_typeE);
# 240 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/basic_string.h" 3
extern __attribute__((visibility("default"))) void _ZNSs4_Rep10_M_destroyERKSaIcE(struct _ZNSs4_RepE *const, const struct _ZSaIcE *);
# 257 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/basic_string.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSs12_Alloc_hiderD1Ev */ __inline__ __attribute__((visibility("default"))) void _ZNSs12_Alloc_hiderD1Ev(struct _ZNSs12_Alloc_hiderE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSs12_Alloc_hiderD2Ev */ __inline__ __attribute__((visibility("default"))) void _ZNSs12_Alloc_hiderD2Ev(struct _ZNSs12_Alloc_hiderE *const);
# 541 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/ios_base.h" 3
extern __attribute__((visibility("default"))) void _ZNSt8ios_base4InitC1Ev(struct _ZNSt8ios_base4InitE *const);
extern __attribute__((visibility("default"))) void _ZNSt8ios_base4InitD1Ev(struct _ZNSt8ios_base4InitE *const);
# 101 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSaIiEC1Ev */ __inline__ void _ZNSaIiEC1Ev(struct _ZSaIiE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSaIiEC2Ev */ __inline__ void _ZNSaIiEC2Ev(struct _ZSaIiE *const);
# 109 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSaIiED1Ev */ __inline__ void _ZNSaIiED1Ev(struct _ZSaIiE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSaIiED2Ev */ __inline__ void _ZNSaIiED2Ev(struct _ZSaIiE *const);
# 104 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseIiSaIiEEC1Ev */ __inline__ void _ZNSt12_Vector_baseIiSaIiEEC1Ev(struct _ZSt12_Vector_baseIiSaIiEE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseIiSaIiEEC2Ev */ __inline__ void _ZNSt12_Vector_baseIiSaIiEEC2Ev(struct _ZSt12_Vector_baseIiSaIiEE *const);
# 131 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseIiSaIiEED1Ev */ __inline__ void _ZNSt12_Vector_baseIiSaIiEED1Ev(struct _ZSt12_Vector_baseIiSaIiEE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseIiSaIiEED2Ev */ __inline__ void _ZNSt12_Vector_baseIiSaIiEED2Ev(struct _ZSt12_Vector_baseIiSaIiEE *const);
# 73 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseIiSaIiEE12_Vector_implD1Ev */ __inline__ void _ZNSt12_Vector_baseIiSaIiEE12_Vector_implD1Ev(struct _ZNSt12_Vector_baseIiSaIiEE12_Vector_implE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseIiSaIiEE12_Vector_implD2Ev */ __inline__ void _ZNSt12_Vector_baseIiSaIiEE12_Vector_implD2Ev(struct _ZNSt12_Vector_baseIiSaIiEE12_Vector_implE *const);
# 207 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt6vectorIiSaIiEEC1Ev */ __inline__ void _ZNSt6vectorIiSaIiEEC1Ev(struct _ZSt6vectorIiSaIiEE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt6vectorIiSaIiEEC2Ev */ __inline__ void _ZNSt6vectorIiSaIiEEC2Ev(struct _ZSt6vectorIiSaIiEE *const);
# 312 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt6vectorIiSaIiEED1Ev */ __inline__ void _ZNSt6vectorIiSaIiEED1Ev(struct _ZSt6vectorIiSaIiEE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt6vectorIiSaIiEED2Ev */ __inline__ void _ZNSt6vectorIiSaIiEED2Ev(struct _ZSt6vectorIiSaIiEE *const);
# 733 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt6vectorIiSaIiEE9push_backERKi */ __inline__ void _ZNSt6vectorIiSaIiEE9push_backERKi(struct _ZSt6vectorIiSaIiEE *const, const _ZNSt6vectorIiSaIiEE10value_typeE *);
# 296 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/vector.tcc" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt6vectorIiSaIiEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPiS1_EERKi */ void _ZNSt6vectorIiSaIiEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPiS1_EERKi(struct _ZSt6vectorIiSaIiEE *const, _ZNSt6vectorIiSaIiEE8iteratorE, const _ZNSt6vectorIiSaIiEE10value_typeE *);
# 101 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSaISt6vectorIdSaIdEEEC1Ev */ __inline__ void _ZNSaISt6vectorIdSaIdEEEC1Ev(struct _ZSaISt6vectorIdSaIdEEE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSaISt6vectorIdSaIdEEEC2Ev */ __inline__ void _ZNSaISt6vectorIdSaIdEEEC2Ev(struct _ZSaISt6vectorIdSaIdEEE *const);
# 109 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSaISt6vectorIdSaIdEEED1Ev */ __inline__ void _ZNSaISt6vectorIdSaIdEEED1Ev(struct _ZSaISt6vectorIdSaIdEEE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSaISt6vectorIdSaIdEEED2Ev */ __inline__ void _ZNSaISt6vectorIdSaIdEEED2Ev(struct _ZSaISt6vectorIdSaIdEEE *const);
# 104 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EEC1Ev */ __inline__ void _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EEC1Ev(struct _ZSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EEC2Ev */ __inline__ void _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EEC2Ev(struct _ZSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE *const);
# 131 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EED1Ev */ __inline__ void _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EED1Ev(struct _ZSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EED2Ev */ __inline__ void _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EED2Ev(struct _ZSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE *const);
# 73 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE12_Vector_implD1Ev */ __inline__ void _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE12_Vector_implD1Ev(struct _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE12_Vector_implE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE12_Vector_implD2Ev */ __inline__ void _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE12_Vector_implD2Ev(struct _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE12_Vector_implE *const);
# 207 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt6vectorIS_IdSaIdEESaIS1_EEC1Ev */ __inline__ void _ZNSt6vectorIS_IdSaIdEESaIS1_EEC1Ev(struct _ZSt6vectorIS_IdSaIdEESaIS1_EE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt6vectorIS_IdSaIdEESaIS1_EEC2Ev */ __inline__ void _ZNSt6vectorIS_IdSaIdEESaIS1_EEC2Ev(struct _ZSt6vectorIS_IdSaIdEESaIS1_EE *const);
# 312 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt6vectorIS_IdSaIdEESaIS1_EED1Ev */ __inline__ void _ZNSt6vectorIS_IdSaIdEESaIS1_EED1Ev(struct _ZSt6vectorIS_IdSaIdEESaIS1_EE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt6vectorIS_IdSaIdEESaIS1_EED2Ev */ __inline__ void _ZNSt6vectorIS_IdSaIdEESaIS1_EED2Ev(struct _ZSt6vectorIS_IdSaIdEESaIS1_EE *const);
# 109 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSaIdED1Ev */ __inline__ void _ZNSaIdED1Ev(struct _ZSaIdE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSaIdED2Ev */ __inline__ void _ZNSaIdED2Ev(struct _ZSaIdE *const);
# 131 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseIdSaIdEED1Ev */ __inline__ void _ZNSt12_Vector_baseIdSaIdEED1Ev(struct _ZSt12_Vector_baseIdSaIdEE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseIdSaIdEED2Ev */ __inline__ void _ZNSt12_Vector_baseIdSaIdEED2Ev(struct _ZSt12_Vector_baseIdSaIdEE *const);
# 73 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseIdSaIdEE12_Vector_implD1Ev */ __inline__ void _ZNSt12_Vector_baseIdSaIdEE12_Vector_implD1Ev(struct _ZNSt12_Vector_baseIdSaIdEE12_Vector_implE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseIdSaIdEE12_Vector_implD2Ev */ __inline__ void _ZNSt12_Vector_baseIdSaIdEE12_Vector_implD2Ev(struct _ZNSt12_Vector_baseIdSaIdEE12_Vector_implE *const);
# 66 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/ext/new_allocator.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIcEC1Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorIcEC1Ev(struct _ZN9__gnu_cxx13new_allocatorIcEE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIcEC2Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorIcEC2Ev(struct _ZN9__gnu_cxx13new_allocatorIcEE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIcEC1ERKS1_ */ __inline__ void _ZN9__gnu_cxx13new_allocatorIcEC1ERKS1_(struct _ZN9__gnu_cxx13new_allocatorIcEE *const, const struct _ZN9__gnu_cxx13new_allocatorIcEE *);
extern  __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIcEC2ERKS1_ */ __inline__ void _ZN9__gnu_cxx13new_allocatorIcEC2ERKS1_(struct _ZN9__gnu_cxx13new_allocatorIcEE *const, const struct _ZN9__gnu_cxx13new_allocatorIcEE *);



extern  __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIcED1Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorIcED1Ev(struct _ZN9__gnu_cxx13new_allocatorIcEE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIcED2Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorIcED2Ev(struct _ZN9__gnu_cxx13new_allocatorIcEE *const);
# 66 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/ext/new_allocator.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIiEC1Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorIiEC1Ev(struct _ZN9__gnu_cxx13new_allocatorIiEE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIiEC2Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorIiEC2Ev(struct _ZN9__gnu_cxx13new_allocatorIiEE *const);





extern  __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIiED1Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorIiED1Ev(struct _ZN9__gnu_cxx13new_allocatorIiEE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIiED2Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorIiED2Ev(struct _ZN9__gnu_cxx13new_allocatorIiEE *const);
# 66 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/ext/new_allocator.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEEC1Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEEC1Ev(struct _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEEE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEEC2Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEEC2Ev(struct _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEEE *const);





extern  __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEED1Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEED1Ev(struct _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEEE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEED2Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEED2Ev(struct _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEEE *const);
# 73 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/ext/new_allocator.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIdED1Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorIdED1Ev(struct _ZN9__gnu_cxx13new_allocatorIdEE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIdED2Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorIdED2Ev(struct _ZN9__gnu_cxx13new_allocatorIdEE *const);
# 48 "/home/saifmulla/openmm/OpenMM/openmmapi/include/openmm/OpenMMException.h"
extern  __attribute__((__weak__)) /* COMDAT group: _ZN6OpenMM15OpenMMExceptionD1Ev */ __inline__ void _ZN6OpenMM15OpenMMExceptionD1Ev(struct _ZN6OpenMM15OpenMMExceptionE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZN6OpenMM15OpenMMExceptionD0Ev */ __inline__ void _ZN6OpenMM15OpenMMExceptionD0Ev(struct _ZN6OpenMM15OpenMMExceptionE *const);
extern  __attribute__((__weak__)) /* COMDAT group: _ZN6OpenMM15OpenMMExceptionD2Ev */ __inline__ void _ZN6OpenMM15OpenMMExceptionD2Ev(struct _ZN6OpenMM15OpenMMExceptionE *const);
# 47 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/functexcept.h" 3
extern __attribute__((__noreturn__)) __attribute__((visibility("default"))) void _ZSt17__throw_bad_allocv(void);
# 67 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/functexcept.h" 3
extern __attribute__((__noreturn__)) __attribute__((visibility("default"))) void _ZSt20__throw_length_errorPKc(const char *);
# 2198 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/basic_string.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_ */ __inline__ void _ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_(struct _ZSs *, const struct _ZSs *, const char *);
# 186 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_algobase.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZSt3minIjERKT_S2_S2_ */ __inline__ const unsigned *_ZSt3minIjERKT_S2_S2_(const unsigned *, const unsigned *);
# 119 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_construct.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZSt8_DestroyIPiEvT_S1_ */ __inline__ void _ZSt8_DestroyIPiEvT_S1_(int *, int *);
# 582 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_algobase.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZSt22__copy_move_backward_aILb0EPiS0_ET1_T0_S2_S1_ */ __inline__ int *_ZSt22__copy_move_backward_aILb0EPiS0_ET1_T0_S2_S1_(int *, int *, int *);
# 209 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_algobase.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZSt3maxImERKT_S2_S2_ */ __inline__ const _ZNSt6vectorIiSaIiEE9size_typeE *_ZSt3maxImERKT_S2_S2_(const _ZNSt6vectorIiSaIiEE9size_typeE *, const _ZNSt6vectorIiSaIiEE9size_typeE *);
# 106 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_uninitialized.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZSt18uninitialized_copyIPiS0_ET0_T_S2_S1_ */ __inline__ int *_ZSt18uninitialized_copyIPiS0_ET0_T_S2_S1_(int *, int *, int *);
# 386 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_algobase.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZSt13__copy_move_aILb0EPiS0_ET1_T0_S2_S1_ */ __inline__ int *_ZSt13__copy_move_aILb0EPiS0_ET1_T0_S2_S1_(int *, int *, int *);
# 119 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_construct.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZSt8_DestroyIPSt6vectorIdSaIdEEEvT_S4_ */ __inline__ void _ZSt8_DestroyIPSt6vectorIdSaIdEEEvT_S4_(struct _ZSt6vectorIdSaIdEE *, struct _ZSt6vectorIdSaIdEE *);
# 119 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_construct.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: _ZSt8_DestroyIPdEvT_S1_ */ __inline__ void _ZSt8_DestroyIPdEvT_S1_(double *, double *);
# 75 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/ext/atomicity.h" 3
static __inline__ __attribute__((__unused__)) __attribute__((visibility("default"))) _Atomic_word _ZN9__gnu_cxx27__exchange_and_add_dispatchEPii(_Atomic_word *, int);
extern void __nv_dummy_param_ref();
extern int __cudaRegisterEntry();
extern int __cudaRegisterVariable();
extern int __cudaRegisterBinary();
static void __sti___45_kCalculateAmoebaCudaGrycuk_compute_20_cpp1_ii_e93cfd52(void) __attribute__((__constructor__));
extern int __cxa_atexit();
extern struct __C8 *__curr_eh_stack_entry;
extern unsigned short __eh_curr_region;
static const struct __si_class_type_info _ZTIN6OpenMM15OpenMMExceptionE;
extern int __catch_clause_number;
static const struct __class_type_info _ZTISt9exception;
extern  __attribute__((__weak__)) /* COMDAT group: _ZTSSt9exception */ const char _ZTSSt9exception[13] __attribute__((visibility("default")));
extern  __attribute__((__weak__)) /* COMDAT group: _ZTSN6OpenMM15OpenMMExceptionE */ const char _ZTSN6OpenMM15OpenMMExceptionE[27];
# 170 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/basic_string.h" 3
extern _ZNSs9size_typeE _ZNSs4_Rep20_S_empty_rep_storageE[] __attribute__((visibility("default")));
# 72 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/iostream" 3
static struct _ZNSt8ios_base4InitE _ZSt8__ioinit __attribute__((visibility("default"))) = {0};
extern void *__dso_handle __attribute__((visibility("hidden")));
static const struct __si_class_type_info _ZTIN6OpenMM15OpenMMExceptionE = {{{(_ZTVN10__cxxabiv120__si_class_type_infoE + 2),_ZTSN6OpenMM15OpenMMExceptionE}},(&_ZTISt9exception)};
static const struct __class_type_info _ZTISt9exception = {{(_ZTVN10__cxxabiv117__class_type_infoE + 2),_ZTSSt9exception}};
 __attribute__((__weak__)) /* COMDAT group: _ZTSSt9exception */ const char _ZTSSt9exception[13] __attribute__((visibility("default"))) = "St9exception";
 __attribute__((__weak__)) /* COMDAT group: _ZTSN6OpenMM15OpenMMExceptionE */ const char _ZTSN6OpenMM15OpenMMExceptionE[27] = "N6OpenMM15OpenMMExceptionE";
# 238 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/x86_64-redhat-linux/bits/gthr-default.h" 3
static __inline__ __attribute__((visibility("default"))) int _Z18__gthread_active_pv(void)
{


return (int)(((void *)_Z22__gthrw_pthread_cancelm) != ((void *)0LL));
}
# 33 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
void _Z27SetCalculateAmoebaGrycukSimP17_amoebaGpuContext( amoebaGpuContext amoebaGpu)
{
 enum cudaError __cuda_local_var_59674_17_non_const_status;
 gpuContext __cuda_local_var_59675_16_non_const_gpu;
# 36 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
__cuda_local_var_59675_16_non_const_gpu = (amoebaGpu->gpuContext);
__cuda_local_var_59674_17_non_const_status = (_Z18cudaMemcpyToSymbolI17cudaGmxSimulationE9cudaErrorRKT_PKvmm14cudaMemcpyKind((((const struct cudaGmxSimulation *)&cSim)), ((const void *)(&(__cuda_local_var_59675_16_non_const_gpu->sim))), 1224UL, 0UL, cudaMemcpyHostToDevice));
if (((int)__cuda_local_var_59674_17_non_const_status) != 0) {  struct _ZN6OpenMM15OpenMMExceptionE *__T20;
 struct _ZSs __T21;
 struct _ZSs __T22;
 _ZSt6string __T23;
 struct _ZSaIcE __T24;
 struct _ZN6OpenMM15OpenMMExceptionE *__T25;
 const _ZSt6string *__T26;
# 38 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
(((((__T20 = ((struct _ZN6OpenMM15OpenMMExceptionE *)(__throw_setup_dtor((&_ZTIN6OpenMM15OpenMMExceptionE), 16UL, 0, _ZN6OpenMM15OpenMMExceptionD1Ev)))) , (void)((((__T25 = __T20) , (void)(__T26 = ((_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_((&__T21), ((_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_((&__T22), ((_ZNSsC1EPKcRKSaIcE((&__T23), ((const char *)"SetCalculateAmoebaGrycukSim: cudaMemcpyToSymbol: SetSim copy to cSim failed"), ((_ZNSaIcEC1Ev((&__T24))) , (((const struct _ZSaIcE *)&__T24))))) , (((const struct _ZSs *)&__T23))), ((const char *)" "))) , (((const struct _ZSs *)&__T22))), (cudaGetErrorString(__cuda_local_var_59674_17_non_const_status)))) , (((const _ZSt6string *)&__T21))))) , (void)(((_ZNSt9exceptionC1Ev((&(__T25->__b_St9exception)))) , (void)(((__T25->__b_St9exception).__vptr) = (_ZTVN6OpenMM15OpenMMExceptionE + 2))) , (void)(_ZNSsC1ERKSs((&(__T25->message)), __T26)))) , (void)(__throw()))) , (void)(_ZNSsD1Ev((&__T21)))) , (void)(_ZNSsD1Ev((&__T22)))) , (void)(_ZNSsD1Ev((&__T23)))) , (void)(_ZNSaIcED1Ev((&__T24))); } ;
__cuda_local_var_59674_17_non_const_status = (_Z18cudaMemcpyToSymbolI23cudaAmoebaGmxSimulationE9cudaErrorRKT_PKvmm14cudaMemcpyKind((((const struct cudaAmoebaGmxSimulation *)&cAmoebaSim)), ((const void *)(&(amoebaGpu->amoebaSim))), 1792UL, 0UL, cudaMemcpyHostToDevice));
if (((int)__cuda_local_var_59674_17_non_const_status) != 0) {  struct _ZN6OpenMM15OpenMMExceptionE *__T27;
 struct _ZSs __T28;
 struct _ZSs __T29;
 _ZSt6string __T210;
 struct _ZSaIcE __T211;
 struct _ZN6OpenMM15OpenMMExceptionE *__T212;
 const _ZSt6string *__T213;
# 40 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
(((((__T27 = ((struct _ZN6OpenMM15OpenMMExceptionE *)(__throw_setup_dtor((&_ZTIN6OpenMM15OpenMMExceptionE), 16UL, 0, _ZN6OpenMM15OpenMMExceptionD1Ev)))) , (void)((((__T212 = __T27) , (void)(__T213 = ((_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_((&__T28), ((_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_((&__T29), ((_ZNSsC1EPKcRKSaIcE((&__T210), ((const char *)"SetCalculateAmoebaGrycukSim: cudaMemcpyToSymbol: SetSim copy to cAmoebaSim failed"), ((_ZNSaIcEC1Ev((&__T211))) , (((const struct _ZSaIcE *)&__T211))))) , (((const struct _ZSs *)&__T210))), ((const char *)" "))) , (((const struct _ZSs *)&__T29))), (cudaGetErrorString(__cuda_local_var_59674_17_non_const_status)))) , (((const _ZSt6string *)&__T28))))) , (void)(((_ZNSt9exceptionC1Ev((&(__T212->__b_St9exception)))) , (void)(((__T212->__b_St9exception).__vptr) = (_ZTVN6OpenMM15OpenMMExceptionE + 2))) , (void)(_ZNSsC1ERKSs((&(__T212->message)), __T213)))) , (void)(__throw()))) , (void)(_ZNSsD1Ev((&__T28)))) , (void)(_ZNSsD1Ev((&__T29)))) , (void)(_ZNSsD1Ev((&__T210)))) , (void)(_ZNSaIcED1Ev((&__T211))); } ; 
}
# 317 "/usr/local/cuda-5.0/include/cuda_runtime.h"
 __attribute__((__weak__)) /* COMDAT group: _Z18cudaMemcpyToSymbolI17cudaGmxSimulationE9cudaErrorRKT_PKvmm14cudaMemcpyKind */ __inline__ enum cudaError _Z18cudaMemcpyToSymbolI17cudaGmxSimulationE9cudaErrorRKT_PKvmm14cudaMemcpyKind(
const struct cudaGmxSimulation *symbol, 
const void *src, 
size_t count, 
size_t offset, 
enum cudaMemcpyKind kind)

{
return cudaMemcpyToSymbol(((const void *)symbol), src, count, offset, kind);
}
# 317 "/usr/local/cuda-5.0/include/cuda_runtime.h"
 __attribute__((__weak__)) /* COMDAT group: _Z18cudaMemcpyToSymbolI23cudaAmoebaGmxSimulationE9cudaErrorRKT_PKvmm14cudaMemcpyKind */ __inline__ enum cudaError _Z18cudaMemcpyToSymbolI23cudaAmoebaGmxSimulationE9cudaErrorRKT_PKvmm14cudaMemcpyKind(
const struct cudaAmoebaGmxSimulation *symbol, 
const void *src, 
size_t count, 
size_t offset, 
enum cudaMemcpyKind kind)

{
return cudaMemcpyToSymbol(((const void *)symbol), src, count, offset, kind);
}
# 43 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
void _Z27GetCalculateAmoebaGrycukSimP17_amoebaGpuContext( amoebaGpuContext amoebaGpu)
{
 enum cudaError __cuda_local_var_59684_17_non_const_status;
 gpuContext __cuda_local_var_59685_16_non_const_gpu;
# 46 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
__cuda_local_var_59685_16_non_const_gpu = (amoebaGpu->gpuContext);
__cuda_local_var_59684_17_non_const_status = (_Z20cudaMemcpyFromSymbolI17cudaGmxSimulationE9cudaErrorPvRKT_mm14cudaMemcpyKind(((void *)(&(__cuda_local_var_59685_16_non_const_gpu->sim))), (((const struct cudaGmxSimulation *)&cSim)), 1224UL, 0UL, cudaMemcpyDeviceToHost));
if (((int)__cuda_local_var_59684_17_non_const_status) != 0) {  struct _ZN6OpenMM15OpenMMExceptionE *__T214;
 struct _ZSs __T215;
 struct _ZSs __T216;
 _ZSt6string __T217;
 struct _ZSaIcE __T218;
 struct _ZN6OpenMM15OpenMMExceptionE *__T219;
 const _ZSt6string *__T220;
# 48 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
(((((__T214 = ((struct _ZN6OpenMM15OpenMMExceptionE *)(__throw_setup_dtor((&_ZTIN6OpenMM15OpenMMExceptionE), 16UL, 0, _ZN6OpenMM15OpenMMExceptionD1Ev)))) , (void)((((__T219 = __T214) , (void)(__T220 = ((_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_((&__T215), ((_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_((&__T216), ((_ZNSsC1EPKcRKSaIcE((&__T217), ((const char *)"GetCalculateAmoebaGrycukSim: cudaMemcpyFromSymbol: SetSim copy from cSim failed"), ((_ZNSaIcEC1Ev((&__T218))) , (((const struct _ZSaIcE *)&__T218))))) , (((const struct _ZSs *)&__T217))), ((const char *)" "))) , (((const struct _ZSs *)&__T216))), (cudaGetErrorString(__cuda_local_var_59684_17_non_const_status)))) , (((const _ZSt6string *)&__T215))))) , (void)(((_ZNSt9exceptionC1Ev((&(__T219->__b_St9exception)))) , (void)(((__T219->__b_St9exception).__vptr) = (_ZTVN6OpenMM15OpenMMExceptionE + 2))) , (void)(_ZNSsC1ERKSs((&(__T219->message)), __T220)))) , (void)(__throw()))) , (void)(_ZNSsD1Ev((&__T215)))) , (void)(_ZNSsD1Ev((&__T216)))) , (void)(_ZNSsD1Ev((&__T217)))) , (void)(_ZNSaIcED1Ev((&__T218))); } ;
__cuda_local_var_59684_17_non_const_status = (_Z20cudaMemcpyFromSymbolI23cudaAmoebaGmxSimulationE9cudaErrorPvRKT_mm14cudaMemcpyKind(((void *)(&(amoebaGpu->amoebaSim))), (((const struct cudaAmoebaGmxSimulation *)&cAmoebaSim)), 1792UL, 0UL, cudaMemcpyDeviceToHost));
if (((int)__cuda_local_var_59684_17_non_const_status) != 0) {  struct _ZN6OpenMM15OpenMMExceptionE *__T221;
 struct _ZSs __T222;
 struct _ZSs __T223;
 _ZSt6string __T224;
 struct _ZSaIcE __T225;
 struct _ZN6OpenMM15OpenMMExceptionE *__T226;
 const _ZSt6string *__T227;
# 50 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
(((((__T221 = ((struct _ZN6OpenMM15OpenMMExceptionE *)(__throw_setup_dtor((&_ZTIN6OpenMM15OpenMMExceptionE), 16UL, 0, _ZN6OpenMM15OpenMMExceptionD1Ev)))) , (void)((((__T226 = __T221) , (void)(__T227 = ((_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_((&__T222), ((_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_((&__T223), ((_ZNSsC1EPKcRKSaIcE((&__T224), ((const char *)"GetCalculateAmoebaGrycukSim: cudaMemcpyFromSymbol: SetSim copy from cAmoebaSim failed"), ((_ZNSaIcEC1Ev((&__T225))) , (((const struct _ZSaIcE *)&__T225))))) , (((const struct _ZSs *)&__T224))), ((const char *)" "))) , (((const struct _ZSs *)&__T223))), (cudaGetErrorString(__cuda_local_var_59684_17_non_const_status)))) , (((const _ZSt6string *)&__T222))))) , (void)(((_ZNSt9exceptionC1Ev((&(__T226->__b_St9exception)))) , (void)(((__T226->__b_St9exception).__vptr) = (_ZTVN6OpenMM15OpenMMExceptionE + 2))) , (void)(_ZNSsC1ERKSs((&(__T226->message)), __T227)))) , (void)(__throw()))) , (void)(_ZNSsD1Ev((&__T222)))) , (void)(_ZNSsD1Ev((&__T223)))) , (void)(_ZNSsD1Ev((&__T224)))) , (void)(_ZNSaIcED1Ev((&__T225))); } ; 
}
# 415 "/usr/local/cuda-5.0/include/cuda_runtime.h"
 __attribute__((__weak__)) /* COMDAT group: _Z20cudaMemcpyFromSymbolI17cudaGmxSimulationE9cudaErrorPvRKT_mm14cudaMemcpyKind */ __inline__ enum cudaError _Z20cudaMemcpyFromSymbolI17cudaGmxSimulationE9cudaErrorPvRKT_mm14cudaMemcpyKind(
void *dst, 
const struct cudaGmxSimulation *symbol, 
size_t count, 
size_t offset, 
enum cudaMemcpyKind kind)

{
return cudaMemcpyFromSymbol(dst, ((const void *)symbol), count, offset, kind);
}
# 415 "/usr/local/cuda-5.0/include/cuda_runtime.h"
 __attribute__((__weak__)) /* COMDAT group: _Z20cudaMemcpyFromSymbolI23cudaAmoebaGmxSimulationE9cudaErrorPvRKT_mm14cudaMemcpyKind */ __inline__ enum cudaError _Z20cudaMemcpyFromSymbolI23cudaAmoebaGmxSimulationE9cudaErrorPvRKT_mm14cudaMemcpyKind(
void *dst, 
const struct cudaAmoebaGmxSimulation *symbol, 
size_t count, 
size_t offset, 
enum cudaMemcpyKind kind)

{
return cudaMemcpyFromSymbol(dst, ((const void *)symbol), count, offset, kind);
}
# 188 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
void _Z24kReduceGrycukGbsaBornSumP17_amoebaGpuContext( amoebaGpuContext amoebaGpu)
{  struct dim3 __T228;
 unsigned __T229;
 struct dim3 __T230;
# 191 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
(cudaConfigureCall((((void)((__T229 = (((amoebaGpu->gpuContext)->sim).blocks)) , (void)((((__T228.x) = __T229) , (void)((__T228.y) = 1U)) , ((__T228.z) = 1U)))) , __T228), (((void)((((__T230.x) = 384U) , (void)((__T230.y) = 1U)) , (void)((__T230.z) = 1U))) , __T230), 0UL, ((struct CUstream_st *)0LL))) ? ((void)0) : (__device_stub__Z31kReduceGrycukGbsaBornSum_kernelv());
{  enum cudaError __cuda_local_var_59823_19_non_const_status;
# 192 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
__cuda_local_var_59823_19_non_const_status = (cudaGetLastError()); if (((int)__cuda_local_var_59823_19_non_const_status) != 0) {  struct _ZN6OpenMM15OpenMMExceptionE *__T231;
 struct _ZSs __T232;
 struct _ZSs __T233;
 struct _ZSs __T234;
 _ZSt6string __T235;
 struct _ZSaIcE __T236;
 struct _ZN6OpenMM15OpenMMExceptionE *__T237;
 const _ZSt6string *__T238;
# 192 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
((((((__T231 = ((struct _ZN6OpenMM15OpenMMExceptionE *)(__throw_setup_dtor((&_ZTIN6OpenMM15OpenMMExceptionE), 16UL, 0, _ZN6OpenMM15OpenMMExceptionD1Ev)))) , (void)((((__T237 = __T231) , (void)(__T238 = ((_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_((&__T232), ((_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_((&__T233), ((_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_((&__T234), ((_ZNSsC1EPKcRKSaIcE((&__T235), ((const char *)"Error: "), ((_ZNSaIcEC1Ev((&__T236))) , (((const struct _ZSaIcE *)&__T236))))) , (((const struct _ZSs *)&__T235))), (cudaGetErrorString(__cuda_local_var_59823_19_non_const_status)))) , (((const struct _ZSs *)&__T234))), ((const char *)" launching kernel "))) , (((const struct _ZSs *)&__T233))), ((const char *)"kReduceGrycukGbsaBornSum"))) , (((const _ZSt6string *)&__T232))))) , (void)(((_ZNSt9exceptionC1Ev((&(__T237->__b_St9exception)))) , (void)(((__T237->__b_St9exception).__vptr) = (_ZTVN6OpenMM15OpenMMExceptionE + 2))) , (void)(_ZNSsC1ERKSs((&(__T237->message)), __T238)))) , (void)(__throw()))) , (void)(_ZNSsD1Ev((&__T232)))) , (void)(_ZNSsD1Ev((&__T233)))) , (void)(_ZNSsD1Ev((&__T234)))) , (void)(_ZNSsD1Ev((&__T235)))) , (void)(_ZNSaIcED1Ev((&__T236))); } } ;

if (0) {
static int callId = 0;
 int __T239;
 _ZSt6string __T240;
 struct _ZSaIcE __T241;
# 196 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
 gpuContext __cuda_local_var_59827_20_non_const_gpu;
 struct _ZSt6vectorIiSaIiEE __cuda_local_var_59828_26_non_const_fileId;

 VectorOfDoubleVectors __cuda_local_var_59830_31_non_const_outputVector;
# 196 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
__cuda_local_var_59827_20_non_const_gpu = (amoebaGpu->gpuContext);
_ZNSt6vectorIiSaIiEEC1Ev((&__cuda_local_var_59828_26_non_const_fileId));
_ZNSt6vectorIiSaIiEE9push_backERKi((&__cuda_local_var_59828_26_non_const_fileId), ((__T239 = (callId++)) , (((const _ZNSt6vectorIiSaIiEE10value_typeE *)&__T239))));
_ZNSt6vectorIS_IdSaIdEESaIS1_EEC1Ev((&__cuda_local_var_59830_31_non_const_outputVector));
_Z22cudaLoadCudaFloatArrayiiP10CUDAStreamIfERSt6vectorIS2_IdSaIdEESaIS4_EEPif((__cuda_local_var_59827_20_non_const_gpu->natoms), 1, (__cuda_local_var_59827_20_non_const_gpu->psBornRadii), (&__cuda_local_var_59830_31_non_const_outputVector), ((__cuda_local_var_59827_20_non_const_gpu->psAtomIndex)->_pSysData), (1.0F));
((_Z36cudaWriteVectorOfDoubleVectorsToFileRKSsRSt6vectorIiSaIiEERS1_IS1_IdSaIdEESaIS6_EE(((_ZNSsC1EPKcRKSaIcE((((_ZSt6string *)&__T240)), ((const char *)"BornRGry"), ((_ZNSaIcEC1Ev((&__T241))) , (((const struct _ZSaIcE *)&__T241))))) , ((const _ZSt6string *)&__T240)), (&__cuda_local_var_59828_26_non_const_fileId), (&__cuda_local_var_59830_31_non_const_outputVector))) , (void)(_ZNSsD1Ev(((struct _ZSs *)((const _ZSt6string *)&__T240))))) , (void)(_ZNSaIcED1Ev((&__T241)));
_ZNSt6vectorIS_IdSaIdEESaIS1_EED1Ev((&__cuda_local_var_59830_31_non_const_outputVector)); _ZNSt6vectorIiSaIiEED1Ev((&__cuda_local_var_59828_26_non_const_fileId)); } 
}
# 224 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
void _Z31kCalculateAmoebaGrycukBornRadiiP17_amoebaGpuContext( amoebaGpuContext amoebaGpu)
{
# 235 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
static unsigned threadsPerBlock = 0U;
# 229 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
 gpuContext __cuda_local_var_60182_16_non_const_gpu;
# 229 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
__cuda_local_var_60182_16_non_const_gpu = (amoebaGpu->gpuContext);
# 236 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
if (threadsPerBlock == 0U) {  unsigned __T242;
 unsigned __cuda_local_var_60190_22_non_const_maxThreads;
if (((int)(__cuda_local_var_60182_16_non_const_gpu->sm_version)) >= 3) {

__cuda_local_var_60190_22_non_const_maxThreads = 512U; } else  {
if (((int)(__cuda_local_var_60182_16_non_const_gpu->sm_version)) >= 2) {
__cuda_local_var_60190_22_non_const_maxThreads = 128U; } else  {

__cuda_local_var_60190_22_non_const_maxThreads = 64U; } }
threadsPerBlock = (*(_ZSt3minIjERKT_S2_S2_(((__T242 = (_Z18getThreadsPerBlockP17_amoebaGpuContextjj(amoebaGpu, 24U, (__cuda_local_var_60182_16_non_const_gpu->sharedMemoryPerBlock)))) , (((const unsigned *)&__T242))), (((const unsigned *)&__cuda_local_var_60190_22_non_const_maxThreads)))));
}

if (__cuda_local_var_60182_16_non_const_gpu->bOutputBufferPerWarp) {  struct dim3 __T243;
 unsigned __T244;
 struct dim3 __T245;
 unsigned __T246;
# 249 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
(cudaConfigureCall((((void)((__T244 = ((__cuda_local_var_60182_16_non_const_gpu->sim).nonbond_blocks)) , (void)((((__T243.x) = __T244) , (void)((__T243.y) = 1U)) , ((__T243.z) = 1U)))) , __T243), (((void)((__T246 = threadsPerBlock) , (void)((((__T245.x) = __T246) , (void)((__T245.y) = 1U)) , ((__T245.z) = 1U)))) , __T245), (24UL * ((unsigned long)threadsPerBlock)), ((struct CUstream_st *)0LL))) ? ((void)0) : (__device_stub__Z46kCalculateAmoebaGrycukBornRadiiN2ByWarp_kernelPj(((__cuda_local_var_60182_16_non_const_gpu->psWorkUnit)->_pDevData)));
} else  {  struct dim3 __T247;
 unsigned __T248;
 struct dim3 __T249;
 unsigned __T250;
# 251 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
(cudaConfigureCall((((void)((__T248 = ((__cuda_local_var_60182_16_non_const_gpu->sim).nonbond_blocks)) , (void)((((__T247.x) = __T248) , (void)((__T247.y) = 1U)) , ((__T247.z) = 1U)))) , __T247), (((void)((__T250 = threadsPerBlock) , (void)((((__T249.x) = __T250) , (void)((__T249.y) = 1U)) , ((__T249.z) = 1U)))) , __T249), (24UL * ((unsigned long)threadsPerBlock)), ((struct CUstream_st *)0LL))) ? ((void)0) : (__device_stub__Z40kCalculateAmoebaGrycukBornRadiiN2_kernelPj(((__cuda_local_var_60182_16_non_const_gpu->psWorkUnit)->_pDevData)));
}
{  enum cudaError __cuda_local_var_60206_19_non_const_status;
# 253 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
__cuda_local_var_60206_19_non_const_status = (cudaGetLastError()); if (((int)__cuda_local_var_60206_19_non_const_status) != 0) {  struct _ZN6OpenMM15OpenMMExceptionE *__T251;
 struct _ZSs __T252;
 struct _ZSs __T253;
 struct _ZSs __T254;
 _ZSt6string __T255;
 struct _ZSaIcE __T256;
 struct _ZN6OpenMM15OpenMMExceptionE *__T257;
 const _ZSt6string *__T258;
# 253 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
((((((__T251 = ((struct _ZN6OpenMM15OpenMMExceptionE *)(__throw_setup_dtor((&_ZTIN6OpenMM15OpenMMExceptionE), 16UL, 0, _ZN6OpenMM15OpenMMExceptionD1Ev)))) , (void)((((__T257 = __T251) , (void)(__T258 = ((_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_((&__T252), ((_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_((&__T253), ((_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_((&__T254), ((_ZNSsC1EPKcRKSaIcE((&__T255), ((const char *)"Error: "), ((_ZNSaIcEC1Ev((&__T256))) , (((const struct _ZSaIcE *)&__T256))))) , (((const struct _ZSs *)&__T255))), (cudaGetErrorString(__cuda_local_var_60206_19_non_const_status)))) , (((const struct _ZSs *)&__T254))), ((const char *)" launching kernel "))) , (((const struct _ZSs *)&__T253))), ((const char *)"kCalculateAmoebaCudaGrycukN2Forces"))) , (((const _ZSt6string *)&__T252))))) , (void)(((_ZNSt9exceptionC1Ev((&(__T257->__b_St9exception)))) , (void)(((__T257->__b_St9exception).__vptr) = (_ZTVN6OpenMM15OpenMMExceptionE + 2))) , (void)(_ZNSsC1ERKSs((&(__T257->message)), __T258)))) , (void)(__throw()))) , (void)(_ZNSsD1Ev((&__T252)))) , (void)(_ZNSsD1Ev((&__T253)))) , (void)(_ZNSsD1Ev((&__T254)))) , (void)(_ZNSsD1Ev((&__T255)))) , (void)(_ZNSaIcED1Ev((&__T256))); } } ; 


}
# 379 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
void _Z27kCalculateGrycukGbsaForces2P17_amoebaGpuContext( amoebaGpuContext amoebaGpu)
{
# 390 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
static unsigned threadsPerBlock = 0U;
# 384 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
 gpuContext __cuda_local_var_60636_16_non_const_gpu;
# 384 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
__cuda_local_var_60636_16_non_const_gpu = (amoebaGpu->gpuContext);
# 391 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
if (threadsPerBlock == 0U) {  unsigned __T259;
 unsigned __cuda_local_var_60644_22_non_const_maxThreads;
if (((int)(__cuda_local_var_60636_16_non_const_gpu->sm_version)) >= 3) {

__cuda_local_var_60644_22_non_const_maxThreads = 512U; } else  {
if (((int)(__cuda_local_var_60636_16_non_const_gpu->sm_version)) >= 2) {
__cuda_local_var_60644_22_non_const_maxThreads = 128U; } else  {

__cuda_local_var_60644_22_non_const_maxThreads = 64U; } }
threadsPerBlock = (*(_ZSt3minIjERKT_S2_S2_(((__T259 = (_Z18getThreadsPerBlockP17_amoebaGpuContextjj(amoebaGpu, 40U, (__cuda_local_var_60636_16_non_const_gpu->sharedMemoryPerBlock)))) , (((const unsigned *)&__T259))), (((const unsigned *)&__cuda_local_var_60644_22_non_const_maxThreads)))));
}

if (__cuda_local_var_60636_16_non_const_gpu->bOutputBufferPerWarp) {  struct dim3 __T260;
 unsigned __T261;
 struct dim3 __T262;
 unsigned __T263;
# 404 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
(cudaConfigureCall((((void)((__T261 = ((__cuda_local_var_60636_16_non_const_gpu->sim).nonbond_blocks)) , (void)((((__T260.x) = __T261) , (void)((__T260.y) = 1U)) , ((__T260.z) = 1U)))) , __T260), (((void)((__T263 = threadsPerBlock) , (void)((((__T262.x) = __T263) , (void)((__T262.y) = 1U)) , ((__T262.z) = 1U)))) , __T262), (40UL * ((unsigned long)threadsPerBlock)), ((struct CUstream_st *)0LL))) ? ((void)0) : (__device_stub__Z46kCalculateAmoebaGrycukChainRuleN2ByWarp_kernelPj(((__cuda_local_var_60636_16_non_const_gpu->psWorkUnit)->_pDevData)));
} else  {  struct dim3 __T264;
 unsigned __T265;
 struct dim3 __T266;
 unsigned __T267;
# 406 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
(cudaConfigureCall((((void)((__T265 = ((__cuda_local_var_60636_16_non_const_gpu->sim).nonbond_blocks)) , (void)((((__T264.x) = __T265) , (void)((__T264.y) = 1U)) , ((__T264.z) = 1U)))) , __T264), (((void)((__T267 = threadsPerBlock) , (void)((((__T266.x) = __T267) , (void)((__T266.y) = 1U)) , ((__T266.z) = 1U)))) , __T266), (40UL * ((unsigned long)threadsPerBlock)), ((struct CUstream_st *)0LL))) ? ((void)0) : (__device_stub__Z40kCalculateAmoebaGrycukChainRuleN2_kernelPj(((__cuda_local_var_60636_16_non_const_gpu->psWorkUnit)->_pDevData)));
}
{  enum cudaError __cuda_local_var_60660_19_non_const_status;
# 408 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
__cuda_local_var_60660_19_non_const_status = (cudaGetLastError()); if (((int)__cuda_local_var_60660_19_non_const_status) != 0) {  struct _ZN6OpenMM15OpenMMExceptionE *__T268;
 struct _ZSs __T269;
 struct _ZSs __T270;
 struct _ZSs __T271;
 _ZSt6string __T272;
 struct _ZSaIcE __T273;
 struct _ZN6OpenMM15OpenMMExceptionE *__T274;
 const _ZSt6string *__T275;
# 408 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
((((((__T268 = ((struct _ZN6OpenMM15OpenMMExceptionE *)(__throw_setup_dtor((&_ZTIN6OpenMM15OpenMMExceptionE), 16UL, 0, _ZN6OpenMM15OpenMMExceptionD1Ev)))) , (void)((((__T274 = __T268) , (void)(__T275 = ((_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_((&__T269), ((_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_((&__T270), ((_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_((&__T271), ((_ZNSsC1EPKcRKSaIcE((&__T272), ((const char *)"Error: "), ((_ZNSaIcEC1Ev((&__T273))) , (((const struct _ZSaIcE *)&__T273))))) , (((const struct _ZSs *)&__T272))), (cudaGetErrorString(__cuda_local_var_60660_19_non_const_status)))) , (((const struct _ZSs *)&__T271))), ((const char *)" launching kernel "))) , (((const struct _ZSs *)&__T270))), ((const char *)"kCalculateAmoebaCudaGrycukN2Forces"))) , (((const _ZSt6string *)&__T269))))) , (void)(((_ZNSt9exceptionC1Ev((&(__T274->__b_St9exception)))) , (void)(((__T274->__b_St9exception).__vptr) = (_ZTVN6OpenMM15OpenMMExceptionE + 2))) , (void)(_ZNSsC1ERKSs((&(__T274->message)), __T275)))) , (void)(__throw()))) , (void)(_ZNSsD1Ev((&__T269)))) , (void)(_ZNSsD1Ev((&__T270)))) , (void)(_ZNSsD1Ev((&__T271)))) , (void)(_ZNSsD1Ev((&__T272)))) , (void)(_ZNSaIcED1Ev((&__T273))); } } ;

if (0) {
static int callId = 0;
 int __T276;
 int __T277;
 int __T278;
 int __T279;
 struct _Z10CUDAStreamIfE *__T280;
 _ZSt6string __T281;
 struct _ZSaIcE __T282;
 struct _Z10CUDAStreamIfE *__T283;
 _ZSt6string __T284;
 struct _ZSaIcE __T285;
# 412 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
 gpuContext __cuda_local_var_60664_20_non_const_gpu;
 struct _ZSt6vectorIiSaIiEE __cuda_local_var_60665_26_non_const_fileId;

 VectorOfDoubleVectors __cuda_local_var_60667_31_non_const_outputVector;


 struct _Z10CUDAStreamIfE *__cuda_local_var_60670_28_non_const_temp;
# 412 "/home/saifmulla/openmm/OpenMM/plugins/amoeba/platforms/cuda/src/kernels//kCalculateAmoebaCudaGrycuk.cu"
__cuda_local_var_60664_20_non_const_gpu = (amoebaGpu->gpuContext);
_ZNSt6vectorIiSaIiEEC1Ev((&__cuda_local_var_60665_26_non_const_fileId));
_ZNSt6vectorIiSaIiEE9push_backERKi((&__cuda_local_var_60665_26_non_const_fileId), ((__T276 = (callId++)) , (((const _ZNSt6vectorIiSaIiEE10value_typeE *)&__T276))));
_ZNSt6vectorIS_IdSaIdEESaIS1_EEC1Ev((&__cuda_local_var_60667_31_non_const_outputVector));


__cuda_local_var_60670_28_non_const_temp = ((((__T277 = 0) , (void)(__T278 = 0)) , (void)(__T279 = 0)) , ((((__T283 = ((struct _Z10CUDAStreamIfE *)((__T280 = ((struct _Z10CUDAStreamIfE *)(_Znwm(64UL)))) ? ((((__T279 = 1) , (void)(_ZN10CUDAStreamIfEC1EjiSs(__T280, (3U * ((__cuda_local_var_60664_20_non_const_gpu->sim).paddedNumberOfAtoms)), 1, ((_ZNSsC1EPKcRKSaIcE((&__T281), ((const char *)"Temp1"), ((_ZNSaIcEC1Ev((&__T282))) , ((__T278 = 1) , (((const struct _ZSaIcE *)&__T282)))))) , ((__T277 = 1) , (&__T281)))))) , (void)(__T279 = 0)) , __T280) : ((struct _Z10CUDAStreamIfE *)0LL)))) , (void)((__T277) ? ((_ZNSsD1Ev((&__T281))) , (void)((void)0)) : ((void)0))) , (void)((__T278) ? ((_ZNSaIcED1Ev((&__T282))) , (void)((void)0)) : ((void)0))) , __T283));

_Z29reduceAndCopyCUDAStreamFloat4P10CUDAStreamI6float4EPS_IfEf((__cuda_local_var_60664_20_non_const_gpu->psForce4), __cuda_local_var_60670_28_non_const_temp, (1.0F));
_Z22cudaLoadCudaFloatArrayiiP10CUDAStreamIfERSt6vectorIS2_IdSaIdEESaIS4_EEPif((__cuda_local_var_60664_20_non_const_gpu->natoms), 3, __cuda_local_var_60670_28_non_const_temp, (&__cuda_local_var_60667_31_non_const_outputVector), ((__cuda_local_var_60664_20_non_const_gpu->psAtomIndex)->_pSysData), (0.2390057296F));
_Z22cudaLoadCudaFloatArrayiiP10CUDAStreamIfERSt6vectorIS2_IdSaIdEESaIS4_EEPif((__cuda_local_var_60664_20_non_const_gpu->natoms), 1, (__cuda_local_var_60664_20_non_const_gpu->psBornForce), (&__cuda_local_var_60667_31_non_const_outputVector), ((__cuda_local_var_60664_20_non_const_gpu->psAtomIndex)->_pSysData), (0.2390057296F));
_Z22cudaLoadCudaFloatArrayiiP10CUDAStreamIfERSt6vectorIS2_IdSaIdEESaIS4_EEPif((__cuda_local_var_60664_20_non_const_gpu->natoms), 1, (__cuda_local_var_60664_20_non_const_gpu->psBornRadii), (&__cuda_local_var_60667_31_non_const_outputVector), ((__cuda_local_var_60664_20_non_const_gpu->psAtomIndex)->_pSysData), (1.0F));
((_Z36cudaWriteVectorOfDoubleVectorsToFileRKSsRSt6vectorIiSaIiEERS1_IS1_IdSaIdEESaIS6_EE(((_ZNSsC1EPKcRKSaIcE((((_ZSt6string *)&__T284)), ((const char *)"GryF"), ((_ZNSaIcEC1Ev((&__T285))) , (((const struct _ZSaIcE *)&__T285))))) , ((const _ZSt6string *)&__T284)), (&__cuda_local_var_60665_26_non_const_fileId), (&__cuda_local_var_60667_31_non_const_outputVector))) , (void)(_ZNSsD1Ev(((struct _ZSs *)((const _ZSt6string *)&__T284))))) , (void)(_ZNSaIcED1Ev((&__T285)));
(__cuda_local_var_60670_28_non_const_temp) ? ((*((void (**)(struct _Z10CUDAStreamIfE *const))(((__cuda_local_var_60670_28_non_const_temp->__b_15SoADeviceObject).__vptr) + 5)))(__cuda_local_var_60670_28_non_const_temp)) : ((void)0);

_ZNSt6vectorIS_IdSaIdEESaIS1_EED1Ev((&__cuda_local_var_60667_31_non_const_outputVector)); _ZNSt6vectorIiSaIiEED1Ev((&__cuda_local_var_60665_26_non_const_fileId)); } 


}
__asm__(".align 2");
# 98 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/cudatypes.h"
 __attribute__((__weak__)) /* COMDAT group: _ZN10CUDAStreamIfEC1EjiSs */ void _ZN10CUDAStreamIfEC1EjiSs( struct _Z10CUDAStreamIfE *const this,  unsigned length,  int subStreams,  _ZSt6string *name)
{ { (void)(((this->__b_15SoADeviceObject).__vptr) = (_ZTV15SoADeviceObject + 2)); } ((this->__b_15SoADeviceObject).__vptr) = (_ZTV10CUDAStreamIfE + 2); (this->_length) = length; (this->_subStreams) = ((unsigned)subStreams); (this->_stride) = ((length + 15U) & 4294967280U); _ZNSsC1ERKSs((&(this->_name)), ((const struct _ZSs *)name));
_ZN10CUDAStreamIfE8AllocateEv(this); 
}
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZN10CUDAStreamIfEC2EjiSs */ void _ZN10CUDAStreamIfEC2EjiSs( struct _Z10CUDAStreamIfE *const this,  unsigned __T286,  int __T287,  _ZSt6string *__T288) {  _ZN10CUDAStreamIfEC1EjiSs(this, __T286, __T287, __T288);  }
__asm__(".align 2");
# 122 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/cudatypes.h"
 __attribute__((__weak__)) /* COMDAT group: _ZN10CUDAStreamIfE8AllocateEv */ void _ZN10CUDAStreamIfE8AllocateEv( struct _Z10CUDAStreamIfE *const this)
{
 enum cudaError __cuda_local_var_53534_17_non_const_status;
(this->_pSysStream) = ((float **)(_Znam((((unsigned long)(this->_subStreams)) * 8UL))));
(this->_pDevStream) = ((float **)(_Znam((((unsigned long)(this->_subStreams)) * 8UL))));
(this->_pSysData) = ((float *)(_Znam((((unsigned long)((this->_subStreams) * (this->_stride))) * 4UL))));

__cuda_local_var_53534_17_non_const_status = (cudaMalloc(((void **)(&(this->_pDevData))), (((unsigned long)((this->_stride) * (this->_subStreams))) * 4UL)));
if (((int)__cuda_local_var_53534_17_non_const_status) != 0) {  struct _ZN6OpenMM15OpenMMExceptionE *__T289;
 struct _ZSs __T290;
 struct _ZSs __T291;
 _ZSt6string __T292;
 struct _ZSs __T293;
 const char *__T294;
 const struct _ZSs *__T295;
 struct _ZSaIcE __T296;
 const struct _ZSs *__T297;
 const char *__T298;
 const struct _ZSs *__T299;
 const char *__T2100;
 struct _ZN6OpenMM15OpenMMExceptionE *__T2101;
 const _ZSt6string *__T2102;
 _ZNSs14allocator_typeE __T2103;
 struct _ZNSs4_RepE *__T2104;
 const struct _ZSaIcE *__T2105;
 void *__T2106;
 _ZNSs14allocator_typeE __T2107;
 struct _ZNSs4_RepE *__T2108;
 const struct _ZSaIcE *__T2109;
 void *__T2110;
 _ZNSs14allocator_typeE __T2111;
 struct _ZNSs4_RepE *__T2112;
 const struct _ZSaIcE *__T2113;
 void *__T2114;
 _ZNSs14allocator_typeE __T2115;
 struct _ZNSs4_RepE *__T2116;
 const struct _ZSaIcE *__T2117;
 void *__T2118;
# 130 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/cudatypes.h"
((((((__T289 = ((struct _ZN6OpenMM15OpenMMExceptionE *)(__throw_setup_dtor((&_ZTIN6OpenMM15OpenMMExceptionE), 16UL, 0, _ZN6OpenMM15OpenMMExceptionD1Ev)))) , (void)((((__T2101 = __T289) , (void)(__T2102 = (((void)(((__T299 = (((void)(((__T297 = ((_ZNSsC1EPKcRKSaIcE((&__T292), ((__T295 = (((void)((__T294 = ((const char *)": cudaMalloc in CUDAStream::Allocate failed")) , (void)((_ZNSsC1ERKSs((&__T293), (((const struct _ZSs *)&(this->_name))))) , (_ZNSs6appendEPKcm((&__T293), __T294, (__builtin_strlen(__T294))))))) , (((const struct _ZSs *)&__T293)))) , ((const char *)((((struct _ZSs *)__T295)->_M_dataplus)._M_p))), ((_ZN9__gnu_cxx13new_allocatorIcEC1Ev(((struct _ZN9__gnu_cxx13new_allocatorIcEE *)(&__T296)))) , (((const struct _ZSaIcE *)&__T296))))) , (((const struct _ZSs *)&__T292)))) , (void)(__T298 = ((const char *)" "))) , (void)((_ZNSsC1ERKSs((&__T291), __T297)) , (_ZNSs6appendEPKcm((&__T291), __T298, (__builtin_strlen(__T298))))))) , (((const struct _ZSs *)&__T291)))) , (void)(__T2100 = (cudaGetErrorString(__cuda_local_var_53534_17_non_const_status)))) , (void)((_ZNSsC1ERKSs((&__T290), __T299)) , (_ZNSs6appendEPKcm((&__T290), __T2100, (__builtin_strlen(__T2100))))))) , (((const _ZSt6string *)&__T290))))) , (void)(((_ZNSt9exceptionC1Ev((&(__T2101->__b_St9exception)))) , (void)(((__T2101->__b_St9exception).__vptr) = (_ZTVN6OpenMM15OpenMMExceptionE + 2))) , (void)(_ZNSsC1ERKSs((&(__T2101->message)), __T2102)))) , (void)(__throw()))) , (void)(((((__T2104 = (((struct _ZNSs4_RepE *)((((struct _ZSs *)((const struct _ZSs *)(&__T290)))->_M_dataplus)._M_p)) + (-1))) , (void)(__T2105 = ((_ZN9__gnu_cxx13new_allocatorIcEC1ERKS1_(((struct _ZN9__gnu_cxx13new_allocatorIcEE *)(&__T2103)), ((const struct _ZN9__gnu_cxx13new_allocatorIcEE *)((struct _ZN9__gnu_cxx13new_allocatorIcEE *)((const struct _ZSaIcE *)(((struct _ZSaIcE *)&(((struct _ZSs *)((const struct _ZSs *)(&__T290)))->_M_dataplus)))))))) , (((const struct _ZSaIcE *)&__T2103))))) , (void)((__builtin_expect(((long)(__T2104 != ((__T2106 = ((void *)_ZNSs4_Rep20_S_empty_rep_storageE)) , ((struct _ZNSs4_RepE *)__T2106)))), 0L)) ? (((_ZN9__gnu_cxx27__exchange_and_add_dispatchEPii((&((__T2104->__b_NSs9_Rep_baseE)._M_refcount)), (-1))) <= 0) ? (_ZNSs4_Rep10_M_destroyERKSaIcE(__T2104, __T2105)) : ((void)0)) : ((void)0))) , (void)(_ZN9__gnu_cxx13new_allocatorIcED1Ev(((struct _ZN9__gnu_cxx13new_allocatorIcEE *)(&__T2103))))) , (void)(_ZNSaIcED1Ev(((struct _ZSaIcE *)(&(__T290._M_dataplus))))))) , (void)(((((__T2108 = (((struct _ZNSs4_RepE *)((((struct _ZSs *)((const struct _ZSs *)(&__T291)))->_M_dataplus)._M_p)) + (-1))) , (void)(__T2109 = ((_ZN9__gnu_cxx13new_allocatorIcEC1ERKS1_(((struct _ZN9__gnu_cxx13new_allocatorIcEE *)(&__T2107)), ((const struct _ZN9__gnu_cxx13new_allocatorIcEE *)((struct _ZN9__gnu_cxx13new_allocatorIcEE *)((const struct _ZSaIcE *)(((struct _ZSaIcE *)&(((struct _ZSs *)((const struct _ZSs *)(&__T291)))->_M_dataplus)))))))) , (((const struct _ZSaIcE *)&__T2107))))) , (void)((__builtin_expect(((long)(__T2108 != ((__T2110 = ((void *)_ZNSs4_Rep20_S_empty_rep_storageE)) , ((struct _ZNSs4_RepE *)__T2110)))), 0L)) ? (((_ZN9__gnu_cxx27__exchange_and_add_dispatchEPii((&((__T2108->__b_NSs9_Rep_baseE)._M_refcount)), (-1))) <= 0) ? (_ZNSs4_Rep10_M_destroyERKSaIcE(__T2108, __T2109)) : ((void)0)) : ((void)0))) , (void)(_ZN9__gnu_cxx13new_allocatorIcED1Ev(((struct _ZN9__gnu_cxx13new_allocatorIcEE *)(&__T2107))))) , (void)(_ZNSaIcED1Ev(((struct _ZSaIcE *)(&(__T291._M_dataplus))))))) , (void)(((((__T2112 = (((struct _ZNSs4_RepE *)((((struct _ZSs *)((const struct _ZSs *)(&__T292)))->_M_dataplus)._M_p)) + (-1))) , (void)(__T2113 = ((_ZN9__gnu_cxx13new_allocatorIcEC1ERKS1_(((struct _ZN9__gnu_cxx13new_allocatorIcEE *)(&__T2111)), ((const struct _ZN9__gnu_cxx13new_allocatorIcEE *)((struct _ZN9__gnu_cxx13new_allocatorIcEE *)((const struct _ZSaIcE *)(((struct _ZSaIcE *)&(((struct _ZSs *)((const struct _ZSs *)(&__T292)))->_M_dataplus)))))))) , (((const struct _ZSaIcE *)&__T2111))))) , (void)((__builtin_expect(((long)(__T2112 != ((__T2114 = ((void *)_ZNSs4_Rep20_S_empty_rep_storageE)) , ((struct _ZNSs4_RepE *)__T2114)))), 0L)) ? (((_ZN9__gnu_cxx27__exchange_and_add_dispatchEPii((&((__T2112->__b_NSs9_Rep_baseE)._M_refcount)), (-1))) <= 0) ? (_ZNSs4_Rep10_M_destroyERKSaIcE(__T2112, __T2113)) : ((void)0)) : ((void)0))) , (void)(_ZN9__gnu_cxx13new_allocatorIcED1Ev(((struct _ZN9__gnu_cxx13new_allocatorIcEE *)(&__T2111))))) , (void)(_ZNSaIcED1Ev(((struct _ZSaIcE *)(&(__T292._M_dataplus))))))) , (void)(_ZN9__gnu_cxx13new_allocatorIcED1Ev(((struct _ZN9__gnu_cxx13new_allocatorIcEE *)(&__T296))))) , (void)(((((__T2116 = (((struct _ZNSs4_RepE *)((((struct _ZSs *)((const struct _ZSs *)(&__T293)))->_M_dataplus)._M_p)) + (-1))) , (void)(__T2117 = ((_ZN9__gnu_cxx13new_allocatorIcEC1ERKS1_(((struct _ZN9__gnu_cxx13new_allocatorIcEE *)(&__T2115)), ((const struct _ZN9__gnu_cxx13new_allocatorIcEE *)((struct _ZN9__gnu_cxx13new_allocatorIcEE *)((const struct _ZSaIcE *)(((struct _ZSaIcE *)&(((struct _ZSs *)((const struct _ZSs *)(&__T293)))->_M_dataplus)))))))) , (((const struct _ZSaIcE *)&__T2115))))) , (void)((__builtin_expect(((long)(__T2116 != ((__T2118 = ((void *)_ZNSs4_Rep20_S_empty_rep_storageE)) , ((struct _ZNSs4_RepE *)__T2118)))), 0L)) ? (((_ZN9__gnu_cxx27__exchange_and_add_dispatchEPii((&((__T2116->__b_NSs9_Rep_baseE)._M_refcount)), (-1))) <= 0) ? (_ZNSs4_Rep10_M_destroyERKSaIcE(__T2116, __T2117)) : ((void)0)) : ((void)0))) , (void)(_ZN9__gnu_cxx13new_allocatorIcED1Ev(((struct _ZN9__gnu_cxx13new_allocatorIcEE *)(&__T2115))))) , (void)(_ZNSaIcED1Ev(((struct _ZSaIcE *)(&(__T293._M_dataplus)))))); } ; {

 unsigned i;
# 132 "/home/saifmulla/openmm/OpenMM/platforms/cuda/src/kernels/cudatypes.h"
i = 0U; for (; (i < (this->_subStreams)); i++)
{
((this->_pSysStream)[i]) = ((this->_pSysData) + (i * (this->_stride)));
((this->_pDevStream)[i]) = ((this->_pDevData) + (i * (this->_stride)));
} } 
}
__asm__(".align 2");
# 62 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/exception" 3
 __attribute__((__weak__)) /* COMDAT group: _ZNSt9exceptionC1Ev */ __inline__ __attribute__((visibility("default"))) void _ZNSt9exceptionC1Ev( struct _ZSt9exception *const this) {  (this->__vptr) = (_ZTVSt9exception + 2);  }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZNSt9exceptionC2Ev */ __inline__ __attribute__((visibility("default"))) void _ZNSt9exceptionC2Ev( struct _ZSt9exception *const this) {  _ZNSt9exceptionC1Ev(this);  }
__asm__(".align 2");
# 101 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
extern __inline__ __attribute__((visibility("default"))) void _ZNSaIcEC1Ev( struct _ZSaIcE *const this) { { _ZN9__gnu_cxx13new_allocatorIcEC1Ev(((struct _ZN9__gnu_cxx13new_allocatorIcEE *)this)); }  }
__asm__(".align 2");
extern __inline__ __attribute__((visibility("default"))) void _ZNSaIcEC2Ev( struct _ZSaIcE *const this) {  _ZNSaIcEC1Ev(this);  }
__asm__(".align 2");




extern __inline__ __attribute__((visibility("default"))) void _ZNSaIcED1Ev( struct _ZSaIcE *const this) {  { { _ZN9__gnu_cxx13new_allocatorIcED1Ev(((struct _ZN9__gnu_cxx13new_allocatorIcEE *)this)); } }  }
__asm__(".align 2");
extern __inline__ __attribute__((visibility("default"))) void _ZNSaIcED2Ev( struct _ZSaIcE *const this) {  _ZNSaIcED1Ev(this);  }
__asm__(".align 2");
# 502 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/basic_string.h" 3
extern __inline__ __attribute__((visibility("default"))) void _ZNSsD1Ev( struct _ZSs *const this)
{  _ZNSs14allocator_typeE __T2119;
 struct _ZNSs4_RepE *__T2120;
 const struct _ZSaIcE *__T2121;
 void *__T2122;
# 503 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/basic_string.h" 3
(((__T2120 = (((struct _ZNSs4_RepE *)((((struct _ZSs *)((const struct _ZSs *)this))->_M_dataplus)._M_p)) + (-1))) , (void)(__T2121 = ((_ZN9__gnu_cxx13new_allocatorIcEC1ERKS1_(((struct _ZN9__gnu_cxx13new_allocatorIcEE *)(&__T2119)), ((const struct _ZN9__gnu_cxx13new_allocatorIcEE *)((struct _ZN9__gnu_cxx13new_allocatorIcEE *)((const struct _ZSaIcE *)(((struct _ZSaIcE *)&(((struct _ZSs *)((const struct _ZSs *)this))->_M_dataplus)))))))) , (((const struct _ZSaIcE *)&__T2119))))) , (void)((__builtin_expect(((long)(__T2120 != ((__T2122 = ((void *)_ZNSs4_Rep20_S_empty_rep_storageE)) , ((struct _ZNSs4_RepE *)__T2122)))), 0L)) ? (((_ZN9__gnu_cxx27__exchange_and_add_dispatchEPii((&((__T2120->__b_NSs9_Rep_baseE)._M_refcount)), (-1))) <= 0) ? (_ZNSs4_Rep10_M_destroyERKSaIcE(__T2120, __T2121)) : ((void)0)) : ((void)0))) , (void)(_ZN9__gnu_cxx13new_allocatorIcED1Ev(((struct _ZN9__gnu_cxx13new_allocatorIcEE *)(&__T2119)))); { { _ZNSaIcED1Ev(((struct _ZSaIcE *)(&(this->_M_dataplus)))); } }  }
__asm__(".align 2");
extern __inline__ __attribute__((visibility("default"))) void _ZNSsD2Ev( struct _ZSs *const this) {  _ZNSsD1Ev(this);  }
__asm__(".align 2");
# 257 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/basic_string.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZNSs12_Alloc_hiderD1Ev */ __inline__ __attribute__((visibility("default"))) void _ZNSs12_Alloc_hiderD1Ev( struct _ZNSs12_Alloc_hiderE *const this) {  { { _ZNSaIcED1Ev(((struct _ZSaIcE *)this)); } }  }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZNSs12_Alloc_hiderD2Ev */ __inline__ __attribute__((visibility("default"))) void _ZNSs12_Alloc_hiderD2Ev( struct _ZNSs12_Alloc_hiderE *const this) {  _ZNSaIcED1Ev(((struct _ZSaIcE *)this));  }
__asm__(".align 2");
# 101 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZNSaIiEC1Ev */ __inline__ void _ZNSaIiEC1Ev( struct _ZSaIiE *const this) { { _ZN9__gnu_cxx13new_allocatorIiEC1Ev(((struct _ZN9__gnu_cxx13new_allocatorIiEE *)this)); }  }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZNSaIiEC2Ev */ __inline__ void _ZNSaIiEC2Ev( struct _ZSaIiE *const this) {  _ZNSaIiEC1Ev(this);  }
__asm__(".align 2");




 __attribute__((__weak__)) /* COMDAT group: _ZNSaIiED1Ev */ __inline__ void _ZNSaIiED1Ev( struct _ZSaIiE *const this) {  { { _ZN9__gnu_cxx13new_allocatorIiED1Ev(((struct _ZN9__gnu_cxx13new_allocatorIiEE *)this)); } }  }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZNSaIiED2Ev */ __inline__ void _ZNSaIiED2Ev( struct _ZSaIiE *const this) {  _ZNSaIiED1Ev(this);  }
__asm__(".align 2");
# 104 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseIiSaIiEEC1Ev */ __inline__ void _ZNSt12_Vector_baseIiSaIiEEC1Ev( struct _ZSt12_Vector_baseIiSaIiEE *const this)
{ { { _ZNSaIiEC1Ev(((struct _ZSaIiE *)(&(this->_M_impl)))); } ((this->_M_impl)._M_start) = ((_ZNSaIiE7pointerE)0LL); ((this->_M_impl)._M_finish) = ((_ZNSaIiE7pointerE)0LL); ((this->_M_impl)._M_end_of_storage) = ((_ZNSaIiE7pointerE)0LL); }  }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseIiSaIiEEC2Ev */ __inline__ void _ZNSt12_Vector_baseIiSaIiEEC2Ev( struct _ZSt12_Vector_baseIiSaIiEE *const this) {  _ZNSt12_Vector_baseIiSaIiEEC1Ev(this);  }
__asm__(".align 2");
# 131 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseIiSaIiEED1Ev */ __inline__ void _ZNSt12_Vector_baseIiSaIiEED1Ev( struct _ZSt12_Vector_baseIiSaIiEE *const this)
{  _ZNSaIiE7pointerE __T2123;
 size_t __T2124;
# 132 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
{ __T2123 = ((this->_M_impl)._M_start); __T2124 = ((size_t)(((this->_M_impl)._M_end_of_storage) - ((this->_M_impl)._M_start))); { if (__T2123) { { _ZdlPv(((void *)__T2123)); } } } } {
{ _ZNSaIiED1Ev(((struct _ZSaIiE *)(&(this->_M_impl)))); } }  }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseIiSaIiEED2Ev */ __inline__ void _ZNSt12_Vector_baseIiSaIiEED2Ev( struct _ZSt12_Vector_baseIiSaIiEE *const this) {  _ZNSt12_Vector_baseIiSaIiEED1Ev(this);  }
__asm__(".align 2");
# 73 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseIiSaIiEE12_Vector_implD1Ev */ __inline__ void _ZNSt12_Vector_baseIiSaIiEE12_Vector_implD1Ev( struct _ZNSt12_Vector_baseIiSaIiEE12_Vector_implE *const this) {  { { _ZNSaIiED1Ev(((struct _ZSaIiE *)this)); } }  }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseIiSaIiEE12_Vector_implD2Ev */ __inline__ void _ZNSt12_Vector_baseIiSaIiEE12_Vector_implD2Ev( struct _ZNSt12_Vector_baseIiSaIiEE12_Vector_implE *const this) {  _ZNSaIiED1Ev(((struct _ZSaIiE *)this));  }
__asm__(".align 2");
# 207 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZNSt6vectorIiSaIiEEC1Ev */ __inline__ void _ZNSt6vectorIiSaIiEEC1Ev( struct _ZSt6vectorIiSaIiEE *const this)
{ { _ZNSt12_Vector_baseIiSaIiEEC1Ev((&(this->__b_St12_Vector_baseIiSaIiEE))); }  }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZNSt6vectorIiSaIiEEC2Ev */ __inline__ void _ZNSt6vectorIiSaIiEEC2Ev( struct _ZSt6vectorIiSaIiEE *const this) {  _ZNSt6vectorIiSaIiEEC1Ev(this);  }
__asm__(".align 2");
# 312 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZNSt6vectorIiSaIiEED1Ev */ __inline__ void _ZNSt6vectorIiSaIiEED1Ev( struct _ZSt6vectorIiSaIiEE *const this)
{  int *__T2125;
 int *__T2126;
# 313 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
{ __T2125 = (((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_start); __T2126 = (((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_finish); { _ZSt8_DestroyIPiEvT_S1_(__T2125, __T2126); } } {
{ _ZNSt12_Vector_baseIiSaIiEED1Ev((&(this->__b_St12_Vector_baseIiSaIiEE))); } }  }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZNSt6vectorIiSaIiEED2Ev */ __inline__ void _ZNSt6vectorIiSaIiEED2Ev( struct _ZSt6vectorIiSaIiEE *const this) {  _ZNSt6vectorIiSaIiEED1Ev(this);  }
__asm__(".align 2");
# 733 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZNSt6vectorIiSaIiEE9push_backERKi */ __inline__ void _ZNSt6vectorIiSaIiEE9push_backERKi( struct _ZSt6vectorIiSaIiEE *const this,  const _ZNSt6vectorIiSaIiEE10value_typeE *__x)
{  _ZN9__gnu_cxx13new_allocatorIiE7pointerE __T2127;
 void *__T2128;
 void *__T2129;
 int *__T2130;
 _ZNSt6vectorIiSaIiEE8iteratorE __T2131;
# 735 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
if ((((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_finish) != (((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_end_of_storage))
{
{ __T2127 = (((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_finish); { (int *)((__T2130 = ((int *)((__T2129 = (__T2128 = ((void *)__T2127))) , __T2129))) ? (((*__T2130) = (*__x)) , __T2130) : ((int *)0LL)); } }
++(((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_finish);
} else  {

_ZNSt6vectorIiSaIiEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPiS1_EERKi(this, (((void)((__T2131._M_current) = (*(((const _ZNSt6vectorIiSaIiEE7pointerE *)&(((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_finish)))))) , __T2131), __x); } 
}
__asm__(".align 2");
# 296 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/vector.tcc" 3
 __attribute__((__weak__)) /* COMDAT group: _ZNSt6vectorIiSaIiEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPiS1_EERKi */ void _ZNSt6vectorIiSaIiEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPiS1_EERKi( struct _ZSt6vectorIiSaIiEE *const this,  _ZNSt6vectorIiSaIiEE8iteratorE __position,  const _ZNSt6vectorIiSaIiEE10value_typeE *__x)

{
if ((((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_finish) != (((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_end_of_storage))
{  _ZN9__gnu_cxx13new_allocatorIiE7pointerE __T2132;
 const int *__T2133;
 void *__T2134;
 void *__T2135;
 int *__T2136;
 int *__T2137;
 int *__T2138;
 int *__T2139;
# 306 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/vector.tcc" 3
 int __cuda_local_var_56112_8_non_const___x_copy;
# 301 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/vector.tcc" 3
{ __T2132 = (((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_finish); __T2133 = ((const int *)((((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_finish) - 1)); { (int *)((__T2136 = ((int *)((__T2135 = (__T2134 = ((void *)__T2132))) , __T2135))) ? (((*__T2136) = (*__T2133)) , __T2136) : ((int *)0LL)); } }


++(((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_finish);

__cuda_local_var_56112_8_non_const___x_copy = (*__x);

{ __T2137 = (*(&(((*(const struct _ZN9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEE *)&__position))._M_current))); __T2138 = ((((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_finish) - 2); __T2139 = ((((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_finish) - 1); { ; (int *)(_ZSt22__copy_move_backward_aILb0EPiS0_ET1_T0_S2_S1_(__T2137, __T2138, __T2139)); } }



(*(((*(const struct _ZN9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEE *)&__position))._M_current)) = __cuda_local_var_56112_8_non_const___x_copy;



}

else  { static struct __C5 __T2140[1] = {{((const struct __type_info *)0LL),((unsigned char)48U),((unsigned char *)0LL)}};
 _ZNSt6vectorIiSaIiEE9size_typeE __T2141;
 const char *__T2142;
 _ZNSt6vectorIiSaIiEE9size_typeE __T2143;
 _ZNSt6vectorIiSaIiEE9size_typeE __T2144;
 _ZNSt6vectorIiSaIiEE8iteratorE __T2145;
 _ZNSt6vectorIiSaIiEE8iteratorE __T2146;
 const struct _ZN9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEE *__T2147;
 struct __C8 __T2148;
 void *__T2149;
 void *__T2150;
 int *__T2151;
 int *__T2152;
 int *__T2153;
 int *__T2154;
 int *__T2155;
 int *__T2156;
 int *__T2157;
 _ZNSaIiE7pointerE __T2158;
 size_t __T2159;
# 319 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/vector.tcc" 3
 _ZNSt6vectorIiSaIiEE9size_typeE __cuda_local_var_56125_20_non_const___len;

 _ZNSt6vectorIiSaIiEE9size_typeE __cuda_local_var_56127_20_non_const___elems_before;
 _ZNSt6vectorIiSaIiEE7pointerE __cuda_local_var_56128_12_non_const___new_start;
 _ZNSt6vectorIiSaIiEE7pointerE __cuda_local_var_56129_12_non_const___new_finish;
# 319 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/vector.tcc" 3
__cuda_local_var_56125_20_non_const___len = (((__T2141 = 1UL) , (void)(__T2142 = ((const char *)"vector::_M_insert_aux"))) , ((((((((const struct _ZN9__gnu_cxx13new_allocatorIiEE *)0LL) , 4611686018427387903UL) - ((_ZNSt6vectorIiSaIiEE9size_typeE)((((((const struct _ZSt6vectorIiSaIiEE *)this)->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_finish) - (((((const struct _ZSt6vectorIiSaIiEE *)this)->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_start)))) < __T2141) ? (_ZSt20__throw_length_errorPKc(__T2142)) : ((void)0)) , (void)(__T2144 = (((_ZNSt6vectorIiSaIiEE9size_typeE)((((((const struct _ZSt6vectorIiSaIiEE *)this)->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_finish) - (((((const struct _ZSt6vectorIiSaIiEE *)this)->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_start))) + (*(_ZSt3maxImERKT_S2_S2_(((__T2143 = ((_ZNSt6vectorIiSaIiEE9size_typeE)((((((const struct _ZSt6vectorIiSaIiEE *)this)->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_finish) - (((((const struct _ZSt6vectorIiSaIiEE *)this)->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_start)))) , (((const _ZNSt6vectorIiSaIiEE9size_typeE *)&__T2143))), (((const _ZNSt6vectorIiSaIiEE9size_typeE *)&__T2141)))))))) , (((__T2144 < ((_ZNSt6vectorIiSaIiEE9size_typeE)((((((const struct _ZSt6vectorIiSaIiEE *)this)->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_finish) - (((((const struct _ZSt6vectorIiSaIiEE *)this)->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_start)))) || (__T2144 > (((const struct _ZN9__gnu_cxx13new_allocatorIiEE *)0LL) , 4611686018427387903UL))) ? (((const struct _ZN9__gnu_cxx13new_allocatorIiEE *)0LL) , 4611686018427387903UL) : __T2144)));

__cuda_local_var_56127_20_non_const___elems_before = ((_ZNSt6vectorIiSaIiEE9size_typeE)((__T2147 = ((const struct _ZN9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEE *)((__T2145 = (((void)((__T2146._M_current) = (*(((const _ZNSt6vectorIiSaIiEE7pointerE *)&(((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_start)))))) , __T2146)) , (&__T2145)))) , ((*(&(((*(const struct _ZN9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEE *)&__position))._M_current))) - (*(&(__T2147->_M_current))))));
__cuda_local_var_56128_12_non_const___new_start = ((__cuda_local_var_56125_20_non_const___len != 0UL) ? (((__builtin_expect(((long)(__cuda_local_var_56125_20_non_const___len > 4611686018427387903UL)), 0L)) ? (_ZSt17__throw_bad_allocv()) : ((void)0)) , ((int *)(_Znwm((__cuda_local_var_56125_20_non_const___len * 4UL))))) : ((_ZN9__gnu_cxx13new_allocatorIiE7pointerE)0LL));
__cuda_local_var_56129_12_non_const___new_finish = __cuda_local_var_56128_12_non_const___new_start; { (__T2148.next) = __curr_eh_stack_entry; __curr_eh_stack_entry = (&__T2148); (__T2148.kind) = ((unsigned char)5U); (((__T2148.variant).try_block).catch_entries) = (__T2140); (((__T2148.variant).try_block).rtinfo) = ((void *)0LL); (((__T2148.variant).try_block).region_number) = __eh_curr_region;
if ((setjmp(((((__T2148.variant).try_block).setjmp_buffer)))) == 0)
{ __T2160:;




{ (int *)((__T2151 = ((int *)((__T2150 = (__T2149 = ((void *)(__cuda_local_var_56128_12_non_const___new_start + __cuda_local_var_56127_20_non_const___elems_before)))) , __T2150))) ? (((*__T2151) = (*__x)) , __T2151) : ((int *)0LL)); }
# 336 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/vector.tcc" 3
__cuda_local_var_56129_12_non_const___new_finish = ((_ZNSt6vectorIiSaIiEE7pointerE)0LL);

__cuda_local_var_56129_12_non_const___new_finish = (((__T2152 = (((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_start)) , (void)(__T2153 = (*(&(((*(const struct _ZN9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEE *)&__position))._M_current))))) , (_ZSt18uninitialized_copyIPiS0_ET0_T_S2_S1_(__T2152, __T2153, __cuda_local_var_56128_12_non_const___new_start)));



++__cuda_local_var_56129_12_non_const___new_finish;

__cuda_local_var_56129_12_non_const___new_finish = (((__T2154 = (*(&(((*(const struct _ZN9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEE *)&__position))._M_current)))) , (void)(__T2155 = (((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_finish))) , (_ZSt18uninitialized_copyIPiS0_ET0_T_S2_S1_(__T2154, __T2155, __cuda_local_var_56129_12_non_const___new_finish)));




}
else  if (__catch_clause_number == 1)
{ __exception_caught();
if (!(__cuda_local_var_56129_12_non_const___new_finish)) {
{ (void)(__cuda_local_var_56128_12_non_const___new_start + __cuda_local_var_56127_20_non_const___elems_before); } } else  {

{ _ZSt8_DestroyIPiEvT_S1_(__cuda_local_var_56128_12_non_const___new_start, __cuda_local_var_56129_12_non_const___new_finish); } }
{ if (__cuda_local_var_56128_12_non_const___new_start) { { _ZdlPv(((void *)__cuda_local_var_56128_12_non_const___new_start)); } } }
__rethrow();
} else  { __suppress_optim_on_vars_in_try((&__cuda_local_var_56129_12_non_const___new_finish)); goto __T2160; } __curr_eh_stack_entry = (__T2148.next); }
{ __T2156 = (((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_start); __T2157 = (((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_finish); { _ZSt8_DestroyIPiEvT_S1_(__T2156, __T2157); } }

{ __T2158 = (((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_start); __T2159 = ((size_t)((((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_end_of_storage) - (((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_start))); { if (__T2158) { { _ZdlPv(((void *)__T2158)); } } } }


(((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_start) = __cuda_local_var_56128_12_non_const___new_start;
(((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_finish) = __cuda_local_var_56129_12_non_const___new_finish;
(((this->__b_St12_Vector_baseIiSaIiEE)._M_impl)._M_end_of_storage) = (__cuda_local_var_56128_12_non_const___new_start + __cuda_local_var_56125_20_non_const___len);
} 
}
__asm__(".align 2");
# 101 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZNSaISt6vectorIdSaIdEEEC1Ev */ __inline__ void _ZNSaISt6vectorIdSaIdEEEC1Ev( struct _ZSaISt6vectorIdSaIdEEE *const this) { { _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEEC1Ev(((struct _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEEE *)this)); }  }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZNSaISt6vectorIdSaIdEEEC2Ev */ __inline__ void _ZNSaISt6vectorIdSaIdEEEC2Ev( struct _ZSaISt6vectorIdSaIdEEE *const this) {  _ZNSaISt6vectorIdSaIdEEEC1Ev(this);  }
__asm__(".align 2");




 __attribute__((__weak__)) /* COMDAT group: _ZNSaISt6vectorIdSaIdEEED1Ev */ __inline__ void _ZNSaISt6vectorIdSaIdEEED1Ev( struct _ZSaISt6vectorIdSaIdEEE *const this) {  { { _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEED1Ev(((struct _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEEE *)this)); } }  }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZNSaISt6vectorIdSaIdEEED2Ev */ __inline__ void _ZNSaISt6vectorIdSaIdEEED2Ev( struct _ZSaISt6vectorIdSaIdEEE *const this) {  _ZNSaISt6vectorIdSaIdEEED1Ev(this);  }
__asm__(".align 2");
# 104 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EEC1Ev */ __inline__ void _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EEC1Ev( struct _ZSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE *const this)
{ { { _ZNSaISt6vectorIdSaIdEEEC1Ev(((struct _ZSaISt6vectorIdSaIdEEE *)(&(this->_M_impl)))); } ((this->_M_impl)._M_start) = ((_ZNSaISt6vectorIdSaIdEEE7pointerE)0LL); ((this->_M_impl)._M_finish) = ((_ZNSaISt6vectorIdSaIdEEE7pointerE)0LL); ((this->_M_impl)._M_end_of_storage) = ((_ZNSaISt6vectorIdSaIdEEE7pointerE)0LL); }  }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EEC2Ev */ __inline__ void _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EEC2Ev( struct _ZSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE *const this) {  _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EEC1Ev(this);  }
__asm__(".align 2");
# 131 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EED1Ev */ __inline__ void _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EED1Ev( struct _ZSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE *const this)
{  _ZNSaISt6vectorIdSaIdEEE7pointerE __T2161;
 size_t __T2162;
# 132 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
{ __T2161 = ((this->_M_impl)._M_start); __T2162 = ((size_t)(((this->_M_impl)._M_end_of_storage) - ((this->_M_impl)._M_start))); { if (__T2161) { { _ZdlPv(((void *)__T2161)); } } } } {
{ _ZNSaISt6vectorIdSaIdEEED1Ev(((struct _ZSaISt6vectorIdSaIdEEE *)(&(this->_M_impl)))); } }  }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EED2Ev */ __inline__ void _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EED2Ev( struct _ZSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE *const this) {  _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EED1Ev(this);  }
__asm__(".align 2");
# 73 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE12_Vector_implD1Ev */ __inline__ void _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE12_Vector_implD1Ev( struct _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE12_Vector_implE *const this) {  { { _ZNSaISt6vectorIdSaIdEEED1Ev(((struct _ZSaISt6vectorIdSaIdEEE *)this)); } }  }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE12_Vector_implD2Ev */ __inline__ void _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE12_Vector_implD2Ev( struct _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EE12_Vector_implE *const this) {  _ZNSaISt6vectorIdSaIdEEED1Ev(((struct _ZSaISt6vectorIdSaIdEEE *)this));  }
__asm__(".align 2");
# 207 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZNSt6vectorIS_IdSaIdEESaIS1_EEC1Ev */ __inline__ void _ZNSt6vectorIS_IdSaIdEESaIS1_EEC1Ev( struct _ZSt6vectorIS_IdSaIdEESaIS1_EE *const this)
{ { _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EEC1Ev((&(this->__b_St12_Vector_baseISt6vectorIdSaIdEESaIS2_EE))); }  }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZNSt6vectorIS_IdSaIdEESaIS1_EEC2Ev */ __inline__ void _ZNSt6vectorIS_IdSaIdEESaIS1_EEC2Ev( struct _ZSt6vectorIS_IdSaIdEESaIS1_EE *const this) {  _ZNSt6vectorIS_IdSaIdEESaIS1_EEC1Ev(this);  }
__asm__(".align 2");
# 312 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZNSt6vectorIS_IdSaIdEESaIS1_EED1Ev */ __inline__ void _ZNSt6vectorIS_IdSaIdEESaIS1_EED1Ev( struct _ZSt6vectorIS_IdSaIdEESaIS1_EE *const this)
{  struct _ZSt6vectorIdSaIdEE *__T2163;
 struct _ZSt6vectorIdSaIdEE *__T2164;
# 313 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
{ __T2163 = (((this->__b_St12_Vector_baseISt6vectorIdSaIdEESaIS2_EE)._M_impl)._M_start); __T2164 = (((this->__b_St12_Vector_baseISt6vectorIdSaIdEESaIS2_EE)._M_impl)._M_finish); { _ZSt8_DestroyIPSt6vectorIdSaIdEEEvT_S4_(__T2163, __T2164); } } {
{ _ZNSt12_Vector_baseISt6vectorIdSaIdEESaIS2_EED1Ev((&(this->__b_St12_Vector_baseISt6vectorIdSaIdEESaIS2_EE))); } }  }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZNSt6vectorIS_IdSaIdEESaIS1_EED2Ev */ __inline__ void _ZNSt6vectorIS_IdSaIdEESaIS1_EED2Ev( struct _ZSt6vectorIS_IdSaIdEESaIS1_EE *const this) {  _ZNSt6vectorIS_IdSaIdEESaIS1_EED1Ev(this);  }
__asm__(".align 2");
# 109 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/allocator.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZNSaIdED1Ev */ __inline__ void _ZNSaIdED1Ev( struct _ZSaIdE *const this) {  { { _ZN9__gnu_cxx13new_allocatorIdED1Ev(((struct _ZN9__gnu_cxx13new_allocatorIdEE *)this)); } }  }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZNSaIdED2Ev */ __inline__ void _ZNSaIdED2Ev( struct _ZSaIdE *const this) {  _ZNSaIdED1Ev(this);  }
__asm__(".align 2");
# 131 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseIdSaIdEED1Ev */ __inline__ void _ZNSt12_Vector_baseIdSaIdEED1Ev( struct _ZSt12_Vector_baseIdSaIdEE *const this)
{  _ZNSaIdE7pointerE __T2165;
 size_t __T2166;
# 132 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
{ __T2165 = ((this->_M_impl)._M_start); __T2166 = ((size_t)(((this->_M_impl)._M_end_of_storage) - ((this->_M_impl)._M_start))); { if (__T2165) { { _ZdlPv(((void *)__T2165)); } } } } {
{ _ZNSaIdED1Ev(((struct _ZSaIdE *)(&(this->_M_impl)))); } }  }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseIdSaIdEED2Ev */ __inline__ void _ZNSt12_Vector_baseIdSaIdEED2Ev( struct _ZSt12_Vector_baseIdSaIdEE *const this) {  _ZNSt12_Vector_baseIdSaIdEED1Ev(this);  }
__asm__(".align 2");
# 73 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_vector.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseIdSaIdEE12_Vector_implD1Ev */ __inline__ void _ZNSt12_Vector_baseIdSaIdEE12_Vector_implD1Ev( struct _ZNSt12_Vector_baseIdSaIdEE12_Vector_implE *const this) {  { { _ZNSaIdED1Ev(((struct _ZSaIdE *)this)); } }  }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZNSt12_Vector_baseIdSaIdEE12_Vector_implD2Ev */ __inline__ void _ZNSt12_Vector_baseIdSaIdEE12_Vector_implD2Ev( struct _ZNSt12_Vector_baseIdSaIdEE12_Vector_implE *const this) {  _ZNSaIdED1Ev(((struct _ZSaIdE *)this));  }
__asm__(".align 2");
# 66 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/ext/new_allocator.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIcEC1Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorIcEC1Ev( struct _ZN9__gnu_cxx13new_allocatorIcEE *const this) {   }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIcEC2Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorIcEC2Ev( struct _ZN9__gnu_cxx13new_allocatorIcEE *const this) {  _ZN9__gnu_cxx13new_allocatorIcEC1Ev(this);  }
__asm__(".align 2");
# 68 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/ext/new_allocator.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIcEC1ERKS1_ */ __inline__ void _ZN9__gnu_cxx13new_allocatorIcEC1ERKS1_( struct _ZN9__gnu_cxx13new_allocatorIcEE *const this,  const struct _ZN9__gnu_cxx13new_allocatorIcEE *__T2167) {   }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIcEC2ERKS1_ */ __inline__ void _ZN9__gnu_cxx13new_allocatorIcEC2ERKS1_( struct _ZN9__gnu_cxx13new_allocatorIcEE *const this,  const struct _ZN9__gnu_cxx13new_allocatorIcEE *__T2168) {  _ZN9__gnu_cxx13new_allocatorIcEC1ERKS1_(this, __T2168);  }
__asm__(".align 2");

 __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIcED1Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorIcED1Ev( struct _ZN9__gnu_cxx13new_allocatorIcEE *const this) {   }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIcED2Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorIcED2Ev( struct _ZN9__gnu_cxx13new_allocatorIcEE *const this) {  _ZN9__gnu_cxx13new_allocatorIcED1Ev(this);  }
__asm__(".align 2");
# 66 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/ext/new_allocator.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIiEC1Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorIiEC1Ev( struct _ZN9__gnu_cxx13new_allocatorIiEE *const this) {   }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIiEC2Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorIiEC2Ev( struct _ZN9__gnu_cxx13new_allocatorIiEE *const this) {  _ZN9__gnu_cxx13new_allocatorIiEC1Ev(this);  }
__asm__(".align 2");



 __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIiED1Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorIiED1Ev( struct _ZN9__gnu_cxx13new_allocatorIiEE *const this) {   }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIiED2Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorIiED2Ev( struct _ZN9__gnu_cxx13new_allocatorIiEE *const this) {  _ZN9__gnu_cxx13new_allocatorIiED1Ev(this);  }
__asm__(".align 2");
# 66 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/ext/new_allocator.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEEC1Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEEC1Ev( struct _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEEE *const this) {   }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEEC2Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEEC2Ev( struct _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEEE *const this) {  _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEEC1Ev(this);  }
__asm__(".align 2");



 __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEED1Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEED1Ev( struct _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEEE *const this) {   }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEED2Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEED2Ev( struct _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEEE *const this) {  _ZN9__gnu_cxx13new_allocatorISt6vectorIdSaIdEEED1Ev(this);  }
__asm__(".align 2");
# 73 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/ext/new_allocator.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIdED1Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorIdED1Ev( struct _ZN9__gnu_cxx13new_allocatorIdEE *const this) {   }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZN9__gnu_cxx13new_allocatorIdED2Ev */ __inline__ void _ZN9__gnu_cxx13new_allocatorIdED2Ev( struct _ZN9__gnu_cxx13new_allocatorIdEE *const this) {  _ZN9__gnu_cxx13new_allocatorIdED1Ev(this);  }
__asm__(".align 2");
# 48 "/home/saifmulla/openmm/OpenMM/openmmapi/include/openmm/OpenMMException.h"
 __attribute__((__weak__)) /* COMDAT group: _ZN6OpenMM15OpenMMExceptionD1Ev */ __inline__ void _ZN6OpenMM15OpenMMExceptionD1Ev( struct _ZN6OpenMM15OpenMMExceptionE *const this) {  ((this->__b_St9exception).__vptr) = (_ZTVN6OpenMM15OpenMMExceptionE + 2); {
_ZNSsD1Ev((&(this->message))); _ZNSt9exceptionD2Ev((&(this->__b_St9exception))); }  }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZN6OpenMM15OpenMMExceptionD0Ev */ __inline__ void _ZN6OpenMM15OpenMMExceptionD0Ev( struct _ZN6OpenMM15OpenMMExceptionE *const this) {  if (this) { _ZN6OpenMM15OpenMMExceptionD1Ev(this); _ZdlPv(((void *)this)); }  }
__asm__(".align 2");
 __attribute__((__weak__)) /* COMDAT group: _ZN6OpenMM15OpenMMExceptionD2Ev */ __inline__ void _ZN6OpenMM15OpenMMExceptionD2Ev( struct _ZN6OpenMM15OpenMMExceptionE *const this) {  _ZN6OpenMM15OpenMMExceptionD1Ev(this);  }
# 2198 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/basic_string.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_ */ __inline__ void _ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_( struct _ZSs *__T2169,  const struct _ZSs *__lhs, 
const char *__rhs)
{
_ZNSsC1ERKSs(__T2169, __lhs);
_ZNSs6appendEPKcm(__T2169, __rhs, (__builtin_strlen(__rhs)));
return;
}
# 186 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_algobase.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZSt3minIjERKT_S2_S2_ */ __inline__ const unsigned *_ZSt3minIjERKT_S2_S2_( const unsigned *__a,  const unsigned *__b)
{



if ((*__b) < (*__a)) {
return __b; }
return __a;
}
# 119 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_construct.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZSt8_DestroyIPiEvT_S1_ */ __inline__ void _ZSt8_DestroyIPiEvT_S1_( int *__first,  int *__last)
{


{ } 

}
# 582 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_algobase.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZSt22__copy_move_backward_aILb0EPiS0_ET1_T0_S2_S1_ */ __inline__ int *_ZSt22__copy_move_backward_aILb0EPiS0_ET1_T0_S2_S1_( int *__first,  int *__last,  int *__result)
{  ptrdiff_t __T2170;



 char __cuda_local_var_37059_18_const___simple;
# 587 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_algobase.h" 3
__cuda_local_var_37059_18_const___simple = ((char)1);




return ((__T2170 = (((const int *)__last) - ((const int *)__first))) , (void)(__builtin_memmove(((void *)(__result - __T2170)), ((const void *)((const int *)__first)), (4UL * ((unsigned long)__T2170))))) , (__result - __T2170);



}
# 209 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_algobase.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZSt3maxImERKT_S2_S2_ */ __inline__ const _ZNSt6vectorIiSaIiEE9size_typeE *_ZSt3maxImERKT_S2_S2_( const _ZNSt6vectorIiSaIiEE9size_typeE *__a,  const _ZNSt6vectorIiSaIiEE9size_typeE *__b)
{



if ((*__a) < (*__b)) {
return __b; }
return __a;
}
# 106 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_uninitialized.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZSt18uninitialized_copyIPiS0_ET0_T_S2_S1_ */ __inline__ int *_ZSt18uninitialized_copyIPiS0_ET0_T_S2_S1_( int *__first,  int *__last, 
int *__result)
{
# 114 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_uninitialized.h" 3
return (int *)(_ZSt13__copy_move_aILb0EPiS0_ET1_T0_S2_S1_(__first, __last, __result));


}
# 386 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_algobase.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZSt13__copy_move_aILb0EPiS0_ET1_T0_S2_S1_ */ __inline__ int *_ZSt13__copy_move_aILb0EPiS0_ET1_T0_S2_S1_( int *__first,  int *__last,  int *__result)
{



 char __cuda_local_var_36949_18_const___simple;
# 391 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_algobase.h" 3
__cuda_local_var_36949_18_const___simple = ((char)1);




return (__builtin_memmove(((void *)__result), ((const void *)((const int *)__first)), (4UL * ((unsigned long)(((const int *)__last) - ((const int *)__first)))))) , (__result + (((const int *)__last) - ((const int *)__first)));

}
# 119 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_construct.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZSt8_DestroyIPSt6vectorIdSaIdEEEvT_S4_ */ __inline__ void _ZSt8_DestroyIPSt6vectorIdSaIdEEEvT_S4_( struct _ZSt6vectorIdSaIdEE *__first,  struct _ZSt6vectorIdSaIdEE *__last)
{  struct _ZSt6vectorIdSaIdEE *__T2171;
 double *__T2172;
 double *__T2173;
{ __T2171 = __first; { for (; (__T2171 != __last); ++__T2171) { { { __T2172 = (((__T2171->__b_St12_Vector_baseIdSaIdEE)._M_impl)._M_start); __T2173 = (((__T2171->__b_St12_Vector_baseIdSaIdEE)._M_impl)._M_finish); { _ZSt8_DestroyIPdEvT_S1_(__T2172, __T2173); } } { { _ZNSt12_Vector_baseIdSaIdEED1Ev((&(__T2171->__b_St12_Vector_baseIdSaIdEE))); } } } } } } 

}
# 119 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/bits/stl_construct.h" 3
 __attribute__((__weak__)) /* COMDAT group: _ZSt8_DestroyIPdEvT_S1_ */ __inline__ void _ZSt8_DestroyIPdEvT_S1_( double *__first,  double *__last)
{


{ } 

}
# 75 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/ext/atomicity.h" 3
static __inline__ __attribute__((__unused__)) __attribute__((visibility("default"))) _Atomic_word _ZN9__gnu_cxx27__exchange_and_add_dispatchEPii( _Atomic_word *__mem,  int __val)
{  _Atomic_word __T2174;

if (_Z18__gthread_active_pv()) {
return (int)(__sync_fetch_and_add_4(((volatile void *)((volatile _Atomic_word *)__mem)), ((unsigned)__val))); } else  {

return ((__T2174 = (*__mem)) , (void)((*__mem) += __val)) , __T2174; }



}
static void __sti___45_kCalculateAmoebaCudaGrycuk_compute_20_cpp1_ii_e93cfd52(void) {
# 72 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../include/c++/4.4.7/iostream" 3
_ZNSt8ios_base4InitC1Ev((&_ZSt8__ioinit)); __cxa_atexit(_ZNSt8ios_base4InitD1Ev, ((void *)(&_ZSt8__ioinit)), (&__dso_handle));  }

#include "kCalculateAmoebaCudaGrycuk.compute_20.cudafe1.stub.c"
