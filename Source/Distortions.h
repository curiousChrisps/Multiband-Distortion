//
//  Distortions.h
//  TestEffectAU
//
//  Created by Christoph Schick on 27/10/2015.
//  Copyright (c) 2015 UWE. All rights reserved.
//

#ifndef TestEffectAU_Distortions_h
#define TestEffectAU_Distortions_h


//NoDistortion (Value 0)
float NoDistortion(float x)
{
    return x;
}

//HardClip (Value 1)
float HardClip(float x)
{
    float y = 0;
    
    if (x > 1) {
        y = 1;
    } else if (x < -1){
        y = -1;
    }else{
        y = x;
    }
    
    return y;
}

//SoftClip (Value 2)
float SoftClip(float x)
{
    float y = 0;
    
    if (x > 1) {
        y = atan(x);
    } else if (x < -1){
        y = atan(x);
    }else{
        y = x;
    }
    
    return y;
}

//Quarter-Circle (Value 3)
float QuarterCircle(float x)
{
    float y = 0;
    
    if (x > 0 && x <= 1) {
        y = sqrt(1-pow(x-1, 2));
    } else if (x >= -1&& x <= 0){
        y = (sqrt(1-pow(x+1, 2))) * (-1);
    }else{
        y = x;
    }
    
    return y;
}

//Asymmetric (Value 4)
float Asymmetric(float x)
{
    float y = 0;
    
    if (x > 1) {
        y = atan(x);
    } else if (x < -0.2){
        y = -0.2;
    }else{
        y = x;
    }
    
    return y;
}


//Folding (Hard limited) (Value 5)
float Folding(float x)
{
    float y = 0;
    
    if (x > 1) {
        y = (1 - (x-1));
    } else if (x < -1){
        y = -1 - (x+1);
    }else{
        y = x;
    }
    
    if (x > 1) {
        y = 1;
    }else if (x < -1){
        y = -1;
    }
    
    return y;
}




#endif
