//
//  Copyright (c) SRG SSR. All rights reserved.
//
//  License information is available from the LICENSE file.
//

#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  Notification sent when the wireless route changes (e.g. AirPlay enabled or disabled).
 *
 *  @discussion Exactly the same as `MPVolumeViewWirelessRouteActiveDidChangeNotification`, but without the need
 *              for a volume view.
 */
OBJC_EXTERN NSString * const SRGMediaPlayerWirelessRouteDidChangeNotification;

@interface AVAudioSession (SRGMediaPlayer)

/**
 *  Return `YES` iff AirPlay is active (i.e. displaying on an external AirPlay device).
 *
 *  @discussion You can listen to the `SRGMediaPlayerWirelessRouteDidChangeNotification` notification to detect route changes.
 */
@property (class, nonatomic, readonly) BOOL srg_isAirPlayActive;

/**
 *  Return the active AirPlay route name if possible, or `nil` when no route is active.
 */
@property (class, nonatomic, readonly, copy, nullable) NSString *srg_activeAirPlayRouteName;

@end

NS_ASSUME_NONNULL_END
