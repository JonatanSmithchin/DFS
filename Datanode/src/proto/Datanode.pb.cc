// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Datanode.proto

#include "proto/Datanode.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace Datanode {
PROTOBUF_CONSTEXPR copyBlockRequest::copyBlockRequest(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.content_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.blockid_)*/uint64_t{0u}
  , /*decltype(_impl_.size_)*/uint64_t{0u}
  , /*decltype(_impl_.checksum_)*/0u
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct copyBlockRequestDefaultTypeInternal {
  PROTOBUF_CONSTEXPR copyBlockRequestDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~copyBlockRequestDefaultTypeInternal() {}
  union {
    copyBlockRequest _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 copyBlockRequestDefaultTypeInternal _copyBlockRequest_default_instance_;
PROTOBUF_CONSTEXPR copyBlockResponse::copyBlockResponse(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.status_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct copyBlockResponseDefaultTypeInternal {
  PROTOBUF_CONSTEXPR copyBlockResponseDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~copyBlockResponseDefaultTypeInternal() {}
  union {
    copyBlockResponse _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 copyBlockResponseDefaultTypeInternal _copyBlockResponse_default_instance_;
}  // namespace Datanode
static ::_pb::Metadata file_level_metadata_Datanode_2eproto[2];
static const ::_pb::EnumDescriptor* file_level_enum_descriptors_Datanode_2eproto[1];
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_Datanode_2eproto = nullptr;

const uint32_t TableStruct_Datanode_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Datanode::copyBlockRequest, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Datanode::copyBlockRequest, _impl_.blockid_),
  PROTOBUF_FIELD_OFFSET(::Datanode::copyBlockRequest, _impl_.size_),
  PROTOBUF_FIELD_OFFSET(::Datanode::copyBlockRequest, _impl_.content_),
  PROTOBUF_FIELD_OFFSET(::Datanode::copyBlockRequest, _impl_.checksum_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Datanode::copyBlockResponse, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Datanode::copyBlockResponse, _impl_.status_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::Datanode::copyBlockRequest)},
  { 10, -1, -1, sizeof(::Datanode::copyBlockResponse)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::Datanode::_copyBlockRequest_default_instance_._instance,
  &::Datanode::_copyBlockResponse_default_instance_._instance,
};

const char descriptor_table_protodef_Datanode_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\016Datanode.proto\022\010Datanode\032\tdfs.proto\"T\n"
  "\020copyBlockRequest\022\017\n\007blockId\030\001 \001(\004\022\014\n\004si"
  "ze\030\002 \001(\004\022\017\n\007Content\030\003 \001(\014\022\020\n\010checkSum\030\004 "
  "\001(\r\"9\n\021copyBlockResponse\022$\n\006status\030\001 \001(\016"
  "2\024.Datanode.copyStatus*-\n\ncopyStatus\022\013\n\007"
  "Unknown\020\000\022\006\n\002OK\020\001\022\n\n\006Failed\020\0022W\n\rBackupS"
  "ervice\022F\n\tcopyBlock\022\032.Datanode.copyBlock"
  "Request\032\033.Datanode.copyBlockResponse(\001b\006"
  "proto3"
  ;
static const ::_pbi::DescriptorTable* const descriptor_table_Datanode_2eproto_deps[1] = {
  &::descriptor_table_dfs_2eproto,
};
static ::_pbi::once_flag descriptor_table_Datanode_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_Datanode_2eproto = {
    false, false, 326, descriptor_table_protodef_Datanode_2eproto,
    "Datanode.proto",
    &descriptor_table_Datanode_2eproto_once, descriptor_table_Datanode_2eproto_deps, 1, 2,
    schemas, file_default_instances, TableStruct_Datanode_2eproto::offsets,
    file_level_metadata_Datanode_2eproto, file_level_enum_descriptors_Datanode_2eproto,
    file_level_service_descriptors_Datanode_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_Datanode_2eproto_getter() {
  return &descriptor_table_Datanode_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_Datanode_2eproto(&descriptor_table_Datanode_2eproto);
namespace Datanode {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* copyStatus_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_Datanode_2eproto);
  return file_level_enum_descriptors_Datanode_2eproto[0];
}
bool copyStatus_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}


// ===================================================================

class copyBlockRequest::_Internal {
 public:
};

copyBlockRequest::copyBlockRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Datanode.copyBlockRequest)
}
copyBlockRequest::copyBlockRequest(const copyBlockRequest& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  copyBlockRequest* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.content_){}
    , decltype(_impl_.blockid_){}
    , decltype(_impl_.size_){}
    , decltype(_impl_.checksum_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.content_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.content_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_content().empty()) {
    _this->_impl_.content_.Set(from._internal_content(), 
      _this->GetArenaForAllocation());
  }
  ::memcpy(&_impl_.blockid_, &from._impl_.blockid_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.checksum_) -
    reinterpret_cast<char*>(&_impl_.blockid_)) + sizeof(_impl_.checksum_));
  // @@protoc_insertion_point(copy_constructor:Datanode.copyBlockRequest)
}

inline void copyBlockRequest::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.content_){}
    , decltype(_impl_.blockid_){uint64_t{0u}}
    , decltype(_impl_.size_){uint64_t{0u}}
    , decltype(_impl_.checksum_){0u}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.content_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.content_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

copyBlockRequest::~copyBlockRequest() {
  // @@protoc_insertion_point(destructor:Datanode.copyBlockRequest)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void copyBlockRequest::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.content_.Destroy();
}

