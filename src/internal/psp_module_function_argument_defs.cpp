
#include "internal/psp_module_function_argument_defs.hpp"

#define CONCAT_(X, Y) X##Y
#define CONCAT(X, Y) CONCAT_(X, Y)
#define S_(x) #x
#define S(x) S_(x)
#define WS(X) CONCAT(L, S(X))
#define WC(x) WS(x)[0]

const char *_get_psp_function_arg_name(psp_function_arg_t arg)
{
    // TODO: optimize
    switch (arg)
    {
    case WC(ARG_NONE):           return "";
    case WC(ARG_VOID):           return "void";
    case WC(ARG_U32):            return "u32";
    case WC(ARG_S32):            return "s32";
    case WC(ARG_FLOAT):          return "float";
    case WC(ARG_U64):            return "u64";
    case WC(ARG_S64):            return "s64";
    case WC(ARG_DOUBLE):         return "double";
    case WC(ARG_CONST_CHAR_PTR): return "const char *";
    case WC(ARG_PTR):            return "ptr";
    case WC(ARG_U32_PTR):        return "u32 *";
    case WC(ARG_S32_PTR):        return "s32 *";
    case WC(ARG_U8):             return "u8";
    case WC(ARG_U8_PTR):         return "u8 *";
    case WC(ARG_CONST_U8_PTR):   return "const u8 *";
    case WC(ARG_CHAR_PTR):       return "char *";
    case WC(ARG_U16):            return "u16";
    case WC(ARG_U16_PTR):        return "u16 *";
    case WC(ARG_S16):            return "s16";
    case WC(ARG_S16_PTR):        return "s16 *";
    case WC(ARG_U64_PTR):        return "u64 *";
    case WC(ARG_S64_PTR):        return "s64 *";
    case WC(ARG_CONST_U64_PTR):  return "const u64 *";
    case WC(ARG_U8_PTR_PTR):     return "u8 **";
    case WC(ARG_S16_PTR_PTR):    return "s16 **";

    case WC(ARG_VOID_PTR):       return "void *";
    case WC(ARG_CONST_VOID_PTR): return "const void *";
    case WC(ARG_VOID_PTR_PTR):   return "void **";

    case WC(ARG_SceUID):         return "SceUID";
    case WC(ARG_SceUID_PTR):     return "SceUID *";
    case WC(ARG_SceSize):        return "SceSize";
    case WC(ARG_SceUChar):       return "SceUChar";
    case WC(ARG_SceUInt):        return "SceUInt";
    case WC(ARG_SceUInt32):      return "SceUInt32";
    case WC(ARG_SceUInt64):      return "SceUInt64";
    case WC(ARG_SceUInt_PTR):    return "SceUInt *";
    case WC(ARG_SceInt):         return "SceInt";
    case WC(ARG_SceInt32):       return "SceInt32";
    case WC(ARG_SceInt64):       return "SceInt64";
    case WC(ARG_SceInt_PTR):     return "SceInt *";
    case WC(ARG_SceInt64_PTR):   return "SceInt64 *";

    case WC(ARG_SceMode):        return "SceMode";
    case WC(ARG_SceOff):         return "SceOff";
    case WC(ARG_SceIores):       return "SceIores";

    case WC(ARG_SceLwMutexWorkarea_PTR):              return "SceLwMutexWorkarea *";
    case WC(ARG_SceKernelEventFlagOptParam_PTR):      return "SceKernelEventFlagOptParam *";
    case WC(ARG_SceKernelEventFlagInfo_PTR):          return "SceKernelEventFlagInfo *";
    case WC(ARG_SceKernelSemaOptParam_PTR):           return "SceKernelSemaOptParam *";
    case WC(ARG_SceKernelSemaInfo_PTR):               return "SceKernelSemaInfo *";
    case WC(ARG_SceKernelThreadEntry):                return "SceKernelThreadEntry";
    case WC(ARG_SceKernelThreadOptParam_PTR):         return "SceKernelThreadOptParam *";
    case WC(ARG_SceKernelSysClock_PTR):               return "SceKernelSysClock *";
    case WC(ARG_SceKernelThreadRunStatus_PTR):        return "SceKernelThreadRunStatus *";
    case WC(ARG_SceKernelThreadInfo_PTR):             return "SceKernelThreadInfo *";
    case WC(ARG_SceKernelIdListType):                 return "SceKernelIdListType";
    case WC(ARG_PspDebugProfilerRegs_PTR):            return "PspDebugProfilerRegs *";
    case WC(ARG_SceKernelSystemStatus_PTR):           return "SceKernelSystemStatus *";
    case WC(ARG_SceKernelAlarmHandler):               return "SceKernelAlarmHandler";
    case WC(ARG_SceKernelAlarmInfo_PTR):              return "SceKernelAlarmInfo *";
    case WC(ARG_SceKernelThreadEventHandler):         return "SceKernelThreadEventHandler";
    case WC(ARG_SceKernelThreadEventHandlerInfo_PTR): return "SceKernelThreadEventHandlerInfo *";
    case WC(ARG_SceKernelCallbackFunction):           return "SceKernelCallbackFunction";
    case WC(ARG_SceKernelCallbackInfo_PTR):           return "SceKernelCallbackInfo *";
    case WC(ARG_SceKernelMbxOptParam_PTR):            return "SceKernelMbxOptParam *";
    case WC(ARG_SceKernelMbxInfo_PTR):                return "SceKernelMbxInfo *";
    case WC(ARG_SceKernelMppInfo_PTR):                return "SceKernelMppInfo *";
    case WC(ARG_SceKernelVplOptParam_PTR):            return "SceKernelVplOptParam *";
    case WC(ARG_SceKernelVplInfo_PTR):                return "SceKernelVplInfo *";
    case WC(ARG_SceKernelFplOptParam_PTR):            return "SceKernelFplOptParam *";
    case WC(ARG_SceKernelFplInfo_PTR):                return "SceKernelFplInfo *";
    case WC(ARG_SceKernelVTimerOptParam_PTR):         return "SceKernelVTimerOptParam *";
    case WC(ARG_SceKernelVTimerInfo_PTR):             return "SceKernelVTimerInfo *";
    case WC(ARG_SceKernelVTimerHandler):              return "SceKernelVTimerHandler";
    case WC(ARG_SceKernelVTimerHandlerWide):          return "SceKernelVTimerHandlerWide";
    case WC(ARG_SceKernelTimeval_PTR):                return "SceKernelTimeval *";
    case WC(ARG_timezone_PTR):                        return "timezone *";
    case WC(ARG_clock_t):                             return "clock_t";
    case WC(ARG_SceKernelLoadExecParam_PTR):          return "SceKernelLoadExecParam *";
    case WC(ARG_SceKernelUtilsMd5Context_PTR):        return "SceKernelUtilsMd5Context *";
    case WC(ARG_time_t):                              return "time_t";
    case WC(ARG_time_t_PTR):                          return "time_t *";
    case WC(ARG_SceKernelUtilsMt19937Context_PTR):    return "SceKernelUtilsMt19937Context *";
    case WC(ARG_PspIntrHandlerOptionParam_PTR):       return "PspIntrHandlerOptionParam *";
    case WC(ARG_SceIoDirent_PTR):                     return "SceIoDirent *";
    case WC(ARG_SceIoStat_PTR):                       return "SceIoStat *";
    case WC(ARG_SceKernelLMOption_PTR):               return "SceKernelLMOption *";
    case WC(ARG_SceKernelSMOption_PTR):               return "SceKernelSMOption *";
    case WC(ARG_SceKernelModuleInfo_PTR):             return "SceKernelModuleInfo *";
    case WC(ARG_SceCtrlData_PTR):                     return "SceCtrlData *";
    case WC(ARG_SceCtrlLatch_PTR):                    return "SceCtrlLatch *";
    case WC(ARG_pspAudioInputParams_PTR):             return "pspAudioInputParams *";
//     case WC(ARG_SceNetMallocStat_PTR):                return "SceNetMallocStat *";
    case WC(ARG_in_addr_PTR):                         return "in_addr *";
    case WC(ARG_CONST_in_addr_PTR):                   return "const in_addr *";
    case WC(ARG_socklen_t):                           return "socklen_t";
    case WC(ARG_socklen_t_PTR):                       return "socklen_t *";
    case WC(ARG_sockaddr_PTR):                        return "sockaddr *";
    case WC(ARG_CONST_sockaddr_PTR):                  return "const sockaddr *";
    case WC(ARG_fd_set_PTR):                          return "fd_set *";
    case WC(ARG_SceNetMallocStat_PTR):                return "SceNetMallocStat *";
    case WC(ARG_msghdr_PTR):                          return "msghdr *";
    case WC(ARG_CONST_msghdr_PTR):                    return "const msghdr *";
    case WC(ARG_in_addr_t):                           return "in_addr_t";
    case WC(ARG_sceNetApctlHandler):                  return "sceNetApctlHandler";
    case WC(ARG_SceNetApctlInfo_PTR):                 return "SceNetApctlInfo *";
    case WC(ARG_pdpStatStruct_PTR):                   return "pdpStatStruct *";
    case WC(ARG_ptpStatStruct_PTR):                   return "ptpStatStruct *";
    case WC(ARG_pspAdhocMatchingCallback):            return "pspAdhocMatchingCallback";
    case WC(ARG_pspAdhocPoolStat_PTR):                return "pspAdhocPoolStat *";
    case WC(ARG_productStruct_PTR):                   return "productStruct *";
    case WC(ARG_sceNetAdhocctlHandler):               return "sceNetAdhocctlHandler";
    case WC(ARG_SceNetAdhocctlParams_PTR):            return "SceNetAdhocctlParams *";
    case WC(ARG_SceNetAdhocctlScanInfo_PTR):          return "SceNetAdhocctlScanInfo *";
    case WC(ARG_SceNetAdhocctlPeerInfo_PTR):          return "SceNetAdhocctlPeerInfo *";
    case WC(ARG_SceNetAdhocctlGameModeInfo_PTR):      return "SceNetAdhocctlGameModeInfo *";
    case WC(ARG_pspTime_PTR):                         return "pspTime *";
    case WC(ARG_CONST_pspTime_PTR):                   return "const pspTime *";
    case WC(ARG_CONST_time_t):                        return "const time_t";
    case WC(ARG_SceMpeg_PTR):                         return "SceMpeg *";
    case WC(ARG_SceMpegStream_PTR):                   return "SceMpegStream *";
    case WC(ARG_SceMpegAu_PTR):                       return "SceMpegAu *";
    case WC(ARG_SceMpegRingbuffer_PTR):               return "SceMpegRingbuffer *";
    case WC(ARG_SceMpeg):                             return "SceMpeg";
    case WC(ARG_SceMpegAvcMode_PTR):                  return "SceMpegAvcMode *";
    case WC(ARG_sceMpegRingbufferCB):                 return "sceMpegRingbufferCB";
    case WC(ARG_SceMp3InitArg_PTR):                   return "SceMp3InitArg *";
    case WC(ARG_PspHttpMethod):                       return "PspHttpMethod";
    case WC(ARG_PspHttpMallocFunction):               return "PspHttpMallocFunction";
    case WC(ARG_PspHttpFreeFunction):                 return "PspHttpFreeFunction";
    case WC(ARG_PspHttpReallocFunction):              return "PspHttpReallocFunction";
    case WC(ARG_PspHttpPasswordCB):                   return "PspHttpPasswordCB";
    case WC(ARG_PspGeListArgs_PTR):                   return "PspGeListArgs *";
    case WC(ARG_PspGeBreakParam_PTR):                 return "PspGeBreakParam *";
    case WC(ARG_PspGeCallbackData_PTR):               return "PspGeCallbackData *";
    case WC(ARG_PspGeContext_PTR):                    return "PspGeContext *";
    case WC(ARG_CONST_PspGeContext_PTR):              return "const PspGeContext *";
    case WC(ARG_PspGeStack_PTR):                      return "PspGeStack *";
    case WC(ARG_pspUmdInfo_PTR):                      return "pspUmdInfo *";
    case WC(ARG_pspUtilityNetConfData_PTR):           return "pspUtilityNetConfData *";
    case WC(ARG_netData_PTR):                         return "netData *";
    case WC(ARG_pspUtilityMsgDialogParams_PTR):       return "pspUtilityMsgDialogParams *";
    case WC(ARG_SceUtilitySavedataParam_PTR):         return "SceUtilitySavedataParam *";
    case WC(ARG_SceUtilityOskParams_PTR):             return "SceUtilityOskParams *";
    case WC(ARG_pspUtilityGameSharingParams_PTR):     return "pspUtilityGameSharingParams *";
    case WC(ARG_pspUtilityHtmlViewerParam_PTR):       return "pspUtilityHtmlViewerParam *";
    case WC(ARG_PspBufferInfo_PTR):                   return "PspBufferInfo *";
    case WC(ARG_PspOpenPSID_PTR):                     return "PspOpenPSID *";
    case WC(ARG_SceKernelUtilsSha1Context_PTR):       return "SceKernelUtilsSha1Context *";
    case WC(ARG_PspDebugPutChar):                     return "PspDebugPutChar";
    case WC(ARG_SceModule_PTR):                       return "SceModule *";
    case WC(ARG_PspIoDrv_PTR):                        return "PspIoDrv *";
    case WC(ARG_SceKernelLoadExecVSHParam_PTR):       return "SceKernelLoadExecVSHParam *";
    case WC(ARG_PspUsbCamSetupVideoParam_PTR):        return "PspUsbCamSetupVideoParam *";
    case WC(ARG_PspUsbCamSetupVideoExParam_PTR):      return "PspUsbCamSetupVideoExParam *";
    case WC(ARG_PspUsbCamSetupStillParam_PTR):        return "PspUsbCamSetupStillParam *";
    case WC(ARG_PspUsbCamSetupStillExParam_PTR):      return "PspUsbCamSetupStillExParam *";
    case WC(ARG_SceNetInetTimeval_PTR):               return "SceNetInetTimeval *";

    case WC(ARG_VA_ARGS):        return "...";
    case WC(ARG_UNKNOWN):        return "?";
    default:                     return "?!";
    }
}
