////////////////////////////////////////////////////////////////////
// FILENAME: NSOPulseMetric.h
// PROJECT: NSONE Pulse Metric Transmission (Cocoa)
// DESCRIPTION:
//
////////////////////////////////////////////////////////////////////
// (C)2015 DigiTar, All Rights Reserved
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

#import "NSOPulseMetric.h"
#import "NSOUtility.h"
#import "AFNetworking.h"

#define kBaseAPIDomain @"ns1p.net"

//API_ENDPOINT,APPID,TRANSACTIONID,SIGNATURE,JOBID,METRIC
#define kDirectMetricAPI @"http://b.%@/?a=%@&x=%@&s=%@&r=%@:%@"


//RANDDOMAIN,API_ENDPOINT,APPID,JOBID,TRANSACTIONID,SIGNATURE
#define kResolverMetricAPI @"http://%@.r.%@/a/r.b?a=%@&j=%@&x=%@&s=%@"

@implementation NSOPulseMetric {
    NSString* _base_api_endpoint;
    NSString* _app_id;
    unsigned int _token;
}

- (NSOPulseMetric*) initWithAppID:(NSString* _Nonnull)app_id
                        authToken:(unsigned int)token {
    if(self = [super init]) {
        _base_api_endpoint = kBaseAPIDomain;
        NSAssert(app_id!=nil, @"NSONE app_id cannot be nil.");
        _app_id = [app_id copy];
        _token = token;
    }
    
    return self;
}

- (void) sendLatency:(NSTimeInterval)latency
               jobID:(NSString* _Nonnull)job_id
      successHandler:(successBlock _Nullable)success_handler
      failureHandler:(failureBlock _Nullable)failure_handler {
    
    NSAssert(job_id!=nil, @"NSONE job_id cannot be nil.");
    
    NSUInteger trans_num = [NSOUtility transactionNumber];
    
    NSString* metric_value = [NSString stringWithFormat:@"%.03f",(latency*1000)];
    
    NSURL* api_url = [NSURL URLWithString:[NSString stringWithFormat:kDirectMetricAPI,
                                                    _base_api_endpoint,
                                                    _app_id,
                                                    [NSOUtility base36Encode:trans_num],
                                                    [NSOUtility signature:trans_num usingToken:_token],
                                                    [job_id copy],
                                                    metric_value]];
    
    NSMutableURLRequest* api_req = [NSMutableURLRequest requestWithURL:api_url];
    
    AFHTTPSessionManager* sess_mgr = [AFHTTPSessionManager manager];
    sess_mgr.responseSerializer = [AFHTTPResponseSerializer serializer];
    
    NSURLSessionDataTask* latency_task = [sess_mgr dataTaskWithRequest:api_req completionHandler:^(NSURLResponse * _Nonnull response,
                                                                                                    id  _Nonnull responseObject,
                                                                                                    NSError * _Nonnull error) {
        if(!error) {
            if(success_handler) {
                success_handler();
            }
        } else {
            if(failure_handler) {
                failure_handler(error);
            }
        }
    }];
    
    [latency_task resume];
}

- (NSString*) sendResolverMapping:(NSString* _Nonnull)job_id
                   successHandler:(successBlock _Nullable)success_handler
                   failureHandler:(failureBlock _Nullable)failure_handler {
    
    NSUInteger trans_num = [NSOUtility transactionNumber];
    NSString* rand_domain = [NSOUtility randomStringWithLength:10];
    
    NSURL* api_url = [NSURL URLWithString:[NSString stringWithFormat:kResolverMetricAPI,
                                           rand_domain,
                                           _base_api_endpoint,
                                           _app_id,
                                           [job_id copy],
                                           [NSOUtility base36Encode:trans_num],
                                           [NSOUtility signature:trans_num usingToken:_token]]];
    
    NSMutableURLRequest* api_req = [NSMutableURLRequest requestWithURL:api_url];
    
    AFHTTPSessionManager* sess_mgr = [AFHTTPSessionManager manager];
    sess_mgr.responseSerializer = [AFHTTPResponseSerializer serializer];
    
    NSURLSessionDataTask* resolver_task = [sess_mgr dataTaskWithRequest:api_req completionHandler:^(NSURLResponse * _Nonnull response,
                                                                                                     id  _Nonnull responseObject,
                                                                                                     NSError * _Nonnull error) {
        if(!error) {
            if(success_handler) {
                success_handler();
            }
        } else {
            if(failure_handler) {
                failure_handler(error);
            }
        }
    }];
    
    [resolver_task resume];
    
    return rand_domain;
}

#pragma mark - Property Handlers

- (NSString* _Nonnull) api_base_domain {
    return [_base_api_endpoint copy];
}

- (void) setApi_base_domain:(NSString *)api_base_domain {
    _base_api_endpoint = [api_base_domain copy];
}

@end
