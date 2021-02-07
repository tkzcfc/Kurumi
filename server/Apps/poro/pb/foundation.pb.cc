// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "foundation.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace protobuf {
namespace foundation {

namespace {

const ::google::protobuf::Descriptor* FoundationResponse_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  FoundationResponse_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_foundation_2eproto() {
  protobuf_AddDesc_foundation_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "foundation.proto");
  GOOGLE_CHECK(file != NULL);
  FoundationResponse_descriptor_ = file->message_type(0);
  static const int FoundationResponse_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FoundationResponse, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FoundationResponse, buy_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FoundationResponse, chargeid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FoundationResponse, goodsid_),
  };
  FoundationResponse_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      FoundationResponse_descriptor_,
      FoundationResponse::default_instance_,
      FoundationResponse_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FoundationResponse, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FoundationResponse, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(FoundationResponse));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_foundation_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    FoundationResponse_descriptor_, &FoundationResponse::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_foundation_2eproto() {
  delete FoundationResponse::default_instance_;
  delete FoundationResponse_reflection_;
}

void protobuf_AddDesc_foundation_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::protobuf::common::protobuf_AddDesc_common_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\020foundation.proto\022\023protobuf.foundation\032"
    "\014common.proto\"P\n\022FoundationResponse\022\n\n\002i"
    "d\030\001 \003(\005\022\013\n\003buy\030\002 \002(\010\022\020\n\010chargeId\030\003 \002(\005\022\017"
    "\n\007goodsId\030\004 \002(\005B&\n\023xag.idgo.core.protoB\017"
    "FoundationProto", 175);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "foundation.proto", &protobuf_RegisterTypes);
  FoundationResponse::default_instance_ = new FoundationResponse();
  FoundationResponse::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_foundation_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_foundation_2eproto {
  StaticDescriptorInitializer_foundation_2eproto() {
    protobuf_AddDesc_foundation_2eproto();
  }
} static_descriptor_initializer_foundation_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int FoundationResponse::kIdFieldNumber;
const int FoundationResponse::kBuyFieldNumber;
const int FoundationResponse::kChargeIdFieldNumber;
const int FoundationResponse::kGoodsIdFieldNumber;
#endif  // !_MSC_VER

FoundationResponse::FoundationResponse()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void FoundationResponse::InitAsDefaultInstance() {
}

FoundationResponse::FoundationResponse(const FoundationResponse& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void FoundationResponse::SharedCtor() {
  _cached_size_ = 0;
  buy_ = false;
  chargeid_ = 0;
  goodsid_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

FoundationResponse::~FoundationResponse() {
  SharedDtor();
}

void FoundationResponse::SharedDtor() {
  if (this != default_instance_) {
  }
}

void FoundationResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* FoundationResponse::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return FoundationResponse_descriptor_;
}

const FoundationResponse& FoundationResponse::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_foundation_2eproto();  return *default_instance_;
}

FoundationResponse* FoundationResponse::default_instance_ = NULL;

FoundationResponse* FoundationResponse::New() const {
  return new FoundationResponse;
}

void FoundationResponse::Clear() {
  if (_has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    buy_ = false;
    chargeid_ = 0;
    goodsid_ = 0;
  }
  id_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool FoundationResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated int32 id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 1, 8, input, this->mutable_id())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_LENGTH_DELIMITED) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, this->mutable_id())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(8)) goto parse_id;
        if (input->ExpectTag(16)) goto parse_buy;
        break;
      }
      
      // required bool buy = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_buy:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &buy_)));
          set_has_buy();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_chargeId;
        break;
      }
      
      // required int32 chargeId = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_chargeId:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &chargeid_)));
          set_has_chargeid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_goodsId;
        break;
      }
      
      // required int32 goodsId = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_goodsId:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &goodsid_)));
          set_has_goodsid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void FoundationResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated int32 id = 1;
  for (int i = 0; i < this->id_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(
      1, this->id(i), output);
  }
  
  // required bool buy = 2;
  if (has_buy()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(2, this->buy(), output);
  }
  
  // required int32 chargeId = 3;
  if (has_chargeid()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->chargeid(), output);
  }
  
  // required int32 goodsId = 4;
  if (has_goodsid()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(4, this->goodsid(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* FoundationResponse::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated int32 id = 1;
  for (int i = 0; i < this->id_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteInt32ToArray(1, this->id(i), target);
  }
  
  // required bool buy = 2;
  if (has_buy()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(2, this->buy(), target);
  }
  
  // required int32 chargeId = 3;
  if (has_chargeid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->chargeid(), target);
  }
  
  // required int32 goodsId = 4;
  if (has_goodsid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(4, this->goodsid(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int FoundationResponse::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    // required bool buy = 2;
    if (has_buy()) {
      total_size += 1 + 1;
    }
    
    // required int32 chargeId = 3;
    if (has_chargeid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->chargeid());
    }
    
    // required int32 goodsId = 4;
    if (has_goodsid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->goodsid());
    }
    
  }
  // repeated int32 id = 1;
  {
    int data_size = 0;
    for (int i = 0; i < this->id_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        Int32Size(this->id(i));
    }
    total_size += 1 * this->id_size() + data_size;
  }
  
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void FoundationResponse::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const FoundationResponse* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const FoundationResponse*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void FoundationResponse::MergeFrom(const FoundationResponse& from) {
  GOOGLE_CHECK_NE(&from, this);
  id_.MergeFrom(from.id_);
  if (from._has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    if (from.has_buy()) {
      set_buy(from.buy());
    }
    if (from.has_chargeid()) {
      set_chargeid(from.chargeid());
    }
    if (from.has_goodsid()) {
      set_goodsid(from.goodsid());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void FoundationResponse::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void FoundationResponse::CopyFrom(const FoundationResponse& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool FoundationResponse::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000000e) != 0x0000000e) return false;
  
  return true;
}

void FoundationResponse::Swap(FoundationResponse* other) {
  if (other != this) {
    id_.Swap(&other->id_);
    std::swap(buy_, other->buy_);
    std::swap(chargeid_, other->chargeid_);
    std::swap(goodsid_, other->goodsid_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata FoundationResponse::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = FoundationResponse_descriptor_;
  metadata.reflection = FoundationResponse_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace foundation
}  // namespace protobuf

// @@protoc_insertion_point(global_scope)
