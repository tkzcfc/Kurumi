// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "resonance.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace protobuf {
namespace resonance {

namespace {

const ::google::protobuf::Descriptor* ResonanceInfo_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ResonanceInfo_reflection_ = NULL;
const ::google::protobuf::Descriptor* HeroInfo_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  HeroInfo_reflection_ = NULL;
const ::google::protobuf::Descriptor* ChangeInfo_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ChangeInfo_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_resonance_2eproto() {
  protobuf_AddDesc_resonance_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "resonance.proto");
  GOOGLE_CHECK(file != NULL);
  ResonanceInfo_descriptor_ = file->message_type(0);
  static const int ResonanceInfo_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ResonanceInfo, stagehero_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ResonanceInfo, packagehero_),
  };
  ResonanceInfo_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ResonanceInfo_descriptor_,
      ResonanceInfo::default_instance_,
      ResonanceInfo_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ResonanceInfo, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ResonanceInfo, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ResonanceInfo));
  HeroInfo_descriptor_ = file->message_type(1);
  static const int HeroInfo_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(HeroInfo, heroid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(HeroInfo, grade_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(HeroInfo, cooltime_),
  };
  HeroInfo_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      HeroInfo_descriptor_,
      HeroInfo::default_instance_,
      HeroInfo_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(HeroInfo, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(HeroInfo, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(HeroInfo));
  ChangeInfo_descriptor_ = file->message_type(2);
  static const int ChangeInfo_offsets_[6] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChangeInfo, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChangeInfo, heroid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChangeInfo, lv_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChangeInfo, beforelv_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChangeInfo, sit_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChangeInfo, cooltime_),
  };
  ChangeInfo_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ChangeInfo_descriptor_,
      ChangeInfo::default_instance_,
      ChangeInfo_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChangeInfo, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChangeInfo, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ChangeInfo));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_resonance_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ResonanceInfo_descriptor_, &ResonanceInfo::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    HeroInfo_descriptor_, &HeroInfo::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ChangeInfo_descriptor_, &ChangeInfo::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_resonance_2eproto() {
  delete ResonanceInfo::default_instance_;
  delete ResonanceInfo_reflection_;
  delete HeroInfo::default_instance_;
  delete HeroInfo_reflection_;
  delete ChangeInfo::default_instance_;
  delete ChangeInfo_reflection_;
}

void protobuf_AddDesc_resonance_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::protobuf::common::protobuf_AddDesc_common_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017resonance.proto\022\022protobuf.resonance\032\014c"
    "ommon.proto\"s\n\rResonanceInfo\022/\n\tstageHer"
    "o\030\001 \003(\0132\034.protobuf.resonance.HeroInfo\0221\n"
    "\013packageHero\030\002 \003(\0132\034.protobuf.resonance."
    "HeroInfo\";\n\010HeroInfo\022\016\n\006heroId\030\001 \002(\005\022\r\n\005"
    "grade\030\002 \001(\005\022\020\n\010coolTime\030\003 \001(\003\"g\n\nChangeI"
    "nfo\022\014\n\004type\030\001 \001(\005\022\016\n\006heroId\030\002 \001(\005\022\n\n\002lv\030"
    "\003 \001(\005\022\020\n\010beforeLv\030\004 \001(\005\022\013\n\003sit\030\005 \001(\005\022\020\n\010"
    "coolTime\030\006 \001(\003B%\n\023xag.idgo.core.protoB\016R"
    "esonanceProto", 373);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "resonance.proto", &protobuf_RegisterTypes);
  ResonanceInfo::default_instance_ = new ResonanceInfo();
  HeroInfo::default_instance_ = new HeroInfo();
  ChangeInfo::default_instance_ = new ChangeInfo();
  ResonanceInfo::default_instance_->InitAsDefaultInstance();
  HeroInfo::default_instance_->InitAsDefaultInstance();
  ChangeInfo::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_resonance_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_resonance_2eproto {
  StaticDescriptorInitializer_resonance_2eproto() {
    protobuf_AddDesc_resonance_2eproto();
  }
} static_descriptor_initializer_resonance_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int ResonanceInfo::kStageHeroFieldNumber;
const int ResonanceInfo::kPackageHeroFieldNumber;
#endif  // !_MSC_VER

