#pragma once
// MESSAGE gps PACKING

#define MAVLINK_MSG_ID_gps 1

MAVPACKED(
typedef struct __mavlink_gps_t {
 double unknown; /*<   to be determined*/
 uint64_t time; /*<   time of sent */
 uint8_t type; /*<  data type*/
 uint8_t mavlink_version; /*<  MAVLink version, not writable by user, gets added by protocol because of magic data type: uint8_t_mavlink_version*/
}) mavlink_gps_t;

#define MAVLINK_MSG_ID_gps_LEN 18
#define MAVLINK_MSG_ID_gps_MIN_LEN 18
#define MAVLINK_MSG_ID_1_LEN 18
#define MAVLINK_MSG_ID_1_MIN_LEN 18

#define MAVLINK_MSG_ID_gps_CRC 45
#define MAVLINK_MSG_ID_1_CRC 45



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_gps { \
    1, \
    "gps", \
    4, \
    {  { "type", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_gps_t, type) }, \
         { "unknown", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_gps_t, unknown) }, \
         { "time", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_gps_t, time) }, \
         { "mavlink_version", NULL, MAVLINK_TYPE_UINT8_T, 0, 17, offsetof(mavlink_gps_t, mavlink_version) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_gps { \
    "gps", \
    4, \
    {  { "type", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_gps_t, type) }, \
         { "unknown", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_gps_t, unknown) }, \
         { "time", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_gps_t, time) }, \
         { "mavlink_version", NULL, MAVLINK_TYPE_UINT8_T, 0, 17, offsetof(mavlink_gps_t, mavlink_version) }, \
         } \
}
#endif

/**
 * @brief Pack a gps message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param type  data type
 * @param unknown   to be determined
 * @param time   time of sent 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gps_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t type, double unknown, uint64_t time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_gps_LEN];
    _mav_put_double(buf, 0, unknown);
    _mav_put_uint64_t(buf, 8, time);
    _mav_put_uint8_t(buf, 16, type);
    _mav_put_uint8_t(buf, 17, 3);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_gps_LEN);
#else
    mavlink_gps_t packet;
    packet.unknown = unknown;
    packet.time = time;
    packet.type = type;
    packet.mavlink_version = 3;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_gps_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_gps;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_gps_MIN_LEN, MAVLINK_MSG_ID_gps_LEN, MAVLINK_MSG_ID_gps_CRC);
}

/**
 * @brief Pack a gps message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param type  data type
 * @param unknown   to be determined
 * @param time   time of sent 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gps_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t type,double unknown,uint64_t time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_gps_LEN];
    _mav_put_double(buf, 0, unknown);
    _mav_put_uint64_t(buf, 8, time);
    _mav_put_uint8_t(buf, 16, type);
    _mav_put_uint8_t(buf, 17, 3);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_gps_LEN);
#else
    mavlink_gps_t packet;
    packet.unknown = unknown;
    packet.time = time;
    packet.type = type;
    packet.mavlink_version = 3;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_gps_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_gps;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_gps_MIN_LEN, MAVLINK_MSG_ID_gps_LEN, MAVLINK_MSG_ID_gps_CRC);
}

/**
 * @brief Encode a gps struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param gps C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gps_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_gps_t* gps)
{
    return mavlink_msg_gps_pack(system_id, component_id, msg, gps->type, gps->unknown, gps->time);
}

/**
 * @brief Encode a gps struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param gps C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gps_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_gps_t* gps)
{
    return mavlink_msg_gps_pack_chan(system_id, component_id, chan, msg, gps->type, gps->unknown, gps->time);
}

/**
 * @brief Send a gps message
 * @param chan MAVLink channel to send the message
 *
 * @param type  data type
 * @param unknown   to be determined
 * @param time   time of sent 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_gps_send(mavlink_channel_t chan, uint8_t type, double unknown, uint64_t time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_gps_LEN];
    _mav_put_double(buf, 0, unknown);
    _mav_put_uint64_t(buf, 8, time);
    _mav_put_uint8_t(buf, 16, type);
    _mav_put_uint8_t(buf, 17, 3);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_gps, buf, MAVLINK_MSG_ID_gps_MIN_LEN, MAVLINK_MSG_ID_gps_LEN, MAVLINK_MSG_ID_gps_CRC);
#else
    mavlink_gps_t packet;
    packet.unknown = unknown;
    packet.time = time;
    packet.type = type;
    packet.mavlink_version = 3;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_gps, (const char *)&packet, MAVLINK_MSG_ID_gps_MIN_LEN, MAVLINK_MSG_ID_gps_LEN, MAVLINK_MSG_ID_gps_CRC);
#endif
}

/**
 * @brief Send a gps message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_gps_send_struct(mavlink_channel_t chan, const mavlink_gps_t* gps)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_gps_send(chan, gps->type, gps->unknown, gps->time);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_gps, (const char *)gps, MAVLINK_MSG_ID_gps_MIN_LEN, MAVLINK_MSG_ID_gps_LEN, MAVLINK_MSG_ID_gps_CRC);
#endif
}

#if MAVLINK_MSG_ID_gps_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_gps_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t type, double unknown, uint64_t time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_double(buf, 0, unknown);
    _mav_put_uint64_t(buf, 8, time);
    _mav_put_uint8_t(buf, 16, type);
    _mav_put_uint8_t(buf, 17, 3);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_gps, buf, MAVLINK_MSG_ID_gps_MIN_LEN, MAVLINK_MSG_ID_gps_LEN, MAVLINK_MSG_ID_gps_CRC);
#else
    mavlink_gps_t *packet = (mavlink_gps_t *)msgbuf;
    packet->unknown = unknown;
    packet->time = time;
    packet->type = type;
    packet->mavlink_version = 3;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_gps, (const char *)packet, MAVLINK_MSG_ID_gps_MIN_LEN, MAVLINK_MSG_ID_gps_LEN, MAVLINK_MSG_ID_gps_CRC);
#endif
}
#endif

#endif

// MESSAGE gps UNPACKING


/**
 * @brief Get field type from gps message
 *
 * @return  data type
 */
static inline uint8_t mavlink_msg_gps_get_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  16);
}

/**
 * @brief Get field unknown from gps message
 *
 * @return   to be determined
 */
static inline double mavlink_msg_gps_get_unknown(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  0);
}

/**
 * @brief Get field time from gps message
 *
 * @return   time of sent 
 */
static inline uint64_t mavlink_msg_gps_get_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  8);
}

/**
 * @brief Get field mavlink_version from gps message
 *
 * @return  MAVLink version, not writable by user, gets added by protocol because of magic data type: uint8_t_mavlink_version
 */
static inline uint8_t mavlink_msg_gps_get_mavlink_version(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  17);
}

/**
 * @brief Decode a gps message into a struct
 *
 * @param msg The message to decode
 * @param gps C-struct to decode the message contents into
 */
static inline void mavlink_msg_gps_decode(const mavlink_message_t* msg, mavlink_gps_t* gps)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    gps->unknown = mavlink_msg_gps_get_unknown(msg);
    gps->time = mavlink_msg_gps_get_time(msg);
    gps->type = mavlink_msg_gps_get_type(msg);
    gps->mavlink_version = mavlink_msg_gps_get_mavlink_version(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_gps_LEN? msg->len : MAVLINK_MSG_ID_gps_LEN;
        memset(gps, 0, MAVLINK_MSG_ID_gps_LEN);
    memcpy(gps, _MAV_PAYLOAD(msg), len);
#endif
}
