// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef SHELL_BROWSER_API_ELECTRON_API_DESKTOP_CAPTURER_EXPAND_H_
#define SHELL_BROWSER_API_ELECTRON_API_DESKTOP_CAPTURER_EXPAND_H_

#include <memory>
#include <string>
#include <vector>

#include "chrome/browser/media/webrtc/native_desktop_media_frame_bound_indicator.h"
#include "gin/handle.h"
#include "gin/wrappable.h"
#include "shell/browser/event_emitter_mixin.h"

namespace electron {

namespace api {

class DesktopCapturerExpand
    : public gin::Wrappable<DesktopCapturerExpand>,
      public gin_helper::EventEmitterMixin<DesktopCapturerExpand>,
      public NativeDesktopMediaFrameBoundObserver {
 public:
  static gin::Handle<DesktopCapturerExpand> Create(v8::Isolate* isolate);

  // gin::Wrappable
  static gin::WrapperInfo kWrapperInfo;
  gin::ObjectTemplateBuilder GetObjectTemplateBuilder(
      v8::Isolate* isolate) override;
  const char* GetTypeName() override;

 protected:
  explicit DesktopCapturerExpand(v8::Isolate* isolate);
  ~DesktopCapturerExpand() override;

  void OnMediaFrameBoundChanged(const gfx::Rect& bound) override;

 private:
  void StartObserving();
  void StopObserving();

  DISALLOW_COPY_AND_ASSIGN(DesktopCapturerExpand);
};

}  // namespace api

}  // namespace electron

#endif  // SHELL_BROWSER_API_ELECTRON_API_DESKTOP_CAPTURER_EXPAND_H_
