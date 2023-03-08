/*
 * vestige.h - simple header to allow VeSTige compilation and eventually work
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * This VeSTige header is included in this package in the good-faith
 * belief that it has been cleanly and legally reverse engineered
 * without reference to the official VST SDK and without its
 * developer(s) having agreed to the VST SDK license agreement.
 *
 * References:
 * https://git.iem.at/zmoelnig/FST/-/blob/master/docs/REVERSE_ENGINEERING.md
 * https://github.com/Ardour/ardour/blob/master/libs/ardour/ardour/vestige/vestige.h
 * https://github.com/juce-framework/JUCE/blob/5.0.0/modules/juce_audio_processors/format_types/juce_VSTInterface.h
 */

#ifndef __vestige__
#define __vestige__

#include <stdint.h>
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

#if JUCE_64BIT
    typedef int64 ptr;
#else
    typedef int32 ptr;
#endif

#if JUCE_GCC
    #pragma pack(push,8)
    #define VSTCALLBACK __cdecl
#elif JUCE_MSVC
    #pragma pack(push)
    #pragma pack(8)
    #define VSTCALLBACK __cdecl
#else
    #define VSTCALLBACK
#endif

struct AEffect;
typedef ptr (VSTCALLBACK *audioMasterCallback)(AEffect *, int32, int32, ptr, void *, float);
typedef ptr (VSTCALLBACK *AEffectDispatcherProc)(AEffect *, int32, int32, ptr, void *, float);
typedef void (VSTCALLBACK *AEffectProcessProc)(AEffect *, float **, float **, int32);
typedef void (VSTCALLBACK *AEffectProcessDoubleProc)(AEffect *, double **, double **, int32);
typedef void (VSTCALLBACK *AEffectSetParameterProc)(AEffect *, int32, float);
typedef float (VSTCALLBACK *AEffectGetParameterProc)(AEffect *, int32);

struct AEffect
{
    int32 magic;
    AEffectDispatcherProc dispatcher;
    AEffectProcessProc process;
    AEffectSetParameterProc setParameter;
    AEffectGetParameterProc getParameter;
    int32 numPrograms; 
    int32 numParams;
    int32 numInputs;
    int32 numOutputs;
    int32 flags;
    ptr resvd1;
    ptr resvd2;
    int32 initialDelay;
    int32 realQualities;
    int32 offQualities;
    float ioRatio;
    void *object;
    void *user;
    int32 uniqueID;
    int32 version;
    AEffectProcessProc processReplacing;
    AEffectProcessDoubleProc processDoubleReplacing;
    char unknown[56];
};

enum
{
    kVstProcessPrecision32 = 0, kVstProcessPrecision64 = 1
};

enum
{
    kVstMaxShortLabelLen = 8, kVstMaxLabelLen = 64, kVstMaxNameLen = 64, kVstMaxVendorStrLen = 64, kVstMaxProductStrLen = 64
};

enum
{
    effFlagsHasEditor = 1 << 0, effFlagsCanReplacing = 1 << 4, effFlagsProgramChunks = 1 << 5, effFlagsIsSynth = 1 << 8, effFlagsNoSoundInStop = 1 << 9, effFlagsCanDoubleReplacing = 1 << 12
};

