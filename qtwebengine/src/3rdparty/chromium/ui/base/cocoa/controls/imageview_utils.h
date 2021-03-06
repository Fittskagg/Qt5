// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_COCOA_CONTROLS_IMAGEVIEW_UTILS_H_
#define UI_BASE_COCOA_CONTROLS_IMAGEVIEW_UTILS_H_

#include "ui/base/ui_base_export.h"

#include <Cocoa/Cocoa.h>

UI_BASE_EXPORT
@interface ImageViewUtils : NSObject

// These methods are a polyfill for convenience constructors that exist on
// NSImageView in macOS 10.12+.
// TODO(ellyjones): once we target only 10.12+, delete these and migrate
// callers over to NSImageView directly.
+ (NSImageView*)imageViewWithImage:(NSImage*)image;

@end

#endif  // UI_BASE_COCOA_CONTROLS_IMAGEVIEW_UTILS_H_
