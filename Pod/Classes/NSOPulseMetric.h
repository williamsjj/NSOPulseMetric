////////////////////////////////////////////////////////////////////
// FILENAME: NSOPulseMetric.h
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
////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import <AFNetworking.h>

typedef void (^successBlock)();
typedef void (^failureBlock)(AFHTTPRequestOperation *operation, NSError *error);

@interface NSOPulseMetric : NSObject

@property (nonatomic, strong) NSString* api_base_domain;

- (NSOPulseMetric*) initWithAppID:(NSString*)app_id
                            jobID:(NSString*)job_id
                        authToken:(unsigned int)token;

- (void) sendLatency:(NSTimeInterval)latency
      successHandler:(successBlock)success_handler
      failureHandler:(failureBlock)failure_handler;

- (NSString*) sendResolverMapping:(successBlock)success_handler
                   failureHandler:(failureBlock)failure_handler;

@end