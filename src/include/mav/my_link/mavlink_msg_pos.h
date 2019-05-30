#pragma once
// MESSAGE POS PACKING

#define MAVLINK_MSG_ID_POS 2

MAVPACKED(
typedef struct __mavlink_pos_t {
 float time; /*<   sec.ms*/
 float lat; /*<   ddmm.mmmm*/
 float lngt; /*<   dddmm.mmmm*/
 float alt; /*<   meter*/
 uint8_t mavlink_version; /*<  MAVLink version, not writable by user, gets added by protocol because of magic data type: uint8_t_mavlink_version*/
}) mavlink_pos_t;

#define MAVLINK_MSG_ID_POS_LEN 17
#define MAVLINK_MSG_ID_POS_MIN_LEN 17
#define MAVLINK_MSG_ID_2_LEN 17
#define MAVLINK_MSG_ID_2_MIN_LEN 17

#define MAVLINK_MSG_ID_POS_CRC 83
#define MAVLINK_MSG_ID_2_CRC 83



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_POS { \
    2, \
    "POS", \
    5, \
    {  { "time", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_pos_t, time) }, \
         { "lat", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_pos_t, lat) }, \
         { "lngt", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_pos_t, lngt) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_pos_t, alt) }, \
         { "mavlink_version", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_pos_t, mavlink_version) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_POS { \
    "POS", \
    5, \
    {  { "time", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_pos_t, time) }, \
         { "lat", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_pos_t, lat) }, \
         { "lngt", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_pos_t, lngt) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_pos_t, alt) }, \
         { "mavlink_version", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_pos_t, mavlink_version) }, \
         } \
}
#endif