ResonanceInfo::ResonanceInfo()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ResonanceInfo::InitAsDefaultInstance() {
}

ResonanceInfo::ResonanceInfo(const ResonanceInfo& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ResonanceInfo::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ResonanceInfo::~ResonanceInfo() {
  SharedDtor();
}

void ResonanceInfo::SharedDtor() {
  if (this != default_instance_) {
  }
}

void ResonanceInfo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ResonanceInfo::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ResonanceInfo_descriptor_;
}

const ResonanceInfo& ResonanceInfo::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_resonance_2eproto();  return *default_instance_;
}

ResonanceInfo* ResonanceInfo::default_instance_ = NULL;

ResonanceInfo* ResonanceInfo::New() const {
  return new ResonanceInfo;
}

void ResonanceInfo::Clear() {
  stagehero_.Clear();
  packagehero_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ResonanceInfo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .protobuf.resonance.HeroInfo stageHero = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_stageHero:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_stagehero()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_stageHero;
        if (input->ExpectTag(18)) goto parse_packageHero;
        break;
      }
      
      // repeated .protobuf.resonance.HeroInfo packageHero = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_packageHero:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_packagehero()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_packageHero;
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

void ResonanceInfo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .protobuf.resonance.HeroInfo stageHero = 1;
  for (int i = 0; i < this->stagehero_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->stagehero(i), output);
  }
  
  // repeated .protobuf.resonance.HeroInfo packageHero = 2;
  for (int i = 0; i < this->packagehero_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->packagehero(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ResonanceInfo::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .protobuf.resonance.HeroInfo stageHero = 1;
  for (int i = 0; i < this->stagehero_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->stagehero(i), target);
  }
  
  // repeated .protobuf.resonance.HeroInfo packageHero = 2;
  for (int i = 0; i < this->packagehero_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->packagehero(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ResonanceInfo::ByteSize() const {
  int total_size = 0;
  
  // repeated .protobuf.resonance.HeroInfo stageHero = 1;
  total_size += 1 * this->stagehero_size();
  for (int i = 0; i < this->stagehero_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->stagehero(i));
  }
  
  // repeated .protobuf.resonance.HeroInfo packageHero = 2;
  total_size += 1 * this->packagehero_size();
  for (int i = 0; i < this->packagehero_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->packagehero(i));
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

void ResonanceInfo::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ResonanceInfo* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ResonanceInfo*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ResonanceInfo::MergeFrom(const ResonanceInfo& from) {
  GOOGLE_CHECK_NE(&from, this);
  stagehero_.MergeFrom(from.stagehero_);
  packagehero_.MergeFrom(from.packagehero_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ResonanceInfo::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ResonanceInfo::CopyFrom(const ResonanceInfo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ResonanceInfo::IsInitialized() const {
  
  for (int i = 0; i < stagehero_size(); i++) {
    if (!this->stagehero(i).IsInitialized()) return false;
  }
  for (int i = 0; i < packagehero_size(); i++) {
    if (!this->packagehero(i).IsInitialized()) return false;
  }
  return true;
}

void ResonanceInfo::Swap(ResonanceInfo* other) {
  if (other != this) {
    stagehero_.Swap(&other->stagehero_);
    packagehero_.Swap(&other->packagehero_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ResonanceInfo::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ResonanceInfo_descriptor_;
  metadata.reflection = ResonanceInfo_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int HeroInfo::kHeroIdFieldNumber;
const int HeroInfo::kGradeFieldNumber;
const int HeroInfo::kCoolTimeFieldNumber;
#endif  // !_MSC_VER

HeroInfo::HeroInfo()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void HeroInfo::InitAsDefaultInstance() {
}

HeroInfo::HeroInfo(const HeroInfo& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void HeroInfo::SharedCtor() {
  _cached_size_ = 0;
  heroid_ = 0;
  grade_ = 0;
  cooltime_ = GOOGLE_LONGLONG(0);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

HeroInfo::~HeroInfo() {
  SharedDtor();
}

void HeroInfo::SharedDtor() {
  if (this != default_instance_) {
  }
}

void HeroInfo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* HeroInfo::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return HeroInfo_descriptor_;
}

const HeroInfo& HeroInfo::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_resonance_2eproto();  return *default_instance_;
}

HeroInfo* HeroInfo::default_instance_ = NULL;

HeroInfo* HeroInfo::New() const {
  return new HeroInfo;
}

void HeroInfo::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    heroid_ = 0;
    grade_ = 0;
    cooltime_ = GOOGLE_LONGLONG(0);
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool HeroInfo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 heroId = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &heroid_)));
          set_has_heroid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_grade;
        break;
      }
      
      // optional int32 grade = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_grade:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &grade_)));
          set_has_grade();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_coolTime;
        break;
      }
      
      // optional int64 coolTime = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_coolTime:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &cooltime_)));
          set_has_cooltime();
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

void HeroInfo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required int32 heroId = 1;
  if (has_heroid()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->heroid(), output);
  }
  
  // optional int32 grade = 2;
  if (has_grade()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->grade(), output);
  }
  
  // optional int64 coolTime = 3;
  if (has_cooltime()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(3, this->cooltime(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* HeroInfo::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required int32 heroId = 1;
  if (has_heroid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->heroid(), target);
  }
  
  // optional int32 grade = 2;
  if (has_grade()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->grade(), target);
  }
  
  // optional int64 coolTime = 3;
  if (has_cooltime()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(3, this->cooltime(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int HeroInfo::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 heroId = 1;
    if (has_heroid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->heroid());
    }
    
    // optional int32 grade = 2;
    if (has_grade()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->grade());
    }
    
    // optional int64 coolTime = 3;
    if (has_cooltime()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int64Size(
          this->cooltime());
    }
    
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

void HeroInfo::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const HeroInfo* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const HeroInfo*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void HeroInfo::MergeFrom(const HeroInfo& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_heroid()) {
      set_heroid(from.heroid());
    }
    if (from.has_grade()) {
      set_grade(from.grade());
    }
    if (from.has_cooltime()) {
      set_cooltime(from.cooltime());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void HeroInfo::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void HeroInfo::CopyFrom(const HeroInfo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool HeroInfo::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;
  
  return true;
}

void HeroInfo::Swap(HeroInfo* other) {
  if (other != this) {
    std::swap(heroid_, other->heroid_);
    std::swap(grade_, other->grade_);
    std::swap(cooltime_, other->cooltime_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata HeroInfo::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = HeroInfo_descriptor_;
  metadata.reflection = HeroInfo_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int ChangeInfo::kTypeFieldNumber;
const int ChangeInfo::kHeroIdFieldNumber;
const int ChangeInfo::kLvFieldNumber;
const int ChangeInfo::kBeforeLvFieldNumber;
const int ChangeInfo::kSitFieldNumber;
const int ChangeInfo::kCoolTimeFieldNumber;
#endif  // !_MSC_VER

ChangeInfo::ChangeInfo()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ChangeInfo::InitAsDefaultInstance() {
}

ChangeInfo::ChangeInfo(const ChangeInfo& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ChangeInfo::SharedCtor() {
  _cached_size_ = 0;
  type_ = 0;
  heroid_ = 0;
  lv_ = 0;
  beforelv_ = 0;
  sit_ = 0;
  cooltime_ = GOOGLE_LONGLONG(0);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ChangeInfo::~ChangeInfo() {
  SharedDtor();
}

void ChangeInfo::SharedDtor() {
  if (this != default_instance_) {
  }
}

void ChangeInfo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ChangeInfo::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ChangeInfo_descriptor_;
}

const ChangeInfo& ChangeInfo::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_resonance_2eproto();  return *default_instance_;
}

ChangeInfo* ChangeInfo::default_instance_ = NULL;

ChangeInfo* ChangeInfo::New() const {
  return new ChangeInfo;
}

void ChangeInfo::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    type_ = 0;
    heroid_ = 0;
    lv_ = 0;
    beforelv_ = 0;
    sit_ = 0;
    cooltime_ = GOOGLE_LONGLONG(0);
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ChangeInfo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 type = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &type_)));
          set_has_type();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_heroId;
        break;
      }
      
      // optional int32 heroId = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_heroId:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &heroid_)));
          set_has_heroid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_lv;
        break;
      }
      
      // optional int32 lv = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_lv:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &lv_)));
          set_has_lv();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_beforeLv;
        break;
      }
      
      // optional int32 beforeLv = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_beforeLv:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &beforelv_)));
          set_has_beforelv();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_sit;
        break;
      }
      
      // optional int32 sit = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_sit:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &sit_)));
          set_has_sit();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_coolTime;
        break;
      }
      
      // optional int64 coolTime = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_coolTime:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &cooltime_)));
          set_has_cooltime();
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

