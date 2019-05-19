#pragma once
// MESSAGE imu PACKING

#define MAVLINK_MSG_ID_imu 0

MAVPACKED(
typedef struct __mavlink_imu_t {
 uint64_t time; /*<   time of sent */
 float x; /*<  x*/
 float y; /*<  y*/
 float z; /*<  z*/
 uint8_t type; /*<  data type*/
 uint8_t mavlink_version; /*<  MAVLink version, not writable by user, gets added by protocol because of magic data type: uint8_t_mavlink_version*/
}) mavlink_imu_t;

#define MAVLINK_MSG_ID_imu_LEN 22
#define MAVLINK_MSG_ID_imu_MIN_LEN 22
#define MAVLINK_MSG_ID_0_LEN 22
#define MAVLINK_MSG_ID_0_MIN_LEN 22

#define MAVLINK_MSG_ID_imu_CRC 40
#define MAVLINK_MSG_ID_0_CRC 40



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_imu { \
    0, \
    "imu", \
    6, \
    {  { "type", NULL, MAVLINK_TYPE_UINT8_T, 0, 20, offsetof(mavlink_imu_t, type) }, \
         { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_imu_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_imu_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_imu_t, z) }, \
         { "time", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_imu_t, time) }, \
         { "mavlink_version", NULL, MAVLINK_TYPE_UINT8_T, 0, 21, offsetof(mavlink_imu_t, mavlink_version) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_imu { \
    "imu", \
    6, \
    {  { "type", NULL, MAVLINK_TYPE_UINT8_T, 0, 20, offsetof(mavlink_imu_t, type) }, \
         { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_imu_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_imu_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_imu_t, z) }, \
         { "time", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_imu_t, time) }, \
         { "mavlink_version", NULL, MAVLINK_TYPE_UINT8_T, 0, 21, offsetof(mavlink_imu_t, mavlink_version) }, \
         } \
}
#endif

