//
//  Copyright (c) SRG SSR. All rights reserved.
//
//  License information is available from the LICENSE file.
//

#import "SRGMediaPlayerIconTemplate.h"

@implementation SRGMediaPlayerIconTemplate

#pragma mark Bezier Paths

+ (UIImage *)imageWithBezierPath:(UIBezierPath *)bezierPath size:(CGSize)size
{
    CGFloat scale = UIScreen.mainScreen.scale;
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef context = CGBitmapContextCreate(NULL, size.width * scale, size.height * scale, 8, 0, colorSpace, (CGBitmapInfo)kCGImageAlphaPremultipliedLast);
    CGColorSpaceRelease(colorSpace);
    
    CGContextScaleCTM(context, scale, scale);
    CGContextAddPath(context, bezierPath.CGPath);
    CGContextSetFillColorWithColor(context, UIColor.blackColor.CGColor);
    CGContextFillPath(context);
    
    CGImageRef imageRef = CGBitmapContextCreateImage(context);
    UIImage *image = [UIImage imageWithCGImage:imageRef scale:scale orientation:UIImageOrientationUp];
    CGImageRelease(imageRef);
    CGContextRelease(context);
    
    return [image imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
}

+ (UIBezierPath *)playBezierPathWithSize:(CGSize)size
{
    UIBezierPath *playBezierPath;
    playBezierPath = [UIBezierPath bezierPath];
    [playBezierPath moveToPoint:CGPointMake(0.f, 0.f)];
    [playBezierPath addLineToPoint:CGPointMake(size.width, size.height / 2.f)];
    [playBezierPath addLineToPoint:CGPointMake(0.f, size.height)];
    [playBezierPath closePath];
    return playBezierPath;
}

+ (UIBezierPath *)pauseBezierPathWithSize:(CGSize)size
{
    CGFloat middle = CGRectGetMidX((CGRect) {CGPointZero, size });
    CGFloat margin = middle * 1.f / 3.f;
    CGFloat width = middle - margin;
    
    UIBezierPath *pauseBezierPath = [UIBezierPath bezierPath];
    [pauseBezierPath moveToPoint:CGPointMake(margin / 2.f, 0.f)];
    [pauseBezierPath addLineToPoint:CGPointMake(width, 0.f)];
    [pauseBezierPath addLineToPoint:CGPointMake(width, size.height)];
    [pauseBezierPath addLineToPoint:CGPointMake(margin / 2.f, size.height)];
    [pauseBezierPath closePath];
    
    [pauseBezierPath moveToPoint:CGPointMake(middle + margin / 2.f, 0.f)];
    [pauseBezierPath addLineToPoint:CGPointMake(middle + width, 0.f)];
    [pauseBezierPath addLineToPoint:CGPointMake(middle + width, size.height)];
    [pauseBezierPath addLineToPoint:CGPointMake(middle + margin / 2.f, size.height)];
    [pauseBezierPath closePath];
    
    return pauseBezierPath;
}

+ (UIBezierPath *)stopBezierPathWithSize:(CGSize)size
{
    CGFloat marginX = 0.f;
    CGFloat marginY = 0.f;
    
    if (size.width > size.height) {
        marginX += (size.width - size.height) / 2.f;
    }
    else if (size.height > size.width) {
        marginY += (size.height - size.width) / 2.f;
    }
    
    UIBezierPath *stopBezierPath = [UIBezierPath bezierPath];
    [stopBezierPath moveToPoint:CGPointMake(marginX, marginY)];
    [stopBezierPath addLineToPoint:CGPointMake(size.width - 2.f * marginX, marginY)];
    [stopBezierPath addLineToPoint:CGPointMake(size.width - 2.f * marginX, size.height - 2.f * marginY)];
    [stopBezierPath addLineToPoint:CGPointMake(marginX, size.height - 2.f * marginY)];
    [stopBezierPath closePath];
    
    return stopBezierPath;
}

#pragma mark Images

+ (UIImage *)playImageWithSize:(CGSize)size
{
    return [self imageWithBezierPath:[self playBezierPathWithSize:size] size:size];
}

+ (UIImage *)pauseImageWithSize:(CGSize)size
{
    return [self imageWithBezierPath:[self pauseBezierPathWithSize:size] size:size];
}

+ (UIImage *)stopImageWithSize:(CGSize)size
{
    return [self imageWithBezierPath:[self stopBezierPathWithSize:size] size:size];
}

@end