enum
{
    effOpen = 0, effClose, effSetProgram, effGetProgram, effSetProgramName, effGetProgramName, effGetParamLabel, effGetParamDisplay, effGetParamName, effGetVu, effSetSampleRate, effSetBlockSize, effMainsChanged, effEditGetRect, effEditOpen, effEditClose, effEditDraw, effEditMouse, effEditKey, effEditIdle, effEditTop, effEditSleep, effIdentify, effGetChunk, effSetChunk, effProcessEvents, effCanBeAutomated, effString2Parameter, effGetNumProgramCategories, effGetProgramNameIndexed, effCopyProgram, effConnectInput, effConnectOutput, effGetInputProperties, effGetOutputProperties, effGetPlugCategory, effGetCurrentPosition, effGetDestinationBuffer, effOfflineNotify, effOfflinePrepare, effOfflineRun, effProcessVarIo, effSetSpeakerArrangement, effSetBlockSizeAndSampleRate, effSetBypass, effGetEffectName, effGetErrorText, effGetVendorString, effGetProductString, effGetVendorVersion, effVendorSpecific, effCanDo, effGetTailSize, effIdle, effGetIcon, effSetViewPosition, effGetParameterProperties, effKeysRequired, effGetVstVersion, effEditKeyDown, effEditKeyUp, effSetEditKnobMode, effGetMidiProgramName, effGetCurrentMidiProgram, effGetMidiProgramCategory, effHasMidiProgramsChanged, effGetMidiKeyName, effBeginSetProgram, effEndSetProgram, effGetSpeakerArrangement, effShellGetNextPlugin, effStartProcess, effStopProcess, effSetTotalSampleToProcess, effSetPanLaw, effBeginLoadBank, effBeginLoadProgram, effSetProcessPrecision, effGetNumMidiInputChannels, effGetNumMidiOutputChannels
};

enum
{
    audioMasterAutomate = 0, audioMasterVersion, audioMasterCurrentId, audioMasterIdle, audioMasterPinConnected, audioMasterUnknownParam, audioMasterWantMidi, audioMasterGetTime, audioMasterProcessEvents, audioMasterSetTime, audioMasterTempoAt, audioMasterGetNumAutomatableParameters, audioMasterGetParameterQuantization, audioMasterIOChanged, audioMasterNeedIdle, audioMasterSizeWindow, audioMasterGetSampleRate, audioMasterGetBlockSize, audioMasterGetInputLatency, audioMasterGetOutputLatency, audioMasterGetPreviousPlug, audioMasterGetNextPlug, audioMasterWillReplaceOrAccumulate, audioMasterGetCurrentProcessLevel, audioMasterGetAutomationState, audioMasterOfflineStart, audioMasterOfflineRead, audioMasterOfflineWrite, audioMasterOfflineGetCurrentPass, audioMasterOfflineGetCurrentMetaPass, audioMasterSetOutputSampleRate, audioMasterGetOutputSpeakerArrangement, audioMasterGetVendorString, audioMasterGetProductString, audioMasterGetVendorVersion, audioMasterVendorSpecific, audioMasterSetIcon, audioMasterCanDo, audioMasterGetLanguage, audioMasterOpenWindow, audioMasterCloseWindow, audioMasterGetDirectory, audioMasterUpdateDisplay, audioMasterBeginEdit, audioMasterEndEdit, audioMasterOpenFileSelector, audioMasterCloseFileSelector, audioMasterEditFile, audioMasterGetChunkFile, audioMasterGetInputSpeakerArrangement
};

struct ERect
{
    int16 top;
    int16 left;
    int16 bottom;
    int16 right;
};

struct VstEvent
{
    int32 type;
    int32 byteSize;
    int32 deltaFrames;
    int32 flags;
    char data[16];
};

struct VstEvents
{
    int32 numEvents;
    ptr unknown;
    VstEvent *events[2];
};

enum
{
    kVstMidiType = 1, kVstSysExType = 6
};

struct VstMidiEvent
{
    int32 type;
    int32 byteSize;
    int32 deltaFrames;
    int32 flags;
    int32 noteLength;
    int32 noteOffset;
    char midiData[4];
    char detune;
    char noteOffVelocity;
    char unknown1;
    char unknown2;
};

struct VstMidiSysexEvent
{
    int32 type;
    int32 byteSize;
    int32 deltaFrames;
    int32 flags;
    int32 dumpBytes;
    ptr resvd1;
    char *sysexDump;
    ptr resvd2;
};

struct VstTimeInfo
{
    double samplePos;
    double sampleRate;
    double nanoSeconds;
    double ppqPos;
    double tempo;
    double barStartPos;
    double cycleStartPos;
    double cycleEndPos;
    int32 timeSigNumerator;
    int32 timeSigDenominator;
    int32 smpteOffset;
    int32 smpteFrameRate;
    int32 samplesToNextClock;
    int32 flags;
};

