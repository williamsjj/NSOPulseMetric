////////////////////////////////////////////////////////////////////
// FILENAME: NSOUtility.h
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

/**
 *  Utility functions needed by NSOPulseMetric.
 *  @see NSOPulseMetric
 */
@interface NSOUtility : NSObject

/**
 *  Generates a unique transaction ID for an NS1 API reqeust.
 *
 *  @return Returns a random number bounded between 0 and UINT_MAX.
 */
+ (NSUInteger) transactionNumber;

/**
 *  Encodes a base10 unsigned integer as a base36 NSString.
 *
 *  @param base10_input Unsigned integer to encode.
 *
 *  @return Base36-encoded string version of base10_input.
 */
+ (NSString*) base36Encode:(NSUInteger)base10_input;

/**
 *  Computes an authentication signature for the API request
 *  by using the request's transactionNumber: and the 
 *  NS1 API authentication token.
 *
 *  @param transaction_number NS1 API request transaction number
 *  @param token              NS1 API authentication token.
 *
 *  @return Signature usable for authenticating NS1 API request identified by transaction_number.
 *  @see transactionNumber:
 */
+ (NSString*) signature:(NSUInteger)transaction_number usingToken:(NSUInteger)token;

/**
 *  Generates a random string of the requested length from the set: a-z0-9.
 *
 *  @param len Desired length for the random string.
 *
 *  @return Generated random string value.
 */
+ (NSString*) randomStringWithLength:(NSUInteger)len;

@end
