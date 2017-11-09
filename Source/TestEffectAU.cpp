//
//  TestEffectAU.cpp
//  TestEffectAU
//
//  Created by Chris Nash on 01/10/2014.
//  Copyright (c) 2014 UWE. All rights reserved.
//

#include "TestEffectAU.h"
#include "Distortions.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

AUDIOCOMPONENT_ENTRY(AUBaseFactory, TestEffectAU)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Initialize and Cleanup are only called on creation and destruction

OSStatus TestEffectAU::Initialize()
{
    OSStatus res = TestEffectAUBase::Initialize(); // do basic setup
    
    // put your own additional initialisations here (e.g. allocating memory)
    iMeasuredLenth = (SInt32)(0.001 * GetSampleRate());
    iMeasuredItems = 0;
    fMax0 = fMax1 = fMax0old = fMax1old = 0;
    bandActives[0] = bandActives[1] = bandActives[2] = bandActives[3] = byPass = false;
    FilterGainNew[0] = FilterGainNew[1] = FilterGainNew[2] = FilterGainNew[3] = 0.0;
    FilterGainOld[0] = FilterGainOld[1] = FilterGainOld[2] = FilterGainOld[3] = 0.0;
    fByPass[0] = fByPass[1] = 0.0;
    return res;
}

void TestEffectAU::Cleanup()
{
    // put your own additional clean up code here (e.g. free memory)
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void TestEffectAU::PresetLoaded(SInt32 iPresetNum, char *sPresetName)
{
    // a preset has been loaded, so you could perform setup, such as retrieving parameter values
    // using GetParameter and use them to set state variables in the plugin
    if (iPresetNum == 0) {                            //DEFAULT
        SetParameter(kValue6, 0.75);
        SetParameterRefreshView(kValue6, 0.75);
    }else if (iPresetNum == 1) {                      //SMOKEY DRUMS
        SetParameter(kOption0, 5.0);
        SetParameterRefreshView(kOption0, 5.0);
        SetParameter(kOption1, 4.0);
        SetParameterRefreshView(kOption1, 4.0);
        SetParameter(kOption2, 1.0);
        SetParameterRefreshView(kOption2, 1.0);
        SetParameter(kOption3, 0.0);
        SetParameterRefreshView(kOption3, 0.0);
        SetParameter(kOption4, 1.0);
        SetParameterRefreshView(kOption4, 1.0);
        SetParameter(kValue0, 0.5);
        SetParameterRefreshView(kValue0, 0.5);
        SetParameter(kValue1, 0.5);
        SetParameterRefreshView(kValue1, 0.5);
        SetParameter(kValue2, 0.5);
        SetParameterRefreshView(kValue2, 0.5);
        SetParameter(kValue3, 0.5);
        SetParameterRefreshView(kValue3, 0.5);
        SetParameter(kValue4, 0.67);
        SetParameterRefreshView(kValue4, 0.67);
        SetParameter(kValue6, 0.75);
        SetParameterRefreshView(kValue6, 0.75);
    }else if (iPresetNum == 2){                     //METAL GUITAR
        SetParameter(kOption0, 5.0);
        SetParameterRefreshView(kOption0, 5.0);
        SetParameter(kOption1, 3.0);
        SetParameterRefreshView(kOption1, 3.0);
        SetParameter(kOption2, 1.0);
        SetParameterRefreshView(kOption2, 1.0);
        SetParameter(kOption3, 4.0);
        SetParameterRefreshView(kOption3, 4.0);
        SetParameter(kOption4, 0.0);
        SetParameterRefreshView(kOption4, 0.0);
        SetParameter(kValue0, 0.67);
        SetParameterRefreshView(kValue0, 0.67);
        SetParameter(kValue1, 0.34);
        SetParameterRefreshView(kValue1, 0.34);
        SetParameter(kValue2, 0.57);
        SetParameterRefreshView(kValue2, 0.57);
        SetParameter(kValue3, 0.72);
        SetParameterRefreshView(kValue3, 0.72);
        SetParameter(kValue4, 0.0);
        SetParameterRefreshView(kValue4, 0.0);
        SetParameter(kValue5, 0.0);
        SetParameterRefreshView(kValue5, 0.0);
        SetParameter(kValue6, 0.75);
        SetParameterRefreshView(kValue6, 0.75);
    }else if (iPresetNum == 3){                     //ROCK GUITAR
        SetParameter(kOption0, 5.0);
        SetParameterRefreshView(kOption0, 5.0);
        SetParameter(kOption1, 2.0);
        SetParameterRefreshView(kOption1, 2.0);
        SetParameter(kOption2, 5.0);
        SetParameterRefreshView(kOption2, 5.0);
        SetParameter(kOption3, 0.0);
        SetParameterRefreshView(kOption3, 0.0);
        SetParameter(kOption4, 1.0);
        SetParameterRefreshView(kOption4, 1.0);
        SetParameter(kValue0, 0.58);
        SetParameterRefreshView(kValue0, 0.58);
        SetParameter(kValue1, 0.58);
        SetParameterRefreshView(kValue1, 0.58);
        SetParameter(kValue2, 0.45);
        SetParameterRefreshView(kValue2, 0.45);
        SetParameter(kValue3, 0.40);
        SetParameterRefreshView(kValue3, 0.40);
        SetParameter(kValue4, 0.82);
        SetParameterRefreshView(kValue4, 0.82);
        SetParameter(kValue6, 0.75);
        SetParameterRefreshView(kValue6, 0.75);
    }else if (iPresetNum == 4) {                    //BRIGHT'N'NOISE
        SetParameter(kOption0, 0.0);
        SetParameterRefreshView(kOption0, 0.0);
        SetParameter(kOption1, 0.0);
        SetParameterRefreshView(kOption1, 0.0);
        SetParameter(kOption2, 1.0);
        SetParameterRefreshView(kOption2, 1.0);
        SetParameter(kOption3, 3.0);
        SetParameterRefreshView(kOption3, 3.0);
        SetParameter(kOption4, 2.0);
        SetParameterRefreshView(kOption4, 2.0);
        SetParameter(kValue0, 0.02);
        SetParameterRefreshView(kValue0, 0.02);
        SetParameter(kValue1, 0.1);
        SetParameterRefreshView(kValue1, 0.1);
        SetParameter(kValue2, 0.25);
        SetParameterRefreshView(kValue2, 0.25);
        SetParameter(kValue3, 0.21);
        SetParameterRefreshView(kValue3, 0.21);
        SetParameter(kValue4, 0.14);
        SetParameterRefreshView(kValue4, 0.14);
        SetParameter(kValue6, 0.75);
        SetParameterRefreshView(kValue6, 0.75);
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void TestEffectAU::OptionChanged(SInt32 iOptionMenu, SInt32 iItem)
{
    // the option menu, with index iOptionMenu, has been changed to the entry, iItem
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void TestEffectAU::ButtonPressed(SInt32 iButton)
{
    if (iButton == 5) {
        byPass = !byPass;
        pfIndicatorValues[4] = byPass;
    }else{
        bandActives[iButton] = !bandActives[iButton];
        pfIndicatorValues[iButton] = bandActives[iButton];
    }

}
//===============================================================================================
//  START                D   I   S   T   O   R   T   I   O   N
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TestEffectAU::Distortion()
{
    for (int indexBand = 0; indexBand < 4; indexBand++) {
        switch (PopOptionDistortion[indexBand]) {
            case 0:
                fInBand[0][indexBand] = NoDistortion(fInBand[0][indexBand]);
                fInBand[1][indexBand] = NoDistortion(fInBand[1][indexBand]);
                break;
                
            case 1:
                fInBand[0][indexBand] = HardClip(fInBand[0][indexBand]);
                fInBand[1][indexBand] = HardClip(fInBand[1][indexBand]);
                break;
                
            case 2:
                fInBand[0][indexBand] = SoftClip(fInBand[0][indexBand]);
                fInBand[1][indexBand] = SoftClip(fInBand[1][indexBand]);
                break;
                
            case 3:
                fInBand[0][indexBand] = QuarterCircle(fInBand[0][indexBand]);
                fInBand[1][indexBand] = QuarterCircle(fInBand[1][indexBand]);
                break;
                
            case 4:
                fInBand[0][indexBand] = Asymmetric(fInBand[0][indexBand]);
                fInBand[1][indexBand] = Asymmetric(fInBand[1][indexBand]);
                break;
                
            case 5:
                fInBand[0][indexBand] = Folding(fInBand[0][indexBand]);
                fInBand[1][indexBand] = Folding(fInBand[1][indexBand]);
                break;
                
            default:
                break;
        }
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  END                  D   I   S   T   O   R   T   I   O   N
//===============================================================================================
//  START            A   D   D   I   N   G       S   I   G   N   A   L   S
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void TestEffectAU::AddingSignals()
{
    //Adding the bands together
    //But only those which are active
    fAllIn[0] = fAllIn[1] = 0;
    for (int indexBand = 0; indexBand < 4; indexBand++) {
        fAllIn[0] += (fInBand[0][indexBand] * bandActives[indexBand]);
        fAllIn[1] += (fInBand[1][indexBand] * bandActives[indexBand]);
    }
    fAllIn[0] *= 0.25;
    fAllIn[1] *= 0.25;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  END              A   D   D   I   N   G       S   I   G   N   A   L   S
//===============================================================================================
//  START                  F   I   L   T   E   R   I   N   G
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TestEffectAU::OutPutFilter()
{
    //Splitting the signal into the 4 filters
    for (int filterNum = 0; filterNum < 4; filterNum++) {
        fAllOut[0][filterNum] = (pFilters[kFilter0 + filterNum]->Filter(fAllIn[0]));
        fAllOut[1][filterNum] = (pFilters[kFilter0 + filterNum]->Filter(fAllIn[1]));
    }
    
    
    fChOut[0] = fChOut[1] = 0;
    //calculating the fading gain between the filters ++ Adding the signals together
    for (int filterNum = 0; filterNum < 4; filterNum++) {
        FilterGainOld[filterNum] = (FilterGainNew[filterNum] * 0.1) + (FilterGainOld[filterNum] * 0.9);
        fChOut[0] += (fAllOut[0][filterNum] * FilterGainOld[filterNum]);
        fChOut[1] += (fAllOut[1][filterNum] * FilterGainOld[filterNum]);
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  END                    F   I   L   T   E   R   I   N   G
//===============================================================================================
//  START                    M   E   T   E   R   I   N   G
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TestEffectAU::UpdateMeters(Float32* pfAllIn){
    Float32 Aval0, Aval1;
    
    //METERING
    //obtain absolute values
    Aval0 = fabsf(pfAllIn[0]);
    Aval1 = fabsf(pfAllIn[1]);
    
    //update if bigger
    if (Aval0 > fMax0) {
        fMax0 = Aval0;
    }
    if (Aval1 > fMax1) {
        fMax1 = Aval1;
    }
    
    //increment counter
    iMeasuredItems++;
    
    //compare to cycle lenth --> output meterValues --> reset values
    if (iMeasuredItems == iMeasuredLenth) {
        //remap values
        fMax0 = log10((fMax0 * 40) + 1) / log10(40);
        fMax1 = log10((fMax1 * 40) + 1) / log10(40);
        
        
        //SLOW DECAY
        if (fMax0 < fMax0old) {
            fMax0 = (fMax0 * 0.1) + (fMax0old * 0.9);
        }
        if (fMax1 < fMax1old) {
            fMax1 = (fMax1 * 0.1) + (fMax1old * 0.9);
        }
        
        //sending values to the meters
        pfIndicatorValues[kMeterLeft] = fMax0;
        pfIndicatorValues[kMeterRight] = fMax1;
        
        //storing old values
        fMax0old = fMax0;
        fMax1old = fMax1;
        
        //reset values
        fMax0 = fMax1 = iMeasuredItems = 0;
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  END                      M   E   T   E   R   I   N   G
//===============================================================================================
//|| START |||||||||||||| P   R   O   C   E   S   S   C   O   R   E  ||||||||||||||||||||||||||||
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
OSStatus TestEffectAU::ProcessCore(const Float32 *pfInBuffer0,
                                   const Float32 *pfInBuffer1,
                                   Float32 *pfOutBuffer0,
                                   Float32 *pfOutBuffer1,
                                   UInt32 iInStride,
                                   UInt32 iOutStride,
                                   UInt32 inFramesToProcess)
{
    
    const int NUMBER_OF_BANDS = 4;
    const int NUMBER_OF_FILTERS = 4;
    
    Float32 fInGainBand[NUMBER_OF_BANDS];                      //Declare and then initialize fInGainBand array
    for (int i = 0; i < NUMBER_OF_BANDS; i++) {
        fInGainBand[i] = GetParameter(kValue0 + i);
        fInGainBand[i] *= 24;
        fInGainBand[i] += 1;
    }
 
    Float32 fCutoff = GetParameter(kValue4);
    Float32 fQ = GetParameter(kValue5);
    Float32 fOutGain = GetParameter(kValue6);
    int PopOptionFilter = (int) GetParameter(kOption4);
    
    for (int i = 0; i < 4; i++) {                               //Initializing PopOptionDistortion array
        PopOptionDistortion[i] = GetParameter(kOption0 + i);
    }
    //Cubing and scaling of UI parameter values
    fOutGain = fOutGain * fOutGain * fOutGain;
    fCutoff = fCutoff * fCutoff * fCutoff;
    fCutoff *= 20000.0;
    fCutoff += 20.0;
    fQ = fQ * fQ * fQ;
    fQ *= 20000.0;
    fQ += 20.0;
    //Filter configurations
    pFilters[kFilter0] -> FilterConfig(kLPF, fCutoff, fQ);      //Output filters that are controlled from the user interface
    pFilters[kFilter1] -> FilterConfig(kHPF, fCutoff, fQ);
    pFilters[kFilter2] -> FilterConfig(kBPF, fCutoff, fQ);
    pFilters[kFilter3] -> FilterConfig(kBRF, fCutoff, fQ);
    pFilters[kFilter4] -> FilterConfig(kBPF, 100, 200);         //Filters to split the signal into 4 bands
    pFilters[kFilter5] -> FilterConfig(kBPF, 600, 900);
    pFilters[kFilter6] -> FilterConfig(kBPF, 4500, 10000);
    pFilters[kFilter7] -> FilterConfig(kBPF, 15000, 15000);
//===============================================================================================
    //Filter Choice; Sets the gain of selected filter to 1 and all others to 0
    switch (PopOptionFilter) {
        case 0:
            break;
            
        case 1:  //LPF
            for (int filterNum = 0; filterNum < NUMBER_OF_FILTERS; filterNum++) {
                FilterGainNew[filterNum] = 0.0;
            }
            FilterGainNew[0] = 1.0;
            break;
            
        case 2: //HPF
            for (int filterNum = 0; filterNum < NUMBER_OF_FILTERS; filterNum++) {
                FilterGainNew[filterNum] = 0.0;
            }
            FilterGainNew[1] = 1.0;
            break;
            
        case 3: //BPF
            for (int filterNum = 0; filterNum < NUMBER_OF_FILTERS; filterNum++) {
                FilterGainNew[filterNum] = 0.0;
            }
            FilterGainNew[2] = 1.0;
            break;
            
        case 4: //kBRF
            for (int filterNum = 0; filterNum < NUMBER_OF_FILTERS; filterNum++) {
                FilterGainNew[filterNum] = 0.0;
            }
            FilterGainNew[3] = 1.0;
            break;
            
        default:
            break;
    }
//================================================================================================
//************//************//  WHILE   LOOP   STARTS  //************//************//***********//
//================================================================================================
    
    // loop while there are still sample frame to process
    while ( inFramesToProcess-- )
    {
        // Read left and right input samples into local array
        // Splitting input signal into four bands
        for (int indexCh = 0; indexCh < 2; indexCh++) {
            for (int indexBand = 0; indexBand < 4; indexBand++) {
                fInBand[indexCh][indexBand] = (indexCh == 0) ? *pfInBuffer0 : *pfInBuffer1;
            }
        }
        
        //Scaling splitted signals' bandwidths ++ applying overdrive gain ++ retrieving bypass signal
        fByPass[0] = fByPass[1] = 0;
        for (int indexBand = 0; indexBand < NUMBER_OF_BANDS; indexBand++) {
            fInBand[0][indexBand] = (pFilters[kFilter4 + indexBand]->Filter(fInBand[0][indexBand]));
            fInBand[1][indexBand] = (pFilters[kFilter4 + indexBand]->Filter(fInBand[1][indexBand]));
            
            fInBand[0][indexBand] *= fInGainBand[indexBand];
            fInBand[1][indexBand] *= fInGainBand[indexBand];
            
            fByPass[0] += (fInBand[0][indexBand] * bandActives[indexBand]);
            fByPass[1] += (fInBand[1][indexBand] * bandActives[indexBand]);
        }
        
        fByPass[0] *= 0.25;
        fByPass[1] *= 0.25;
//=============================================Processing Functions==============================
        Distortion();
        AddingSignals();
        OutPutFilter();
        UpdateMeters(fAllIn);
//=============================================Output Processing=================================
        //Output Gain
        for (int i = 0; i < 2; i++) {
            fAllIn[i] *= fOutGain;
            fChOut[i] *= fOutGain;
            fByPass[i]  *= fOutGain;
        }
        // write processed local variables to left and right output samples
        // IF filter is OFF then only output distortion, else filter.
        if (PopOptionFilter == 0) {
            *pfOutBuffer0 = fAllIn[0];
            *pfOutBuffer1 = fAllIn[1];
        }else{
            *pfOutBuffer0 = fChOut[0];
            *pfOutBuffer1 = fChOut[1];
        }
        if(byPass == 1){
            *pfOutBuffer0 = fByPass[0];
            *pfOutBuffer1 = fByPass[1];
        }
        // move pointers along input and output buffers ready for next frame
        pfInBuffer0 += iInStride;
        pfInBuffer1 += iInStride;
        pfOutBuffer0 += iOutStride;
        pfOutBuffer1 += iOutStride;
    }
//================================================================================================
//************//************//  WHILE   LOOP   ENDS  //*************//************//************//
//================================================================================================
    return noErr;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//|| END |||||||||||||| P   R   O   C   E   S   S   C   O   R   E  |||||||||||||||||||||||||||||||
//================================================================================================