void ChangeInfo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional int32 type = 1;
  if (has_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->type(), output);
  }
  
  // optional int32 heroId = 2;
  if (has_heroid()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->heroid(), output);
  }
  
  // optional int32 lv = 3;
  if (has_lv()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->lv(), output);
  }
  
  // optional int32 beforeLv = 4;
  if (has_beforelv()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(4, this->beforelv(), output);
  }
  
  // optional int32 sit = 5;
  if (has_sit()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(5, this->sit(), output);
  }
  
  // optional int64 coolTime = 6;
  if (has_cooltime()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(6, this->cooltime(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ChangeInfo::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional int32 type = 1;
  if (has_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->type(), target);
  }
  
  // optional int32 heroId = 2;
  if (has_heroid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->heroid(), target);
  }
  
  // optional int32 lv = 3;
  if (has_lv()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->lv(), target);
  }
  
  // optional int32 beforeLv = 4;
  if (has_beforelv()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(4, this->beforelv(), target);
  }
  
  // optional int32 sit = 5;
  if (has_sit()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(5, this->sit(), target);
  }
  
  // optional int64 coolTime = 6;
  if (has_cooltime()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(6, this->cooltime(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ChangeInfo::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional int32 type = 1;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->type());
    }
    
    // optional int32 heroId = 2;
    if (has_heroid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->heroid());
    }
    
    // optional int32 lv = 3;
    if (has_lv()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->lv());
    }
    
    // optional int32 beforeLv = 4;
    if (has_beforelv()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->beforelv());
    }
    
    // optional int32 sit = 5;
    if (has_sit()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->sit());
    }
    
    // optional int64 coolTime = 6;
    if (has_cooltime()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int64Size(
          this->cooltime());
    }
    
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

void ChangeInfo::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ChangeInfo* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ChangeInfo*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ChangeInfo::MergeFrom(const ChangeInfo& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_type()) {
      set_type(from.type());
    }
    if (from.has_heroid()) {
      set_heroid(from.heroid());
    }
    if (from.has_lv()) {
      set_lv(from.lv());
    }
    if (from.has_beforelv()) {
      set_beforelv(from.beforelv());
    }
    if (from.has_sit()) {
      set_sit(from.sit());
    }
    if (from.has_cooltime()) {
      set_cooltime(from.cooltime());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ChangeInfo::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ChangeInfo::CopyFrom(const ChangeInfo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ChangeInfo::IsInitialized() const {
  
  return true;
}

void ChangeInfo::Swap(ChangeInfo* other) {
  if (other != this) {
    std::swap(type_, other->type_);
    std::swap(heroid_, other->heroid_);
    std::swap(lv_, other->lv_);
    std::swap(beforelv_, other->beforelv_);
    std::swap(sit_, other->sit_);
    std::swap(cooltime_, other->cooltime_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ChangeInfo::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ChangeInfo_descriptor_;
  metadata.reflection = ChangeInfo_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace resonance
}  // namespace protobuf

// @@protoc_insertion_point(global_scope)
