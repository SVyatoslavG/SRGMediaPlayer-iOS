//
//  Copyright (c) SRG SSR. All rights reserved.
//
//  License information is available from the LICENSE file.
//

#import <CoreMedia/CoreMedia.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

// Default amount of seconds at the end of a DVR stream assumed to correspond to live conditions (same tolerance as the built-in iOS player).
static NSTimeInterval const SRGMediaPlayerDefaultLiveTolerance = 30.;

// Default absolute tolerance applied when attempting to play a stream (or segment thereof) starting near its end.
static NSTimeInterval const SRGMediaPlayerDefaultEndTolerance = 0.;

// Default relative tolerance applied when attempting to play a stream (or segment thereof) starting near its end.
static float const SRGMediaPlayerDefaultEndToleranceRatio = 0.f;

/**
 *  Calculate the effective end tolerance applied for an absolute and relative tolerance, for a content having the provided duration.
 */
OBJC_EXPORT CMTime SRGMediaPlayerEffectiveEndTolerance(NSTimeInterval endTolerance, float endToleranceRatio, NSTimeInterval contentDuration);

/**
 *  @name Types
 */

/**
 *  Media types.
 */
typedef NS_ENUM(NSInteger, SRGMediaPlayerMediaType) {
    /**
     *  Unknown type.
     */
    SRGMediaPlayerMediaTypeUnknown = 0,
    /**
     *  Video.
     */
    SRGMediaPlayerMediaTypeVideo,
    /**
     *  Audio.
     */
    SRGMediaPlayerMediaTypeAudio
};

/**
 *  Stream types.
 */
typedef NS_ENUM(NSInteger, SRGMediaPlayerStreamType) {
    /**
     *  Unknown type.
     */
    SRGMediaPlayerStreamTypeUnknown = 0,
    /**
     *  On-demand stream.
     */
    SRGMediaPlayerStreamTypeOnDemand,
    /**
     *  Live stream.
     */
    SRGMediaPlayerStreamTypeLive,
    /**
     *  DVR stream.
     */
    SRGMediaPlayerStreamTypeDVR
};

/**
 *  Playback states.
 */
typedef NS_ENUM(NSInteger, SRGMediaPlayerPlaybackState) {
    /**
     *  The player is idle. This state occurs after the player has been initialized, reset, or when an error has been
     *  encountered.
     */
    SRGMediaPlayerPlaybackStateIdle = 1,
    /**
     *  The player is preparing to play a media.
     */
    SRGMediaPlayerPlaybackStatePreparing,
    /**
     *  A media is being played.
     */
    SRGMediaPlayerPlaybackStatePlaying,
    /**
     *  The player is seeking to another position.
     */
    SRGMediaPlayerPlaybackStateSeeking,
    /**
     *  The player is paused.
     */
    SRGMediaPlayerPlaybackStatePaused,
    /**
     *  The player is stalled, i.e. waiting for media playback to restart (most probably because of poor networking
     *  conditions).
     */
    SRGMediaPlayerPlaybackStateStalled,
    /**
     *  The player has reached the end of the media and has automatically stopped playback.
     */
    SRGMediaPlayerPlaybackStateEnded
};

/**
 *  @name Notifications
 */

/**
 *  Notification sent when the player state changes.
 */
OBJC_EXTERN NSString * const SRGMediaPlayerPlaybackStateDidChangeNotification;              // Notification name.

/**
 *  Notification sent when playback failed. Use the `SRGMediaPlayerErrorKey` to retrieve an `NSError` information 
 *  from the notification `userInfo` dictionary).
 */
OBJC_EXTERN NSString * const SRGMediaPlayerPlaybackDidFailNotification;                     // Notification name.

/**
 *  Notification sent just before a seek is made (the player is already in the seeking state, though). Use the `SRGMediaPlayerSeekTimeKey`
 *  to retrieve an `NSValue` containing the `CMTime` of the target seek position.
 *
 *  @discussion If multiple seeks are made, no additional state change notification is sent (and thus the new target seek
 *              time is not received in a notification).
 */
OBJC_EXTERN NSString * const SRGMediaPlayerSeekNotification;                                // Notification name.

/**
 *  Notification sent when the picture in picture state changes.
 */
OBJC_EXTERN NSString * const SRGMediaPlayerPictureInPictureStateDidChangeNotification;

/**
 *  Notification sent when the external playback is enabled or disabled.
 */
OBJC_EXTERN NSString * const SRGMediaPlayerExternalPlaybackStateDidChangeNotification;

/**
 *  Notification sent when tracks changed. Use the keys available below to retrieve information from the notification
 *  `userInfo` dictionary.
 */
OBJC_EXTERN NSString * const SRGMediaPlayerAudioTrackDidChangeNotification;
OBJC_EXTERN NSString * const SRGMediaPlayerSubtitleTrackDidChangeNotification;

/**
 *  Notification sent when the current segment changes. Use the keys available below to retrieve information from
 *  the notification `userInfo` dictionary.
 */
OBJC_EXTERN NSString * const SRGMediaPlayerSegmentDidStartNotification;                     // Notification sent when a segment starts.
OBJC_EXTERN NSString * const SRGMediaPlayerSegmentDidEndNotification;                       // Notification sent when a segment ends.

