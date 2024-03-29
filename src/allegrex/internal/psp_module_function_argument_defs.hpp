
#pragma once

#include "allegrex/internal/map_macro.hpp"

#define CONCAT__(X, Y) X##Y
#define CONCAT_(X, Y) CONCAT__(X, Y)
#define S__(x) #x
#define S_(x) S__(x)
#define WS_(X) CONCAT_(L, S_(X))
#define C_(x) S__(x)[0]
#define WC_(x) WS_(x)[0]
#define RET(x) WS_(x)[0] // same as WC_

#define ARGS(...) MAP(WS_, __VA_ARGS__)

#define NO_ARGS L""

typedef wchar_t psp_function_arg_t;
const char *_get_psp_function_arg_name(psp_function_arg_t arg);

// type of arguments and return value of psp functions
#define ARG_NONE           \x0000
#define ARG_VOID           \x0001
#define ARG_U32            \x0002
#define ARG_S32            \x0003
#define ARG_FLOAT          \x0004
#define ARG_U64            \x0005
#define ARG_S64            \x0006
#define ARG_DOUBLE         \x0007
#define ARG_CONST_CHAR_PTR \x0008
#define ARG_PTR            \x0009  // u32*
#define ARG_U32_PTR        \x000a
#define ARG_S32_PTR        \x000b
#define ARG_U8             \x000c
#define ARG_U8_PTR         \x000d
#define ARG_CONST_U8_PTR   \x000e
#define ARG_CHAR_PTR       \x000f
#define ARG_U16            \x0010
#define ARG_U16_PTR        \x0011
#define ARG_S16            \x0012
#define ARG_S16_PTR        \x0013
#define ARG_U64_PTR        \x0014
#define ARG_S64_PTR        \x0015
#define ARG_CONST_U64_PTR  \x0016
#define ARG_U8_PTR_PTR     \x0017
#define ARG_S16_PTR_PTR    \x0018

#define ARG_VOID_PTR       \x001d
#define ARG_CONST_VOID_PTR \x001e
#define ARG_VOID_PTR_PTR   \x001f

#define ARG_SceUID         \x0020
#define ARG_SceUID_PTR     \x0021
#define ARG_SceSize        \x0022
#define ARG_SceUChar       \x0023
#define ARG_SceUInt        \x0024
#define ARG_SceUInt32      \x0025
#define ARG_SceUInt64      \x0026
#define ARG_SceUInt_PTR    \x0027
#define ARG_SceInt         \x0028
#define ARG_SceInt32       \x0029
#define ARG_SceInt64       \x002a
#define ARG_SceInt_PTR     \x002b
#define ARG_SceInt64_PTR   \x002c

#define ARG_SceMode        \x0030
#define ARG_SceOff         \x0031
#define ARG_SceIores       \x0032