/**
 * @brief Pack a imu message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param type  data type
 * @param x  x
 * @param y  y
 * @param z  z
 * @param time   time of sent 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_imu_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t type, float x, float y, float z, uint64_t time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_imu_LEN];
    _mav_put_uint64_t(buf, 0, time);
    _mav_put_float(buf, 8, x);
    _mav_put_float(buf, 12, y);
    _mav_put_float(buf, 16, z);
    _mav_put_uint8_t(buf, 20, type);
    _mav_put_uint8_t(buf, 21, 3);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_imu_LEN);
#else
    mavlink_imu_t packet;
    packet.time = time;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.type = type;
    packet.mavlink_version = 3;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_imu_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_imu;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_imu_MIN_LEN, MAVLINK_MSG_ID_imu_LEN, MAVLINK_MSG_ID_imu_CRC);
}

/**
 * @brief Pack a imu message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param type  data type
 * @param x  x
 * @param y  y
 * @param z  z
 * @param time   time of sent 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_imu_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t type,float x,float y,float z,uint64_t time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_imu_LEN];
    _mav_put_uint64_t(buf, 0, time);
    _mav_put_float(buf, 8, x);
    _mav_put_float(buf, 12, y);
    _mav_put_float(buf, 16, z);
    _mav_put_uint8_t(buf, 20, type);
    _mav_put_uint8_t(buf, 21, 3);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_imu_LEN);
#else
    mavlink_imu_t packet;
    packet.time = time;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.type = type;
    packet.mavlink_version = 3;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_imu_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_imu;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_imu_MIN_LEN, MAVLINK_MSG_ID_imu_LEN, MAVLINK_MSG_ID_imu_CRC);
}

/**
 * @brief Encode a imu struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param imu C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_imu_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_imu_t* imu)
{
    return mavlink_msg_imu_pack(system_id, component_id, msg, imu->type, imu->x, imu->y, imu->z, imu->time);
}

/**
 * @brief Encode a imu struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param imu C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_imu_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_imu_t* imu)
{
    return mavlink_msg_imu_pack_chan(system_id, component_id, chan, msg, imu->type, imu->x, imu->y, imu->z, imu->time);
}

/**
 * @brief Send a imu message
 * @param chan MAVLink channel to send the message
 *
 * @param type  data type
 * @param x  x
 * @param y  y
 * @param z  z
 * @param time   time of sent 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_imu_send(mavlink_channel_t chan, uint8_t type, float x, float y, float z, uint64_t time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_imu_LEN];
    _mav_put_uint64_t(buf, 0, time);
    _mav_put_float(buf, 8, x);
    _mav_put_float(buf, 12, y);
    _mav_put_float(buf, 16, z);
    _mav_put_uint8_t(buf, 20, type);
    _mav_put_uint8_t(buf, 21, 3);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_imu, buf, MAVLINK_MSG_ID_imu_MIN_LEN, MAVLINK_MSG_ID_imu_LEN, MAVLINK_MSG_ID_imu_CRC);
#else
    mavlink_imu_t packet;
    packet.time = time;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.type = type;
    packet.mavlink_version = 3;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_imu, (const char *)&packet, MAVLINK_MSG_ID_imu_MIN_LEN, MAVLINK_MSG_ID_imu_LEN, MAVLINK_MSG_ID_imu_CRC);
#endif
}

/**
 * @brief Send a imu message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_imu_send_struct(mavlink_channel_t chan, const mavlink_imu_t* imu)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_imu_send(chan, imu->type, imu->x, imu->y, imu->z, imu->time);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_imu, (const char *)imu, MAVLINK_MSG_ID_imu_MIN_LEN, MAVLINK_MSG_ID_imu_LEN, MAVLINK_MSG_ID_imu_CRC);
#endif
}

#if MAVLINK_MSG_ID_imu_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_imu_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t type, float x, float y, float z, uint64_t time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time);
    _mav_put_float(buf, 8, x);
    _mav_put_float(buf, 12, y);
    _mav_put_float(buf, 16, z);
    _mav_put_uint8_t(buf, 20, type);
    _mav_put_uint8_t(buf, 21, 3);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_imu, buf, MAVLINK_MSG_ID_imu_MIN_LEN, MAVLINK_MSG_ID_imu_LEN, MAVLINK_MSG_ID_imu_CRC);
#else
    mavlink_imu_t *packet = (mavlink_imu_t *)msgbuf;
    packet->time = time;
    packet->x = x;
    packet->y = y;
    packet->z = z;
    packet->type = type;
    packet->mavlink_version = 3;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_imu, (const char *)packet, MAVLINK_MSG_ID_imu_MIN_LEN, MAVLINK_MSG_ID_imu_LEN, MAVLINK_MSG_ID_imu_CRC);
#endif
}
#endif

#endif

// MESSAGE imu UNPACKING


/**
 * @brief Get field type from imu message
 *
 * @return  data type
 */
static inline uint8_t mavlink_msg_imu_get_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  20);
}

/**
 * @brief Get field x from imu message
 *
 * @return  x
 */
static inline float mavlink_msg_imu_get_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field y from imu message
 *
 * @return  y
 */
static inline float mavlink_msg_imu_get_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field z from imu message
 *
 * @return  z
 */
static inline float mavlink_msg_imu_get_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field time from imu message
 *
 * @return   time of sent 
 */
static inline uint64_t mavlink_msg_imu_get_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field mavlink_version from imu message
 *
 * @return  MAVLink version, not writable by user, gets added by protocol because of magic data type: uint8_t_mavlink_version
 */
static inline uint8_t mavlink_msg_imu_get_mavlink_version(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  21);
}

/**
 * @brief Decode a imu message into a struct
 *
 * @param msg The message to decode
 * @param imu C-struct to decode the message contents into
 */
static inline void mavlink_msg_imu_decode(const mavlink_message_t* msg, mavlink_imu_t* imu)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    imu->time = mavlink_msg_imu_get_time(msg);
    imu->x = mavlink_msg_imu_get_x(msg);
    imu->y = mavlink_msg_imu_get_y(msg);
    imu->z = mavlink_msg_imu_get_z(msg);
    imu->type = mavlink_msg_imu_get_type(msg);
    imu->mavlink_version = mavlink_msg_imu_get_mavlink_version(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_imu_LEN? msg->len : MAVLINK_MSG_ID_imu_LEN;
        memset(imu, 0, MAVLINK_MSG_ID_imu_LEN);
    memcpy(imu, _MAV_PAYLOAD(msg), len);
#endif
}
