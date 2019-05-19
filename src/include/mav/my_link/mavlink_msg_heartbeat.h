#pragma once
// MESSAGE heartbeat PACKING

#define MAVLINK_MSG_ID_heartbeat 2

MAVPACKED(
typedef struct __mavlink_heartbeat_t {
 uint64_t time; /*<   time of sent*/
 uint32_t buf_cnt; /*<   remaining data on buffer*/
 uint8_t type; /*<   data type*/
 uint8_t status; /*<   current status of device*/
}) mavlink_heartbeat_t;

#define MAVLINK_MSG_ID_heartbeat_LEN 14
#define MAVLINK_MSG_ID_heartbeat_MIN_LEN 14
#define MAVLINK_MSG_ID_2_LEN 14
#define MAVLINK_MSG_ID_2_MIN_LEN 14

#define MAVLINK_MSG_ID_heartbeat_CRC 214
#define MAVLINK_MSG_ID_2_CRC 214



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_heartbeat { \
    2, \
    "heartbeat", \
    4, \
    {  { "type", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_heartbeat_t, type) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_heartbeat_t, status) }, \
         { "buf_cnt", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_heartbeat_t, buf_cnt) }, \
         { "time", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_heartbeat_t, time) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_heartbeat { \
    "heartbeat", \
    4, \
    {  { "type", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_heartbeat_t, type) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_heartbeat_t, status) }, \
         { "buf_cnt", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_heartbeat_t, buf_cnt) }, \
         { "time", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_heartbeat_t, time) }, \
         } \
}
#endif