#define ARG_SceLwMutexWorkarea_PTR              \x0100
#define ARG_SceKernelEventFlagOptParam_PTR      \x0101
#define ARG_SceKernelEventFlagInfo_PTR          \x0102
#define ARG_SceKernelSemaOptParam_PTR           \x0103
#define ARG_SceKernelSemaInfo_PTR               \x0104
#define ARG_SceKernelThreadEntry                \x0105
#define ARG_SceKernelThreadOptParam_PTR         \x0106
#define ARG_SceKernelSysClock_PTR               \x0107
#define ARG_SceKernelThreadRunStatus_PTR        \x0108
#define ARG_SceKernelThreadInfo_PTR             \x0109
#define ARG_SceKernelIdListType                 \x010a
#define ARG_PspDebugProfilerRegs_PTR            \x010b
#define ARG_SceKernelSystemStatus_PTR           \x010c
#define ARG_SceKernelAlarmHandler               \x010d
#define ARG_SceKernelAlarmInfo_PTR              \x010e
#define ARG_SceKernelThreadEventHandler         \x010f
#define ARG_SceKernelThreadEventHandlerInfo_PTR \x0110
#define ARG_SceKernelCallbackFunction           \x0111
#define ARG_SceKernelCallbackInfo_PTR           \x0112
#define ARG_SceKernelMbxOptParam_PTR            \x0113
#define ARG_SceKernelMbxInfo_PTR                \x0114
#define ARG_SceKernelMppInfo_PTR                \x0115
#define ARG_SceKernelVplOptParam_PTR            \x0116
#define ARG_SceKernelVplInfo_PTR                \x0117
#define ARG_SceKernelFplOptParam_PTR            \x0118
#define ARG_SceKernelFplInfo_PTR                \x0119
#define ARG_SceKernelVTimerOptParam_PTR         \x011a
#define ARG_SceKernelVTimerInfo_PTR             \x011b
#define ARG_SceKernelVTimerHandler              \x011c
#define ARG_SceKernelVTimerHandlerWide          \x011d
#define ARG_SceKernelTimeval_PTR                \x011e
#define ARG_timezone_PTR                        \x011f
#define ARG_clock_t                             \x0120
#define ARG_SceKernelLoadExecParam_PTR          \x0121
#define ARG_SceKernelUtilsMd5Context_PTR        \x0122
#define ARG_time_t                              \x0123
#define ARG_time_t_PTR                          \x0124
#define ARG_SceKernelUtilsMt19937Context_PTR    \x0125
#define ARG_PspIntrHandlerOptionParam_PTR       \x0126
#define ARG_SceIoDirent_PTR                     \x0127
#define ARG_SceIoStat_PTR                       \x0128
#define ARG_SceKernelLMOption_PTR               \x0129
#define ARG_SceKernelSMOption_PTR               \x012a
#define ARG_SceKernelModuleInfo_PTR             \x012b
#define ARG_SceCtrlData_PTR                     \x012c
#define ARG_SceCtrlLatch_PTR                    \x012d
#define ARG_pspAudioInputParams_PTR             \x012e
#define ARG_msghdr_PTR                          \x012f
#define ARG_CONST_msghdr_PTR                    \x0130
#define ARG_in_addr_PTR                         \x0131
#define ARG_CONST_in_addr_PTR                   \x0132
#define ARG_socklen_t                           \x0133
#define ARG_socklen_t_PTR                       \x0134
#define ARG_sockaddr_PTR                        \x0135
#define ARG_CONST_sockaddr_PTR                  \x0136
#define ARG_fd_set_PTR                          \x0137
#define ARG_SceNetMallocStat_PTR                \x0138
#define ARG_in_addr_t                           \x0139
#define ARG_sceNetApctlHandler                  \x013a
#define ARG_SceNetApctlInfo_PTR                 \x013b
#define ARG_pdpStatStruct_PTR                   \x013c
#define ARG_ptpStatStruct_PTR                   \x013d
#define ARG_pspAdhocMatchingCallback            \x013e
#define ARG_pspAdhocPoolStat_PTR                \x013f
#define ARG_productStruct_PTR                   \x0140
#define ARG_sceNetAdhocctlHandler               \x0141
#define ARG_SceNetAdhocctlParams_PTR            \x0142
#define ARG_SceNetAdhocctlScanInfo_PTR          \x0143
#define ARG_SceNetAdhocctlPeerInfo_PTR          \x0144
#define ARG_SceNetAdhocctlGameModeInfo_PTR      \x0145
#define ARG_pspTime_PTR                         \x0146
#define ARG_CONST_pspTime_PTR                   \x0147
#define ARG_CONST_time_t                        \x0148
#define ARG_SceMpeg_PTR                         \x0149
#define ARG_SceMpegStream_PTR                   \x014a
#define ARG_SceMpegAu_PTR                       \x014b
#define ARG_SceMpegRingbuffer_PTR               \x014c
#define ARG_SceMpeg                             \x014d // should this exist or be replaced with ARG_SceMpeg_PTR?
#define ARG_SceMpegAvcMode_PTR                  \x014e
#define ARG_sceMpegRingbufferCB                 \x014f
#define ARG_SceMp3InitArg_PTR                   \x0150
#define ARG_PspHttpMethod                       \x0151
#define ARG_PspHttpMallocFunction               \x0152
#define ARG_PspHttpFreeFunction                 \x0153
#define ARG_PspHttpReallocFunction              \x0154
#define ARG_PspHttpPasswordCB                   \x0155
#define ARG_PspGeListArgs_PTR                   \x0156
#define ARG_PspGeBreakParam_PTR                 \x0157
#define ARG_PspGeCallbackData_PTR               \x0158
#define ARG_PspGeContext_PTR                    \x0159
#define ARG_CONST_PspGeContext_PTR              \x015a
#define ARG_PspGeStack_PTR                      \x015b
#define ARG_pspUmdInfo_PTR                      \x015c
#define ARG_pspUtilityNetConfData_PTR           \x015d
#define ARG_netData_PTR                         \x015e
#define ARG_pspUtilityMsgDialogParams_PTR       \x015f
#define ARG_SceUtilitySavedataParam_PTR         \x0160
#define ARG_SceUtilityOskParams_PTR             \x0161
#define ARG_pspUtilityGameSharingParams_PTR     \x0162
#define ARG_pspUtilityHtmlViewerParam_PTR       \x0163
#define ARG_PspBufferInfo_PTR                   \x0164
#define ARG_PspOpenPSID_PTR                     \x0165
#define ARG_SceKernelUtilsSha1Context_PTR       \x0166
#define ARG_PspDebugPutChar                     \x0167
#define ARG_SceModule_PTR                       \x0168
#define ARG_PspIoDrv_PTR                        \x0169
#define ARG_SceKernelLoadExecVSHParam_PTR       \x016a
#define ARG_PspUsbCamSetupVideoParam_PTR        \x016b
#define ARG_PspUsbCamSetupVideoExParam_PTR      \x016c
#define ARG_PspUsbCamSetupStillParam_PTR        \x016d
#define ARG_PspUsbCamSetupStillExParam_PTR      \x016e
#define ARG_SceNetInetTimeval_PTR               \x016f

#define ARG_VA_ARGS        \xfffe
#define ARG_UNKNOWN        \xffff

