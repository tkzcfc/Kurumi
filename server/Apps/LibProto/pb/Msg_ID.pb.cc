// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Msg_ID.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Msg_ID.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

void protobuf_ShutdownFile_Msg_5fID_2eproto() {
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_Msg_5fID_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_Msg_5fID_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Msg_5fID_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_Msg_5fID_2eproto_once_);
void protobuf_AddDesc_Msg_5fID_2eproto() {
  ::google::protobuf::::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_Msg_5fID_2eproto_once_,
                 &protobuf_AddDesc_Msg_5fID_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Msg_5fID_2eproto {
  StaticDescriptorInitializer_Msg_5fID_2eproto() {
    protobuf_AddDesc_Msg_5fID_2eproto();
  }
} static_descriptor_initializer_Msg_5fID_2eproto_;
#endif
bool MessageID_IsValid(int value) {
  switch(value) {
    case 0:
    case 100001:
    case 200001:
    case 200002:
    case 300003:
    case 300004:
    case 300006:
    case 600001:
    case 600002:
    case 800001:
    case 800002:
    case 800003:
    case 800004:
    case 800005:
    case 800006:
    case 800007:
    case 800008:
    case 900001:
    case 900002:
    case 900010:
    case 900101:
    case 900102:
    case 900103:
    case 900104:
    case 900105:
    case 900106:
    case 900200:
    case 900303:
    case 900304:
    case 900305:
    case 900306:
      return true;
    default:
      return false;
  }
}

bool FightType_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
