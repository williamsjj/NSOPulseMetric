# NSOPulseMetric


## Usage

Success and failure callbacks can be `nil`.

Direct metric example:

```Objective-C
#import <NSOPulseMetric.h>
NSOPulseMetric* pulse_metric = [[NSOPulseMetric alloc] initWithAppID:@"nmkj234"
                                                           authToken:1234567890];
[pulse_metric sendLatency:1.0 //NSTimeInterval in secs
				    jobID:@"def456"
           successHandler:^{ /*Success callback...can be nil*/ }
           failureHandler:^(NSError *error) {
               NSLog(@"NSONE Latency Transmission Error (%@)",
                     error);
           }];
```

Resolver mapping example:
```Objective-C
#import <NSOPulseMetric.h>
NSOPulseMetric* pulse_metric = [[NSOPulseMetric alloc] initWithAppID:@"zxs123"
                                                           authToken:1234567890];
    
[pulse_metric sendResolverMapping:@"abc123"
				   successHandler:^{ /*Success callback...can be nil*/ }
                   failureHandler:^(NSError *error) {
                       NSLog(@"NSONE Resolver Mapping Transmission Error (%@)",
                             error);
}];
```
	

## Requirements

* Requires AFNetworking 2.3 or greater.

## Installation

(Not yet in CocoaPods, use local link version below) NSOPulseMetric is available through [CocoaPods](http://cocoapods.org). To install
it, simply add the following line to your Podfile:

    pod "NSOPulseMetric"
	
Or to link against the Pod locally add this to your Podfile:

	pod "NSOPulseMetric",:path => '</path/to/repo/>'
	
Then run 

	pod install

## Author

Jason Williams, williamsjj@digitar.com

## License

NSOPulseMetric is available under the BSD license. See the LICENSE file for more info.

Copyright DigiTar Inc.

