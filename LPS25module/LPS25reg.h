#define LPS25H_REF_P_XL       0x08
#define LPS25H_REF_P_L        0x09
#define LPS25H_REF_P_H        0x0A

#define LPS25H_WHO_AM_I       0x0F

#define LPS25H_RES_CONF       0x10

#define LPS25H_CTRL_REG1      0x20
#define LPS25H_CTRL_REG2      0x21
#define LPS25H_CTRL_REG3      0x22
#define LPS25H_CTRL_REG4      0x23
#define LPS25H_INTERRUPT_CFG  0x24
#define LPS25H_INT_SOURCE     0x25
#define LPS25H_STATUS_REG     0x27

#define LPS25H_PRESS_OUT_XL   0x28
#define LPS25H_PRESS_OUT_L    0x29
#define LPS25H_PRESS_OUT_H    0x2A

#define LPS25H_TEMP_OUT_L     0x2B
#define LPS25H_TEMP_OUT_H     0x2C

#define LPS25H_FIFO_CTRL      0x2E
#define LPS25H_FIFO_STATUS    0x2F
#define LPS25H_THS_P_L        0x30
#define LPS25H_THS_P_H        0x31
#define LPS25H_RPDS_L         0x39
#define LPS25H_RPDS_H         0x3A

/* CUSTOM VALUES FOR LPS25H SENSOR */
#define LPS25H_WAI_ID             0xBD
#define LPS25H_ODR_ADDR           0x20
#define LPS25H_ODR_MASK           0x70
#define LPS25H_ODR_AVL_1HZ_VAL    0x01
#define LPS25H_ODR_AVL_7HZ_VAL    0x02
#define LPS25H_ODR_AVL_13HZ_VAL   0x03
#define LPS25H_ODR_AVL_25HZ_VAL   0x04
#define LPS25H_PW_ADDR            0x20
#define LPS25H_PW_MASK            0x80
#define LPS25H_FS_ADDR            0x00
#define LPS25H_FS_MASK            0x00
#define LPS25H_FS_AVL_1260_VAL    0x00
#define LPS25H_FS_AVL_1260_GAIN   KPASCAL_NANO_SCALE
#define LPS25H_FS_AVL_TEMP_GAIN   CELSIUS_NANO_SCALE
#define LPS25H_BDU_ADDR           0x20
#define LPS25H_BDU_MASK           0x04
#define LPS25H_DRDY_IRQ_ADDR      0x23
#define LPS25H_DRDY_IRQ_INT1_MASK 0x01
#define LPS25H_DRDY_IRQ_INT2_MASK 0x10
#define LPS25H_MULTIREAD_BIT      true
#define LPS25H_TEMP_OFFSET        (float)(42.5f)
#define LPS25H_OUT_XL_ADDR        0x28
#define LPS25H_TEMP_OUT_L_ADDR    0x2B

// Self test parameters. Only checks that values are sane
#define LPS25H_ST_PRESS_MAX   (1100.0f) //mbar
#define LPS25H_ST_PRESS_MIN   (450.0f)  //mbar
#define LPS25H_ST_TEMP_MAX    (80.0f)   //degree celcius
#define LPS25H_ST_TEMP_MIN    (-20.0f)  //degree celcius
