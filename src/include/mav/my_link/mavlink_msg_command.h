#pragma once
// MESSAGE command PACKING

#define MAVLINK_MSG_ID_command 5

MAVPACKED(
typedef struct __mavlink_command_t {
 uint8_t cmd; /*<  */
}) mavlink_command_t;

#define MAVLINK_MSG_ID_command_LEN 1
#define MAVLINK_MSG_ID_command_MIN_LEN 1
#define MAVLINK_MSG_ID_5_LEN 1
#define MAVLINK_MSG_ID_5_MIN_LEN 1

#define MAVLINK_MSG_ID_command_CRC 19
#define MAVLINK_MSG_ID_5_CRC 19



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_command { \
    5, \
    "command", \
    1, \
    {  { "cmd", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_command_t, cmd) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_command { \
    "command", \
    1, \
    {  { "cmd", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_command_t, cmd) }, \
         } \
}
#endif

/**
 * @brief Pack a command message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param cmd  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_command_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_command_LEN];
    _mav_put_uint8_t(buf, 0, cmd);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_command_LEN);
#else
    mavlink_command_t packet;
    packet.cmd = cmd;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_command_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_command;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_command_MIN_LEN, MAVLINK_MSG_ID_command_LEN, MAVLINK_MSG_ID_command_CRC);
}

/**
 * @brief Pack a command message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param cmd  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_command_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_command_LEN];
    _mav_put_uint8_t(buf, 0, cmd);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_command_LEN);
#else
    mavlink_command_t packet;
    packet.cmd = cmd;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_command_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_command;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_command_MIN_LEN, MAVLINK_MSG_ID_command_LEN, MAVLINK_MSG_ID_command_CRC);
}

/**
 * @brief Encode a command struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param command C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_command_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_command_t* command)
{
    return mavlink_msg_command_pack(system_id, component_id, msg, command->cmd);
}

/**
 * @brief Encode a command struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param command C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_command_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_command_t* command)
{
    return mavlink_msg_command_pack_chan(system_id, component_id, chan, msg, command->cmd);
}

/**
 * @brief Send a command message
 * @param chan MAVLink channel to send the message
 *
 * @param cmd  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_command_send(mavlink_channel_t chan, uint8_t cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_command_LEN];
    _mav_put_uint8_t(buf, 0, cmd);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_command, buf, MAVLINK_MSG_ID_command_MIN_LEN, MAVLINK_MSG_ID_command_LEN, MAVLINK_MSG_ID_command_CRC);
#else
    mavlink_command_t packet;
    packet.cmd = cmd;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_command, (const char *)&packet, MAVLINK_MSG_ID_command_MIN_LEN, MAVLINK_MSG_ID_command_LEN, MAVLINK_MSG_ID_command_CRC);
#endif
}

/**
 * @brief Send a command message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_command_send_struct(mavlink_channel_t chan, const mavlink_command_t* command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_command_send(chan, command->cmd);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_command, (const char *)command, MAVLINK_MSG_ID_command_MIN_LEN, MAVLINK_MSG_ID_command_LEN, MAVLINK_MSG_ID_command_CRC);
#endif
}

#if MAVLINK_MSG_ID_command_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_command_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, cmd);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_command, buf, MAVLINK_MSG_ID_command_MIN_LEN, MAVLINK_MSG_ID_command_LEN, MAVLINK_MSG_ID_command_CRC);
#else
    mavlink_command_t *packet = (mavlink_command_t *)msgbuf;
    packet->cmd = cmd;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_command, (const char *)packet, MAVLINK_MSG_ID_command_MIN_LEN, MAVLINK_MSG_ID_command_LEN, MAVLINK_MSG_ID_command_CRC);
#endif
}
#endif

#endif

// MESSAGE command UNPACKING


/**
 * @brief Get field cmd from command message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_command_get_cmd(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Decode a command message into a struct
 *
 * @param msg The message to decode
 * @param command C-struct to decode the message contents into
 */
static inline void mavlink_msg_command_decode(const mavlink_message_t* msg, mavlink_command_t* command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    command->cmd = mavlink_msg_command_get_cmd(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_command_LEN? msg->len : MAVLINK_MSG_ID_command_LEN;
        memset(command, 0, MAVLINK_MSG_ID_command_LEN);
    memcpy(command, _MAV_PAYLOAD(msg), len);
#endif
}
