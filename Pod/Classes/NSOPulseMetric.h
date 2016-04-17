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

#import <Foundation/Foundation.h>
#import "AFNetworking.h"

typedef void (^successBlock)();
typedef void (^failureBlock)(NSError* _Nonnull error);

/**
 *  Enables Objective-C/Swift programs to send client latency metrics and DNS resolver mappings to [NS1](https://ns1.com/platform/pulsar) Pulsar service. This lets NS1 provide more accurate (DNS-based) geo-load balancing for your clients.
 */
@interface NSOPulseMetric : NSObject

/**
 *  Base domain to use for the NS1 API endpoint. Default: ns1p.net
 *  
 *  @return Current base domain used for NS1 API endpoint.
 */
@property (nonatomic, strong) NSString* _Nonnull api_base_domain;

/**
 *  Set up NSOPulseMetric for communicating with the NS1 API.
 *
 *  @param app_id Unique ID assigned by NS1 Pulsar for this application/service.
 *  @param token  NS1 Pulsar API authentication token.
 *
 *  @return NSOPulseMetric instance
 */
- (NSOPulseMetric* _Nullable) initWithAppID:(NSString* _Nonnull)app_id
                                  authToken:(unsigned int)token;

/**
 *  Send a latency-based metric value to NS1 Pulsar. It should
 *  measure the round-trip time between your client and your
 *  servers. How you measure the latency is up to you (it can
 *  be as simple as TCP connect time, or as complex as measuring
 *  the last HTTP API request transaction time).
 *
 *  NS1 uses these metrics to map out the average latency between
 *  between anonymized client IP ranges and your server IPs 
 *  (identified by job_id).
 *
 *  Those mappings are then analyzed to return the closest server
 *  to your clients based on network distance instead of 
 *  geographic distance alone.
 *
 *  @param latency         Round-trip time in seconds.
 *  @param job_id          Unique ID for the service this metric applies to within your app. (see initWithAppID:authToken:)
 *  @param success_handler Optional block called when submission is successful.
 *  @param failure_handler Optional block called when the submission fails.
 *  @see initWithAppID:authToken:
 */
- (void) sendLatency:(NSTimeInterval)latency
               jobID:(NSString* _Nonnull)job_id
      successHandler:(successBlock _Nullable)success_handler
      failureHandler:(failureBlock _Nullable)failure_handler;

/**
 *  Maps the geography of the client's IP range to the DNS
 *  resolver they use. Works by generating a unique
 *  sub-domain of the NS1 Pulsar API endpoint and then 
 *  connecting to that unique sub-dowmain endpoint with 
 *  a unique transaction number. 
 *
 *  Since DNS-based geolocation relies on the IP of the resolver
 *  not the client, it's really important that a resolver be 
 *  associated with the geography of its clients and not its own
 *  physical location. For example, Comcast customers in Washington
 *  DC might normally be routed to a Miami server instead of a
 *  WDC server because their Comcast resolver is located in Atlanta.
 *  This helps fix that.
 *
 *  @param job_id          Unique ID for the service this metric applies to within your app. (see initWithAppID:authToken:)
 *  @param success_handler Optional block called when submission is successful.
 *  @param failure_handler Optional block called when the submission fails.
 *
 *  @return Unique sub-domain used for the mapping request.
 *  @see initWithAppID:authToken:
 */
- (NSString* _Nonnull) sendResolverMapping:(NSString* _Nonnull)job_id
                            successHandler:(successBlock _Nullable)success_handler
                            failureHandler:(failureBlock _Nullable)failure_handler;

@end