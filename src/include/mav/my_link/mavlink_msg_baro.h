#pragma once
// MESSAGE baro PACKING

#define MAVLINK_MSG_ID_baro 4

MAVPACKED(
typedef struct __mavlink_baro_t {
 float time; /*<   s.ms*/
 float pressure; /*<   pressure value*/
}) mavlink_baro_t;

#define MAVLINK_MSG_ID_baro_LEN 8
#define MAVLINK_MSG_ID_baro_MIN_LEN 8
#define MAVLINK_MSG_ID_4_LEN 8
#define MAVLINK_MSG_ID_4_MIN_LEN 8

#define MAVLINK_MSG_ID_baro_CRC 99
#define MAVLINK_MSG_ID_4_CRC 99



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_baro { \
    4, \
    "baro", \
    2, \
    {  { "time", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_baro_t, time) }, \
         { "pressure", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_baro_t, pressure) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_baro { \
    "baro", \
    2, \
    {  { "time", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_baro_t, time) }, \
         { "pressure", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_baro_t, pressure) }, \
         } \
}
#endif

/**
 * @brief Pack a baro message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time   s.ms
 * @param pressure   pressure value
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_baro_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float time, float pressure)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_baro_LEN];
    _mav_put_float(buf, 0, time);
    _mav_put_float(buf, 4, pressure);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_baro_LEN);
#else
    mavlink_baro_t packet;
    packet.time = time;
    packet.pressure = pressure;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_baro_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_baro;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_baro_MIN_LEN, MAVLINK_MSG_ID_baro_LEN, MAVLINK_MSG_ID_baro_CRC);
}

/**
 * @brief Pack a baro message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time   s.ms
 * @param pressure   pressure value
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_baro_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float time,float pressure)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_baro_LEN];
    _mav_put_float(buf, 0, time);
    _mav_put_float(buf, 4, pressure);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_baro_LEN);
#else
    mavlink_baro_t packet;
    packet.time = time;
    packet.pressure = pressure;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_baro_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_baro;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_baro_MIN_LEN, MAVLINK_MSG_ID_baro_LEN, MAVLINK_MSG_ID_baro_CRC);
}

/**
 * @brief Encode a baro struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param baro C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_baro_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_baro_t* baro)
{
    return mavlink_msg_baro_pack(system_id, component_id, msg, baro->time, baro->pressure);
}

/**
 * @brief Encode a baro struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param baro C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_baro_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_baro_t* baro)
{
    return mavlink_msg_baro_pack_chan(system_id, component_id, chan, msg, baro->time, baro->pressure);
}

/**
 * @brief Send a baro message
 * @param chan MAVLink channel to send the message
 *
 * @param time   s.ms
 * @param pressure   pressure value
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_baro_send(mavlink_channel_t chan, float time, float pressure)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_baro_LEN];
    _mav_put_float(buf, 0, time);
    _mav_put_float(buf, 4, pressure);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_baro, buf, MAVLINK_MSG_ID_baro_MIN_LEN, MAVLINK_MSG_ID_baro_LEN, MAVLINK_MSG_ID_baro_CRC);
#else
    mavlink_baro_t packet;
    packet.time = time;
    packet.pressure = pressure;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_baro, (const char *)&packet, MAVLINK_MSG_ID_baro_MIN_LEN, MAVLINK_MSG_ID_baro_LEN, MAVLINK_MSG_ID_baro_CRC);
#endif
}

/**
 * @brief Send a baro message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_baro_send_struct(mavlink_channel_t chan, const mavlink_baro_t* baro)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_baro_send(chan, baro->time, baro->pressure);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_baro, (const char *)baro, MAVLINK_MSG_ID_baro_MIN_LEN, MAVLINK_MSG_ID_baro_LEN, MAVLINK_MSG_ID_baro_CRC);
#endif
}

#if MAVLINK_MSG_ID_baro_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_baro_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float time, float pressure)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, time);
    _mav_put_float(buf, 4, pressure);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_baro, buf, MAVLINK_MSG_ID_baro_MIN_LEN, MAVLINK_MSG_ID_baro_LEN, MAVLINK_MSG_ID_baro_CRC);
#else
    mavlink_baro_t *packet = (mavlink_baro_t *)msgbuf;
    packet->time = time;
    packet->pressure = pressure;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_baro, (const char *)packet, MAVLINK_MSG_ID_baro_MIN_LEN, MAVLINK_MSG_ID_baro_LEN, MAVLINK_MSG_ID_baro_CRC);
#endif
}
#endif

#endif

// MESSAGE baro UNPACKING


/**
 * @brief Get field time from baro message
 *
 * @return   s.ms
 */
static inline float mavlink_msg_baro_get_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field pressure from baro message
 *
 * @return   pressure value
 */
static inline float mavlink_msg_baro_get_pressure(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Decode a baro message into a struct
 *
 * @param msg The message to decode
 * @param baro C-struct to decode the message contents into
 */
static inline void mavlink_msg_baro_decode(const mavlink_message_t* msg, mavlink_baro_t* baro)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    baro->time = mavlink_msg_baro_get_time(msg);
    baro->pressure = mavlink_msg_baro_get_pressure(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_baro_LEN? msg->len : MAVLINK_MSG_ID_baro_LEN;
        memset(baro, 0, MAVLINK_MSG_ID_baro_LEN);
    memcpy(baro, _MAV_PAYLOAD(msg), len);
#endif
}
