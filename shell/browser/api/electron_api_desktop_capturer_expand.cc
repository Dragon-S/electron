// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "shell/browser/api/electron_api_desktop_capturer_expand.h"

#include "base/strings/string_number_conversions.h"
#include "base/strings/utf_string_conversions.h"
#include "base/threading/thread_restrictions.h"
#include "chrome/browser/media/webrtc/desktop_media_list.h"
#include "chrome/browser/media/webrtc/window_icon_util.h"
#include "content/public/browser/desktop_capture.h"
#include "gin/object_template_builder.h"
#include "shell/browser/javascript_environment.h"
#include "shell/browser/login_handler.h"
#include "shell/common/api/electron_api_native_image.h"
#include "shell/common/gin_converters/gfx_converter.h"
#include "shell/common/gin_helper/dictionary.h"
#include "shell/common/gin_helper/event_emitter_caller.h"
#include "shell/common/node_includes.h"
#include "third_party/webrtc/modules/desktop_capture/desktop_capture_options.h"
#include "third_party/webrtc/modules/desktop_capture/desktop_capturer.h"

#if defined(OS_WIN)
#include "ui/display/win/screen_win.h"
#endif

namespace electron {

namespace api {

gin::WrapperInfo DesktopCapturerExpand::kWrapperInfo = {
    gin::kEmbedderNativeGin};

DesktopCapturerExpand::DesktopCapturerExpand(v8::Isolate* isolate) {}

DesktopCapturerExpand::~DesktopCapturerExpand() = default;

void DesktopCapturerExpand::StartObserving() {
  LOG(ERROR) << "sll-------StartObserving";
  NativeDesktopMediaFrameBoundIndicator* media_frame_bound_indicator =
      NativeDesktopMediaFrameBoundIndicator::GetInstance();
  media_frame_bound_indicator->StartObserving(this);
}

void DesktopCapturerExpand::StopObserving() {
  LOG(ERROR) << "sll-------StopObserving";
  NativeDesktopMediaFrameBoundIndicator* media_frame_bound_indicator =
      NativeDesktopMediaFrameBoundIndicator::GetInstance();
  media_frame_bound_indicator->StopObserving();
}

void DesktopCapturerExpand::OnMediaFrameBoundChanged(const gfx::Rect& bound) {
  gfx::Rect new_bounds = bound;

#if defined(OS_WIN)
  new_bounds = display::win::ScreenWin::ScreenToDIPRect(nullptr, bound);
#endif

  Emit("media-frame-bound-changed", new_bounds);
}

// static
gin::Handle<DesktopCapturerExpand> DesktopCapturerExpand::Create(
    v8::Isolate* isolate) {
  return gin::CreateHandle(isolate, new DesktopCapturerExpand(isolate));
}

gin::ObjectTemplateBuilder DesktopCapturerExpand::GetObjectTemplateBuilder(
    v8::Isolate* isolate) {
  return gin_helper::EventEmitterMixin<
             DesktopCapturerExpand>::GetObjectTemplateBuilder(isolate)
      .SetMethod("startObserving", &DesktopCapturerExpand::StartObserving)
      .SetMethod("stopObserving", &DesktopCapturerExpand::StopObserving);
}

const char* DesktopCapturerExpand::GetTypeName() {
  return "DesktopCapturerExpand";
}

}  // namespace api

}  // namespace electron

namespace {

using electron::api::DesktopCapturerExpand;

void Initialize(v8::Local<v8::Object> exports,
                v8::Local<v8::Value> unused,
                v8::Local<v8::Context> context,
                void* priv) {
  v8::Isolate* isolate = context->GetIsolate();
  gin_helper::Dictionary dict(isolate, exports);
  dict.Set("desktopCapturerExpand", DesktopCapturerExpand::Create(isolate));
}

}  // namespace

NODE_LINKED_MODULE_CONTEXT_AWARE(electron_browser_desktop_capturer_expand,
                                 Initialize)
