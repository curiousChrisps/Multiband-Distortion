//
//  TestEffectAU.h
//  TestEffectAU
//
//  Created by Chris Nash on 03/10/2014.
//  Copyright (c) 2014 UWE. All rights reserved.
//

#pragma once

#include "TestEffectAUBase.h"


class TestEffectAU : public TestEffectAUBase
{
public:
    TestEffectAU(AudioUnit component) : TestEffectAUBase(component) {}
    
    // for preparing the creation and destruction of your plugin (e.g. allocating/freeing memory)
    OSStatus Initialize();
    void Cleanup();
    
    // callbacks use signed int values as sometimes can be dummy or user values (negative)
    void PresetLoaded(SInt32 iPresetNum, char *sPresetName);
    void OptionChanged(SInt32 iOptionMenu, SInt32 iItem);
    void ButtonPressed(SInt32 iButton);
    
    // tail time describes how long it takes for nominal-level signal to decay to silence at the
    // end of input
    bool SupportsTail() { return true; }
    Float64 GetTailTime() { return 0; }
    
    void UpdateMeters(Float32* pfAllIn);
    void Distortion();
    void OutPutFilter();
    void AddingSignals();
    
    
private:
    SInt32 iMeasuredLenth, iMeasuredItems;
    Float32 fMax0, fMax1, fMax0old, fMax1old;
    
    OSStatus ProcessCore(const Float32 *pfInBuffer0, const Float32 *pfInBuffer1,
                         Float32 *pfOutBuffer0, Float32 *pfOutBuffer1, UInt32 iInStride,
                         UInt32 iOutStride, UInt32 inFramesToProcess );
    
    // add your own shared variables here (accessible by all TestEffectAU functions)
    Float32 FilterGainNew[4];
    Float32 FilterGainOld[4];
    bool bandActives[4];
    bool byPass;
    Float32 fInBand[2][4];
    int PopOptionDistortion[4];
    Float32 fAllIn[2];
    Float32 fAllOut[2][4];
    Float32 fChOut[2];
    Float32 fByPass[2];
};