/**
 * @brief Pack a pos message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time   sec.ms
 * @param lat   ddmm.mmmm
 * @param lngt   dddmm.mmmm
 * @param alt   meter
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_pos_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float time, float lat, float lngt, float alt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_POS_LEN];
    _mav_put_float(buf, 0, time);
    _mav_put_float(buf, 4, lat);
    _mav_put_float(buf, 8, lngt);
    _mav_put_float(buf, 12, alt);
    _mav_put_uint8_t(buf, 16, 3);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_POS_LEN);
#else
    mavlink_pos_t packet;
    packet.time = time;
    packet.lat = lat;
    packet.lngt = lngt;
    packet.alt = alt;
    packet.mavlink_version = 3;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_POS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_POS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_POS_MIN_LEN, MAVLINK_MSG_ID_POS_LEN, MAVLINK_MSG_ID_POS_CRC);
}

/**
 * @brief Pack a pos message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time   sec.ms
 * @param lat   ddmm.mmmm
 * @param lngt   dddmm.mmmm
 * @param alt   meter
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_pos_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float time,float lat,float lngt,float alt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_POS_LEN];
    _mav_put_float(buf, 0, time);
    _mav_put_float(buf, 4, lat);
    _mav_put_float(buf, 8, lngt);
    _mav_put_float(buf, 12, alt);
    _mav_put_uint8_t(buf, 16, 3);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_POS_LEN);
#else
    mavlink_pos_t packet;
    packet.time = time;
    packet.lat = lat;
    packet.lngt = lngt;
    packet.alt = alt;
    packet.mavlink_version = 3;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_POS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_POS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_POS_MIN_LEN, MAVLINK_MSG_ID_POS_LEN, MAVLINK_MSG_ID_POS_CRC);
}

/**
 * @brief Encode a pos struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param pos C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_pos_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_pos_t* pos)
{
    return mavlink_msg_pos_pack(system_id, component_id, msg, pos->time, pos->lat, pos->lngt, pos->alt);
}

/**
 * @brief Encode a pos struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param pos C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_pos_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_pos_t* pos)
{
    return mavlink_msg_pos_pack_chan(system_id, component_id, chan, msg, pos->time, pos->lat, pos->lngt, pos->alt);
}

/**
 * @brief Send a pos message
 * @param chan MAVLink channel to send the message
 *
 * @param time   sec.ms
 * @param lat   ddmm.mmmm
 * @param lngt   dddmm.mmmm
 * @param alt   meter
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_pos_send(mavlink_channel_t chan, float time, float lat, float lngt, float alt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_POS_LEN];
    _mav_put_float(buf, 0, time);
    _mav_put_float(buf, 4, lat);
    _mav_put_float(buf, 8, lngt);
    _mav_put_float(buf, 12, alt);
    _mav_put_uint8_t(buf, 16, 3);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POS, buf, MAVLINK_MSG_ID_POS_MIN_LEN, MAVLINK_MSG_ID_POS_LEN, MAVLINK_MSG_ID_POS_CRC);
#else
    mavlink_pos_t packet;
    packet.time = time;
    packet.lat = lat;
    packet.lngt = lngt;
    packet.alt = alt;
    packet.mavlink_version = 3;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POS, (const char *)&packet, MAVLINK_MSG_ID_POS_MIN_LEN, MAVLINK_MSG_ID_POS_LEN, MAVLINK_MSG_ID_POS_CRC);
#endif
}

/**
 * @brief Send a pos message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_pos_send_struct(mavlink_channel_t chan, const mavlink_pos_t* pos)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_pos_send(chan, pos->time, pos->lat, pos->lngt, pos->alt);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POS, (const char *)pos, MAVLINK_MSG_ID_POS_MIN_LEN, MAVLINK_MSG_ID_POS_LEN, MAVLINK_MSG_ID_POS_CRC);
#endif
}

#if MAVLINK_MSG_ID_POS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_pos_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float time, float lat, float lngt, float alt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, time);
    _mav_put_float(buf, 4, lat);
    _mav_put_float(buf, 8, lngt);
    _mav_put_float(buf, 12, alt);
    _mav_put_uint8_t(buf, 16, 3);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POS, buf, MAVLINK_MSG_ID_POS_MIN_LEN, MAVLINK_MSG_ID_POS_LEN, MAVLINK_MSG_ID_POS_CRC);
#else
    mavlink_pos_t *packet = (mavlink_pos_t *)msgbuf;
    packet->time = time;
    packet->lat = lat;
    packet->lngt = lngt;
    packet->alt = alt;
    packet->mavlink_version = 3;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POS, (const char *)packet, MAVLINK_MSG_ID_POS_MIN_LEN, MAVLINK_MSG_ID_POS_LEN, MAVLINK_MSG_ID_POS_CRC);
#endif
}
#endif

#endif

// MESSAGE POS UNPACKING


/**
 * @brief Get field time from pos message
 *
 * @return   sec.ms
 */
static inline float mavlink_msg_pos_get_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field lat from pos message
 *
 * @return   ddmm.mmmm
 */
static inline float mavlink_msg_pos_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field lngt from pos message
 *
 * @return   dddmm.mmmm
 */
static inline float mavlink_msg_pos_get_lngt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field alt from pos message
 *
 * @return   meter
 */
static inline float mavlink_msg_pos_get_alt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field mavlink_version from pos message
 *
 * @return  MAVLink version, not writable by user, gets added by protocol because of magic data type: uint8_t_mavlink_version
 */
static inline uint8_t mavlink_msg_pos_get_mavlink_version(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  16);
}

/**
 * @brief Decode a pos message into a struct
 *
 * @param msg The message to decode
 * @param pos C-struct to decode the message contents into
 */
static inline void mavlink_msg_pos_decode(const mavlink_message_t* msg, mavlink_pos_t* pos)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    pos->time = mavlink_msg_pos_get_time(msg);
    pos->lat = mavlink_msg_pos_get_lat(msg);
    pos->lngt = mavlink_msg_pos_get_lngt(msg);
    pos->alt = mavlink_msg_pos_get_alt(msg);
    pos->mavlink_version = mavlink_msg_pos_get_mavlink_version(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_POS_LEN? msg->len : MAVLINK_MSG_ID_POS_LEN;
        memset(pos, 0, MAVLINK_MSG_ID_POS_LEN);
    memcpy(pos, _MAV_PAYLOAD(msg), len);
#endif
}