enum
{
    kVstTransportChanged = 1, kVstTransportPlaying = 1 << 1, kVstTransportCycleActive = 1 << 2, kVstTransportRecording = 1 << 3, kVstAutomationWriting = 1 << 6, kVstAutomationReading = 1 << 7, kVstNanosValid = 1 << 8, kVstPpqPosValid = 1 << 9, kVstTempoValid = 1 << 10, kVstBarsValid = 1 << 11, kVstCyclePosValid = 1 << 12, kVstTimeSigValid = 1 << 13, kVstSmpteValid = 1 << 14
};

enum
{
    kVstSmpte24fps = 0, kVstSmpte25fps = 1, kVstSmpte2997fps = 2, kVstSmpte30fps = 3, kVstSmpte2997dfps = 4, kVstSmpte30dfps = 5, kVstSmpteFilm16mm = 6, kVstSmpteFilm35mm = 7, kVstSmpte239fps = 10, kVstSmpte249fps = 11, kVstSmpte599fps = 12, kVstSmpte60fps = 13
};

struct VstPinProperties
{
    char label[kVstMaxLabelLen];
    int32 flags;
    int32 arrangementType;
    char shortLabel[kVstMaxShortLabelLen];
    char unknown[48];
};

enum
{
    kVstPinIsActive = 1 << 0, kVstPinIsStereo = 1 << 1, kVstPinUseSpeaker = 1 << 2  
};

enum VstPlugCategory
{
    kPlugCategUnknown = 0, kPlugCategEffect, kPlugCategSynth, kPlugCategAnalysis, kPlugCategMastering, kPlugCategSpacializer, kPlugCategRoomFx, kPlugSurroundFx, kPlugCategRestoration, kPlugCategOfflineProcess, kPlugCategShell, kPlugCategGenerator, kPlugCategMaxCount
};

struct VstSpeakerProperties
{
    float azimuth;
    float elevation;
    float radius;
    float reserved;
    char name[kVstMaxNameLen];
    int32 type;
    char unknown[28];
};

struct VstSpeakerArrangement
{
    int32 type;
    int32 numChannels;
    VstSpeakerProperties speakers[8];
};

enum
{
    kSpeakerUndefined = 0x7fffffff, kSpeakerM = 0, kSpeakerL, kSpeakerR, kSpeakerC, kSpeakerLfe, kSpeakerLs, kSpeakerRs, kSpeakerLc, kSpeakerRc, kSpeakerS, kSpeakerCs = kSpeakerS, kSpeakerSl, kSpeakerSr, kSpeakerTm, kSpeakerTfl, kSpeakerTfc, kSpeakerTfr, kSpeakerTrl, kSpeakerTrc, kSpeakerTrr, kSpeakerLfe2
};

enum
{
    kSpeakerArrUserDefined = -2, kSpeakerArrEmpty = -1, kSpeakerArrMono = 0, kSpeakerArrStereo, kSpeakerArrStereoSurround, kSpeakerArrStereoCenter, kSpeakerArrStereoSide, kSpeakerArrStereoCLfe, kSpeakerArr30Cine, kSpeakerArr30Music, kSpeakerArr31Cine, kSpeakerArr31Music, kSpeakerArr40Cine, kSpeakerArr40Music, kSpeakerArr41Cine, kSpeakerArr41Music, kSpeakerArr50, kSpeakerArr51, kSpeakerArr60Cine, kSpeakerArr60Music, kSpeakerArr61Cine, kSpeakerArr61Music, kSpeakerArr70Cine, kSpeakerArr70Music, kSpeakerArr71Cine, kSpeakerArr71Music, kSpeakerArr80Cine, kSpeakerArr80Music, kSpeakerArr81Cine, kSpeakerArr81Music, kSpeakerArr102
};

#pragma pack(pop)

#endif // __vestige__