void copyBlockRequest::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void copyBlockRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:Datanode.copyBlockRequest)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.content_.ClearToEmpty();
  ::memset(&_impl_.blockid_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.checksum_) -
      reinterpret_cast<char*>(&_impl_.blockid_)) + sizeof(_impl_.checksum_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* copyBlockRequest::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint64 blockId = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.blockid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint64 size = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _impl_.size_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // bytes Content = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_content();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint32 checkSum = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 32)) {
          _impl_.checksum_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* copyBlockRequest::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Datanode.copyBlockRequest)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // uint64 blockId = 1;
  if (this->_internal_blockid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt64ToArray(1, this->_internal_blockid(), target);
  }

  // uint64 size = 2;
  if (this->_internal_size() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt64ToArray(2, this->_internal_size(), target);
  }

  // bytes Content = 3;
  if (!this->_internal_content().empty()) {
    target = stream->WriteBytesMaybeAliased(
        3, this->_internal_content(), target);
  }

  // uint32 checkSum = 4;
  if (this->_internal_checksum() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(4, this->_internal_checksum(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Datanode.copyBlockRequest)
  return target;
}

size_t copyBlockRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Datanode.copyBlockRequest)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bytes Content = 3;
  if (!this->_internal_content().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_content());
  }

  // uint64 blockId = 1;
  if (this->_internal_blockid() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(this->_internal_blockid());
  }

  // uint64 size = 2;
  if (this->_internal_size() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(this->_internal_size());
  }

  // uint32 checkSum = 4;
  if (this->_internal_checksum() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_checksum());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData copyBlockRequest::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    copyBlockRequest::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*copyBlockRequest::GetClassData() const { return &_class_data_; }


void copyBlockRequest::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<copyBlockRequest*>(&to_msg);
  auto& from = static_cast<const copyBlockRequest&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Datanode.copyBlockRequest)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_content().empty()) {
    _this->_internal_set_content(from._internal_content());
  }
  if (from._internal_blockid() != 0) {
    _this->_internal_set_blockid(from._internal_blockid());
  }
  if (from._internal_size() != 0) {
    _this->_internal_set_size(from._internal_size());
  }
  if (from._internal_checksum() != 0) {
    _this->_internal_set_checksum(from._internal_checksum());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void copyBlockRequest::CopyFrom(const copyBlockRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Datanode.copyBlockRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool copyBlockRequest::IsInitialized() const {
  return true;
}

void copyBlockRequest::InternalSwap(copyBlockRequest* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.content_, lhs_arena,
      &other->_impl_.content_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(copyBlockRequest, _impl_.checksum_)
      + sizeof(copyBlockRequest::_impl_.checksum_)
      - PROTOBUF_FIELD_OFFSET(copyBlockRequest, _impl_.blockid_)>(
          reinterpret_cast<char*>(&_impl_.blockid_),
          reinterpret_cast<char*>(&other->_impl_.blockid_));
}

::PROTOBUF_NAMESPACE_ID::Metadata copyBlockRequest::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_Datanode_2eproto_getter, &descriptor_table_Datanode_2eproto_once,
      file_level_metadata_Datanode_2eproto[0]);
}

// ===================================================================

class copyBlockResponse::_Internal {
 public:
};

copyBlockResponse::copyBlockResponse(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Datanode.copyBlockResponse)
}
copyBlockResponse::copyBlockResponse(const copyBlockResponse& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  copyBlockResponse* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.status_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _this->_impl_.status_ = from._impl_.status_;
  // @@protoc_insertion_point(copy_constructor:Datanode.copyBlockResponse)
}

inline void copyBlockResponse::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.status_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

copyBlockResponse::~copyBlockResponse() {
  // @@protoc_insertion_point(destructor:Datanode.copyBlockResponse)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void copyBlockResponse::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void copyBlockResponse::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void copyBlockResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:Datanode.copyBlockResponse)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.status_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* copyBlockResponse::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .Datanode.copyStatus status = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_status(static_cast<::Datanode::copyStatus>(val));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* copyBlockResponse::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Datanode.copyBlockResponse)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // .Datanode.copyStatus status = 1;
  if (this->_internal_status() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteEnumToArray(
      1, this->_internal_status(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Datanode.copyBlockResponse)
  return target;
}

size_t copyBlockResponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Datanode.copyBlockResponse)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .Datanode.copyStatus status = 1;
  if (this->_internal_status() != 0) {
    total_size += 1 +
      ::_pbi::WireFormatLite::EnumSize(this->_internal_status());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData copyBlockResponse::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    copyBlockResponse::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*copyBlockResponse::GetClassData() const { return &_class_data_; }


void copyBlockResponse::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<copyBlockResponse*>(&to_msg);
  auto& from = static_cast<const copyBlockResponse&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Datanode.copyBlockResponse)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_status() != 0) {
    _this->_internal_set_status(from._internal_status());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void copyBlockResponse::CopyFrom(const copyBlockResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Datanode.copyBlockResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool copyBlockResponse::IsInitialized() const {
  return true;
}

void copyBlockResponse::InternalSwap(copyBlockResponse* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_.status_, other->_impl_.status_);
}

::PROTOBUF_NAMESPACE_ID::Metadata copyBlockResponse::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_Datanode_2eproto_getter, &descriptor_table_Datanode_2eproto_once,
      file_level_metadata_Datanode_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace Datanode
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Datanode::copyBlockRequest*
Arena::CreateMaybeMessage< ::Datanode::copyBlockRequest >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Datanode::copyBlockRequest >(arena);
}
template<> PROTOBUF_NOINLINE ::Datanode::copyBlockResponse*
Arena::CreateMaybeMessage< ::Datanode::copyBlockResponse >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Datanode::copyBlockResponse >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>