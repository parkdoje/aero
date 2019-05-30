#pragma once
// MESSAGE NAV PACKING

#define MAVLINK_MSG_ID_NAV 3

MAVPACKED(
typedef struct __mavlink_nav_t {
 float time; /*<   sec.ms*/
 float lat; /*<   ddmm.mmmm*/
 float lngt; /*<   dddmm.mmmm*/
 float speed; /*<   knots*/
 float heading; /*<   degree*/
 uint8_t mavlink_version; /*<  MAVLink version, not writable by user, gets added by protocol because of magic data type: uint8_t_mavlink_version*/
}) mavlink_nav_t;

#define MAVLINK_MSG_ID_NAV_LEN 21
#define MAVLINK_MSG_ID_NAV_MIN_LEN 21
#define MAVLINK_MSG_ID_3_LEN 21
#define MAVLINK_MSG_ID_3_MIN_LEN 21

#define MAVLINK_MSG_ID_NAV_CRC 32
#define MAVLINK_MSG_ID_3_CRC 32



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_NAV { \
    3, \
    "NAV", \
    6, \
    {  { "time", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_nav_t, time) }, \
         { "lat", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_nav_t, lat) }, \
         { "lngt", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_nav_t, lngt) }, \
         { "speed", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_nav_t, speed) }, \
         { "heading", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_nav_t, heading) }, \
         { "mavlink_version", NULL, MAVLINK_TYPE_UINT8_T, 0, 20, offsetof(mavlink_nav_t, mavlink_version) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_NAV { \
    "NAV", \
    6, \
    {  { "time", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_nav_t, time) }, \
         { "lat", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_nav_t, lat) }, \
         { "lngt", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_nav_t, lngt) }, \
         { "speed", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_nav_t, speed) }, \
         { "heading", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_nav_t, heading) }, \
         { "mavlink_version", NULL, MAVLINK_TYPE_UINT8_T, 0, 20, offsetof(mavlink_nav_t, mavlink_version) }, \
         } \
}
#endif

