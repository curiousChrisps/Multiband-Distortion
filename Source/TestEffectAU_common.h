#ifndef __TestEffectAU_common_h__
#define __TestEffectAU_common_h__

// Much of this information is used twice; once to setup the generic AU view and again for the
// graphical (Cocoa) view.

// Note: KDUMMYVAL cannot be used as a genuine parameter value
#define KDUMMYVAL -1000
#define DUMMYSTRING "?????"
#define GCCNOWARN __attribute__((unused))

enum {
    kOption0 = 0, kOption1, kOption2, kOption3, kOption4, kValue0, kValue1, kValue2, kValue3, kValue4, kValue5, kValue6, kValue7, kValue8, kValue9, kValue10, kValue11, kNumberOfParameters
};

enum { kNumberOfOptionMenus = kValue0 };

static const char* __attribute__((unused)) kParameterNames[kNumberOfParameters] = {
    "LF Dist.", "Low Mid Dist.", "High Mid Dist.", "HF Dist.", "Output Filter",
    "LF Gain", "Low Mid Gain", "High Mid Gain", "HF Gain",
    "Filter Cutoff", "Q", "Output Gain", "Value 7",
    "Value 8", "Value 9", "Value 10", "Value 11"};

static const Boolean kParameterVisible[kNumberOfParameters] =
{true, true, true, true, true, true, true, true, true, true, true, true, false, false, false, false, false};

// ====================================================================================
// Popup menu (option) items

enum {
    kItem0 = 0, kItem1, kItem2, kItem3, kItem4, kItem5, kMaxItems
};

static const char *kItemNames[kNumberOfOptionMenus][kMaxItems] = {
    {"No Distortion", "Hard Clipping", "Soft Clipping", "Quarter Circle", "Assymetric", "Folding"},
    {"No Distortion", "Hard Clipping", "Soft Clipping", "Quarter Circle", "Assymetric", "Folding"},
    {"No Distortion", "Hard Clipping", "Soft Clipping", "Quarter Circle", "Assymetric", "Folding"},
    {"No Distortion", "Hard Clipping", "Soft Clipping", "Quarter Circle", "Assymetric", "Folding"},
    {"No Filter", "Low Pass", "High Pass", "Band Pass", "Band Reject"}
    
};
// REMEMBER to update the kMaxValues array if the number of items change
// (not very elegant, but cannot initialise an array with a value computed with sizeof at compile time)

// ====================================================================================
// Ranges and defaults

static const Float32 kMinValues[kNumberOfParameters] = {kItem0, kItem0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static const Float32 kMaxValues[kNumberOfParameters] = {kItem5, kItem5, kItem5, kItem5, kItem4, 1, 1, 1, 1, 1, 1, 1, 1, 1};
static const Float32 kDefaultValues[kNumberOfParameters] = {kItem0, kItem0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// parameter defaults will only apply if have not saved a different configuration in the host
// (e.g. in AU Lab .trak file settings will often override these)

// ====================================================================================
// Buttons

enum {
    kButton0 = 0, kButton1, kButton2, kButton3, kButton4, kNumberOfButtons
};

static const char GCCNOWARN *kButtonNames[kNumberOfButtons] = {
    "Band 1", "Band 2", "Band 3", "Band 4", "Bypass"};
static const Boolean kButtonsVisible = true; // including the indicators

// ====================================================================================
// Filters

enum { kFilter0 = 0, kFilter1, kFilter2, kFilter3, kFilter4, kFilter5, kFilter6, kFilter7, kNumberOfFilters };

// ====================================================================================
// Documentation window

static const char GCCNOWARN *kDocumentationTitle = "Information";
static const char GCCNOWARN *kDocumentationText =
"This is the place to describe what the plugin does and how to use the controls.\n\n"
"At the moment this is just some example text.\n";

// ====================================================================================
// Factory presets

enum{
    kPreset0 = 0, kPreset1, kPreset2, kPreset3, kPreset4, kNumberOfPresets
};

static const char GCCNOWARN *kPresetNames[kNumberOfPresets] = {"Default", "Smokey Drums", "Metal Guitar", "Rock Guitar", "Bright'N'Noise"};

// use KDUMMYVAL if something is supposed to be ignored

static const Float32 kPresetValues[kNumberOfPresets][kNumberOfParameters] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {kItem5, kItem5, kItem5, kItem5, kItem4, 1, 1, 1, 1, 1, 0, 1, 0, 0},
    {kItem5, kItem5, kItem5, kItem5, kItem4, 1, 1, 1, 1, 1, 0, 1, 0, 0},
    {kItem5, kItem5, kItem5, kItem5, kItem4, 1, 1, 1, 1, 1, 0, 1, 0, 0},
    {kItem5, kItem5, kItem5, kItem5, kItem4, 1, 1, 1, 1, 1, 0, 1, 0, 0}
};
static const int kDefaultPreset = KDUMMYVAL;

// ====================================================================================
// Notification Interval for parameter listener
#define PARAMETER_UPDATE_TIME 0.050

// Notification Interval for property event listener
#define PROPERTY_UPDATE_TIME 0.005
// Multiple events are ignored below granularity limit
#define PROPERTY_GRANULARITY_TIME 0.001

// constant to describe indicator update rate in seconds,
// such that can update values at suitable speed etc.
#define INDICATOR_UPDATE_TIME 0.020

// ====================================================================================
// indicators above buttons first, then meters
enum
{
    kMeterLeft = kNumberOfButtons,
    kMeterRight,
    kNumberOfIndicators
};

static const Boolean kMetersVisible = true;

#define kIndicatorsPropertyID 64000
#define kButtonsPropertyID 64001

#endif