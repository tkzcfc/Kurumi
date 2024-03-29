// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Msg_Err.proto

#include "Msg_Err.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
namespace err {
}  // namespace err
namespace err {
bool Code_IsValid(int value) {
  switch (value) {
    case 0:
    case 100001:
    case 100002:
    case 100003:
    case 100004:
    case 100005:
    case 100006:
    case 100007:
    case 100100:
    case 100101:
    case 100102:
    case 100200:
    case 100201:
    case 100202:
    case 100203:
    case 200000:
    case 200001:
    case 200002:
    case 200003:
    case 200100:
    case 210000:
    case 210001:
    case 210002:
    case 210003:
    case 210004:
    case 210005:
    case 210006:
    case 210007:
    case 210008:
    case 210100:
    case 210101:
    case 210102:
    case 220001:
    case 220002:
    case 220003:
    case 220010:
    case 220011:
    case 220012:
    case 220030:
    case 220031:
    case 220032:
    case 220033:
    case 220034:
      return true;
    default:
      return false;
  }
}

static ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<std::string> Code_strings[43] = {};

static const char Code_names[] =
  "ACCOUNT_NOT_EXIST"
  "EXIT_GAME_CLIENT_DIS"
  "EXIT_GAME_LOGIN_REPEAT"
  "EXIT_GAME_PLAYER_REQ"
  "FIGHT_FRAME_ERR"
  "FIGHT_INIT_FAIL"
  "FIGHT_LEAVE_GAME"
  "FIGHT_NOE_FOUND_PLAYER"
  "FIGHT_PAST_RECORDS_INC"
  "FIGHT_PLAYERID_REPEAT"
  "FIGHT_PLAYER_TOO_MUCH"
  "FIGHT_PLAYING"
  "FIGHT_SVR_BUSY"
  "FIGHT_SVR_NONE"
  "FIGHT_SVR_NOT_FOUND"
  "GAME_LOGIN_AGAIN"
  "GAME_LOGIN_MUT_PID"
  "GAME_LOGIN_NO_FOUND_PLAYER"
  "GATE_CONNECT_FAIL"
  "LOGIN_TIMEOUT"
  "NAME_STR_CONTAIN_ILLEGAL_CAHR"
  "NAME_STR_TO_LONG"
  "NAME_STR_TO_SHORT"
  "NAME_TARGET_REPEAT"
  "NOT_FOUND"
  "NOT_FOUND_FIGHT"
  "NO_MEMORY"
  "OCC_NOT_FOUND"
  "OVERDUE"
  "OVERLOAD"
  "PARAM_ERROR"
  "PVP_MATCHING"
  "PVP_MATCH_SUC"
  "PVP_MATCH_SUC_NO_SVR"
  "PVP_MATCH_TIMEOUT"
  "PVP_RIVAL_EXIT"
  "ROLE_NOT_EXIST"
  "SUCCESS"
  "SVR_ERROR"
  "TARGET_REPEAT"
  "TOKEN_ERR"
  "UNKNOWN"
  "WRONG_PASSWORD";

static const ::PROTOBUF_NAMESPACE_ID::internal::EnumEntry Code_entries[] = {
  { {Code_names + 0, 17}, 200000 },
  { {Code_names + 17, 20}, 220011 },
  { {Code_names + 37, 22}, 220010 },
  { {Code_names + 59, 20}, 220012 },
  { {Code_names + 79, 15}, 210007 },
  { {Code_names + 94, 15}, 210001 },
  { {Code_names + 109, 16}, 210006 },
  { {Code_names + 125, 22}, 210002 },
  { {Code_names + 147, 22}, 210008 },
  { {Code_names + 169, 21}, 210005 },
  { {Code_names + 190, 21}, 210004 },
  { {Code_names + 211, 13}, 210003 },
  { {Code_names + 224, 14}, 210100 },
  { {Code_names + 238, 14}, 210101 },
  { {Code_names + 252, 19}, 210102 },
  { {Code_names + 271, 16}, 220002 },
  { {Code_names + 287, 18}, 220001 },
  { {Code_names + 305, 26}, 220003 },
  { {Code_names + 331, 17}, 200100 },
  { {Code_names + 348, 13}, 200003 },
  { {Code_names + 361, 29}, 100202 },
  { {Code_names + 390, 16}, 100201 },
  { {Code_names + 406, 17}, 100200 },
  { {Code_names + 423, 18}, 100203 },
  { {Code_names + 441, 9}, 100002 },
  { {Code_names + 450, 15}, 210000 },
  { {Code_names + 465, 9}, 100100 },
  { {Code_names + 474, 13}, 100007 },
  { {Code_names + 487, 7}, 100003 },
  { {Code_names + 494, 8}, 100101 },
  { {Code_names + 502, 11}, 100102 },
  { {Code_names + 513, 12}, 220030 },
  { {Code_names + 525, 13}, 220032 },
  { {Code_names + 538, 20}, 220033 },
  { {Code_names + 558, 17}, 220031 },
  { {Code_names + 575, 14}, 220034 },
  { {Code_names + 589, 14}, 200002 },
  { {Code_names + 603, 7}, 0 },
  { {Code_names + 610, 9}, 100005 },
  { {Code_names + 619, 13}, 100004 },
  { {Code_names + 632, 9}, 100006 },
  { {Code_names + 641, 7}, 100001 },
  { {Code_names + 648, 14}, 200001 },
};

static const int Code_entries_by_number[] = {
  37, // 0 -> SUCCESS
  41, // 100001 -> UNKNOWN
  24, // 100002 -> NOT_FOUND
  28, // 100003 -> OVERDUE
  39, // 100004 -> TARGET_REPEAT
  38, // 100005 -> SVR_ERROR
  40, // 100006 -> TOKEN_ERR
  27, // 100007 -> OCC_NOT_FOUND
  26, // 100100 -> NO_MEMORY
  29, // 100101 -> OVERLOAD
  30, // 100102 -> PARAM_ERROR
  22, // 100200 -> NAME_STR_TO_SHORT
  21, // 100201 -> NAME_STR_TO_LONG
  20, // 100202 -> NAME_STR_CONTAIN_ILLEGAL_CAHR
  23, // 100203 -> NAME_TARGET_REPEAT
  0, // 200000 -> ACCOUNT_NOT_EXIST
  42, // 200001 -> WRONG_PASSWORD
  36, // 200002 -> ROLE_NOT_EXIST
  19, // 200003 -> LOGIN_TIMEOUT
  18, // 200100 -> GATE_CONNECT_FAIL
  25, // 210000 -> NOT_FOUND_FIGHT
  5, // 210001 -> FIGHT_INIT_FAIL
  7, // 210002 -> FIGHT_NOE_FOUND_PLAYER
  11, // 210003 -> FIGHT_PLAYING
  10, // 210004 -> FIGHT_PLAYER_TOO_MUCH
  9, // 210005 -> FIGHT_PLAYERID_REPEAT
  6, // 210006 -> FIGHT_LEAVE_GAME
  4, // 210007 -> FIGHT_FRAME_ERR
  8, // 210008 -> FIGHT_PAST_RECORDS_INC
  12, // 210100 -> FIGHT_SVR_BUSY
  13, // 210101 -> FIGHT_SVR_NONE
  14, // 210102 -> FIGHT_SVR_NOT_FOUND
  16, // 220001 -> GAME_LOGIN_MUT_PID
  15, // 220002 -> GAME_LOGIN_AGAIN
  17, // 220003 -> GAME_LOGIN_NO_FOUND_PLAYER
  2, // 220010 -> EXIT_GAME_LOGIN_REPEAT
  1, // 220011 -> EXIT_GAME_CLIENT_DIS
  3, // 220012 -> EXIT_GAME_PLAYER_REQ
  31, // 220030 -> PVP_MATCHING
  34, // 220031 -> PVP_MATCH_TIMEOUT
  32, // 220032 -> PVP_MATCH_SUC
  33, // 220033 -> PVP_MATCH_SUC_NO_SVR
  35, // 220034 -> PVP_RIVAL_EXIT
};

const std::string& Code_Name(
    Code value) {
  static const bool dummy =
      ::PROTOBUF_NAMESPACE_ID::internal::InitializeEnumStrings(
          Code_entries,
          Code_entries_by_number,
          43, Code_strings);
  (void) dummy;
  int idx = ::PROTOBUF_NAMESPACE_ID::internal::LookUpEnumName(
      Code_entries,
      Code_entries_by_number,
      43, value);
  return idx == -1 ? ::PROTOBUF_NAMESPACE_ID::internal::GetEmptyString() :
                     Code_strings[idx].get();
}
bool Code_Parse(
    const std::string& name, Code* value) {
  int int_value;
  bool success = ::PROTOBUF_NAMESPACE_ID::internal::LookUpEnumValue(
      Code_entries, 43, name, &int_value);
  if (success) {
    *value = static_cast<Code>(int_value);
  }
  return success;
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace err
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