/**
 * @brief Pack a heartbeat message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param type   data type
 * @param status   current status of device
 * @param buf_cnt   remaining data on buffer
 * @param time   time of sent
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_heartbeat_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t type, uint8_t status, uint32_t buf_cnt, uint64_t time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_heartbeat_LEN];
    _mav_put_uint64_t(buf, 0, time);
    _mav_put_uint32_t(buf, 8, buf_cnt);
    _mav_put_uint8_t(buf, 12, type);
    _mav_put_uint8_t(buf, 13, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_heartbeat_LEN);
#else
    mavlink_heartbeat_t packet;
    packet.time = time;
    packet.buf_cnt = buf_cnt;
    packet.type = type;
    packet.status = status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_heartbeat_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_heartbeat;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_heartbeat_MIN_LEN, MAVLINK_MSG_ID_heartbeat_LEN, MAVLINK_MSG_ID_heartbeat_CRC);
}

/**
 * @brief Pack a heartbeat message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param type   data type
 * @param status   current status of device
 * @param buf_cnt   remaining data on buffer
 * @param time   time of sent
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_heartbeat_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t type,uint8_t status,uint32_t buf_cnt,uint64_t time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_heartbeat_LEN];
    _mav_put_uint64_t(buf, 0, time);
    _mav_put_uint32_t(buf, 8, buf_cnt);
    _mav_put_uint8_t(buf, 12, type);
    _mav_put_uint8_t(buf, 13, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_heartbeat_LEN);
#else
    mavlink_heartbeat_t packet;
    packet.time = time;
    packet.buf_cnt = buf_cnt;
    packet.type = type;
    packet.status = status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_heartbeat_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_heartbeat;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_heartbeat_MIN_LEN, MAVLINK_MSG_ID_heartbeat_LEN, MAVLINK_MSG_ID_heartbeat_CRC);
}

/**
 * @brief Encode a heartbeat struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param heartbeat C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_heartbeat_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_heartbeat_t* heartbeat)
{
    return mavlink_msg_heartbeat_pack(system_id, component_id, msg, heartbeat->type, heartbeat->status, heartbeat->buf_cnt, heartbeat->time);
}

/**
 * @brief Encode a heartbeat struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param heartbeat C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_heartbeat_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_heartbeat_t* heartbeat)
{
    return mavlink_msg_heartbeat_pack_chan(system_id, component_id, chan, msg, heartbeat->type, heartbeat->status, heartbeat->buf_cnt, heartbeat->time);
}

/**
 * @brief Send a heartbeat message
 * @param chan MAVLink channel to send the message
 *
 * @param type   data type
 * @param status   current status of device
 * @param buf_cnt   remaining data on buffer
 * @param time   time of sent
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_heartbeat_send(mavlink_channel_t chan, uint8_t type, uint8_t status, uint32_t buf_cnt, uint64_t time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_heartbeat_LEN];
    _mav_put_uint64_t(buf, 0, time);
    _mav_put_uint32_t(buf, 8, buf_cnt);
    _mav_put_uint8_t(buf, 12, type);
    _mav_put_uint8_t(buf, 13, status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_heartbeat, buf, MAVLINK_MSG_ID_heartbeat_MIN_LEN, MAVLINK_MSG_ID_heartbeat_LEN, MAVLINK_MSG_ID_heartbeat_CRC);
#else
    mavlink_heartbeat_t packet;
    packet.time = time;
    packet.buf_cnt = buf_cnt;
    packet.type = type;
    packet.status = status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_heartbeat, (const char *)&packet, MAVLINK_MSG_ID_heartbeat_MIN_LEN, MAVLINK_MSG_ID_heartbeat_LEN, MAVLINK_MSG_ID_heartbeat_CRC);
#endif
}

/**
 * @brief Send a heartbeat message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_heartbeat_send_struct(mavlink_channel_t chan, const mavlink_heartbeat_t* heartbeat)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_heartbeat_send(chan, heartbeat->type, heartbeat->status, heartbeat->buf_cnt, heartbeat->time);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_heartbeat, (const char *)heartbeat, MAVLINK_MSG_ID_heartbeat_MIN_LEN, MAVLINK_MSG_ID_heartbeat_LEN, MAVLINK_MSG_ID_heartbeat_CRC);
#endif
}

#if MAVLINK_MSG_ID_heartbeat_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_heartbeat_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t type, uint8_t status, uint32_t buf_cnt, uint64_t time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time);
    _mav_put_uint32_t(buf, 8, buf_cnt);
    _mav_put_uint8_t(buf, 12, type);
    _mav_put_uint8_t(buf, 13, status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_heartbeat, buf, MAVLINK_MSG_ID_heartbeat_MIN_LEN, MAVLINK_MSG_ID_heartbeat_LEN, MAVLINK_MSG_ID_heartbeat_CRC);
#else
    mavlink_heartbeat_t *packet = (mavlink_heartbeat_t *)msgbuf;
    packet->time = time;
    packet->buf_cnt = buf_cnt;
    packet->type = type;
    packet->status = status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_heartbeat, (const char *)packet, MAVLINK_MSG_ID_heartbeat_MIN_LEN, MAVLINK_MSG_ID_heartbeat_LEN, MAVLINK_MSG_ID_heartbeat_CRC);
#endif
}
#endif

#endif

// MESSAGE heartbeat UNPACKING


/**
 * @brief Get field type from heartbeat message
 *
 * @return   data type
 */
static inline uint8_t mavlink_msg_heartbeat_get_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Get field status from heartbeat message
 *
 * @return   current status of device
 */
static inline uint8_t mavlink_msg_heartbeat_get_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  13);
}

/**
 * @brief Get field buf_cnt from heartbeat message
 *
 * @return   remaining data on buffer
 */
static inline uint32_t mavlink_msg_heartbeat_get_buf_cnt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field time from heartbeat message
 *
 * @return   time of sent
 */
static inline uint64_t mavlink_msg_heartbeat_get_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Decode a heartbeat message into a struct
 *
 * @param msg The message to decode
 * @param heartbeat C-struct to decode the message contents into
 */
static inline void mavlink_msg_heartbeat_decode(const mavlink_message_t* msg, mavlink_heartbeat_t* heartbeat)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    heartbeat->time = mavlink_msg_heartbeat_get_time(msg);
    heartbeat->buf_cnt = mavlink_msg_heartbeat_get_buf_cnt(msg);
    heartbeat->type = mavlink_msg_heartbeat_get_type(msg);
    heartbeat->status = mavlink_msg_heartbeat_get_status(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_heartbeat_LEN? msg->len : MAVLINK_MSG_ID_heartbeat_LEN;
        memset(heartbeat, 0, MAVLINK_MSG_ID_heartbeat_LEN);
    memcpy(heartbeat, _MAV_PAYLOAD(msg), len);
#endif
}