/**
 * @brief Pack a nav message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time   sec.ms
 * @param lat   ddmm.mmmm
 * @param lngt   dddmm.mmmm
 * @param speed   knots
 * @param heading   degree
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_nav_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float time, float lat, float lngt, float speed, float heading)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_NAV_LEN];
    _mav_put_float(buf, 0, time);
    _mav_put_float(buf, 4, lat);
    _mav_put_float(buf, 8, lngt);
    _mav_put_float(buf, 12, speed);
    _mav_put_float(buf, 16, heading);
    _mav_put_uint8_t(buf, 20, 3);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_NAV_LEN);
#else
    mavlink_nav_t packet;
    packet.time = time;
    packet.lat = lat;
    packet.lngt = lngt;
    packet.speed = speed;
    packet.heading = heading;
    packet.mavlink_version = 3;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_NAV_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_NAV;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_NAV_MIN_LEN, MAVLINK_MSG_ID_NAV_LEN, MAVLINK_MSG_ID_NAV_CRC);
}

/**
 * @brief Pack a nav message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time   sec.ms
 * @param lat   ddmm.mmmm
 * @param lngt   dddmm.mmmm
 * @param speed   knots
 * @param heading   degree
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_nav_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float time,float lat,float lngt,float speed,float heading)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_NAV_LEN];
    _mav_put_float(buf, 0, time);
    _mav_put_float(buf, 4, lat);
    _mav_put_float(buf, 8, lngt);
    _mav_put_float(buf, 12, speed);
    _mav_put_float(buf, 16, heading);
    _mav_put_uint8_t(buf, 20, 3);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_NAV_LEN);
#else
    mavlink_nav_t packet;
    packet.time = time;
    packet.lat = lat;
    packet.lngt = lngt;
    packet.speed = speed;
    packet.heading = heading;
    packet.mavlink_version = 3;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_NAV_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_NAV;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_NAV_MIN_LEN, MAVLINK_MSG_ID_NAV_LEN, MAVLINK_MSG_ID_NAV_CRC);
}

/**
 * @brief Encode a nav struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param nav C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_nav_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_nav_t* nav)
{
    return mavlink_msg_nav_pack(system_id, component_id, msg, nav->time, nav->lat, nav->lngt, nav->speed, nav->heading);
}

/**
 * @brief Encode a nav struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param nav C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_nav_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_nav_t* nav)
{
    return mavlink_msg_nav_pack_chan(system_id, component_id, chan, msg, nav->time, nav->lat, nav->lngt, nav->speed, nav->heading);
}

/**
 * @brief Send a nav message
 * @param chan MAVLink channel to send the message
 *
 * @param time   sec.ms
 * @param lat   ddmm.mmmm
 * @param lngt   dddmm.mmmm
 * @param speed   knots
 * @param heading   degree
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_nav_send(mavlink_channel_t chan, float time, float lat, float lngt, float speed, float heading)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_NAV_LEN];
    _mav_put_float(buf, 0, time);
    _mav_put_float(buf, 4, lat);
    _mav_put_float(buf, 8, lngt);
    _mav_put_float(buf, 12, speed);
    _mav_put_float(buf, 16, heading);
    _mav_put_uint8_t(buf, 20, 3);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NAV, buf, MAVLINK_MSG_ID_NAV_MIN_LEN, MAVLINK_MSG_ID_NAV_LEN, MAVLINK_MSG_ID_NAV_CRC);
#else
    mavlink_nav_t packet;
    packet.time = time;
    packet.lat = lat;
    packet.lngt = lngt;
    packet.speed = speed;
    packet.heading = heading;
    packet.mavlink_version = 3;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NAV, (const char *)&packet, MAVLINK_MSG_ID_NAV_MIN_LEN, MAVLINK_MSG_ID_NAV_LEN, MAVLINK_MSG_ID_NAV_CRC);
#endif
}

/**
 * @brief Send a nav message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_nav_send_struct(mavlink_channel_t chan, const mavlink_nav_t* nav)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_nav_send(chan, nav->time, nav->lat, nav->lngt, nav->speed, nav->heading);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NAV, (const char *)nav, MAVLINK_MSG_ID_NAV_MIN_LEN, MAVLINK_MSG_ID_NAV_LEN, MAVLINK_MSG_ID_NAV_CRC);
#endif
}

#if MAVLINK_MSG_ID_NAV_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_nav_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float time, float lat, float lngt, float speed, float heading)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, time);
    _mav_put_float(buf, 4, lat);
    _mav_put_float(buf, 8, lngt);
    _mav_put_float(buf, 12, speed);
    _mav_put_float(buf, 16, heading);
    _mav_put_uint8_t(buf, 20, 3);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NAV, buf, MAVLINK_MSG_ID_NAV_MIN_LEN, MAVLINK_MSG_ID_NAV_LEN, MAVLINK_MSG_ID_NAV_CRC);
#else
    mavlink_nav_t *packet = (mavlink_nav_t *)msgbuf;
    packet->time = time;
    packet->lat = lat;
    packet->lngt = lngt;
    packet->speed = speed;
    packet->heading = heading;
    packet->mavlink_version = 3;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NAV, (const char *)packet, MAVLINK_MSG_ID_NAV_MIN_LEN, MAVLINK_MSG_ID_NAV_LEN, MAVLINK_MSG_ID_NAV_CRC);
#endif
}
#endif

#endif

// MESSAGE NAV UNPACKING


/**
 * @brief Get field time from nav message
 *
 * @return   sec.ms
 */
static inline float mavlink_msg_nav_get_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field lat from nav message
 *
 * @return   ddmm.mmmm
 */
static inline float mavlink_msg_nav_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field lngt from nav message
 *
 * @return   dddmm.mmmm
 */
static inline float mavlink_msg_nav_get_lngt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field speed from nav message
 *
 * @return   knots
 */
static inline float mavlink_msg_nav_get_speed(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field heading from nav message
 *
 * @return   degree
 */
static inline float mavlink_msg_nav_get_heading(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field mavlink_version from nav message
 *
 * @return  MAVLink version, not writable by user, gets added by protocol because of magic data type: uint8_t_mavlink_version
 */
static inline uint8_t mavlink_msg_nav_get_mavlink_version(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  20);
}

/**
 * @brief Decode a nav message into a struct
 *
 * @param msg The message to decode
 * @param nav C-struct to decode the message contents into
 */
static inline void mavlink_msg_nav_decode(const mavlink_message_t* msg, mavlink_nav_t* nav)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    nav->time = mavlink_msg_nav_get_time(msg);
    nav->lat = mavlink_msg_nav_get_lat(msg);
    nav->lngt = mavlink_msg_nav_get_lngt(msg);
    nav->speed = mavlink_msg_nav_get_speed(msg);
    nav->heading = mavlink_msg_nav_get_heading(msg);
    nav->mavlink_version = mavlink_msg_nav_get_mavlink_version(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_NAV_LEN? msg->len : MAVLINK_MSG_ID_NAV_LEN;
        memset(nav, 0, MAVLINK_MSG_ID_NAV_LEN);
    memcpy(nav, _MAV_PAYLOAD(msg), len);
#endif
}
