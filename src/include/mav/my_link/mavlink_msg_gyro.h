#pragma once
// MESSAGE gyro PACKING

#define MAVLINK_MSG_ID_gyro 1

MAVPACKED(
typedef struct __mavlink_gyro_t {
 float time; /*<   sec.ms*/
 float x; /*<  x*/
 float y; /*<  y*/
 float z; /*<  z*/
 uint8_t mavlink_version; /*<  MAVLink version, not writable by user, gets added by protocol because of magic data type: uint8_t_mavlink_version*/
}) mavlink_gyro_t;

#define MAVLINK_MSG_ID_gyro_LEN 17
#define MAVLINK_MSG_ID_gyro_MIN_LEN 17
#define MAVLINK_MSG_ID_1_LEN 17
#define MAVLINK_MSG_ID_1_MIN_LEN 17

#define MAVLINK_MSG_ID_gyro_CRC 97
#define MAVLINK_MSG_ID_1_CRC 97



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_gyro { \
    1, \
    "gyro", \
    5, \
    {  { "time", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_gyro_t, time) }, \
         { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_gyro_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_gyro_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_gyro_t, z) }, \
         { "mavlink_version", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_gyro_t, mavlink_version) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_gyro { \
    "gyro", \
    5, \
    {  { "time", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_gyro_t, time) }, \
         { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_gyro_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_gyro_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_gyro_t, z) }, \
         { "mavlink_version", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_gyro_t, mavlink_version) }, \
         } \
}
#endif

/**
 * @brief Pack a gyro message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time   sec.ms
 * @param x  x
 * @param y  y
 * @param z  z
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gyro_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float time, float x, float y, float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_gyro_LEN];
    _mav_put_float(buf, 0, time);
    _mav_put_float(buf, 4, x);
    _mav_put_float(buf, 8, y);
    _mav_put_float(buf, 12, z);
    _mav_put_uint8_t(buf, 16, 3);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_gyro_LEN);
#else
    mavlink_gyro_t packet;
    packet.time = time;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.mavlink_version = 3;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_gyro_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_gyro;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_gyro_MIN_LEN, MAVLINK_MSG_ID_gyro_LEN, MAVLINK_MSG_ID_gyro_CRC);
}

/**
 * @brief Pack a gyro message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time   sec.ms
 * @param x  x
 * @param y  y
 * @param z  z
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gyro_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float time,float x,float y,float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_gyro_LEN];
    _mav_put_float(buf, 0, time);
    _mav_put_float(buf, 4, x);
    _mav_put_float(buf, 8, y);
    _mav_put_float(buf, 12, z);
    _mav_put_uint8_t(buf, 16, 3);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_gyro_LEN);
#else
    mavlink_gyro_t packet;
    packet.time = time;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.mavlink_version = 3;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_gyro_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_gyro;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_gyro_MIN_LEN, MAVLINK_MSG_ID_gyro_LEN, MAVLINK_MSG_ID_gyro_CRC);
}

/**
 * @brief Encode a gyro struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param gyro C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gyro_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_gyro_t* gyro)
{
    return mavlink_msg_gyro_pack(system_id, component_id, msg, gyro->time, gyro->x, gyro->y, gyro->z);
}

/**
 * @brief Encode a gyro struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param gyro C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gyro_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_gyro_t* gyro)
{
    return mavlink_msg_gyro_pack_chan(system_id, component_id, chan, msg, gyro->time, gyro->x, gyro->y, gyro->z);
}

/**
 * @brief Send a gyro message
 * @param chan MAVLink channel to send the message
 *
 * @param time   sec.ms
 * @param x  x
 * @param y  y
 * @param z  z
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_gyro_send(mavlink_channel_t chan, float time, float x, float y, float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_gyro_LEN];
    _mav_put_float(buf, 0, time);
    _mav_put_float(buf, 4, x);
    _mav_put_float(buf, 8, y);
    _mav_put_float(buf, 12, z);
    _mav_put_uint8_t(buf, 16, 3);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_gyro, buf, MAVLINK_MSG_ID_gyro_MIN_LEN, MAVLINK_MSG_ID_gyro_LEN, MAVLINK_MSG_ID_gyro_CRC);
#else
    mavlink_gyro_t packet;
    packet.time = time;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.mavlink_version = 3;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_gyro, (const char *)&packet, MAVLINK_MSG_ID_gyro_MIN_LEN, MAVLINK_MSG_ID_gyro_LEN, MAVLINK_MSG_ID_gyro_CRC);
#endif
}

/**
 * @brief Send a gyro message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_gyro_send_struct(mavlink_channel_t chan, const mavlink_gyro_t* gyro)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_gyro_send(chan, gyro->time, gyro->x, gyro->y, gyro->z);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_gyro, (const char *)gyro, MAVLINK_MSG_ID_gyro_MIN_LEN, MAVLINK_MSG_ID_gyro_LEN, MAVLINK_MSG_ID_gyro_CRC);
#endif
}

#if MAVLINK_MSG_ID_gyro_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_gyro_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float time, float x, float y, float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, time);
    _mav_put_float(buf, 4, x);
    _mav_put_float(buf, 8, y);
    _mav_put_float(buf, 12, z);
    _mav_put_uint8_t(buf, 16, 3);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_gyro, buf, MAVLINK_MSG_ID_gyro_MIN_LEN, MAVLINK_MSG_ID_gyro_LEN, MAVLINK_MSG_ID_gyro_CRC);
#else
    mavlink_gyro_t *packet = (mavlink_gyro_t *)msgbuf;
    packet->time = time;
    packet->x = x;
    packet->y = y;
    packet->z = z;
    packet->mavlink_version = 3;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_gyro, (const char *)packet, MAVLINK_MSG_ID_gyro_MIN_LEN, MAVLINK_MSG_ID_gyro_LEN, MAVLINK_MSG_ID_gyro_CRC);
#endif
}
#endif

#endif

// MESSAGE gyro UNPACKING


/**
 * @brief Get field time from gyro message
 *
 * @return   sec.ms
 */
static inline float mavlink_msg_gyro_get_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field x from gyro message
 *
 * @return  x
 */
static inline float mavlink_msg_gyro_get_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field y from gyro message
 *
 * @return  y
 */
static inline float mavlink_msg_gyro_get_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field z from gyro message
 *
 * @return  z
 */
static inline float mavlink_msg_gyro_get_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field mavlink_version from gyro message
 *
 * @return  MAVLink version, not writable by user, gets added by protocol because of magic data type: uint8_t_mavlink_version
 */
static inline uint8_t mavlink_msg_gyro_get_mavlink_version(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  16);
}

/**
 * @brief Decode a gyro message into a struct
 *
 * @param msg The message to decode
 * @param gyro C-struct to decode the message contents into
 */
static inline void mavlink_msg_gyro_decode(const mavlink_message_t* msg, mavlink_gyro_t* gyro)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    gyro->time = mavlink_msg_gyro_get_time(msg);
    gyro->x = mavlink_msg_gyro_get_x(msg);
    gyro->y = mavlink_msg_gyro_get_y(msg);
    gyro->z = mavlink_msg_gyro_get_z(msg);
    gyro->mavlink_version = mavlink_msg_gyro_get_mavlink_version(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_gyro_LEN? msg->len : MAVLINK_MSG_ID_gyro_LEN;
        memset(gyro, 0, MAVLINK_MSG_ID_gyro_LEN);
    memcpy(gyro, _MAV_PAYLOAD(msg), len);
#endif
}
