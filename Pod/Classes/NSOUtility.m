////////////////////////////////////////////////////////////////////
// FILENAME: NSOUtility.m
// PROJECT: NSONE Pulse Metric Transmission (Cocoa)
// DESCRIPTION:
//
////////////////////////////////////////////////////////////////////
// (C)2014 DigiTar, All Rights Reserved
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// * Neither the name of NSOPulseMetric nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//         SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#import "NSOUtility.h"

#define kRandomStringSet @"abcdefghijklmnopqrstuvwxyz0123456789"

@implementation NSOUtility

+ (NSUInteger) transactionNumber; {
    return arc4random_uniform(UINT_MAX);
}

+ (NSString*) base36Encode:(NSUInteger)base10_input {
    //Modified from: https://gist.github.com/furkanmustafa/5660086
    NSMutableString* final = NSMutableString.string;
    int temp, j;
    
    j = -1;
    do {
        temp = base10_input % 36;
        if (temp < 10)
            [final appendFormat:@"%c", 48 + temp];
        else
            [final appendFormat:@"%c", 65 + temp - 10];
        base10_input = base10_input / 36;
    } while (base10_input != 0);
    
    const char* chars = [final cStringUsingEncoding:NSASCIIStringEncoding];
    NSUInteger length = strlen(chars);
    char* new = (char*)malloc(length+1);
    for (int i = 0; i < length; i++)
        new[i] = chars[length - i - 1];
    new[length] = '\0';
    NSString* reverseString = [NSString stringWithCString:new encoding:NSASCIIStringEncoding];
    free(new);
    return reverseString.lowercaseString;
}

+ (NSString*) signature:(NSUInteger)transaction_number usingToken:(NSUInteger)token {
    NSUInteger minute = (NSUInteger)floor([[NSDate date] timeIntervalSince1970]/60);
    return [NSString stringWithFormat:@"%lu",(unsigned long)(token^transaction_number^minute)];
}


+ (NSString*) randomStringWithLength:(NSUInteger)len {
    
    NSMutableString* randomString = [NSMutableString stringWithCapacity: len];
    
    for (int i=0; i<len; i++) {
        [randomString appendFormat:@"%C",
         [kRandomStringSet characterAtIndex:arc4random_uniform((unsigned int)[kRandomStringSet length])]];
    }
    
    return randomString;
}

@end