/**
 *  Blocked segments skipping notifications.
 */
OBJC_EXTERN NSString * const SRGMediaPlayerWillSkipBlockedSegmentNotification;              // Notification sent when the player starts skipping a blocked segment.
OBJC_EXTERN NSString * const SRGMediaPlayerDidSkipBlockedSegmentNotification;               // Notification sent when the player finishes skipping a blocked segment.

/**
 *  @name Notification user information keys
 */

/**
 *  Information available for `SRGMediaPlayerPlaybackStateDidChangeNotification`.
 */
OBJC_EXTERN NSString * const SRGMediaPlayerPlaybackStateKey;                                // Key to access the current playback state as an `NSNumber` (wrapping an `SRGMediaPlayerPlaybackState` value).
OBJC_EXTERN NSString * const SRGMediaPlayerPreviousPlaybackStateKey;                        // Key to access the previous playback state as an `NSNumber` (wrapping an `SRGMediaPlayerPlaybackState` value).
OBJC_EXTERN NSString * const SRGMediaPlayerPreviousContentURLKey;                           // Key to access the previously played URL.
OBJC_EXTERN NSString * const SRGMediaPlayerPreviousPlayerItemKey;                           // Key to access the previously played `AVPlayerItem`.
OBJC_EXTERN NSString * const SRGMediaPlayerPreviousTimeRangeKey;                            // Key to access the previous time range as an `NSValue` (wrapping an `CMTimeRange` value).
OBJC_EXTERN NSString * const SRGMediaPlayerPreviousMediaTypeKey;                            // Key to access the previous media type as an `NSNumber` (wrapping an `SRGMediaPlayerMediaType` value).
OBJC_EXTERN NSString * const SRGMediaPlayerPreviousStreamTypeKey;                           // Key to access the previous stream type as an `NSNumber` (wrapping an `SRGMediaPlayerStreamType` value).
OBJC_EXTERN NSString * const SRGMediaPlayerPreviousUserInfoKey;                             // Key to access the previous user information.

/**
 *  Information available for `SRGMediaPlayerPlaybackDidFailNotification`.
 */
OBJC_EXTERN NSString * const SRGMediaPlayerErrorKey;                                        // Key to access error information.

/**
 *  Information available for `SRGMediaPlayerSeekNotification`.
 */
OBJC_EXTERN NSString * const SRGMediaPlayerSeekTimeKey;                                     // Key to access the time to which the seek is made, as an `NSValue` (wrapping a `CMTime` value).

/**
 *  Information available for all segment-related notifications.
 */
OBJC_EXTERN NSString * const SRGMediaPlayerSegmentKey;                                      // The involved segment as an `id<SRGSegment>` object.

/**
 *  Information available for `SRGMediaPlayerSegmentDidStartNotification` and `SRGMediaPlayerSegmentDidEndNotification`.
 */
OBJC_EXPORT NSString * const SRGMediaPlayerSelectedKey;                                     // Key to an `NSNumber` wrapping a boolean, set to `YES` iff the segment was selected.

/**
 *  Information available for `SRGMediaPlayerSegmentDidStartNotification`.
 */
OBJC_EXTERN NSString * const SRGMediaPlayerPreviousSegmentKey;                              // The previously played segment, if any, as an `id<SRGSegment>` object.

/**
 *  Information available for `SRGMediaPlayerSegmentDidEndNotification`.
 */
OBJC_EXTERN NSString * const SRGMediaPlayerNextSegmentKey;                                  // The segment which will be played next, if any, as an `id<SRGSegment>` object.
OBJC_EXTERN NSString * const SRGMediaPlayerInterruptionKey;                                 // Key to an `NSNumber` wrapping a boolean, set to `YES` iff the end notification results because segment playback was interrupted.

/**
 *  Information available for `SRGMediaPlayerSegmentDidStartNotification`, `SRGMediaPlayerSegmentDidEndNotification` and `SRGMediaPlayerPlaybackStateDidChangeNotification`.
 */
OBJC_EXTERN NSString * const SRGMediaPlayerSelectionKey;                                    // Key to an `NSNumber` wrapping a boolean, set to `YES` iff the notification results from a segment selection.

/**
 *  Information available for `SRGMediaPlayerAudioTrackDidChangeNotification` and `SRGMediaPlayerSubtitleTrackDidChangeNotification`.
 */
OBJC_EXPORT NSString * const SRGMediaPlayerTrackKey;                                       // Key to the current `AVMediaSelectionOption`.
OBJC_EXPORT NSString * const SRGMediaPlayerPreviousTrackKey;                               // Key to the previous `AVMediaSelectionOption`.

/**
 *  Information available for all notifications, except `SRGMediaPlayerPictureInPictureStateDidChangeNotification` and `SRGMediaPlayerExternalPlaybackStateDidChangeNotification`.
 *  For `SRGMediaPlayerPlaybackStateDidChangeNotification` notifications, this key is only present when the player returns to idle, and provides the last known playback position.
 */
OBJC_EXPORT NSString * const SRGMediaPlayerLastPlaybackTimeKey;                             // Key to an `NSValue` wrapping a `CMTime` specifying the last playback position before the event occurred.

NS_ASSUME_NONNULL_END
