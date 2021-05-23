// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Msg_ID.proto

#ifndef PROTOBUF_Msg_5fID_2eproto__INCLUDED
#define PROTOBUF_Msg_5fID_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_Msg_5fID_2eproto();
void protobuf_AssignDesc_Msg_5fID_2eproto();
void protobuf_ShutdownFile_Msg_5fID_2eproto();


enum MessageID {
  MSG_BEGIN = 0,
  MSG_LOGIN_GATE_ACK = 100001,
  MSG_NEW_FIGHT_REQ = 200001,
  MSG_NEW_FIGHT_ACK = 200002,
  MSG_CKECK_TOKEN_REQ = 300003,
  MSG_CKECK_TOKEN_ACK = 300004,
  MES_CHANGE_TOKEN_NTF = 300006,
  MSG_REG_SERVER_NODE_REQ = 600001,
  MSG_REG_SERVER_NODE_ACK = 600002,
  MSG_JOIN_FIGHT_REQ = 800001,
  MSG_JOIN_FIGHT_ACK = 800002,
  MSG_RUN_NEXT_FRAME_REQ = 800003,
  MSG_RUN_NEXT_FRAME_ACK = 800004,
  MSG_PLAYER_READY_NTF = 800005,
  MSG_PLAYER_EXIT_FIGHT_NTF = 800006,
  MSG_EXIT_FIGHT_REQ = 800007,
  MSG_EXIT_FIGHT_ACK = 800008,
  MSG_LOADING_PERCENT_REQ = 800009,
  MSG_LOADING_PERCENT_ACK = 800010,
  MSG_PUSH_FRAME_BEGIN = 800011,
  MSG_PUSH_FRAME_INPUT = 800012,
  MSG_PUSH_FRAME_END = 800013,
  MSG_LOGIN_REQ = 900001,
  MSG_LOGIN_ACK = 900002,
  MSG_CREATE_ROLE_REQ = 900303,
  MSG_CREATE_ROLE_ACK = 900304,
  MSG_ENTER_GAME_REQ = 900305,
  MSG_ENTER_GAME_ACK = 900306,
  MSG_EXIT_GAME_NTF = 900010,
  MSG_START_PVE_REQ = 900101,
  MSG_START_PVE_ACK = 900102,
  MSG_START_PVP_REQ = 900103,
  MSG_START_PVP_ACK = 900104,
  MSG_STOP_PVP_REQ = 900105,
  MSG_STOP_PVP_ACK = 900106,
  MSG_START_FIGHT_NTF = 900200
};
bool MessageID_IsValid(int value);
const MessageID MessageID_MIN = MSG_BEGIN;
const MessageID MessageID_MAX = MSG_ENTER_GAME_ACK;
const int MessageID_ARRAYSIZE = MessageID_MAX + 1;

enum FightType {
  FIGHT_PVE = 0,
  FIGHT_PVP = 1
};
bool FightType_IsValid(int value);
const FightType FightType_MIN = FIGHT_PVE;
const FightType FightType_MAX = FIGHT_PVP;
const int FightType_ARRAYSIZE = FightType_MAX + 1;

// ===================================================================


// ===================================================================


// ===================================================================


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Msg_5fID_2eproto__INCLUDED
